#include <iostream>
#include <memory>
#include <vector>

namespace cpplab {

// Szablon klasy allocator
template <typename T>
class allocator {
public:
    using value_type = T;

    // Alokuje pamięć na n elementów typu T
    T* allocate(std::size_t n) {
        if (n == 0) {
            return nullptr;
        }
        T* ptr = static_cast<T*>(::operator new(n * sizeof(T)));
        return ptr;
    }

    // Zwalnia pamięć wskazaną przez p
    void deallocate(T* p, std::size_t n) {
        if (p) {
            ::operator delete(static_cast<void*>(p));
        }
    }
};

} // namespace cpplab

int main() {
    cpplab::allocator<int> alloc;

    // Wyświetlenie typu value_type
    std::cout << typeid(cpplab::allocator<int>::value_type).name() << std::endl;

    // Alokacja i dealokacja pamięci
    cpplab::allocator<int>::value_type* p_test = alloc.allocate(1);
    *p_test = 3;
    std::cout << *p_test << std::endl;
    alloc.deallocate(p_test, 1);

    // Test z std::vector
    std::vector<int, cpplab::allocator<int>> v;
    v.push_back(13);
    v.push_back(23);

    std::cout << *(v.end() - 1) << std::endl;

    return 0;
}
