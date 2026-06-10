#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>

template<typename T>
struct BinaryTreeBase {
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(T x, Node* left = nullptr, Node* right = nullptr)
            : data(x), left(left), right(right) {}
    };

    Node* root = nullptr;

    BinaryTreeBase() = default;
    explicit BinaryTreeBase(T value) : root(new Node(value)) {}

    std::vector<std::vector<T>> levelOrder() const {
        std::vector<std::vector<T>> bfs;
        if (!root) return bfs;

        std::queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            int level_size = static_cast<int>(q.size());
            std::vector<T> level;
            for (int i = 0; i < level_size; ++i) {
                Node* curr = q.front();
                q.pop();
                level.push_back(curr->data);
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            bfs.push_back(level);
        }
        return bfs;
    }

    std::vector<T>& preorder_recursive(Node* curr, std::vector<T>& pre) const {
        if (!curr) return pre;
        pre.push_back(curr->data);
        preorder_recursive(curr->left, pre);
        preorder_recursive(curr->right, pre);
        return pre;
    }

    std::vector<T> preorder_recursive() const {
        std::vector<T> pre;
        return preorder_recursive(root, pre);
    }

    std::vector<T> preorder_iterative() const {
        std::vector<T> pre;
        if (!root) return pre;

        std::stack<Node*> s;
        s.push(root);
        while (!s.empty()) {
            Node* temp = s.top();
            s.pop();
            pre.push_back(temp->data);
            if (temp->right) s.push(temp->right);
            if (temp->left) s.push(temp->left);
        }
        return pre;
    }

    std::vector<T>& inorder_recursive(Node* curr, std::vector<T>& in) const {
        if (!curr) return in;
        inorder_recursive(curr->left, in);
        in.push_back(curr->data);
        inorder_recursive(curr->right, in);
        return in;
    }

    std::vector<T> inorder_recursive() const {
        std::vector<T> in;
        return inorder_recursive(root, in);
    }

    std::vector<T> inorder_iterative() const {
        std::vector<T> in;
        std::stack<Node*> s;
        Node* temp = root;
        while (temp || !s.empty()) {
            while (temp) {
                s.push(temp);
                temp = temp->left;
            }
            temp = s.top();
            s.pop();
            in.push_back(temp->data);
            temp = temp->right;
        }
        return in;
    }

    std::vector<T>& postorder_recursive(Node* curr, std::vector<T>& post) const {
        if (!curr) return post;
        postorder_recursive(curr->left, post);
        postorder_recursive(curr->right, post);
        post.push_back(curr->data);
        return post;
    }

    std::vector<T> postorder_recursive() const {
        std::vector<T> post;
        return postorder_recursive(root, post);
    }

    std::vector<T> postorder_iterative() const {
        std::vector<T> post;
        if (!root) return post;

        std::stack<Node*> s1;
        std::stack<Node*> s2;
        s1.push(root);
        while (!s1.empty()) {
            Node* temp = s1.top();
            s1.pop();
            s2.push(temp);
            if (temp->left) s1.push(temp->left);
            if (temp->right) s1.push(temp->right);
        }
        while (!s2.empty()) {
            post.push_back(s2.top()->data);
            s2.pop();
        }
        return post;
    }

    std::vector<T>& eulertraversal_recursive(Node* curr, std::vector<T>& euler) const {
        if (!curr) return euler;
        euler.push_back(curr->data);
        eulertraversal_recursive(curr->left, euler);
        euler.push_back(curr->data);
        eulertraversal_recursive(curr->right, euler);
        euler.push_back(curr->data);
        return euler;
    }

    std::vector<T> eulertraversal_recursive() const {
        std::vector<T> euler;
        return eulertraversal_recursive(root, euler);
    }

    std::vector<T> eulertraversal_iterative() const {
        std::vector<T> euler;
        if (!root) return euler;

        std::stack<std::pair<Node*, int>> s;
        s.push({root, 0});
        while (!s.empty()) {
            auto [node, state] = s.top();
            s.pop();
            if (state == 0) {
                euler.push_back(node->data);
                s.push({node, 1});
                if (node->left) s.push({node->left, 0});
            } else if (state == 1) {
                euler.push_back(node->data);
                s.push({node, 2});
                if (node->right) s.push({node->right, 0});
            } else {
                euler.push_back(node->data);
            }
        }
        return euler;
    }

    std::vector<T> morris_inorder(Node* curr) const {
        std::vector<T> in;
        while (curr) {
            if (!curr->left) {
                in.push_back(curr->data);
                curr = curr->right;
            } else {
                Node* pre = curr->left;
                while (pre->right && pre->right != curr) pre = pre->right;
                if (!pre->right) {
                    pre->right = curr;
                    curr = curr->left;
                } else {
                    pre->right = nullptr;
                    in.push_back(curr->data);
                    curr = curr->right;
                }
            }
        }
        return in;
    }

    std::vector<T> morris_inorder() const {
        return morris_inorder(root);
    }

    std::vector<T> morris_preorder(Node* curr) const {
        std::vector<T> pre;
        while (curr) {
            if (!curr->left) {
                pre.push_back(curr->data);
                curr = curr->right;
            } else {
                Node* pred = curr->left;
                while (pred->right && pred->right != curr) pred = pred->right;
                if (!pred->right) {
                    pre.push_back(curr->data);
                    pred->right = curr;
                    curr = curr->left;
                } else {
                    pred->right = nullptr;
                    curr = curr->right;
                }
            }
        }
        return pre;
    }

    std::vector<T> morris_preorder() const {
        return morris_preorder(root);
    }

    std::vector<T> zigzag_traversal() const {
        std::vector<T> zigzag;
        if (!root) return zigzag;

        std::stack<Node*> current;
        std::stack<Node*> next;
        bool left_to_right = true;
        current.push(root);

        while (!current.empty()) {
            Node* top = current.top();
            current.pop();
            zigzag.push_back(top->data);

            if (left_to_right) {
                if (top->left) next.push(top->left);
                if (top->right) next.push(top->right);
            } else {
                if (top->right) next.push(top->right);
                if (top->left) next.push(top->left);
            }

            if (current.empty()) {
                std::swap(current, next);
                left_to_right = !left_to_right;
            }
        }

        return zigzag;
    }

    int height(Node* curr) const {
        if (!curr) return 0;
        return std::max(height(curr->left), height(curr->right)) + 1;
    }

    int height() const {
        return height(root);
    }

