#include <iostream>
#include <memory>

// Szablon klasy BST
template <typename T>
class BST {
private:
    struct Node {
        T value;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        Node* parent;

        Node(const T& val, Node* par = nullptr)
            : value(val), parent(par), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> root;

    // Funkcja pomocnicza do print_in_order
    void print_in_order(const Node* node) const {
        if (!node) return;
        print_in_order(node->left.get()); // Odwiedzanie lewego poddrzewa
        std::cout << node->value << " "; // Wypisywanie wartości w węźle
        print_in_order(node->right.get()); // Odwiedzanie prawego poddrzewa
    }

public:
    BST() : root(nullptr) {}

    // Dodawanie elementu do drzewa
    void insert(const T& value) {
        if (!root) {
            root = std::make_unique<Node>(value);
            return;
        }

        Node* current = root.get();
        Node* parent = nullptr;

        while (current) {
            parent = current;
            if (value < current->value) {
                current = current->left.get();
            } else {
                current = current->right.get();
            }
        }

        if (value < parent->value) {
            parent->left = std::make_unique<Node>(value, parent);
        } else {
            parent->right = std::make_unique<Node>(value, parent);
        }
    }

    // Wypisywanie elementów w porządku "lewe poddrzewo - korzeń - prawe poddrzewo"
    void print_in_order() const {
        print_in_order(root.get());
        std::cout << std::endl;
    }
};

// Przykład użycia
int main() {
    BST<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);

    std::cout << "In-order traversal: ";
    tree.print_in_order();

    return 0;
}