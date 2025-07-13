#include <iostream>
#include <unordered_map>
#include <string>

class TreeNode {
public:
    int value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
public:
    static void inorderTraversal(TreeNode *root) {
        if (root == nullptr) return;
        inorderTraversal(root->left);
        std::cout << root->value << " ";
        inorderTraversal(root->right);
    }

    static std::string serialize(TreeNode *root, std::unordered_map<std::string, int> &map, bool &found) {
        if (!root) return "#";

        std::string left = serialize(root->left, map, found);
        std::string right = serialize(root->right, map, found);

        std::string s = std::to_string(root->value) + "," + left + "," + right;

        if (left != "#" || right != "#") {
            if (++map[s] == 2) found = true;
        }

        return s;
    }

    static bool hasDuplicateSubtree(TreeNode *root) {
        std::unordered_map<std::string, int> map;
        bool found = false;
        serialize(root, map, found);
        return found;
    }
};

int main() {
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    std::cout << "Inorder Traversal: ";
    BinaryTree::inorderTraversal(root);
    std::cout << "\n";

    if (BinaryTree::hasDuplicateSubtree(root)) {
        std::cout << "Duplicate subtree found.\n";
    } else {
        std::cout << "No duplicate subtree.\n";
    }

    return 0;
}
