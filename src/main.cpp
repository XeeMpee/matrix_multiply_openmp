#include "matplotlibcpp.h"
#include "utils/matrix_operations.hpp"

namespace plt = matplotlibcpp;

int main()
{
    Matrix2D matrixA = matrix::generate2DMatrix(3, 4, 0.0, 100.0);
    Matrix2D matrixB = matrix::generate2DMatrix(4, 2, 200.0, 250.0);
    Matrix2D outputMatrix = matrix::multiply2DMatrixSerial(matrixA, matrixB);

    plt::figure(1);
    std::vector<double> x{1, 2, 4, 5};
    plt::plot(x,x, "r--");

    plt::figure(2);
    std::vector<double> xx{1, 2, 4, 5};
    plt::plot(xx, xx,"b");

    plt::show();
}