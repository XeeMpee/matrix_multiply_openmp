#pragma once
#include "matrix/matrix.hpp"

using ProcessingDuration = double;

class Matrix;
struct MatrixMultiplicationOutput
{
    MatrixMultiplicationOutput(Matrix outputMatrix, ProcessingDuration processingDuration)
        : matrix{outputMatrix}
        , duration(processingDuration)
    {
    }

    Matrix matrix;
    ProcessingDuration duration;
};
