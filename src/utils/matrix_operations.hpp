#pragma once
#include <vector>
#include <cstdint>

using Matrix2D = std::vector<std::vector<double>>;

namespace matrix {

Matrix2D generate2DMatrix(uint32_t rows, uint32_t cols, double min, double max);
bool isMatrix2DValid(const Matrix2D& matrix);
bool isMatrix2DMultiplable(const Matrix2D& matrixA, const Matrix2D& matrixB);
Matrix2D fromArray(double** array);

Matrix2D multiply2DMatrixSerial(const Matrix2D& matrixA, const Matrix2D& matrixB);
Matrix2D multiply2DMatrixParallel(const Matrix2D& matrixA, const Matrix2D& matrixB);

} // namespace matrix
