#pragma once
#include <vector>
#include <functional>

#include "matrix/i_matrix_multiplications.hpp"
#include "matrix/matrix_array.hpp"

class MatrixMultiplicationOutput;

class Matrix : public std::vector<std::vector<double>>
{
public:
    static Matrix generate(uint32_t rows, uint32_t cols, double min, double max);
    static MatrixMultiplicationOutput multiply(IMatrixMultiplications&& strategy, const Matrix& matrixA, const Matrix& matrixB);

private:
    static Matrix fromArray(double** array, uint32_t rows, uint32_t cols);

    bool isValid();
    bool isMultiplable(const Matrix& matrixB);
};
