#pragma once
#include <cstdint>

class Matrix;
class MatrixArray;
class IMatrixMultiplications
{
public:
    virtual void operator()(const Matrix& matrixA, const Matrix& matrixB, MatrixArray& matrix, uint32_t aRows, uint32_t aCols, uint32_t bCols) = 0;
};