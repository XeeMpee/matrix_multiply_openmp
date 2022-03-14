#pragma once
#include <vector>
#include <functional>

class MatrixArray
{
public:
    MatrixArray(uint32_t rows, uint32_t cols);
    ~MatrixArray();

    double** get();

private:
    double** matrix_;
    uint32_t rows_;
    uint32_t cols_;
};

class MatrixMultiplicationOutput;
class Matrix : public std::vector<std::vector<double>>
{
public:
    static Matrix generate(uint32_t rows, uint32_t cols, double min, double max);

    static MatrixMultiplicationOutput multiplyMatrixSerial(const Matrix& matrixA, const Matrix& matrixB);
    static MatrixMultiplicationOutput multiplyMatrixParallelInnerLoop(const Matrix& matrixA, const Matrix& matrixB);
    static MatrixMultiplicationOutput multiplyMatrixParallelOuterLoop(const Matrix& matrixA, const Matrix& matrixB);


private:
    static Matrix fromArray(double** array, uint32_t rows, uint32_t cols);

    static MatrixMultiplicationOutput multiplyMatrix(
        const Matrix& matrixA,
        const Matrix& matrixB,
        std::function<void(const Matrix& matrixA, const Matrix& matrixB, MatrixArray& matrix, uint32_t aRows, uint32_t aCols, uint32_t bCols)> multiplication);

    bool isValid();
    bool isMultiplable(const Matrix& matrixB);
};
