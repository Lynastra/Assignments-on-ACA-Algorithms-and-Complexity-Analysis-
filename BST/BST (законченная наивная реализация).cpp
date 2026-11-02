#include <iostream>

using namespace std;
/*
Правило двоичного дерева поиска:
1) у любой вершины в левом поддереве ключи < ключу в самой вершине
2) у любой вершины в правом поддереве ключи > ключу в самой вершине
*/

// Версия без использования информации о родителе:
// в узле только ключ и указатели на детей.
class BST {
	struct Node
	{
		int key;
		Node* left_child = nullptr, * right_child = nullptr;
		explicit Node(int k) : key(k) {}
	};
	Node* root = nullptr;

	bool contains(Node* n, int key) const
	{
		if (!n)
			return false;
		if (key == n->key)
			return true;
		if (key < n->key)
			return contains(n->left_child, key);
		else
			return contains(n->right_child, key);
	}
	// Node*& - ссылка на сам указатель: присваивая n = new Node(key),
	// мы меняем указатель в родителе (или root)
	bool insert(Node*& n, int key)
	{
		if (!n)
		{
			n = new Node(key);
			return true;
		}
		if (key == n->key)
			return false;
		if (key < n->key)
			return insert(n->left_child, key);
		else
			return insert(n->right_child, key);
	}
	// Отцепляет самый левый узел поддерева n и возвращает его (сам узел не удаляет).
	// На его место в дереве встаёт его правый ребёнок (или nullptr).
	Node* extract_min(Node*& n)
	{
		if (n->left_child)
			return extract_min(n->left_child);
		Node* m = n;
		n = n->right_child;
		return m;
	}
	bool remove(Node*& n, int key)
	{
		if (!n)
			return false;
		if (key < n->key)
			return remove(n->left_child, key);
		if (key > n->key)
			return remove(n->right_child, key);

		// нашли узел, который надо удалить
		Node* old = n;
		if (!n->left_child)
			n = n->right_child;               // нет левого: заменяем правым (или nullptr)
		else if (!n->right_child)
			n = n->left_child;                // нет правого: заменяем левым
		else
		{
			// два ребёнка: отцепляем преемника (минимум правого поддерева)
			// и сажаем на место удаляемого узла
			Node* m = extract_min(n->right_child);
			m->left_child = n->left_child;
			m->right_child = n->right_child;  // читаем уже после extract_min
			n = m;
		}
		delete old;
		return true;
	}
	// вывод "боком": уровень узла показан точками
	void print(Node* n, int level) const
	{
		if (!n)
			return;
		print(n->left_child, level + 1);
		for (int i = 0; i < level; i++)
			cout << ".";
		cout << n->key << "\n";
		print(n->right_child, level + 1);
	}
	// прямой обход: узел, левое, правое
	void preorder(Node* n) const
	{
		if (!n)
			return;
		cout << n->key << " ";
		preorder(n->left_child);
		preorder(n->right_child);
	}
	// симметричный обход: левое, узел, правое (ключи по возрастанию)
	void inorder(Node* n) const
	{
		if (!n)
			return;
		inorder(n->left_child);
		cout << n->key << " ";
		inorder(n->right_child);
	}
	// обратный обход: левое, правое, узел
	void postorder(Node* n) const
	{
		if (!n)
			return;
		postorder(n->left_child);
		postorder(n->right_child);
		cout << n->key << " ";
	}
	void destroy(Node* n)
	{
		if (!n)
			return;
		destroy(n->left_child);
		destroy(n->right_child);
		delete n;
	}
public:
	BST() = default;
	BST(const BST&) = delete;
	BST& operator=(const BST&) = delete;

	bool contains(int key) const { return contains(root, key); }
	bool insert(int key) { return insert(root, key); }
	bool remove(int key) { return remove(root, key); }
	void print() const { print(root, 0); }
	void preorder() const { preorder(root); cout << "\n"; }
	void inorder() const { inorder(root); cout << "\n"; }
	void postorder() const { postorder(root); cout << "\n"; }
	~BST() { destroy(root); }
};

void show(const BST& bst)
{
	cout << "Tree (level = number of dots):\n";
	bst.print();
	cout << "Preorder:  "; bst.preorder();
	cout << "Inorder:   "; bst.inorder();
	cout << "Postorder: "; bst.postorder();
	cout << "\n";
}

int main()
{
	BST bst;
	int keys[] = { 7, 3, 2, 1, 9, 5, 4, 6, 8 };
	for (int k : keys)
		bst.insert(k);
	show(bst);

	cout << "insert 5 again: " << (bst.insert(5) ? "DONE" : "ALREADY") << "\n";
	cout << "contains 6: " << (bst.contains(6) ? "YES" : "NO") << "\n";
	cout << "contains 10: " << (bst.contains(10) ? "YES" : "NO") << "\n\n";

	// удаляем так, чтобы встретились все случаи
	int to_remove[] = { 1, 2, 5, 7, 100 };   // лист, один ребёнок, два ребёнка, корень, нет такого
	for (int k : to_remove)
	{
		cout << "remove " << k << ": " << (bst.remove(k) ? "DONE" : "NOT FOUND") << "\n";
		show(bst);
	}
}