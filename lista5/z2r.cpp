#include <iostream>
#include <memory>
#include <utility>
#include <stdexcept>

namespace cpplab {

// Szablon klasy cpplab::unique_ptr
template <typename T>
class unique_ptr {
private:
    T* ptr;

public:
    // Konstruktor domyślny
    unique_ptr() : ptr(nullptr) {}

    // Konstruktor z wskaźnikiem
    explicit unique_ptr(T* p) : ptr(p) {}

    // Usuwanie kopii
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    // Przenoszenie
    unique_ptr(unique_ptr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            reset();
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Destruktor
    ~unique_ptr() {
        delete ptr;
    }

    // Dostęp do zarządzanego wskaźnika
    T* get() const { return ptr; }

    T& operator*() const {
        if (!ptr) throw std::runtime_error("Dereferencing nullptr");
        return *ptr;
    }

    T* operator->() const { return ptr; }

    // Zwolnienie zarządzanego wskaźnika
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    // Resetowanie wskaźnika
    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }

    // Sprawdzanie, czy wskaźnik jest niepusty
    explicit operator bool() const { return ptr != nullptr; }
};

// Klasa non0_ptr
template <typename T>
class non0_ptr {
private:
    T* ptr;

public:
    // Konstruktor
    explicit non0_ptr(T* p) : ptr(p) {
        if (!ptr) throw std::invalid_argument("non0_ptr cannot be null");
    }

    // Usuwanie kopii
    non0_ptr(const non0_ptr&) = delete;
    non0_ptr& operator=(const non0_ptr&) = delete;

    // Dostęp do zarządzanego wskaźnika
    T* get() const { return ptr; }
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
};

} // namespace cpplab

// Przykład użycia
int main() {
    // Przykład cpplab::unique_ptr
    cpplab::unique_ptr<int> uptr(new int(42));
    std::cout << "Value: " << *uptr << std::endl;

    // Przykład cpplab::non0_ptr
    try {
        cpplab::non0_ptr<int> nptr(nullptr); // To spowoduje wyjątek
    } catch (const std::invalid_argument& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    int value = 10;
    cpplab::non0_ptr<int> nptr(&value);
    std::cout << "Non0_ptr Value: " << *nptr << std::endl;

    return 0;
}
