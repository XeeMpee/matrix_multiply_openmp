#pragma once
#include <cstdint>

class MatrixArray
{
public:
    MatrixArray(uint32_t rows, uint32_t cols);
    ~MatrixArray();

    double** get();

private:
    double** matrix_;
    uint32_t rows_;
    uint32_t cols_;
};
