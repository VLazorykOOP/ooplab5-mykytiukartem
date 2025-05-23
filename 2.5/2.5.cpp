#include <iostream>
#include <fstream>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;

// Клас вузла дерева
class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {
        cout << "Створено вузол з значенням: " << value << endl;
    }

    ~TreeNode() {
        cout << "Видалено вузол з значенням: " << value << endl;
    }
};

// Клас бінарного дерева
class BinaryTree {
private:
    TreeNode* root;
    static int count;

    void insert(TreeNode*& node, int val) {
        if (!node) {
            node = new TreeNode(val);
            count++;
        } else if (val < node->value) {
            insert(node->left, val);
        } else if (val > node->value) {
            insert(node->right, val);
        } else {
            cout << "Повторне значення (" << val << ") не додається." << endl;
        }
    }

    void reverseInOrderTraversal(TreeNode* node) {
        if (!node) return;
        reverseInOrderTraversal(node->right);
        cout << node->value << " ";
        reverseInOrderTraversal(node->left);
    }

    void clear(TreeNode* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BinaryTree() : root(nullptr) {}

    virtual ~BinaryTree() {
        clear(root);
    }

    void insert(int val) {
        insert(root, val);
    }

    void breadthTraversal() {
        if (!root) return;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* current = q.front(); q.pop();
            cout << current->value << " ";
            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        cout << endl;
    }

    void reverseInOrderTraversal() {
        reverseInOrderTraversal(root);
        cout << endl;
    }

    static int getCount() {
        return count;
    }
};

int BinaryTree::count = 0;

// --- ТЕСТИ ---
void testFromKeyboard() {
    BinaryTree tree;
    int n, val;
    cout << "[Ввід з клавіатури] Введіть кількість елементів: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Елемент " << i + 1 << ": ";
        cin >> val;
        tree.insert(val);
    }
    cout << "Обхід в ширину: ";
    tree.breadthTraversal();
    cout << "Зворотній обхід: ";
    tree.reverseInOrderTraversal();
}

void testFromFile() {
    BinaryTree tree;
    ifstream fin("tree.txt");
    if (!fin) {
        cerr << "Файл tree.txt не знайдено!" << endl;
        return;
    }
    int val;
    while (fin >> val) {
        tree.insert(val);
    }
    fin.close();
    cout << "[Ввід з файлу]" << endl;
    cout << "Обхід в ширину: ";
    tree.breadthTraversal();
    cout << "Зворотній обхід: ";
    tree.reverseInOrderTraversal();
}

void testRandom() {
    BinaryTree tree;
    srand(time(0));
    cout << "[Випадкові числа]" << endl;
    for (int i = 0; i < 7; i++) {
        int val = rand() % 100;
        cout << "Додаємо: " << val << endl;
        tree.insert(val);
    }
    cout << "Обхід в ширину: ";
    tree.breadthTraversal();
    cout << "Зворотній обхід: ";
    tree.reverseInOrderTraversal();
}

int main() {
    cout << "--- Тестування BinaryTree ---" << endl;
    testFromKeyboard();
    cout << endl;
    testFromFile();
    cout << endl;
    testRandom();
    cout << "\nЗагальна кількість вузлів: " << BinaryTree::getCount() << endl;
    return 0;
}
