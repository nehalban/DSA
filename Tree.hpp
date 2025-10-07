#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//level order traversal
//inorder iter, postorder iter
template<typename T>
struct BinaryTree {
	struct Node {
		T data;
		Node* left;
		Node* right;
		Node(T x, Node* left = nullptr, Node* right = nullptr) 
			: data(x), left(left), right(right) {}
	};
	Node* root;
	vector<vector<T>> levelOrder() {
		vector<vector<T>> bfs;
		vector<T> level;
		queue<Node*> q;
		q.push(nullptr);
		Node* temp = root;
		while(!q.empty()){
			if (temp==nullptr){
				bfs.push_back(level);
				level.clear();
				if(q.empty()) return bfs;
				else q.push(nullptr);
			}
			else{
				level.push_back(temp->data);
				if (temp->left) q.push(temp->left);
				if (temp->right) q.push(temp->right);
			}
			temp = q.front();
			q.pop();
		}
		if(!level.empty()) bfs.push_back(level);
		return bfs;
	}
	// vector<vector<T>> verticalorder(){
	// 	vector<vector<T>> left_;
	// 	vector<vector<T>> right_;
	// 	queue<pair<int, Node*>> q;
	// 	q.push(make_pair(0,root));
		
	// }
	// vector<vector<T>> verticalorder(){
	// 	vector<pair<int, vector<T>>> vot;
	// }
	vector<T> preorder_recursive(Node* curr=root, vector<T>& pre){
		if(curr==nullptr) return pre;
		pre.push_back(curr->data);
		preorder_recursive(curr->left, pre);
		preorder_recursive(curr->right, pre);
		return pre;
	}
	vector<T> preorder_iterative(){
		vector<T> pre;
		if(root==nullptr) return pre;
		stack<Node*> s;
		s.push(root);
		while(!s.empty()){
			Node* temp = s.top();
			s.pop();
			pre.push_back(temp->data);
			if(temp->right) s.push(temp->right);
			if(temp->left) s.push(temp->left);
		}
		return pre;
	}
	vector<T> inorder_recursive(Node* curr=root, vector<T>& in){
		if(curr==nullptr) return in;
		inorder_recursive(curr->left, in);
		in.push_back(curr->data);
		inorder_recursive(curr->right, in);
		return in;
	}
	// vector<T> inorder_iterative(){
	// 	vector<T> in;
	// 	if(root==nullptr) return in;
	// 	stack<Node*> s;
	// 	Node* temp = root;
	// 	while(temp!=nullptr || !s.empty()){
	// 		while(temp!=nullptr){
	// 			s.push(temp);
	// 			temp = temp->left;
	// 		}
	// 		temp = s.top();
	// 		s.pop();
	// 		in.push_back(temp->data);
	// 		temp = temp->right;
	// 	}
	// 	return in;
	// }
	vector<T> postorder_recursive(Node* curr=root, vector<T>& post){
		if(curr==nullptr) return post;
		postorder_recursive(curr->left, post);
		postorder_recursive(curr->right, post);
		post.push_back(curr->data);
		return post;
	}
	// vector<T> postorder_iterative(){
	// 	vector<T> post;
	// 	if(root==nullptr) return post;
	// 	stack<Node*> s1, s2;
	// 	s1.push(root);
	// 	while(!s1.empty()){
	// 		Node* temp = s1.top();
	// 		s1.pop();
	// 		s2.push(temp);
	// 		if(temp->left) s1.push(temp->left);
	// 		if(temp->right) s1.push(temp->right);
	// 	}
	// 	while(!s2.empty()){
	// 		post.push_back(s2.top()->data);
	// 		s2.pop();
	// 	}
	// 	return post;
	// }
	vector<T> eulertraversal_recursive(Node* curr=root, vector<T>& euler){
		if(curr==nullptr) return euler;
		euler.push_back(curr->data);
		eulertraversal_recursive(curr->left, euler);
		euler.push_back(curr->data);
		eulertraversal_recursive(curr->right, euler);
		euler.push_back(curr->data);
		return euler;
	}
	// vector<T> eulertraversal_iterative(){
	// 	vector<T> euler;
	// 	if(root==nullptr) return euler;
	// 	stack<pair<Node*, int>> s;
	// 	s.push(make_pair(root, 0));
	// 	while(!s.empty()){
	// 		pair<Node*, int> temp = s.top();
	// 		s.pop();
	// 		if(temp.second==0){
	// 			euler.push_back(temp.first->data);
	// 			s.push(make_pair(temp.first, 1));
	// 			if(temp.first->left) s.push(make_pair(temp.first->left, 0));
	// 		}
	// 		else if(temp.second==1){
	// 			euler.push_back(temp.first->data);
	// 			s.push(make_pair(temp.first, 2));
	// 			if(temp.first->right) s.push(make_pair(temp.first->right, 0));
	// 		}
	// 		else{
	// 			euler.push_back(temp.first->data);
	// 		}
	// 	}
	// 	return euler;
	// }
	vector<T> morris_inorder(Node* curr=root){
		vector<T> in;
		if(curr==nullptr) return in;
		while(curr){
			if(!curr->left){
				in.push_back(curr->data);
				curr = curr->right;
			}
			else{
				Node* pre = curr->left;
				while(pre->right && pre->right!=curr){
					pre = pre->right;
				}
				if(!pre->right){
					pre->right = curr;
					curr = curr->left;
				}
				else{
					pre->right = nullptr;
					in.push_back(curr->data);
					curr = curr->right;
				}
			}
		}
		return in;
	}
	// vector<T> morris_preorder(Node* curr=root){
	// 	vector<T> pre;
	// 	if(curr==nullptr) return pre;
	// 	while(curr!=nullptr){
	// 		if(curr->left==nullptr){
	// 			pre.push_back(curr->data);
	// 			curr = curr->right;
	// 		}
	// 		else{
	// 			Node* pre_ = curr->left;
	// 			while(pre_->right!=nullptr && pre_->right!=curr){
	// 				pre_ = pre_->right;
	// 			}
	// 			if(pre_->right==nullptr){
	// 				pre_.right = curr;
	// 				pre.push_back(curr->data);
	// 				curr = curr->left;
	// 			}
	// 			else{
	// 				pre_->right = nullptr;
	// 				curr = curr->right;
	// 			}
	// 		}
	// 	}
	// 	return pre;
	// }
	vector<T> zigzag_traversal(){
		stack<Node*> A;
        stack<Node*> B;
        vector<int> zigzag;
        A.push(root);
        while(!A.empty()){
            while(!A.empty()){
                Node* top = A.top();
                A.pop();
                zigzag.push_back(top->data);
                if(top->left) B.push(top->left);
                if(top->right) B.push(top->right);
            }
            while(!B.empty()){
                Node* top = B.top();
                B.pop();
                zigzag.push_back(top->data);
                if(top->right) A.push(top->right);
                if(top->left) A.push(top->left);
            }
        }
        return zigzag;
	}
	int height(Node* curr) {
        if(curr==nullptr) return 0;
        int lheight = height(curr->left);
        int rheight = height(curr->right);
        return max(lheight, rheight)+1;
    }
	private:
	int isBalancedHelper(Node* curr){
        int lheight, rheight;
        if(curr->left){
            lheight = isBalancedHelper(curr->left);
            if (lheight==-1) return -1;
        }
        else lheight=0;
        if(curr->right){
            rheight = isBalancedHelper(curr->right);
            if(rheight==-1) return -1;
        }
        else rheight=0;
        if(abs(lheight-rheight)>1) return -1;
        else return max(lheight, rheight)+1;
    }
	public:
    bool isBalanced(Node* root) {
        // code here
        if(isBalancedHelper(root)==-1) return false;
        else return true;
    }
	// int diameter(Node* curr){
	// 	if(curr==nullptr) return 0;
	// 	int lheight = height(curr->left);
	// 	int rheight = height(curr->right);
	// 	int ldiameter = diameter(curr->left);
	// 	int rdiameter = diameter(curr->right);
	// 	return max(lheight+rheight+1, max(ldiameter, rdiameter));
	// }
	void mirror(Node* curr){
		if(curr==nullptr) return;
		swap(curr->left, curr->right);
		mirror(curr->left);
		mirror(curr->right);
	}
};

