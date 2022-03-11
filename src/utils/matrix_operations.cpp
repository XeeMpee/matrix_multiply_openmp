#include <random>
#include <stdexcept>
#include <omp.h>

#include "matrix_operations.hpp"

namespace matrix {

struct Matrix2DArray
{
    Matrix2DArray(uint32_t rows, uint32_t cols)
        : rows_{rows}
        , cols_{cols}
    {
        matrix_ = new double*[rows];
        for (uint32_t row = 0; row < rows; row++)
            matrix_[row] = new double[cols];
    }

    ~Matrix2DArray()
    {
        for (uint32_t row = 0; row < rows_; row++)
        {
            delete[] matrix_[row];
        }
        delete[] matrix_;
    }

    double** get()
    {
        return matrix_;
    }

private:
    double** matrix_;
    uint32_t rows_;
    uint32_t cols_;
};


Matrix2D generate2DMatrix(uint32_t rows, uint32_t cols, double min, double max)
{
    std::random_device randomDevice;
    std::mt19937 generator{randomDevice()};
    std::uniform_real_distribution<> distribution{min, max};

    Matrix2D matrix{};

    for (uint32_t r = 0; r < rows; r++)
    {
        std::vector<double> row{};
        for (uint32_t c = 0; c < cols; c++)
        {
            row.push_back(distribution(generator));
        }
        matrix.push_back(row);
    }

    return matrix;
}


bool isMatrix2DValid(const Matrix2D& matrix)
{
    uint32_t rowSize = matrix.front().size();
    for (const auto& row : matrix)
    {
        if (row.size() != rowSize)
        {
            return false;
        }
    }
    return true;
}


bool isMatrix2DMultiplable(const Matrix2D& matrixA, const Matrix2D& matrixB)
{
    return isMatrix2DValid(matrixA) && isMatrix2DValid(matrixB) && matrixA.front().size() == matrixB.size();
}


Matrix2D fromArray(double** array)
{
    uint32_t rows = sizeof(array) / sizeof(array[0]);
    uint32_t cols = sizeof(array[0]) / sizeof(array[0][0]);
    std::vector<std::vector<double>> matrix{};
    for (uint32_t row = 0; row < rows; row++)
    {
        matrix.push_back(std::vector<double>{});
        for (uint32_t col = 0; col < cols; col++)
        {
            matrix[row].push_back(array[row][col]);
        }
    }
    return matrix;
}


Matrix2D multiply2DMatrixSerial(const Matrix2D& matrixA, const Matrix2D& matrixB)
{
    if (!isMatrix2DMultiplable(matrixA, matrixB))
    {
        throw std::runtime_error("Multiply matrix failed!");
    }

    uint32_t matrixARows = matrixA.size();
    uint32_t matrixACols = matrixA.front().size();
    uint32_t matrixBRows = matrixB.size();
    uint32_t matrixBCols = matrixB.front().size();

    Matrix2DArray matrix{matrixARows, matrixBCols};

    uint32_t rowIndex{0};
    uint32_t columnIndex{0};
    for (rowIndex; rowIndex < matrixARows; rowIndex++)
    {
        uint32_t value{0};
        for (columnIndex; columnIndex < matrixBCols; columnIndex++)
        {
            value += matrixA[rowIndex][columnIndex] * matrixB[columnIndex][rowIndex];
        }
        matrix.get()[rowIndex][columnIndex] = value;
        value = 0;
    }

    return fromArray(matrix.get());
}

Matrix2D multiply2DMatrixParallel(const Matrix2D& matrixA, const Matrix2D& matrixB)
{
    if (!isMatrix2DMultiplable(matrixA, matrixB))
    {
        throw std::runtime_error("Multiply matrix failed!");
    }

    uint32_t matrixARows = matrixA.size();
    uint32_t matrixACols = matrixA.front().size();
    uint32_t matrixBRows = matrixB.size();
    uint32_t matrixBCols = matrixB.front().size();

    Matrix2DArray matrix{matrixARows, matrixBCols};

    uint32_t rowIndex{0};
    uint32_t columnIndex{0};
    for (rowIndex; rowIndex < matrixARows; rowIndex++)
    {
        uint32_t value{0};
        for (columnIndex; columnIndex < matrixBCols; columnIndex++)
        {
            value += matrixA[rowIndex][columnIndex] * matrixB[columnIndex][rowIndex];
        }
        matrix.get()[rowIndex][columnIndex] = value;
        value = 0;
    }

    return fromArray(matrix.get());
}

} // namespace name
