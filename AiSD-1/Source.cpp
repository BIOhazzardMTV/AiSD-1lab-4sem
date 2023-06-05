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
	void printTree(node* tree, int n) {
		if (tree) {
			printTree(tree->right, n + 1);
			for (int i = 0; i < n; i++) {
				std::cout << "  ";
			}
			std::cout << tree->key << "\n";
			printTree(tree->left, n + 1);
		}
	}
	bool insertTree(node*& tree, int k) {
		if (tree) {
			if (k > tree->key) return insertTree(tree->right, k);
			else if (k < tree->key) return insertTree(tree->left, k);
			else return false;
		}
		tree = new node(k);
		return true;
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
	BinarySearchTree& operator=(const BinarySearchTree& tree) {
		clear();
		root = copyTree(tree.root);
		return *this;
	}
	void print() {
		printTree(root, 0);
	}
	bool insert(int k) {
		return insertTree(root, k);
	}
};