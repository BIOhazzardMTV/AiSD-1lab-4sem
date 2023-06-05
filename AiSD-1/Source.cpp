#include<iostream>
#include<chrono>
#include<vector>
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
	node* getRoot() {
		return root;
	}
};
int lcg() {
	static int x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}

double TreeTimeFilling(int number) {
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < 100; i++)
	{
		BinarySearchTree Tree;
		for (int j = 0; j < number; j++)
		{
			Tree.insert(lcg());
		}
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> result = end - start;
	return result.count() / 100;
}

double TreeTimeSearch(int number) {
	BinarySearchTree Tree;
	for (int j = 0; j < number; j++)
	{
		Tree.insert(lcg());
	}
	auto start = std::chrono::steady_clock::now();

	for (int i = 0; i < 1000; i++)
	{
		if (!Tree.contains(lcg())) {};
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> result = end - start;
	return result.count() / 1000;
}

double TreeTimeInsert(int number) {
	BinarySearchTree Tree;
	for (int j = 0; j < number; j++)
	{
		Tree.insert(lcg());
	}
	auto start = std::chrono::steady_clock::now();

	for (int i = 0; i < 1000; i++)
	{
		if (!Tree.insert(lcg())) {};
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> result = end - start;
	return result.count() / 1000;
}

double TreeTimeErase(int number) {
	BinarySearchTree Tree;
	for (int j = 0; j < number; j++)
	{
		Tree.insert(lcg());
	}
	auto start = std::chrono::steady_clock::now();

	for (int i = 0; i < 1000; i++)
	{
		if (!Tree.erase(lcg())) {};
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> result = end - start;
	return result.count() / 1000;
}

double VecTimeFilling(int number) {
	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < 100; i++)
	{
		std::vector<int> V;
		for (int j = 0; j < number; j++)
		{
			V.push_back(lcg());
		}
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> result = end - start;
	return result.count() / 100;
}

double VecTimeSearch(int number) {
	std::vector<int> V;
	for (int j = 0; j < number; j++)
	{
		V.push_back(lcg());
	}

	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < 1000; i++)
	{
		V.push_back(lcg());
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> result = end - start;
	return result.count() / 1000;
}

double VecTimeInsert(int number) {
	std::vector<int> V;
	for (int j = 0; j < number; j++)
	{
		V.push_back(lcg());
	}

	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < 1000; i++)
	{
		if (find(V.begin(), V.end(), lcg()) != V.end()) {};
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> result = end - start;
	return result.count() / 1000;
}

double VecTimeErase(int number) {
	std::vector<int> V;
	for (int j = 0; j < number; j++)
	{
		V.push_back(lcg());
	}

	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < 1000; i++)
	{
		auto it = std::remove(V.begin(), V.end(), lcg());
		V.erase(it, V.end());
	}
	auto end = std::chrono::steady_clock::now();
	std::chrono::duration<double> result = end - start;
	return result.count() / 1000;
}

void TimeTest() {
	std::cout << "time filling of tree and vector\n";
	std::cout << TreeTimeFilling(1000) << "   " << VecTimeFilling(1000) << std::endl;
	std::cout << TreeTimeFilling(10000) << "   " << VecTimeFilling(10000) << std::endl;
	std::cout << TreeTimeFilling(100000) << "   " << VecTimeFilling(100000) << std::endl;

	std::cout << "time search of tree and vector\n";
	std::cout << TreeTimeSearch(1000) << "   " << VecTimeSearch(1000) << std::endl;
	std::cout << TreeTimeSearch(10000) << "   " << VecTimeSearch(10000) << std::endl;
	std::cout << TreeTimeSearch(100000) << "   " << VecTimeSearch(100000) << std::endl;

	std::cout << "time insert of tree and vector\n";
	std::cout << TreeTimeInsert(1000) << "   " << VecTimeInsert(1000) << std::endl;
	std::cout << TreeTimeInsert(10000) << "   " << VecTimeInsert(10000) << std::endl;
	std::cout << TreeTimeInsert(100000) << "   " << VecTimeInsert(100000) << std::endl;

	std::cout << "time erase of tree and vector\n";
	std::cout << TreeTimeErase(1000) << "   " << VecTimeErase(1000) << std::endl;
	std::cout << TreeTimeErase(10000) << "   " << VecTimeErase(10000) << std::endl;
	std::cout << TreeTimeErase(100000) << "   " << VecTimeErase(100000) << std::endl;
}

void IgnoreLine() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int GetInt() {
	while (true) {
		int x{};
		std::cin >> x;
		if (std::cin.fail()) {
			std::cin.clear();
			IgnoreLine();
			system("cls");
			std::cout << "Oops, that input is invalid.  Please try again.\n" << std::endl;
		}
		else {
			IgnoreLine();
			return x;
		}
	}
}

BinarySearchTree AddElem(BinarySearchTree tree) {
	std::cout << "Enter value" << std::endl;
	int value = GetInt();
	while (tree.contains(value)) {
		std::cout << "Oops, that input is invalid.  Please try again.\n" << std::endl;
		value = GetInt();
	}
	tree.insert(value);
	return tree;
}

BinarySearchTree DeleteElem(BinarySearchTree tree) {
	std::cout << "Enter value" << std::endl;
	int value = GetInt();
	while (!tree.contains(value)) {
		std::cout << "Oops, that input is invalid.  Please try again.\n" << std::endl;
		value = GetInt();
	}
	tree.erase(value);
	return tree;
}

void SearchElement(BinarySearchTree tree) {
	std::cout << "Enter value" << std::endl;
	int value = GetInt();
	if (tree.contains(value)) std::cout << "The tree contains the given element" << std::endl;
	else std::cout << "The tree does not contain this element" << std::endl;
}

BinarySearchTree WorkingWithTree(BinarySearchTree tree, char num) {
	while (true) {
		system("cls");
		std::cout << "\tWorking with tree #" << num << std::endl;
		std::cout << "1 - Print tree" << std::endl;
		std::cout << "2 - Enter value to add" << std::endl;
		std::cout << "3 - Enter value to delete" << std::endl;
		std::cout << "4 - Delete the whole tree" << std::endl;
		std::cout << "5 - Search element" << std::endl;
		std::cout << "0 - Go back" << std::endl;
		int ans2 = -1;
		int ans = _getch();
		system("cls");
		switch (ans) {
		default:
			break;
		case '1':
			tree.print();
			std::cout << "Press any key to continue..." << std::endl;
			if (_getch()) {};
			break;
		case '2':
			tree = AddElem(tree);
			break;
		case '3':
			tree = DeleteElem(tree);
			break;
		case '4':
			std::cout << "Are you sure you want to delete the whole tree?\n1 - yes\n2 - no\nEnter your answer: ";
			ans2 = GetInt();
			while (ans2 != 1 && ans2 != 2) {
				std::cout << "Oops, that input is invalid.  Please try again.\n" << std::endl;
				ans2 = GetInt();
			}
			if (ans2 == 1) tree.clear();
			break;
		case '5':
			SearchElement(tree);
			std::cout << "Press any key to continue..." << std::endl;
			if (_getch()) {};
			break;
		case '0':
			return tree;
		}
	}
}

void task1(BinarySearchTree& result, node* tree) {
	if (tree) {
		if (tree->left) task1(result, tree->left);
		if (tree->right) task1(result, tree->right);
		result.insert(tree->key);
	}
}

void task2(BinarySearchTree& result, node* tree) {
	if (tree) {
		if (tree->left) task2(result, tree->left);
		if (tree->right) task2(result, tree->right);
		if (result.contains(tree->key)) result.erase(tree->key);
		else result.insert(tree->key);
	}
}

void menuTask(BinarySearchTree tree1, BinarySearchTree tree2, int ans) {
	BinarySearchTree result = tree1;
	node* tmp = tree2.getRoot();
	if (tmp) {
		switch (ans) {
		case 1:
			task1(result, tmp);
			break;
		case 2:
			task2(result, tmp);
			break;
		default:
			break;
		}
	}
	result.print();
	std::cout << "Press any key to continue..." << std::endl;
	if (_getch()) {};
}

int main() {
	BinarySearchTree tree1, tree2;
	while (true) {
		system("cls");
		std::cout << "1 - Working with tree #1" << std::endl;
		std::cout << "2 - Working with tree #2" << std::endl;
		std::cout << "3 - Time test" << std::endl;
		std::cout << "4 - Union of sets" << std::endl;
		std::cout << "5 - Symmetric difference of sets" << std::endl;
		std::cout << "0 - Exit" << std::endl;
		int num = -1;
		int ans = _getch();
		system("cls");
		switch (ans)
		{
		case '1':
			tree1 = WorkingWithTree(tree1, '1');
			break;
		case '2':
			tree2 = WorkingWithTree(tree2, '2');
			break;
		case '3':
			TimeTest();
			std::cout << "Press any key to continue..." << std::endl;
			if (_getch()) {};
			break;
		case '4':
			menuTask(tree1, tree2, 1);
			break;
		case '5':
			menuTask(tree1, tree2, 2);
			break;
		case '0':
			std::cout << "See you soon :)" << std::endl;
			return 0;
		default:
			break;
		}
	}
}