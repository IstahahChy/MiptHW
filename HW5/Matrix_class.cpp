#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

class Matrix {
public:
    Matrix(size_t rows, size_t cols) 
        : rows_(rows), cols_(cols), data_(new std::vector<std::vector<int>>(rows, std::vector<int>(cols))) {}

    Matrix(const Matrix& other) 
        : rows_(other.rows_), cols_(other.cols_), data_(new std::vector<std::vector<int>>(*other.data_)) {}

    Matrix(Matrix&& other) noexcept
        : rows_(other.rows_), cols_(other.cols_), data_(std::move(other.data_)) {
        other.rows_ = 0;
        other.cols_ = 0;
    }

    Matrix& operator=(Matrix other) {
        swap(*this, other);
        return *this;
    }

    friend void swap(Matrix& first, Matrix& second) noexcept {
        using std::swap;
        swap(first.rows_, second.rows_);
        swap(first.cols_, second.cols_);
        swap(first.data_, second.data_);
    }

    int& operator()(size_t row, size_t col) {
        return (*data_)[row][col];
    }

    int operator()(size_t row, size_t col) const {
        return (*data_)[row][col];
    }

    Matrix operator+(const Matrix& other) const {
        checkDimensionsForAdditionOrSubtraction(other);
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result(i, j) = (*data_)[i][j] + (*other.data_)[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other) const {
        checkDimensionsForAdditionOrSubtraction(other);
        Matrix result(rows_, cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                result(i, j) = (*data_)[i][j] - (*other.data_)[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        checkDimensionsForMultiplication(other);
        Matrix result(rows_, other.cols_);
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < other.cols_; ++j) {
                result(i, j) = 0;
                for (size_t k = 0; k < cols_; ++k) {
                    result(i, j) += (*data_)[i][k] * (*other.data_)[k][j];
                }
            }
        }
        return result;
    }

    void print() const {
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                std::cout << (*data_)[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    size_t getRows() const { return rows_; }
    size_t getCols() const { return cols_; }

private:
    size_t rows_, cols_;
    std::unique_ptr<std::vector<std::vector<int>>> data_;

    void checkDimensionsForAdditionOrSubtraction(const Matrix& other) const {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrices dimensions do not match for addition or subtraction.");
        }
    }

    void checkDimensionsForMultiplication(const Matrix& other) const {
        if (cols_ != other.rows_) {
            throw std::invalid_argument("Matrices dimensions do not match for multiplication.");
        }
    }
};

//matrix transpose
auto transpose = [](const Matrix& mat) -> Matrix {
    Matrix result(mat.getCols(), mat.getRows());
    for (size_t i = 0; i < mat.getRows(); ++i) {
        for (size_t j = 0; j < mat.getCols(); ++j) {
            result(j, i) = mat(i, j);
        }
    }
    return result;
};

//trace of a square matrix
template<typename T>
int trace(const T& mat) {
    if (mat.getRows() != mat.getCols()) {
        throw std::invalid_argument("Matrix must be square to calculate the trace.");
    }
    int sum = 0;
    for (size_t i = 0; i < mat.getRows(); ++i) {
        sum += mat(i, i);
    }
    return sum;
}

int main() {
    // Example usage
    Matrix mat1(2, 2);
    mat1(0, 0) = 1; mat1(0, 1) = 2;
    mat1(1, 0) = 3; mat1(1, 1) = 4;

    Matrix mat2(2, 2);
    mat2(0, 0) = 5; mat2(0, 1) = 6;
    mat2(1, 0) = 7; mat2(1, 1) = 8;

    std::cout << "Matrix 1:" << std::endl;
    mat1.print();
    std::cout << "Matrix 2:" << std::endl;
    mat2.print();

    Matrix result = mat1 + mat2;
    std::cout << "Addition:" << std::endl;
    result.print();

    result = mat1 - mat2;
    std::cout << "Subtraction:" << std::endl;
    result.print();

    result = mat1 * mat2;
    std::cout << "Multiplication:" << std::endl;
    result.print();

    Matrix transposed = transpose(mat1);
    std::cout << "Transpose of Matrix 1:" << std::endl;
    transposed.print();

    int mat1_trace = trace(mat1);
    std::cout << "Trace of Matrix 1: " << mat1_trace << std::endl;

    return 0;
}
