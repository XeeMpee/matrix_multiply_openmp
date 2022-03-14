#include "matrix_array.hpp"

MatrixArray::MatrixArray(uint32_t rows, uint32_t cols)
    : rows_{rows}
    , cols_{cols}
{
    matrix_ = new double*[rows];
    for (uint32_t row = 0; row < rows; row++)
    {
        matrix_[row] = new double[cols];
        for (uint32_t col = 0; col < cols; col++)
        {
            matrix_[row][col] = 0;
        }
    }
}

MatrixArray::~MatrixArray()
{
    for (uint32_t row = 0; row < rows_; row++)
    {
        delete[] matrix_[row];
    }
    delete[] matrix_;
}

double** MatrixArray::get()
{
    return matrix_;
}