private:
    int isBalancedHelper(Node* curr) const {
        if (!curr) return 0;
        int lheight = isBalancedHelper(curr->left);
        if (lheight == -1) return -1;
        int rheight = isBalancedHelper(curr->right);
        if (rheight == -1) return -1;
        if (std::abs(lheight - rheight) > 1) return -1;
        return std::max(lheight, rheight) + 1;
    }

public:
    bool isBalanced(Node* node) const {
        return isBalancedHelper(node) != -1;
    }

    bool isBalanced() const {
        return isBalanced(root);
    }

    int diameter(Node* curr) const {
        if (!curr) return 0;
        int lheight = height(curr->left);
        int rheight = height(curr->right);
        int ldiameter = diameter(curr->left);
        int rdiameter = diameter(curr->right);
        return std::max(lheight + rheight + 1, std::max(ldiameter, rdiameter));
    }

    int diameter() const {
        return diameter(root);
    }

    void mirror(Node* curr) {
        if (!curr) return;
        std::swap(curr->left, curr->right);
        mirror(curr->left);
        mirror(curr->right);
    }

    void mirror() {
        mirror(root);
    }

    std::string encode_tree(Node* g) const {
        if (!g) return "";
        std::string left = encode_tree(g->left);
        std::string right = encode_tree(g->right);
        if (right < left) std::swap(left, right);
        return "(" + left + right + ")";
    }

    bool operator==(const BinaryTreeBase& b) const {
        return encode_tree(root) == encode_tree(b.root);
    }
};

template<typename T>
struct BST : public BinaryTreeBase<T> {
    using Base = BinaryTreeBase<T>;
    using Node = typename Base::Node;

    Node* find(T x) const {
        Node* curr = this->root;
        if (!curr) return nullptr;

        while (curr) {
            if (curr->data == x) return curr;
            if (curr->data > x) {
                if (!curr->left) return curr;
                curr = curr->left;
            } else {
                if (!curr->right) return curr;
                curr = curr->right;
            }
        }
        return nullptr;
    }

    bool exists(T x) const {
        Node* found = find(x);
        return found && found->data == x;
    }

    Node* insert(T x) {
        if (!this->root) {
            this->root = new Node(x);
            return this->root;
        }

        Node* curr = find(x);
        if (curr->data == x) return curr;
        if (curr->data > x) {
            curr->left = new Node(x);
            return curr->left;
        }

        curr->right = new Node(x);
        return curr->right;
    }

    Node* insert_recursive(Node* curr, T x) {
        if (!curr) return new Node(x);
        if (curr->data == x) return curr;
        if (curr->data > x) curr->left = insert_recursive(curr->left, x);
        else curr->right = insert_recursive(curr->right, x);
        return curr;
    }

    Node* insert_recursive(T x) {
        this->root = insert_recursive(this->root, x);
        return this->root;
    }

    Node* deleteNode(Node* curr, T x) {
        if (!curr) return curr;
        if (curr->data > x) curr->left = deleteNode(curr->left, x);
        else if (curr->data < x) curr->right = deleteNode(curr->right, x);
        else {
            if (!curr->left) {
                Node* temp = curr->right;
                delete curr;
                return temp;
            }
            if (!curr->right) {
                Node* temp = curr->left;
                delete curr;
                return temp;
            }

            Node* succ = minValueNode(curr->right);
            curr->data = succ->data;
            curr->right = deleteNode(curr->right, succ->data);
        }
        return curr;
    }

    Node* deleteNode(T x) {
        this->root = deleteNode(this->root, x);
        return this->root;
    }

    Node* minValueNode(Node* node) const {
        Node* current = node;
        while (current && current->left) current = current->left;
        return current;
    }

    Node* maxValueNode(Node* node) const {
        Node* current = node;
        while (current && current->right) current = current->right;
        return current;
    }
};

struct RedBlackTree : public BinaryTreeBase<int> {
    struct RBNode : public BinaryTreeBase<int>::Node {
        bool isRed;

        explicit RBNode(int data) : BinaryTreeBase<int>::Node(data), isRed(true) {}
    };
};

struct Tree {
    struct Node {
        int data;
        std::vector<Node*> children;

        explicit Node(int value) : data(value) {}
    };

    Node* root = nullptr;

    std::string encode_tree(Node* g) const {
        if (!g) return "";

        std::vector<std::string> labels;
        for (Node* child : g->children) {
            labels.push_back(encode_tree(child));
        }
        std::sort(labels.begin(), labels.end());

        std::string encoding = "(";
        for (const std::string& label : labels) {
            encoding += label;
        }
        encoding += ")";
        return encoding;
    }

    bool operator==(const Tree& b) const {
        return encode_tree(root) == encode_tree(b.root);
    }
};
