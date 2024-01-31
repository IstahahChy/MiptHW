#include <iostream>
#include <cmath> // Include <cmath> for pow function

// Base case: if k = 0, the sum is 0
template<int n, int k>
struct SumSequence {
    static const int value = SumSequence<n, k - 1>::value + std::pow(n, k);
};

// Base case: if k = 0, the sum is 0
template<int n>
struct SumSequence<n, 0> {
    static const int value = 0;
};

int main() {
    constexpr int n = 4;
    constexpr int k = 5;

    // Calculate the sum of the sequence F(n, k) at compile time
    constexpr int sum = SumSequence<n, k>::value;

    std::cout << "Sum of sequence F(" << n << ", " << k << ") = " << sum << std::endl;

    return 0;
}
