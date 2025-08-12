// ===========================================================================
// ScopedTimer_Lambda_vs_Std_Function.cpp
// ===========================================================================

#include "../LoggerUtility/ScopedTimer.h"

#include <functional>
#include <print>

namespace Benchmarking_Lambda_vs_Std_Function_Vorbereitung {

    auto product = [](int a, int b) -> int {
        return a * b;
    };

    void rufeLambdaAuf()
    {
        auto result = product(3, 4);
    }

    void VerwendeStdFunction()
    {
        std::function< int(int, int) > f
        ([](int a, int b) -> int {
            return a * b;
        });

        auto result = f(3, 4);
    }

    // Go-for  auto
    // Go-for  std::function

    // Ist egal

    // Performanz: std::function ist ein Wrapper / H�lle
    // Langsamer: 
}


namespace Benchmarking_Lambda_vs_Std_Function {

    static const size_t Iterations = 1000000;
    static const size_t InnerIterations = 100;

    static double MyFunction(double input)
    {
        double total = input * 2.0f + 1.0f;
        return total;
    }

    static void Lambda()
    {
        auto lambda = [](double input) {
            auto total = input * 2.0 + 1.0;
            return total;
        };

        std::println("Lambda");

        ScopedTimer watch{};

        for (size_t i{}; i != Iterations; ++i) {
            auto volatile total = 0.0;
            for (size_t i{}; i != InnerIterations; ++i) {
                total += lambda(total);
            }
        }
    }

    static void StdFunctionWithLambda()
    {
        auto lambda = [](double input) {
            auto total = input * 2.0 + 1.0;
            return total;
        };

    //    std::function<double(double)> func{ lambda };

        std::function<double(double)> func{ [](double input) {
            auto total = input * 2.0 + 1.0;
            return total;
        } };

        std::println("StdFunctionWithLambda");

        ScopedTimer watch{};

        for (size_t i{}; i != Iterations; ++i) {
            auto volatile total = 0.0;
            for (size_t i{}; i != InnerIterations; ++i) {
                total += func(total);
            }
        }
    }

    static void StdFunctionWithFreeFunction()
    {
        std::function<double(double)> func{ &MyFunction };

        std::println("StdFunctionWithFreeFunction");

        ScopedTimer watch{};

        for (size_t i{}; i != Iterations; ++i) {
            auto volatile total = 0.0;
            for (size_t i{}; i != InnerIterations; ++i) {
                total += func(total);
            }
        }
    }
}

void benchmarking_lambda_vs_std_function()
{
    using namespace Benchmarking_Lambda_vs_Std_Function;

    Lambda();
    StdFunctionWithLambda();
    StdFunctionWithFreeFunction();
}

// ===========================================================================
// End-of-File
// ===========================================================================
