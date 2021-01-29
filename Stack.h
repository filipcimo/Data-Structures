#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <initializer_list>
#define en '\n'


template<typename T>
class Stack
{
    public:
        Stack();
        Stack(const Stack<T>& it);
        explicit Stack(const std::initializer_list<T>& it);
        constexpr Stack<T>& operator=(const Stack<T>& it);
        ~Stack();

        void push_back(const T& it);
        void pop_back();
        void clear();
        constexpr size_t size() const;
        constexpr T& operator[](const size_t& pos) const;
        constexpr T& value(const size_t& pos) const;
        constexpr T* values() const;

        friend std::ostream& operator<<(std::ostream& os, const Stack<T>& it)
        {
            for (size_t i = 0; i < it.data->size; i++)
            {
                if (i == (it.data->size - 1)) { os << it.data->items[i]; }
                else { os << it.data->items[i] << en; }
            }

            return os;
        }


    private:
        class Data
        {
            public:
                Data();
                ~Data();

                T* items;
                size_t size;
        };

        Data* data;
};


template<typename T>
Stack<T>::Stack()
{
    data = nullptr;
}


template<typename T>
Stack<T>::~Stack()
{
    if (data != nullptr) { delete data; }
}


template<typename T>
Stack<T>::Stack(const Stack<T>& it)
{
    data = new Data;
    data->items = new T[it.data->size];
    data->size = it.data->size;

    for (size_t i = 0; i < data->size; i++)
    {
        data->items[i] = it.data->items[i];
    }
}


template<typename T>
Stack<T>::Stack(const std::initializer_list<T>& it)
{
    data = new Data;
    data->items = new T[it.size()];
    data->size = it.size();

    for (size_t i = 0; i < data->size; i++)
    {
        data->items[i] = (*it.begin() + i);
    }
}


template<typename T>
constexpr Stack<T>& Stack<T>::operator=(const Stack<T>& it)
{
    if (data != nullptr) { clear(); }

    data = new Data;
    data->items = new T[it.data->size];
    data->size = it.data->size;

    for (size_t i = 0; i < it.data->size; i++)
    {
        data->items[i] = it.data->items[i];
    }

    return *this;
}


template<typename T>
void Stack<T>::push_back(const T& it)
{
    if (data == nullptr)
    {
        data = new Data;
        data->size += 1;
        data->items = new T[data->size];
        data->items[data->size - 1] = it;
    }

    else if (data != nullptr)
    {
        T* temp = data->items;
        data->size += 1;
        data->items = new T[data->size];

        for (size_t i = 0; i < (data->size - 1); i++)
        {
            data->items[i] = temp[i];
        }

        data->items[data->size - 1] = it;

        if ((data->size - 1) == 1) { delete temp; }
        else if ((data->size - 1) > 1) { delete [] temp; }
    }
}


template<typename T>
void Stack<T>::pop_back()
{
    if (data != nullptr)
    {
        if (data->size == 1)
        {
            delete data->items;
            data->items = nullptr;
            data->size = 0;
        }

        else if (data->size > 1)
        {
            data->size -= 1;
            T* temp = data->items;
            data->items = new T[data->size];

            for (size_t i = 0; i < data->size; i++)
            {
                data->items[i] = temp[i];
            }

            delete [] temp;
        }
    }
}


template<typename T>
void Stack<T>::clear()
{
    if (data != nullptr)
    {
        delete data;
        data = nullptr;
    }
}


template<typename T>
constexpr size_t Stack<T>::size() const
{
    if (data == nullptr) { return 0; }
    else if (data != nullptr) { return (data->size); }
}


template<typename T>
constexpr T& Stack<T>::operator[](const size_t& pos) const
{
    return data->items[pos];
}

template<typename T>
constexpr T& Stack<T>::value(const size_t& pos) const
{
    return data->items[pos];
}

template<typename T>
constexpr T* Stack<T>::values() const
{
    return data->items;
}


template<typename T>
Stack<T>::Data::Data()
{
    items = nullptr;
    size = 0;
}


template<typename T>
Stack<T>::Data::~Data()
{
    if (items != nullptr)
    {
        if (size == 1) { delete items; }
        else if (size > 1) { delete [] items; }
    }
}


#endif
