#include <omp.h>
#include "matrix_multiplications.hpp"
#include "matrix/matrix.hpp"
#include "matrix/matrix_array.hpp"


void SerialMatrixMultiplications::operator()(const Matrix& matrixA, const Matrix& matrixB, MatrixArray& matrix, uint32_t aRows, uint32_t aCols, uint32_t bCols)
{
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
}


void ParallelInnerLoopMatrixMultiplications::operator()(
    const Matrix& matrixA, const Matrix& matrixB, MatrixArray& matrix, uint32_t aRows, uint32_t aCols, uint32_t bCols)
{
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
}


void ParallelOuterLoopMatrixMultiplications::operator()(
    const Matrix& matrixA, const Matrix& matrixB, MatrixArray& matrix, uint32_t aRows, uint32_t aCols, uint32_t bCols)
{
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
}
