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
	bool containsKey(node* tree, int k) {
		if (!tree) {
			return false;
		}
		else {
			if (k < tree->key) return containsKey(tree->left, k);
			else if (k > tree->key) return containsKey(tree->right, k);
			else return true;
		}
	}
	bool eraseKey(node*& tree, int k) {
		if (!tree) {
			return false;
		}
		else {
			if (k < tree->key) return eraseKey(tree->left, k);
			else {
				if (k > tree->key) return eraseKey(tree->right, k);
				else {
					tree = deleteNode(tree);
					return true;
				}
			}
		}
	}
	node* deleteNode(node*& tree) {
		if (!tree->left && !tree->right) {
			delete tree;
			tree = nullptr;
			return tree;
		}
		if (!tree->right) {
			node* tmp = tree;
			tree = tree->left;
			delete tmp;
			return tree;
		}
		if (!tree->left) {
			node* tmp = tree;
			tree = tree->right;
			delete tmp;
			return tree;
		}
		node* tmp = tree->right;
		if (tmp->left) {
			while (tmp->left->left != nullptr) tmp = tmp->left;
			if (!tmp->left->right) {
				tree->key = tmp->left->key;
				delete tmp->left;
				tmp->left = nullptr;
			}
			else {
				tree->key = tmp->left->key;
				node* tmp2 = tmp->left;
				tmp->left = tmp->left->right;
				delete tmp2;
			}
		}
		else {
			tree->key = tmp->key;
			tree->right = tmp->right;
			delete tmp;
		}
		return tree;
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
	bool contains(int k) {
		return containsKey(root, k);
	}
	bool erase(int k) {
		return eraseKey(root, k);
	}
};
int main() {
	BinarySearchTree tree;
	tree.insert(1);
	tree.insert(2);
	tree.insert(0);
	std::cout << "Current tree:" << std::endl;
	tree.print();
	int k = 1;
	std::cout << "Is tree contains element " << k << "? - ";
	tree.contains(k) ? std::cout << "Yes" << std::endl : std::cout << "No" << std::endl;
	if (tree.erase(k)) std::cout << "Element " << k << " deleted" << std::endl;
	std::cout << "Is tree contains element " << k << "? - ";
	tree.contains(k) ? std::cout << "Yes" << std::endl : std::cout << "No" << std::endl;
}