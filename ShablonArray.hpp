#ifndef SHABLON_ARRAY_HPP
#define SHABLON_ARRAY_HPP

#include <iostream>
#include <cstddef>//size_t

//приведенный ниже класс с натяжкой аналогичен классу vector

template <typename T>
class Array {
public:
    //   Конструктор класса, который создает массив
    //   Array размера size, заполненный значениями
    //   value типа T. Если у класса нет конструктора
    //   по умолчанию, то второй аргумент этого конструктора
    //   обязателен.
    explicit Array(size_t size, const T& value = T()){
        size_ = size;
        data_ = (T*) new char[size_ * sizeof(T)];
        for (size_t i = 0; i != size_; ++i)
            new (data_ + i) T(value);//не выделяем, а инициализируем память
    }
    // Конструктор по умолчанию;
    Array(){
        data_ = 0;
        size_ = 0;
    }
    //   Конструктор копирования, который создает
    //   копию параметра. Для типа T оператор
    //   присваивания не определен.
    Array(const Array &a){
        size_ = a.size();
        data_ = (T*) new char[size_ * sizeof(T)];
        for (size_t i = 0; i != size_; ++i)
            new (data_ + i) T(a[i]);
    }
    //   деструктор, если он вам необходим.
    ~Array()
    {
        for (size_t i = 0; i != size_; ++i)
            data_[i].~T();
        delete [] (char *)data_;
    }
    //   Переопределение оператора присваивания
    Array & operator=(Array const& a)
    {
        if (this != &a){
            for (size_t i = 0; i != size_; ++i)
                data_[i].~T();
            delete [] (char *)data_;
            size_ = a.size();
            data_ = (T*) new char[size_ * sizeof(T)];
            for (size_t i = 0; i != size_; ++i)
                new (data_ + i) T(a[i]);
        }
        return *this;
    }
    //   Размер массива(количество элементов).
    size_t size() const{ return size_; }
    //   две версии оператора доступа по индексу(константный и не константный).
    T& operator[](size_t i) { return *(data_ + i); }
    const T& operator[](size_t i) const { return *(data_ + i); }

private:
    T * data_;
    size_t size_;
};

#endif

