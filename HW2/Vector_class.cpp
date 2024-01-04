#include <iostream>
#include <vector>

class Vector {
private:
    std::vector<double> elements;

public:
    Vector(const std::vector<double>& elems = {}) : elements(elems) {}

    // Explicitly declare and define copy constructor
    Vector(const Vector& other) : elements(other.elements) {}

    std::vector<double> getElements() const {
        return elements;
    }

    void setElements(const std::vector<double>& elems) {
        elements = elems;
    }

    Vector operator+(const Vector& other) const {
        if (elements.size() == other.elements.size()) {
            Vector result(elements);
            for (size_t i = 0; i < elements.size(); ++i) {
                result.elements[i] += other.elements[i];
            }
            return result;
        } else {
            std::cerr << "Error: Vectors must have the same size for addition!" << std::endl;
            return *this;
        }
    }

    Vector operator-(const Vector& other) const {
        if (elements.size() == other.elements.size()) {
            Vector result(elements);
            for (size_t i = 0; i < elements.size(); ++i) {
                result.elements[i] -= other.elements[i];
            }
            return result;
        } else {
            std::cerr << "Error: Vectors must have the same size for subtraction!" << std::endl;
            return *this;
        }
    }

    Vector operator*(const double scalar) const {
        Vector result(elements);
        for (double& element : result.elements) {
            element *= scalar;
        }
        return result;
    }

    double operator*(const Vector& other) const {
        if (elements.size() == other.elements.size()) {
            double result = 0.0;
            for (size_t i = 0; i < elements.size(); ++i) {
                result += elements[i] * other.elements[i];
            }
            return result;
        } else {
            std::cerr << "Error: Vectors must have the same size for dot product!" << std::endl;
            return 0.0;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
        os << "(";
        for (size_t i = 0; i < vec.elements.size(); ++i) {
            os << vec.elements[i];
            if (i < vec.elements.size() - 1) {
                os << ", ";
            }
        }
        os << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vector& vec) {
        std::vector<double> elems;
        double element;
        char delimiter;

        is >> delimiter; // Read '('
        while (is >> element) {
            elems.push_back(element);
            is >> delimiter; // Read ',' or ')'
            if (delimiter == ')') {
                break;
            }
        }

        vec.setElements(elems);
        return is;
    }

    Vector& operator=(const Vector& other) {
        elements = other.elements;
        return *this;
    }
};

int main() {
    Vector v1({1.0, 2.0, 3.0});
    Vector v2({4.0, 5.0, 6.0});

    std::cout << "Vector v1: " << v1 << std::endl;
    std::cout << "Vector v2: " << v2 << std::endl;

    Vector v3 = v1 + v2;
    std::cout << "v1 + v2 = " << v3 << std::endl;

    Vector v4 = v1 - v2;
    std::cout << "v1 - v2 = " << v4 << std::endl;

    Vector v5 = v1 * 2.5;
    std::cout << "v1 * 2.5 = " << v5 << std::endl;

    double dotProduct = v1 * v2;
    std::cout << "v1 * v2 (dot product) = " << dotProduct << std::endl;

    return 0;
}
