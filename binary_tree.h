#include <iostream>

template <typename T>
class TreeNode
{
public:
    T value;
    TreeNode<int>* left;
    TreeNode<int>* right;

    TreeNode(T _value) : value(_value)
    {
        left = nullptr;
        right = nullptr;
    }

    TreeNode(T _value, TreeNode<T>* _left, TreeNode<T>* _right) :
            value(_value)
    {
        left = _left;
        right = _right;
    }
};

template <typename T>
class BinaryTree
{
private:
    TreeNode<T>* root;

    // Preorder traversal
    void copyTree(TreeNode<T>* thisNode, TreeNode<T>* otherNode)
    {
        if (otherNode == nullptr) return;
        thisNode = new TreeNode<T>(otherNode->value);
        copyTree(otherNode->left);
        copyTree(otherNode->right);
    }

    // Postorder traversal
    void deleteTree(TreeNode<T>* node)
    {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    // Inorder traversal
    void printTree(TreeNode<T>* node) const
    {
        if (node == nullptr) return;
        printTree(node->left);
        std::cout << node->value << " ";
        printTree(node->right);
    }

public:
    BinaryTree(T _value)
    {
        root = new TreeNode<T>(_value);
    }

    BinaryTree(TreeNode<T> _root)
    {
        root = new TreeNode<T>(_root);
    }

    // Copy constructor
    BinaryTree(const BinaryTree<T>& other)
    {
        copyTree(root, other.root);
    }

    // Copy operator
    BinaryTree<T>& operator= (const BinaryTree<T>& other)
    {
        if (is_empty()) {
            copyTree(root, other.root);
        } else {
            deleteTree(root);
            copyTree(root, other.root);
        }
        return *this;
    }

    bool is_empty() const 
    {
        return (root->left == nullptr && root->right == nullptr);
    }

    // Destructor
    virtual ~BinaryTree()
    {
        deleteTree(root);
    }

    void print() const
    {
        printTree(root);
        std::cout << std::endl;
    }

    T is_contained(T _value) const
    {
        TreeNode<T>* temp = root;
        while (temp) {
            if (temp->value == _value){
                break;
            } else if (temp->value > _value) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        return (temp != nullptr);
    }

    void insert(T _value)
    {
        TreeNode<T>* temp = root;
        if (!is_contained(_value)) {
            while(temp) {
                if (temp->value > _value ) {
                    if (temp->left == nullptr) {
                        temp->left = new TreeNode<T>(_value);
                        break;
                    } else {
                        temp = temp->left;
                    }
                } else {
                    if (temp->right == nullptr) {
                        temp->right = new TreeNode<T>(_value);
                        break;
                    } else {
                        temp = temp->right;
                    }
                }
            }
        }
    }

    T getMax() const
    {
        TreeNode<T>* temp = root;
        while(temp->right) temp = temp->right;
        return temp->value;
    }

    T getMin() const
    {
        TreeNode<T>* temp = root;
        while(temp->left) temp = temp->left;
        return temp->value;
    }
};