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
protected:
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

    TreeNode<T>* find(T _value) const
    {
        TreeNode<T>* temp = root;
        while(temp) {
            if (temp->value == _value) {
                break;
            } else if (temp->value > _value) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        return temp;
    }

    void remove(T _value)
    {
        TreeNode<T>* curr = root;
        TreeNode<T>* next = root;
        while (next) {
            if (next->value == _value) {
                // У удаляемого узла нет потомков
                if (next->left == nullptr && next->right == nullptr) {
                    if (curr->left == next) {
                        curr->left = nullptr;
                    } else {
                        curr->right = nullptr;
                    }
                    delete next;
                // У удаляемого узла один потомок справа
                } else if (next->left == nullptr && next->right) {
                    if (curr->left == next) {
                        curr->left = next->right;
                    } else {
                        curr->right = next->right;
                    }
                    delete next;
                // У удаляемого узла один потомок слева
                } else if (next->left && next->right == nullptr)  {
                    if (curr->left == next) {
                        curr->left = next->left;
                    } else {
                        curr->right = next->left;
                    }
                    delete next;
                // У удаляемого узла два потомка
                } else {
                    curr = next;
                    next = next->right;
                    if (next->left == nullptr) {
                        curr->value = next->value;
                        curr->right = next->right;
                        delete next;
                    } else {
                        TreeNode<T>* deleteNode = curr;
                        while (next->left) {
                            curr = next;
                            next = next->left;
                        }
                        if (next->right == nullptr) {
                            deleteNode->value = next->value;
                            curr->left = nullptr;
                            delete next;
                        } else {
                            deleteNode->value = next->value;
                            curr->left = next->right;
                            delete next;
                        }
                    }
                }
                break;
            } else if (next->value > _value) {
                curr = next;
                next = next->left;
            } else {
                curr = next;
                next = next->right;
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

    TreeNode<T>* getRoot() const
    {
        return root;
    }
};

template <typename T>
class AVLTree : public BinaryTree<T>
{

};