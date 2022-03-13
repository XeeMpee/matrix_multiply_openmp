#include "matplotlibcpp.h"
#include "utils/matrix_operations.hpp"
#include "utils/matplotlibcpp_helpers.hpp"
#include "types/types.hpp"
#include "types/types.hpp"
#include <spdlog/spdlog.h>

namespace plt = matplotlibcpp;

int main()
{
    Matrix2D matrixASmall = matrix::generate2DMatrix(10, 10, 0.0, 100.0);
    Matrix2D matrixBSmall = matrix::generate2DMatrix(10, 10, 200.0, 250.0);

    spdlog::info("small matrixes multiplications (operation may take a while)");
    Matrix2DMultiplicationOutput serialOutputMatrixSmall = matrix::multiply2DMatrixSerial(matrixASmall, matrixBSmall);
    Matrix2DMultiplicationOutput innerLoopParallelInnerMatrixSmall = matrix::multiply2DMatrixParallelInnerLoop(matrixASmall, matrixBSmall);
    Matrix2DMultiplicationOutput outerLoopParallelOutputMatrixSmall = matrix::multiply2DMatrixParallelOuterLoop(matrixASmall, matrixBSmall);

    Matrix2D matrixMediumA = matrix::generate2DMatrix(100, 100, 0.0, 100.0);
    Matrix2D matrixMediumB = matrix::generate2DMatrix(100, 100, 200.0, 250.0);

    spdlog::info("medium matrixes multiplications (operation may take a while)");
    Matrix2DMultiplicationOutput serialOutputMatrixMedium = matrix::multiply2DMatrixSerial(matrixMediumA, matrixMediumB);
    Matrix2DMultiplicationOutput innerLoopParallelInnerMatrixMedium = matrix::multiply2DMatrixParallelInnerLoop(matrixMediumA, matrixMediumB);
    Matrix2DMultiplicationOutput outerLoopParallelOutputMatrixMedium = matrix::multiply2DMatrixParallelOuterLoop(matrixMediumA, matrixMediumB);

    Matrix2D matrixLargeA = matrix::generate2DMatrix(500, 500, 0.0, 100.0);
    Matrix2D matrixLargeB = matrix::generate2DMatrix(500, 500, 200.0, 250.0);

    spdlog::info("large matrixes multiplications (operation may take a while)");
    Matrix2DMultiplicationOutput serialOutputMatrixLarge = matrix::multiply2DMatrixSerial(matrixLargeA, matrixLargeB);
    Matrix2DMultiplicationOutput innerLoopParallelInnerMatrixLarge = matrix::multiply2DMatrixParallelInnerLoop(matrixLargeA, matrixLargeB);
    Matrix2DMultiplicationOutput outerLoopParallelOutputMatrixLarge = matrix::multiply2DMatrixParallelOuterLoop(matrixLargeA, matrixLargeB);

    plt::figure(1);
    std::vector<double> indx = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<double> data = {
        std::get<1>(serialOutputMatrixSmall),
        std::get<1>(innerLoopParallelInnerMatrixSmall),
        std::get<1>(outerLoopParallelOutputMatrixSmall),
        std::get<1>(serialOutputMatrixMedium),
        std::get<1>(innerLoopParallelInnerMatrixMedium),
        std::get<1>(outerLoopParallelOutputMatrixMedium),
        std::get<1>(serialOutputMatrixLarge),
        std::get<1>(innerLoopParallelInnerMatrixLarge),
        std::get<1>(outerLoopParallelOutputMatrixLarge)};
    std::vector<std::string> tags = {
        fmt::format("serial\n small\n {}s", std::to_string(std::get<1>(serialOutputMatrixSmall))),
        fmt::format("parallel\n inner loop\n small\n {}s", std::to_string(std::get<1>(innerLoopParallelInnerMatrixSmall))),
        fmt::format("parallel\n outer loop\n small\n {}s", std::to_string(std::get<1>(outerLoopParallelOutputMatrixSmall))),
        fmt::format("serial\n medium\n {}s", std::to_string(std::get<1>(serialOutputMatrixMedium))),
        fmt::format("parallel\n inner loop\n  medium\n {}s", std::to_string(std::get<1>(innerLoopParallelInnerMatrixMedium))),
        fmt::format("parallel\n outer loop\n medium\n {}s", std::to_string(std::get<1>(outerLoopParallelOutputMatrixMedium))),
        fmt::format("serial\n large\n {}s", std::to_string(std::get<1>(serialOutputMatrixLarge))),
        fmt::format("parallel\n inner loop\n large\n {}s", std::to_string(std::get<1>(innerLoopParallelInnerMatrixLarge))),
        fmt::format("parallel\n outer loop\n large\n {}s", std::to_string(std::get<1>(outerLoopParallelOutputMatrixLarge)))};
    plt::xticks(indx, tags);
    plt::yticks(data, plthelpers::ylabels(data));
    plt::bar(data);
    plt::show();
}