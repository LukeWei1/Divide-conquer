#include <array>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <vector>

class Matrix {

private:
    size_t rows;
    size_t cols;
    std::vector<double> data;  // row-major: element (r, c) is data[r * cols + c]

    void checkIndex(size_t r, size_t c) const {
        if (r >= rows || c >= cols) {
            throw std::out_of_range("Matrix index out of range");
        }
    }

public:
    // Create an n x n square matrix filled with zeros.
    Matrix(size_t n) : rows(n), cols(n), data(n * n, 0.0) {}

    size_t numRows() const { return rows; }
    size_t numCols() const { return cols; }

    double get(size_t r, size_t c) const {
        checkIndex(r, c);
        return data[r * cols + c];
    }

    void set(size_t r, size_t c, double value) {
        checkIndex(r, c);
        data[r * cols + c] = value;
    }

    // Split into four (n/2) x (n/2) quadrants:
    // {top-left, top-right, bottom-left, bottom-right}
    std::array<Matrix, 4> split() const {
        if (rows != cols || rows % 2 != 0) {
            throw std::logic_error("split() requires a square matrix of even size");
        }
        size_t h = rows / 2;
        Matrix a11(h), a12(h), a21(h), a22(h);
        for (size_t r = 0; r < h; r++) {
            for (size_t c = 0; c < h; c++) {
                a11.set(r, c, get(r, c));
                a12.set(r, c, get(r, c + h));
                a21.set(r, c, get(r + h, c));
                a22.set(r, c, get(r + h, c + h));
            }
        }
        return {a11, a12, a21, a22};
    }

    void print() const {
        for (size_t r = 0; r < rows; r++) {
            for (size_t c = 0; c < cols; c++) {
                std::cout << get(r, c) << "\t";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    Matrix m(4);
    double v = 1;
    for (size_t r = 0; r < 4; r++)
        for (size_t c = 0; c < 4; c++)
            m.set(r, c, v++);

    std::cout << "Original:\n";
    m.print();

    std::array<Matrix, 4> q = m.split();
    const char* names[] = {"Top-left", "Top-right", "Bottom-left", "Bottom-right"};
    for (int i = 0; i < 4; i++) {
        std::cout << "\n" << names[i] << ":\n";
        q[i].print();
    }
    return 0;
}