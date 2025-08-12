// ===========================================================================
// CustomAllocator_Test.cpp // Performance Optimization Advanced
// ===========================================================================

#include "../Person/Person.h"

#include "CustomAllocator.h"

#include <vector>
#include <memory>


static void test_custom_allocator_test_value_type()
{
    using MyType = int;

    using MyContainer = std::vector<MyType>;

    MyContainer numbers;

    MyContainer::value_type  n = 123;

    numbers.push_back(n);
}


static void test_custom_allocator_01()
{
    // create an allocator to use
    std::allocator<Person> alloc;

    // allocate an uninitialized memory block for 1 instance of 'Person'
    auto* memory{ alloc.allocate(1) };

    // use 'placement new' operator to construct a 'Person' object in place
    ::new (memory) Person{};

    // Template Parameter Deduction
    std::construct_at(memory, Person{ "Hans", "Mueller", 30});

    // destroy 'Person' instance
    std::destroy_at(memory);

    // deallocate memory block
    alloc.deallocate(memory, 1);

    memory = nullptr;
}

static void test_custom_allocator_02()
{
    CustomAllocator<int> alloc;

    std::vector<int, CustomAllocator<int>> vec(alloc);

    vec.reserve(3);

    // std::vector<int, CustomAllocator<int>> vec;  // works too

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    for (int i : vec) {
        std::println("{} ", i);
    }
}

static void test_custom_allocator_03()
{
    std::vector<Person, CustomAllocator<Person>> vec;

    vec.push_back(Person { "Sepp", "Mueller", 30 });
    vec.push_back(Person { "Hans", "Wagner", 30 });
    vec.push_back(Person { "Anton", "Meier", 30 });

    for (const auto& person : vec) {
        std::println("{} ", person);
    }
}

static void test_custom_allocator_04()
{
    CustomAllocator<int> alloc;

    std::vector<int, CustomAllocator<int>> vec(alloc);

    // std::vector<int, SimpleAllocator<int>> vec;  // works too

    std::println("Adding elements to vector:");
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    std::println("Vector contents: ");
    for (int i : vec) {
        std::print("{} ", i);
    }
    std::println("");

    std::println("Resizing vector to 1 element:");
    vec.resize(1);

    std::println("Clearing vector:");
    vec.clear();
}

void test_custom_allocator()
{
//    test_custom_allocator_01();
    //test_custom_allocator_02();
    test_custom_allocator_03();
//    test_custom_allocator_04();
}

// ===========================================================================
// End-of-File
// ===========================================================================
