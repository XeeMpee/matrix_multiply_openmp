#include <omp.h>
#include <random>
#include <stdexcept>

#include "matrix/matrix_multiplication_output.hpp"


Matrix Matrix::generate(uint32_t rows, uint32_t cols, double min, double max)
{
    std::random_device randomDevice;
    std::mt19937 generator{randomDevice()};
    std::uniform_real_distribution<> distribution{min, max};

    Matrix matrix{};

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


MatrixMultiplicationOutput Matrix::multiply(IMatrixMultiplications&& multiplication, const Matrix& matrixA, const Matrix& matrixB)
{
    if (!const_cast<Matrix&>(matrixA).isMultiplable(matrixB))
    {
        throw std::runtime_error("Multiply matrix failed!");
    }

    uint32_t aRows = matrixA.size();
    uint32_t aCols = matrixA.front().size();
    uint32_t bCols = matrixB.front().size();

    ProcessingDuration duration;
    MatrixArray matrix{aRows, bCols};

    uint32_t rowIndex{0};
    uint32_t columnIndex{0};

    duration = omp_get_wtime();
    multiplication(matrixA, matrixB, matrix, aRows, aCols, bCols);
    duration = omp_get_wtime() - duration;

    return MatrixMultiplicationOutput(fromArray(matrix.get(), aRows, bCols), duration);
}


Matrix Matrix::fromArray(double** array, uint32_t rows, uint32_t cols)
{
    Matrix matrix{};
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

bool Matrix::isValid()
{
    uint32_t rowSize = front().size();
    for (const auto& row : *this)
    {
        if (row.size() != rowSize)
        {
            return false;
        }
    }
    return true;
}

bool Matrix::isMultiplable(const Matrix& matrixB)
{
    return isValid() && const_cast<Matrix&>(matrixB).isValid() && front().size() == matrixB.size();
}
