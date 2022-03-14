#include <spdlog/spdlog.h>
#include <matplotlibcpp.h>

#include "matrix/matrix.hpp"
#include "matrix/matrix_multiplication_output.hpp"
#include "utils/matplotlibcpp_helpers.hpp"

namespace plt = matplotlibcpp;

int main()
{
    Matrix matrixASmall = Matrix::generate(10, 10, 0.0, 100.0);
    Matrix matrixBSmall = Matrix::generate(10, 10, 200.0, 250.0);

    spdlog::info("small matrixes multiplications (operation may take a while)");
    MatrixMultiplicationOutput serialOutputMatrixSmall = Matrix::multiplyMatrixSerial(matrixASmall, matrixBSmall);
    MatrixMultiplicationOutput innerLoopParallelInnerMatrixSmall = Matrix::multiplyMatrixParallelInnerLoop(matrixASmall, matrixBSmall);
    MatrixMultiplicationOutput outerLoopParallelOutputMatrixSmall = Matrix::multiplyMatrixParallelOuterLoop(matrixASmall, matrixBSmall);
    MatrixMultiplicationOutput::equal("small", {serialOutputMatrixSmall, innerLoopParallelInnerMatrixSmall, outerLoopParallelOutputMatrixSmall});

    Matrix matrixMediumA = Matrix::generate(100, 100, 0.0, 100.0);
    Matrix matrixMediumB = Matrix::generate(100, 100, 200.0, 250.0);

    spdlog::info("medium matrixes multiplications (operation may take a while)");
    MatrixMultiplicationOutput serialOutputMatrixMedium = Matrix::multiplyMatrixSerial(matrixMediumA, matrixMediumB);
    MatrixMultiplicationOutput innerLoopParallelInnerMatrixMedium = Matrix::multiplyMatrixParallelInnerLoop(matrixMediumA, matrixMediumB);
    MatrixMultiplicationOutput outerLoopParallelOutputMatrixMedium = Matrix::multiplyMatrixParallelOuterLoop(matrixMediumA, matrixMediumB);
    MatrixMultiplicationOutput::equal("medium", {serialOutputMatrixMedium, innerLoopParallelInnerMatrixMedium, outerLoopParallelOutputMatrixMedium});

    Matrix matrixLargeA = Matrix::generate(500, 500, 0.0, 100.0);
    Matrix matrixLargeB = Matrix::generate(500, 500, 200.0, 250.0);

    spdlog::info("large matrixes multiplications (operation may take a while)");
    MatrixMultiplicationOutput serialOutputMatrixLarge = Matrix::multiplyMatrixSerial(matrixLargeA, matrixLargeB);
    MatrixMultiplicationOutput innerLoopParallelInnerMatrixLarge = Matrix::multiplyMatrixParallelInnerLoop(matrixLargeA, matrixLargeB);
    MatrixMultiplicationOutput outerLoopParallelOutputMatrixLarge = Matrix::multiplyMatrixParallelOuterLoop(matrixLargeA, matrixLargeB);
    MatrixMultiplicationOutput::equal("large", {serialOutputMatrixLarge, innerLoopParallelInnerMatrixLarge, outerLoopParallelOutputMatrixLarge});

    plt::figure(1);
    std::vector<double> indx = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<double> data = {
        serialOutputMatrixSmall.duration,
        innerLoopParallelInnerMatrixSmall.duration,
        outerLoopParallelOutputMatrixSmall.duration,
        serialOutputMatrixMedium.duration,
        innerLoopParallelInnerMatrixMedium.duration,
        outerLoopParallelOutputMatrixMedium.duration,
        serialOutputMatrixLarge.duration,
        innerLoopParallelInnerMatrixLarge.duration,
        outerLoopParallelOutputMatrixLarge.duration};
    std::vector<std::string> tags = {
        fmt::format("serial\n small\n {}s", std::to_string(serialOutputMatrixSmall.duration)),
        fmt::format("parallel\n inner loop\n small\n {}s", std::to_string(innerLoopParallelInnerMatrixSmall.duration)),
        fmt::format("parallel\n outer loop\n small\n {}s", std::to_string(outerLoopParallelOutputMatrixSmall.duration)),
        fmt::format("serial\n medium\n {}s", std::to_string(serialOutputMatrixMedium.duration)),
        fmt::format("parallel\n inner loop\n  medium\n {}s", std::to_string(innerLoopParallelInnerMatrixMedium.duration)),
        fmt::format("parallel\n outer loop\n medium\n {}s", std::to_string(outerLoopParallelOutputMatrixMedium.duration)),
        fmt::format("serial\n large\n {}s", std::to_string(serialOutputMatrixLarge.duration)),
        fmt::format("parallel\n inner loop\n large\n {}s", std::to_string(innerLoopParallelInnerMatrixLarge.duration)),
        fmt::format("parallel\n outer loop\n large\n {}s", std::to_string(outerLoopParallelOutputMatrixLarge.duration))};
    plt::xticks(indx, tags);
    plt::yticks(data, plthelpers::ylabels(data));
    plt::bar(data);
    plt::show();
}