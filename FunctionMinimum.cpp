#include <iostream>
#include <cstddef>// size_t
#include "ShablonArray.hpp"

// поиск минимального или максимального числа в массиве через функцию компаратор

bool less(int a, int b) { return a < b; }

struct Greater {
    bool operator()(int a, int b) const { return b < a; }
};

template <typename T, typename Comp>
T minimum(Array<T> & a, Comp function)
{
    T rez = a[0];
    for (size_t i = 0; i != a.size(); ++i)
    {
        if (function(a[i], rez))
            rez = a[i];
    }
    return rez;
}

//Пример применения:

// int main() {
//    Array<int> ints(3);
//    ints[0] = 10;
//    ints[1] = 2;
//    ints[2] = 15;
//    int min = minimum(ints, less); // в мин число 2
//    int max = minimum(ints, Greater()); // в макс число 15
//
//    std::cout << min << std::endl;
//    std::cout << max << std::endl;
//
//    return 0;
//}
