// Folding

#include <iostream>
#include <string_view>
#include <vector>
#include <algorithm>
#include <print>


// 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8

template <typename ... TArgs>  // einpacken: int, int, int, int, int
                               //   => Pack
int addierer(TArgs ... args)   // einpacken: 1, 2, 3, 4, 5
{                              //   == Pack
    auto result = ( ... + args);   // auspacken
    return result;
}

template <typename ... TArgs>
constexpr int addiererC(TArgs ... args)   // einpacken: 1, 2, 3, 4, 5
{                              //   == Pack
    auto result = (... + args);   // auspacken
    return result;
}

void test_folding()
{
    int result = addierer<>(1, 2, 3, 4, 5, 6, 7, 8);

    constexpr auto result2 = addiererC(1, 2, 3, 4, 5, 6, 7, 8);
}