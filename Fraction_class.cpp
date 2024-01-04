#include <iostream>

class Fraction {
private:
    int numerator;
    int denominator;

public:
    Fraction(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        simplify();
    }

    int getNumerator() const {
        return numerator;
    }

    void setNumerator(int num) {
        numerator = num;
        simplify();
    }

    int getDenominator() const {
        return denominator;
    }

    void setDenominator(int denom) {
        if (denom != 0) {
            denominator = denom;
            simplify();
        } else {
            std::cerr << "Error: Denominator cannot be zero!" << std::endl;
        }
    }

    Fraction& operator+=(const Fraction& other) {
        numerator = numerator * other.denominator + other.numerator * denominator;
        denominator *= other.denominator;
        simplify();
        return *this;
    }

    Fraction& operator-=(const Fraction& other) {
        numerator = numerator * other.denominator - other.numerator * denominator;
        denominator *= other.denominator;
        simplify();
        return *this;
    }

    Fraction& operator*=(const Fraction& other) {
        numerator *= other.numerator;
        denominator *= other.denominator;
        simplify();
        return *this;
    }

    Fraction& operator/=(const Fraction& other) {
        if (other.numerator != 0) {
            numerator *= other.denominator;
            denominator *= other.numerator;
            simplify();
        } else {
            std::cerr << "Error: Division by zero!" << std::endl;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& frac) {
        os << frac.numerator << "/" << frac.denominator;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Fraction& frac) {
        is >> frac.numerator >> frac.denominator;
        frac.simplify();
        return is;
    }

    operator double() const {
        return static_cast<double>(numerator) / denominator;
    }

private:
    int gcd(int a, int b) const {
        return b == 0 ? a : gcd(b, a % b);
    }

    void simplify() {
        int common = gcd(numerator, denominator);
        numerator /= common;
        denominator /= common;

        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }
};

int main() {
    Fraction a(2, 3);
    Fraction b(4, 5);

    std::cout << "Fraction a: " << a << std::endl;
    std::cout << "Fraction b: " << b << std::endl;

    Fraction c = a + b;
    std::cout << "a + b = " << c << " (as double: " << static_cast<double>(c) << ")" << std::endl;

    Fraction d = a - b;
    std::cout << "a - b = " << d << " (as double: " << static_cast<double>(d) << ")" << std::endl;

    Fraction e = a * b;
    std::cout << "a * b = " << e << " (as double: " << static_cast<double>(e) << ")" << std::endl;

    Fraction f = a / b;
    std::cout << "a / b = " << f << " (as double: " << static_cast<double>(f) << ")" << std::endl;

    return 0;
}
