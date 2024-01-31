#include <iostream>
#include <type_traits> // for is_same

template<typename T>
struct TrueType {
    using type = T;
};

template<typename T>
struct TrueType<T*> : TrueType<T> {};

template<typename T>
struct TrueType<const T> : TrueType<T> {};

template<typename T>
struct TrueType<T&> : TrueType<T> {};

template<typename T, size_t N>
struct TrueType<T[N]> : TrueType<T> {};

// TestExample to test the behavior of TrueType
template<typename T, typename Expected>
struct TestExample {
    static constexpr const char* value = std::is_same_v<typename TrueType<T>::type, Expected> ? "True" : "False";
};

int main() {
    // Test Example
    std::cout << "Test Example: " << std::endl;
    std::cout << "int: " << TestExample<int, int>::value << std::endl; // True
    std::cout << "const char*: " << TestExample<const char*, const char*>::value << std::endl; // False
    std::cout << "int&: " << TestExample<int&, int>::value << std::endl; // True
    std::cout << "int*: " << TestExample<int*, int>::value << std::endl; // True
    std::cout << "int[5]: " << TestExample<int[5], int>::value << std::endl; // True

    return 0;
}
