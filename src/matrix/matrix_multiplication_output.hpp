#pragma once
#include <spdlog/spdlog.h>
#include "matrix/matrix.hpp"

using ProcessingDuration = double;

class Matrix;
struct MatrixMultiplicationOutput
{
    Matrix matrix;
    ProcessingDuration duration;

    MatrixMultiplicationOutput(Matrix outputMatrix, ProcessingDuration processingDuration)
        : matrix{outputMatrix}
        , duration(processingDuration)
    {
    }

    static bool equal(std::vector<MatrixMultiplicationOutput> outputs)
    {
        return equal("", outputs);
    }

    static bool equal(const std::string& label, std::vector<MatrixMultiplicationOutput> outputs)
    {
        for (int indx = 0; indx < outputs.size() - 1; indx++)
        {
            if (!std::equal(outputs[0].matrix.begin(), outputs[0].matrix.end(), outputs[indx].matrix.begin()))
            {
                spdlog::error("Matrixes ({}) NOT equal - mismatch on index:{}", label != "" ? fmt::format("({})", label) : "", indx);
                return false;
            }
        }
        spdlog::info("Matrixes ({}) equal", label);
        return true;
    }
};
