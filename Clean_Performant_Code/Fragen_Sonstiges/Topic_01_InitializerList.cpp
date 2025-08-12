// =====================================================================================
// InitializerList.cpp // std::initializer_list
// =====================================================================================

#include "../LoggerUtility/ScopedTimer.h"

#include <iostream>
#include <vector>
#include <algorithm>

namespace InitializerList {

    // function using std::initializer_list
    static int adder(std::initializer_list<int> list)
    {
        int result{};

        std::for_each(
            list.begin(),
            list.end(),
            [&result](int value) {
                result += value;
            }
        );

        return result;
    }

    // delegating std::initializer_list with range based loop
    static void print(std::initializer_list<int> list) {

        for (const auto& value : list) {
            std::cout << value << " - ";
        }
        std::cout << std::endl;
    }

    static void test_01() {

        // testing functions expecting lists in function call
        int sum = adder ( { 1, 2, 3, 4, 5, 6, 7, 8 } ) ;
        std::cout << sum << std::endl;

        print({ 1, 2, 3, 4, 5 });
    }

    // =================================================================================

    static void test_02() {

        std::initializer_list<int> list{ 1, 2, 3, 4, 5 };
        std::vector<int> vec{ list };
    }

    // =================================================================================

    class Point {
    public:
        // c'tors
        Point() : Point{ 0.0, 0.0 } {}
        Point(double x, double y) : m_x{ x }, m_y{ y } {}

        // getter
        double X() const { return m_x; }
        double Y() const { return m_y; }

    private:
        double m_x;
        double m_y;
    };

    // container-like classes
    class Polygon {
    public:
        Polygon(std::initializer_list<Point> points)
            : m_points{ points }
        {
        }

    private:
        std::vector<Point> m_points;
    };

    static void test_03() {

        Polygon polygon
        {                          // c'tor Polygon - using brace initialization syntax
            {                      // braces for std::initializer_list<Point> object
                { 45.0, 45.0 },    // c'tor Point - using brace initialization syntax
                { 60.0, 60.0 },    // c'tor Point - using brace initialization syntax
                { 120.0, 120.0 },
                { 180.0, 180.0 }
            }
        };

        // same example - with brace elision
        Polygon polygon2
        {                          // c'tor Polygon - using brace initialization syntax
            { 45.0, 45.0 },        // c'tor Point - using brace initialization syntax
            { 60.0, 60.0 },        // c'tor Point - using brace initialization syntax
            { 120.0, 120.0 },
            { 180.0, 180.0 }
        };
    }

    // =================================================================================

    // container-like class: testing precedence of constructors
    class TinyContainer {
    public:
        TinyContainer() {}
        TinyContainer(int value) {}
        TinyContainer(std::initializer_list<int>) {};
    };

    static void test_04() {

        TinyContainer tc0;                  // TinyContainer::TinyContainer()
        TinyContainer tc1{ 1, 2, 3, 4 };    // TinyContainer::TinyContainer(std::initializer_list<int>)
        TinyContainer tc2{ 1 };             // TinyContainer::TinyContainer(std::initializer_list<int>)
        TinyContainer tc3(1);               // TinyContainer::TinyContainer(int)
        TinyContainer tc4{ };               // TinyContainer::TinyContainer()
    }

    // =================================================================================

    // delegating templated std::initializer_list to range based loop
    template<typename T>
    void printEx(std::initializer_list<T> list) {

        for (const auto& value : list) {
            std::cout << value << " - ";
        }
        std::cout << std::endl;
    }

    // delegating templated std::initializer_list to std::for_each with lambda
    template<typename T>
    void printExEx(std::initializer_list<T> list) {

        std::cout << "Begin of list: ";

        std::for_each(
            list.begin(),
            list.end(),
            [](const T& elem) {
                std::cout << elem << " - ";
            }
        );

        std::cout << " End of list." << std::endl;
    }

    static void test_05() {

        // testing generic functions expecting lists
        printEx({ 11, 12, 13, 14, 15 });

        std::cout << "--------------------------------" << std::endl;

        printEx({ 'a', 'b', 'c' });        // template argument T can be deduced automatically
        printEx<char>({ 'a','b', 'c' });   // template argument T specified explicitly
        printEx<int>({ 'A', 'B', 'C' });
        printEx({ "ABC", "DEF", "GHI" });
        printEx<std::string>({ "ABC", "DEF", "GHI" });
        printEx<std::string>({ std::string("RST"), std::string("UVW"), std::string("XYZ") });

        std::cout << "--------------------------------" << std::endl;

        printExEx({ 'a', 'b', 'c' });        // template argument T can be deduced automatically
        printExEx<char>({ 'a','b', 'c' });   // template argument T specified explicitly
        printExEx<int>({ 'A', 'B', 'C' });
        printExEx({ "ABC", "DEF", "GHI" });
        printExEx<std::string>({ "ABC", "DEF", "GHI" });
        printExEx<std::string>({ std::string("RST"), std::string("UVW"), std::string("XYZ") });
    }
}

namespace Exercise_02 {

    class SomeStrings
    {
    public:
        static auto transferData(const std::vector<std::string>& strings)
        {
            // prevent optimizer to work too hard ...
            const auto first = strings.begin();
            const auto last = std::prev(strings.end());
            return *first + *last;
            //std::cout << "first=" << first << std::endl;
            //std::cout << "last=" << last << std::endl;
        }

        static auto transferData(const std::initializer_list<std::string> strings)
        {
            // prevent optimizer to work too hard ...
            const auto first = strings.begin();
            const auto last = std::prev(strings.end());
            return *first + *last;
            //std::cout << "first=" << *first << std::endl;
            //std::cout << "last=" << *last << std::endl;
        }
    };

    // Note: Debug vs Release Mode
    constexpr int MaxIteration = 1000'000;

    static void testExercise_02() {
        {
            ScopedTimer watch{};

            for (size_t i{}; i != MaxIteration; ++i) {

                // heap-based transfer of strings
                SomeStrings::transferData(
                    std::vector<std::string> {
                    "A", "B", "C", "D", "E", "F", "G", "H", "I",
                        "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                        "S", "T", "U", "V", "W", "X", "Y", "Z"
                });
            }

            std::cout << "std::vector: " << std::endl;
        }

        {
            ScopedTimer watch{};

            for (size_t i{}; i != MaxIteration; ++i) {

                // stack-based transfer of strings
                SomeStrings::transferData(
                    std::initializer_list<std::string> {
                    "A", "B", "C", "D", "E", "F", "G", "H", "I",
                        "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                        "S", "T", "U", "V", "W", "X", "Y", "Z"
                });
            }

            std::cout << "std::initializer_list: " << std::endl;;
        }
    }
}

void main_initializer_list()
{
    using namespace InitializerList;

    Exercise_02::testExercise_02();


    //test_01();
    //test_02();
    //test_03();
    //test_04();
    //test_05();
}

// =====================================================================================
// End-of-File
// =====================================================================================
