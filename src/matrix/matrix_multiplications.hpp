#include "i_matrix_multiplications.hpp"

class SerialMatrixMultiplications : public IMatrixMultiplications
{
public:
    void operator()(const Matrix& matrixA, const Matrix& matrixB, MatrixArray& matrix, uint32_t aRows, uint32_t aCols, uint32_t bCols) override;
};

class ParallelInnerLoopMatrixMultiplications : public IMatrixMultiplications
{
public:
    void operator()(const Matrix& matrixA, const Matrix& matrixB, MatrixArray& matrix, uint32_t aRows, uint32_t aCols, uint32_t bCols) override;
};

class ParallelOuterLoopMatrixMultiplications : public IMatrixMultiplications
{
public:
    void operator()(const Matrix& matrixA, const Matrix& matrixB, MatrixArray& matrix, uint32_t aRows, uint32_t aCols, uint32_t bCols) override;
};