template<typename T>
struct BST: public BinaryTree<T> {
	Node* find(T x){
		if(!root) return nullptr;
		Node* curr = this->root;
		while(true){
			if(curr->data==x) break;
			else if(curr->data>x){
				if(curr->left) curr = curr->left;
				else break;
			}
			else{
				if(curr->right) curr = curr->right;
				else break;
			}
		}
		return curr;
	}
	bool search(T x){
		if(find(x)->data==x) return true;
		else return false;
	}
	Node* insert(T x){
		if(!this->root){
			this->root = new Node(x);
			return this->root;
		}
		else{
			Node* curr= find(x);
			if(curr->data==x) return curr;
			else if (curr->data>x){
				curr->left = new Node(x);
				return curr->left;
			}
			else{
				curr->right = new Node(x);
				return curr->right;
			}
		}
	}
	Node* insert_recursive(Node* curr = root, T x){
		if(curr==nullptr) return new Node(x);
		if(curr->data==x) return curr;
		else if(curr->data>x) curr->left = insert_recursive(curr->left, x);
		else curr->right = insert_recursive(curr->right, x);
		return curr;
	}
	Node* deleteNode(Node* curr = root, T x){
		if(!curr) return curr;
		if(curr->data>x) curr->left = deleteNode(curr->left, x);
		else if(curr->data<x) curr->right = deleteNode(curr->right, x);
		else{
			if(!curr->left){
				Node* temp = curr->right;
				delete curr;
				return temp;
			}
			else if(!curr->right){
				Node* temp = curr->left;
				delete curr;
				return temp;
			}
			else{
				Node* succParent = curr;
				Node* succ = curr->right;
				while(succ->left){
					succParent = succ;
					succ = succ->left;
				}
				if(succParent!=curr) succParent->left = succ->right;
				else succParent->right = succ->right;
				curr->data = succ->data;
				delete succ;
			}
		}
		return curr;
	}
};
