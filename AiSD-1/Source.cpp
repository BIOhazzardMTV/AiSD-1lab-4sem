#include<iostream>
#include<conio.h>
#include<limits>
struct node {
	int key;
	node* right;
	node* left;
	node(int k) : key(k), left(NULL), right(NULL) {}
};
class BinarySearchTree {
private:
	node* root;
	node* copyTree(node* n) {
		if (!n) return NULL;
		node* new_node = new node(n->key);
		new_node->left = copyTree(n->left);
		new_node->right = copyTree(n->right);
		return new_node;
	}
	void clearTree(node* r) {
		if (r) {
			clearTree(r->left);
			clearTree(r->right);
			delete r;
		}

	}
public:
	BinarySearchTree() : root(NULL) { }
	BinarySearchTree(const BinarySearchTree& tree) : root(copyTree(tree.root)) { }
	~BinarySearchTree() {
		clear();
	}
	void clear() {
		clearTree(root);
		root = NULL;
	}
};