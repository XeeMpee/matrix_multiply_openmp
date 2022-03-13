#pragma once
#include <vector>
#include <cstdint>
#include "types/types.hpp"

namespace matrix {

Matrix2D generate2DMatrix(uint32_t rows, uint32_t cols, double min, double max);
bool isMatrix2DValid(const Matrix2D& matrix);
bool isMatrix2DMultiplable(const Matrix2D& matrixA, const Matrix2D& matrixB);
Matrix2D fromArray(double** array);

Matrix2DMultiplicationOutput multiply2DMatrixSerial(const Matrix2D& matrixA, const Matrix2D& matrixB);
Matrix2DMultiplicationOutput multiply2DMatrixParallelInnerLoop(const Matrix2D& matrixA, const Matrix2D& matrixB);
Matrix2DMultiplicationOutput multiply2DMatrixParallelOuterLoop(const Matrix2D& matrixA, const Matrix2D& matrixB);

} // namespace matrix
