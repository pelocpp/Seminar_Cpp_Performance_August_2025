
#include <iostream>
#include <string_view>
#include <vector>
#include <algorithm>
#include <print>
#include <memory>


static std::unique_ptr<int> loadUniquePointer()
{
    std::unique_ptr<int> emtpy;

    std::unique_ptr<int> ptr{ std::make_unique<int>(100) };
    
    return std::move (ptr);  // gut / schlecht ????
}

static std::shared_ptr<int> loadSharedPointer()
{
    std::shared_ptr<int> emtpy;

    std::shared_ptr<int> ptr{ std::make_shared<int>(100) };

    return ptr;
}

static void test_02()
{
    // retrieving a unique pointer from a function
    std::unique_ptr<int> ptr1{ loadUniquePointer() };
    std::println("*ptr:    {}", *ptr1);

    // retrieving a unique pointer from a function
    std::shared_ptr<int> ptr2{ loadSharedPointer() };
    std::println("*ptr:    {}", *ptr2);
}

void copy_move_elision()
{
    test_02();
}