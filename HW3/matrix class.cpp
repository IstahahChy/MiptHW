#include <iostream>
#include <vector>
#include <cassert>
#include <cmath> // Include <cmath> for sqrt

template<typename T, size_t Rows, size_t Cols>
class Matrix {
private:
    std::vector<std::vector<T>> data;

public:
    Matrix() {
        data.resize(Rows, std::vector<T>(Cols));
    }

    // Function to transpose the matrix
    Matrix<T, Cols, Rows> Transpose() const {
        Matrix<T, Cols, Rows> transposed;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                transposed[j][i] = data[i][j];
            }
        }
        return transposed;
    }

    // Overloaded operator to access elements
    std::vector<T>& operator[](size_t index) {
        assert(index < Rows);
        return data[index];
    }

    const std::vector<T>& operator[](size_t index) const {
        assert(index < Rows);
        return data[index];
    }

    // Overloaded arithmetic operators
    Matrix<T, Rows, Cols> operator+(const Matrix<T, Rows, Cols>& other) const {
        Matrix<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result[i][j] = data[i][j] + other[i][j];
            }
        }
        return result;
    }

    Matrix<T, Rows, Cols> operator-(const Matrix<T, Rows, Cols>& other) const {
        Matrix<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result[i][j] = data[i][j] - other[i][j];
            }
        }
        return result;
    }

    template<size_t OtherCols>
    Matrix<T, Rows, OtherCols> operator*(const Matrix<T, Cols, OtherCols>& other) const {
        Matrix<T, Rows, OtherCols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < OtherCols; ++j) {
                for (size_t k = 0; k < Cols; ++k) {
                    result[i][j] += data[i][k] * other[k][j];
                }
            }
        }
        return result;
    }

    Matrix<T, Rows, Cols> operator*(const T& scalar) const {
        Matrix<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }
};

// Specialization for vector (n, 1) with 'int' type inside
template<size_t Rows>
class Matrix<int, Rows, 1> {
private:
    std::vector<int> data;

public:
    // Constructor
    Matrix() : data(Rows) {}

    // Overloaded operator to access elements
    int& operator[](size_t index) {
        assert(index < Rows);
        return data[index];
    }

    const int& operator[](size_t index) const {
        assert(index < Rows);
        return data[index];
    }

    // Method to calculate L2 norm of the vector
    double Norm() const {
        double norm = 0.0;
        for (size_t i = 0; i < Rows; ++i) {
            norm += data[i] * data[i];
        }
        return std::sqrt(norm);
    }
};

int main() {
    // mat1 with values 
    Matrix<int, 2, 2> mat1;
    mat1[0][0] = 1;
    mat1[0][1] = 3;
    mat1[1][0] = 5;
    mat1[1][1] = 7;

    // mat2 with values 
    Matrix<int, 2, 2> mat2;
    mat2[0][0] = 2;
    mat2[0][1] = 4;
    mat2[1][0] = 6;
    mat2[1][1] = 8;

    // Example usage of operations
    auto mat3 = mat1 + mat2;
    auto mat4 = mat1 - mat2;
    auto mat5 = mat1 * mat2;
    auto mat6 = mat1 * 2;

    // Example usage of transpose
    auto mat1_transpose = mat1.Transpose();

    // Initialize vec with values from 1 to 3
    Matrix<int, 3, 1> vec;
    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;

    double norm = vec.Norm();

    // Print results
    std::cout << "Result of mat1 + mat2:\n";
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            std::cout << mat3[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Result of mat1 - mat2:\n";
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            std::cout << mat4[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Result of mat1 * mat2:\n";
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            std::cout << mat5[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Result of mat1 * 2:\n";
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            std::cout << mat6[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Transpose of mat1:\n";
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            std::cout << mat1_transpose[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Norm of vec: " << norm << std::endl;

    return 0;
}

