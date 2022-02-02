#include <iostream>
#include <cstddef>// size_t
#include "ShablonArray.hpp"

// распечатка элементов массива через перегруженные операторы

//прогоняем функцию шаблон
//с многомерным массивом(неограниченная глубина вложенности)

template <typename T>
void flatten(const T& t, std::ostream& out)
//перегрузка рекурсии,
//которая вызывается, когда на входе НЕ массив, а конкретный элемент(int, doublе)
{
        out << " " << t << " ";
}

template <typename T>
void flatten(const Array<T>& t, std::ostream& out)
{
        for (size_t i = 0; i != t.size(); ++i)
            flatten(t[i], out);//используем перегруженную рекурсию
}


// Пример применения:

//int main()
//{
//    Array<int> ints(2, 0);
//    ints[0] = 10;
//    ints[1] = 20;
//    flatten(ints, std::cout); // выводит на экран строку "10 20"
//    std::cout << std::endl;
//
//    Array< Array<int> > array_of_ints(2, ints);// массив в массиве
//    flatten(array_of_ints, std::cout); // выводит на экран строку "10 20 10 20"
//    std::cout << std::endl;
//
//    Array<double> doubles(10, 0.0);
//    flatten(doubles, std::cout); // работать должно не только для типа int
//    std::cout << std::endl;
//    return 0;
//}