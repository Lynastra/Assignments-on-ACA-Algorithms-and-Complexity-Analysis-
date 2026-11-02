// Двоичное дерево поиска (BST) на C++17.
// Без windows.h: работает на любой ОС.

#include <iostream>
#include <limits>
#include <queue>
#include <string>
using namespace std;

class BST {
public:
    BST() = default;
    ~BST() { clear(root); } // освобождаем всё дерево

    // Копировать дерево запрещаем: иначе два объекта владели бы одними узлами
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    // ---- Основные операции. Возвращают true/false, ничего не печатают ----
    bool insert(int key) { return insertHelper(root, key); }
    bool remove(int key) { return removeHelper(root, key); }
    bool contains(int key) const { return findHelper(root, key) != nullptr; }
    bool empty() const { return root == nullptr; }

    // ---- Три обхода ----
    void preorder() const { preorderHelper(root);  cout << '\n'; }   // узел, левое, правое
    void inorder() const { inorderHelper(root);   cout << '\n'; }   // левое, узел, правое
    void postorder() const { postorderHelper(root); cout << '\n'; }   // левое, правое, узел

    // ---- Обход по уровням (через очередь, за O(n)) ----
    void levelOrder() const {
        if (!root) { cout << '\n'; return; }
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* cur = q.front();
            q.pop();
            cout << cur->key << ' ';
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        cout << '\n';
    }

    // Высота в рёбрах: пустое дерево -1, одиночный узел 0
    int height() const { return heightHelper(root); }

    // Дерево, повёрнутое на 90 градусов: корень слева, правые дети сверху
    void print2D() const {
        if (!root) { cout << "(пусто)\n"; return; }
        print2DHelper(root, 0);
    }

private:
    struct Node {
        int key;
        Node* left = nullptr;
        Node* right = nullptr;
        explicit Node(int k) : key(k) {}
    };

    Node* root = nullptr;

    // ---- Вставка ----
    // Node*& значит "ссылка на сам указатель". 
    // Присвоив node = new Node(...),
    // мы меняем тот указатель, который лежит в родителе (или root).
    bool insertHelper(Node*& node, int key) {
        if (!node) {                              // нашли пустое место
            node = new Node(key);
            return true;
        }
        if (key < node->key) return insertHelper(node->left, key);
        if (key > node->key) return insertHelper(node->right, key);
        return false;                             // такой ключ уже есть
    }

    // ---- Поиск ----
    Node* findHelper(Node* node, int key) const {
        while (node && node->key != key)
            node = (key < node->key) ? node->left : node->right;
        return node;                              // nullptr, если не нашли
    }

    // ---- Удаление ----
    bool removeHelper(Node*& node, int key) {
        if (!node) return false;                  // не нашли
        if (key < node->key) return removeHelper(node->left, key);
        if (key > node->key) return removeHelper(node->right, key);

        // Нашли удаляемый узел.
        if (!node->left) {                        // нет левого: заменяем правым (или nullptr)
            Node* old = node;
            node = node->right;
            delete old;
        }
        else if (!node->right) {                // нет правого: заменяем левым
            Node* old = node;
            node = node->left;
            delete old;
        }
        else {                                  // два ребёнка
            Node* succ = node->right;             // преемник = минимум правого поддерева
            while (succ->left) succ = succ->left;
            node->key = succ->key;                // копируем его ключ сюда
            removeHelper(node->right, succ->key); // и удаляем преемника (у него нет левого)
        }
        return true;
    }

    // ---- Обходы ----
    void preorderHelper(const Node* node) const {
        if (!node) return;
        cout << node->key << ' ';
        preorderHelper(node->left);
        preorderHelper(node->right);
    }
    void inorderHelper(const Node* node) const {
        if (!node) return;
        inorderHelper(node->left);
        cout << node->key << ' ';
        inorderHelper(node->right);
    }
    void postorderHelper(const Node* node) const {
        if (!node) return;
        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << node->key << ' ';
    }

    int heightHelper(const Node* node) const {
        if (!node) return -1;
        int l = heightHelper(node->left);
        int r = heightHelper(node->right);
        return 1 + (l > r ? l : r);
    }

    void print2DHelper(const Node* node, int depth) const {
        if (!node) return;
        print2DHelper(node->right, depth + 1);    // сначала правое: оно окажется сверху
        cout << string(depth * 4, ' ') << node->key << '\n';
        print2DHelper(node->left, depth + 1);
    }

    // Удаление всего поддерева обратным обходом: сначала дети, потом сам узел
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
};

// Читает целое число; при неверном вводе очищает поток и возвращает false
bool readInt(const char* prompt, int& value) {
    cout << prompt;
    if (cin >> value) return true;
    if (cin.eof()) exit(0);                       // конец ввода: выходим
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Нужно ввести целое число.\n";
    return false;
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    BST tree;
    int option = -1;

    while (option != 0) {
        cout << "\n1. Вставить  2. Найти  3. Удалить  4. Обходы и вывод  5. Высота  0. Выход\n";
        if (!readInt("> ", option)) { option = -1; continue; }

        int val;
        switch (option) {
        case 0:
            break;
        case 1:
            if (readInt("Ключ: ", val))
                cout << (tree.insert(val) ? "Вставлено\n" : "Такой ключ уже есть\n");
            break;
        case 2:
            if (readInt("Ключ: ", val))
                cout << (tree.contains(val) ? "Найден\n" : "Не найден\n");
            break;
        case 3:
            if (readInt("Ключ: ", val))
                cout << (tree.remove(val) ? "Удалён\n" : "Не найден\n");
            break;
        case 4:
            cout << "Прямой:      "; tree.preorder();
            cout << "Симметричный: "; tree.inorder();
            cout << "Обратный:    "; tree.postorder();
            cout << "По уровням:  "; tree.levelOrder();
            cout << "Дерево:\n";    tree.print2D();
            break;
        case 5:
            cout << "Высота: " << tree.height() << '\n';
            break;
        default:
            cout << "Нет такого пункта\n";
        }
    }
    return 0;
}