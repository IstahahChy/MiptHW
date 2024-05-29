#include <iostream>
#include <utility>

// Base case: no arguments to print
void print() {
    std::cout << std::endl;
}

//function to handle multiple arguments
template <typename T, typename... Args>
void print(T&& firstArg, Args&&... args) {
    // Print the first argument
    std::cout << std::forward<T>(firstArg);

    // If more arguments, print a separator
    if (sizeof...(args) > 0) {
        std::cout << ", ";
    }


    print(std::forward<Args>(args)...);
}

int main() {
    int x = 10;
    double y = 20.5;
    std::string str = "Hello";

    // Example usage
    print(x, y, str);
    print(42);
    print("This", "is", "a", "test");
    print("Another test with", 123, 45.67, "and a string");

    return 0;
}

