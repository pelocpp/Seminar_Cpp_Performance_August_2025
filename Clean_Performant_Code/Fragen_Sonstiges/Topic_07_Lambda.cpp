

#include <iostream>
#include <string_view>
#include <vector>
#include <algorithm>
#include <print>
#include <memory>


static void tueWas()
{
    int n = 1;
    int m = 2;
    int offset = 10;

    auto l = [&m, &n, offset](int n) {

        return n + offset;
    };

    auto result = l(20);
}

static void test_12() {

    // Feature: Generalized Lambda Capture

    class SampleClass
    {
    public:
        void doSomething() { std::println("Doing Something"); };
    };

    // local
    std::unique_ptr<SampleClass> ptr{
        std::make_unique<SampleClass>()
    };

    // Does not compile: by-value capture with move-only type (!)
    // auto lambda = [=] () { ptr->doSomething(); };

    // Compiles: by-reference capture with move-only type (!)
    auto lambda = [&]() { ptr->doSomething(); };

    // How about by-move capture?
    // Instead of adding it, C++14 introduced the "Generalized Lambda Capture",
    // also known as "Init Capture":

    auto lambda2 = [ ptrSampleClass = std::move(ptr) ]() {
        ptrSampleClass->doSomething();
    };

    lambda2();

    // Note:
    // We are allowed to keep the name of the variable 'ptr' 
    // the same inside the lambda:

    ptr = std::make_unique<SampleClass>();

    // Hier sind ZWEI verschiedene Variablen verwendet:
    // ptr und ptr1 //
    // Man könnte ptr1 auch ptr benennen :)
    auto lambda3 = [ptr1 = std::move(ptr)]() {
        ptr1->doSomething();
    };

    lambda3();
}

void lambdas()
{
    test_12();
    tueWas();
}