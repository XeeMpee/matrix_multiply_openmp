#include <random>
#include <stdexcept>
#include <functional>
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


Matrix2DMultiplicationOutput multiply2DMatrix(
    const Matrix2D& matrixA,
    const Matrix2D& matrixB,
    std::function<void(const Matrix2D& matrixA, const Matrix2D& matrixB, Matrix2DArray& matrix, uint32_t aRows, uint32_t aCols, uint32_t bCols)> multiplication)
{
    if (!isMatrix2DMultiplable(matrixA, matrixB))
    {
        throw std::runtime_error("Multiply matrix failed!");
    }

    uint32_t aRows = matrixA.size();
    uint32_t aCols = matrixA.front().size();
    uint32_t bCols = matrixB.front().size();

    Duration duration;
    Matrix2DArray matrix{aRows, bCols};

    uint32_t rowIndex{0};
    uint32_t columnIndex{0};

    duration = omp_get_wtime();
    multiplication(matrixA, matrixB, matrix, aRows, aCols, bCols);
    duration = omp_get_wtime() - duration;

    return std::make_tuple(fromArray(matrix.get()), duration);
}

Matrix2DMultiplicationOutput multiply2DMatrixSerial(const Matrix2D& matrixA, const Matrix2D& matrixB)
{
    return multiply2DMatrix(
        matrixA, matrixB, [](const Matrix2D& matrixA, const Matrix2D& matrixB, Matrix2DArray& matrix, uint32_t aRows, uint32_t aCols, uint32_t bCols) {
            for (int row = 0; row < aRows; row++)
            {
                for (int col = 0; col < bCols; col++)
                {
                    for (int inner = 0; inner < aCols; inner++)
                    {
                        matrix.get()[row][col] += matrixA[row][inner] * matrixB[inner][col];
                    }
                }
            }
        });
}


Matrix2DMultiplicationOutput multiply2DMatrixParallelInnerLoop(const Matrix2D& matrixA, const Matrix2D& matrixB)
{
    return multiply2DMatrix(
        matrixA, matrixB, [](const Matrix2D& matrixA, const Matrix2D& matrixB, Matrix2DArray& matrix, uint32_t aRows, uint32_t aCols, uint32_t bCols) {
            for (int row = 0; row < aRows; row++)
            {
#pragma omp parallel for firstprivate(row)
                for (int col = 0; col < bCols; col++)
                {
                    for (int inner = 0; inner < aCols; inner++)
                    {
                        matrix.get()[row][col] += matrixA[row][inner] * matrixB[inner][col];
                    }
                }
            }
        });
}

Matrix2DMultiplicationOutput multiply2DMatrixParallelOuterLoop(const Matrix2D& matrixA, const Matrix2D& matrixB)
{
    return multiply2DMatrix(
        matrixA, matrixB, [](const Matrix2D& matrixA, const Matrix2D& matrixB, Matrix2DArray& matrix, uint32_t aRows, uint32_t aCols, uint32_t bCols) {
#pragma omp parallel for
            for (int row = 0; row < aRows; row++)
            {
                for (int col = 0; col < bCols; col++)
                {
                    for (int inner = 0; inner < aCols; inner++)
                    {
                        matrix.get()[row][col] += matrixA[row][inner] * matrixB[inner][col];
                    }
                }
            }
        });
}

} // namespace name
