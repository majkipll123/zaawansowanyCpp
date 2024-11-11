#include <iostream>
#include <memory>

// Szablon klasy forward_list implementującej listę pojedynczo wiązaną
template <typename T>
class forward_list {
private:
    // Struktura węzła
    struct Node {
        T data;  // wartość węzła
        std::unique_ptr<Node> next;  // wskaźnik do następnego węzła

        // Konstruktor węzła
        Node(T value) : data(value), next(nullptr) {}
    };

    std::unique_ptr<Node> head;  // wskaźnik do głowy listy

public:
    // Konstruktor domyślny listy
    forward_list() : head(nullptr) {}

    // Metoda dodająca element na początku listy
    void push_front(T value) {
        auto new_node = std::make_unique<Node>(value);
        new_node->next = std::move(head);
        head = std::move(new_node);
    }

    // Metoda odwracająca kolejność elementów w liście
    void reverse() {
        std::unique_ptr<Node> prev = nullptr;
        std::unique_ptr<Node> current = std::move(head);

        while (current) {
            auto next = std::move(current->next);
            current->next = std::move(prev);
            prev = std::move(current);
            current = std::move(next);
        }
        head = std::move(prev);
    }

    // Metoda wyświetlająca zawartość listy
    void print() const {
        Node* current = head.get();
        while (current) {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << "\n";
    }
};

int main() {
    forward_list<int> flist;

    // Dodanie kilku elementów na początku listy
    flist.push_front(1);
    flist.push_front(2);
    flist.push_front(3);
    flist.push_front(4);
    flist.push_front(5);

    std::cout << "Lista przed odwróceniem: ";
    flist.print();

    // Odwracanie kolejności elementów
    flist.reverse();

    std::cout << "Lista po odwróceniu: ";
    flist.print();

    // Dodanie kolejnych elementów i ponowne testowanie
    flist.push_front(6);
    flist.push_front(7);

    std::cout << "Lista po dodaniu nowych elementów: ";
    flist.print();

    flist.reverse();

    std::cout << "Lista po ponownym odwróceniu: ";
    flist.print();

    return 0;
}