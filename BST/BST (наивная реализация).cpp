#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
/* 
Правило двоичного дерева поиска:
1) у любой вершины в левом поддереве ключи < ключу в самой вершине
2) у любой вершины в правом поддереве ключи > ключу в самой вершине
*/

/*class BST {
	struct Node
	{
		int key;
		Node *left_child = nullptr, * right_child = nullptr;
		// конструктор. принимает значение ключа и 
		// записывает это значение в поле key
		Node(int k) : key(k) {}
	}
	*root = nullptr;

	bool contains(Node* n, int key) const 
	{
		if (!n)
			return false;
		if (key == n -> key)
			return true;
		if (key < n->key)
			return contains(n->left_child, key);
		else
			return contains(n->right_child, key);
	}
	void insert(Node *n, int key)
	{
		if (!root)
		{
			root = new Node(key);
			return;
		}
		if (key == n ->key)
		{
			return;
		}
		if (key < n->key)
		{
			if (n->left_child)
			{
				insert(n->left_child, key);
			}
			else
			{
				n->left_child = new Node(key);
			}
		}
		else
		{
			if (n->right_child)
			{
				insert(n->right_child, key);
			}
			else
			{
				n->right_child = new Node(key);
			}
		}
	}
public:
	bool contains(int key) const
	{
		return contains(root, key);
	}
	void insert(int key) 
	{
		insert(root, key);
	}
};
*/

class BST {
	struct Node
	{
		int key;
		Node* left_child = nullptr, * right_child = nullptr;
		Node(int k) : key(k) {}
	}
	*root = nullptr;

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
	// основная функция, от кот. отталкиваемся
	// и модифицируем
	/*void insert(Node*& n, int key)
	{
		if (!n)
		{
			n = new Node(key);
			return;
		}
		if (key == n->key)
		{
			return;
		}
		if (key < n->key)
		{
			insert(n->left_child, key);
		}
		else
		{
			insert(n->right_child, key);
		}
	}
	*/
	// модификация функции вставки под задачу 2
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
	// основная функция, от кот.отталкиваемся
	// и модифицируем
	/*
	void print(Node *n) const
	{
		if (!n)
			return;
		print(n->left_child);
		if (n->left_child && n->right_child)
		{
			cout << n->key << "\n";
		}
		//cout << n->key << "\n";
		print(n->right_child);
	}
	*/
	void print(Node* n, int level) const
	{
		if (!n)
			return;
		print(n->left_child, level + 1);
		for (int i = 0; i < level; i++)
		{
			cout << ".";
		}		
		cout << n->key << "\n";
		print(n->right_child, level + 1);
	}
	void destroy(Node *n)
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

	bool contains(int key) const
	{
		return contains(root, key);
	}
	bool insert(int key)
	{
		return insert(root, key);
	}
	/*
	void insert(int key)
	{
		insert(root, key);
	}
	
	void print() const 
	{
		print(root);
	}
	*/
	void print() const
	{
		print(root, 0);
	}
	~BST() 
	{
		destroy(root);
	}
};

// для проверки (тестирования кода) решим несколько задач
/*
* -----Задача 1:
* Вводится последовательность целых чисел, оканчивающаяся на нулём.
* Сам ноль в последовательность не входит.
* Постройте в этой последовательности дерева.
* Для полученного дерева выведите список всех вершин, имеющих по два ребёнка
* в порядке возрастания.
* Замечание: если во входных данных есть повторяющие числа, то их нужно 
игнорировать, т.е. все элементы дерева уникальны
* Пример:
* 7 3 2 1 9 5 4 6 8 0
* -----Задача 2:
* Напишите программу, которая будет реализовывать действия в бинарном дереве
* поиска "вставить" и "найти" (по значению). 
* Программа должна обрабатывать запросы 3х видов:
* 1) ADD n - если указанного числа ещё нет в дереве, вставлять его и выводить слово
* "DONE", если уже есть - оставлять дерево как было и выводи слово "ALREADY".
* 2) SEARCH - следует выводить слово "YES" (если значение найдено в дереве)
* или слово "NO" (если не найдено). Дерево при этом не меняется.
* 3) PRINTTREE - выводить всё дерево, обязательно используя алгоритм, указанный
* далее в условии задачи.

Алгоритм для вывода дерева:
template<class T> void print_tree(Node<T> *p, int level)
{
	if (p == nullptr)
		return;
	print_tree(p->left, level + 1);
	for(int i = 0; i < level; i++)
		cout << ".";
	cout << p->data << end;
	print_tree(p->right, level + 1);
}
* Изначальный вызов этой функции - print_tree(root, 0)
* Пример:
ADD 2
ADD 3
ADD 2
SEARCH 2
ADD 5
PRINTTREE
SEARCH 7
*/
int main()
{
	// для задачи 2:
	// Если есть input.txt, то переключаем ввод на него.
	// Раз есть файл с входными данными — значит предполагается, что 
	// есть файл и для результата, пишем в него.
	// Если output.txt отсутствует — вывод останется в консоли.
	if (freopen("input.txt", "r", stdin)) {
		(void) freopen("output.txt", "w", stdout);
	}
	// Если input.txt не открылся — freopen вернул nullptr,
	// cin по-прежнему связан с консолью, работаем через неё
	BST bst;
	// для 1й задачи

	/*
	while (true)
	{
		int x;
		cin >> x;
		if (x == 0)
		{
			break;
		}
		bst.insert(x);
	}
	bst.print();
	*/

	string command;
	while (cin >> command)
	{
		if (command == "SEARCH")
		{
			int key;
			cin >> key;
			cout << (bst.contains(key) ? "YES\n" : "NO\n");
		}
		else if (command == "ADD")
		{
			int key;
			cin >> key;
			cout << (bst.insert(key) ? "DONE\n" : "ALREADY\n");
		}
		else if (command == "PRINTTREE") 
			bst.print();
		else cout << "Unknown command\n";
	}
}
