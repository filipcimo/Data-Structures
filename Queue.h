#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <initializer_list>
#define en '\n'


template<typename T>
class Queue
{
    public:
        Queue();
        Queue(const Queue<T>& it);
        explicit Queue(const std::initializer_list<T>& it);
        constexpr Queue<T>& operator=(const Queue<T>& it);
        ~Queue();

        void enqueue(const T& it);
        void dequeue();
        void clear();
        constexpr size_t size() const;
        constexpr T& operator[](const size_t& pos) const;
        constexpr T& value(const size_t& pos) const;

        friend std::ostream& operator<<(std::ostream& os, const Queue<T>& it)
        {
            Node* temp = it.head;

            while (temp != nullptr)
            {
                if (temp->next == nullptr) { os << *temp->data; }
                else { os << *temp->data << en; }

                temp = temp->next;
            }

            return os;
        }


    private:
        class Node
        {
            public:
                Node();
                ~Node();

                T* data;
                Node* next;
                Node* prev;
        };

        Node* head;
        Node* last;
};


template<typename T>
Queue<T>::Queue()
{
    head = nullptr;
    last = nullptr;
}


template<typename T>
Queue<T>::~Queue()
{
    Node* temp = nullptr;
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}


template<typename T>
Queue<T>::Queue(const Queue<T>& it) : head(nullptr), last(nullptr)
{
    Node* temp = it.head;
    while (temp != nullptr)
    {
        add(*temp->data);
        temp = temp->next;
    }
}


template<typename T>
Queue<T>::Queue(const std::initializer_list<T>& it) : head(nullptr), last(nullptr)
{
    for (size_t i = 0; i < it.size(); i++)
    {
        add(*it.begin() + i);
    }
}


template<typename T>
constexpr Queue<T>& Queue<T>::operator=(const Queue<T>& it)
{
    if (head != nullptr) { clear(); }

    Node* temp = it.head;
    while (temp != nullptr)
    {
        add(*temp->data);
        temp = temp->next;
    }
}


template<typename T>
void Queue<T>::enqueue(const T& it)
{
    if (head == nullptr)
    {
        Node* new_node = new Node;
        new_node->data = new T;
        *new_node->data = it;
        new_node->next = nullptr;
        new_node->prev = nullptr;

        head = new_node;
        last = new_node;
    }

    else if (head != nullptr)
    {
        Node* temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }

        Node* new_node = new Node;
        new_node->data = new T;
        *new_node->data = it;
        new_node->next = nullptr;

        temp->next = new_node;
        new_node->prev = temp;
        last = new_node;
    }
}


template<typename T>
void Queue<T>::dequeue()
{
    if (head != nullptr)
    {
        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            last = nullptr;
        }

        else
        {
            Node* temp = last->prev;
            last->prev->next = nullptr;
            delete last;
            last = temp;
        }
    }
}


template<typename T>
void Queue<T>::clear()
{
    Node* temp = nullptr;
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        delete temp;
    }

    head = nullptr;
    last = nullptr;
}


template<typename T>
constexpr size_t Queue<T>::size() const
{
    Node* temp = head;
    size_t i = 0;

    while (temp != nullptr)
    {
        temp = temp->next;
        i += 1;
    }

    return i;
}


template<typename T>
constexpr T& Queue<T>::operator[](const size_t& pos) const
{
    Node* temp = head;
    size_t i = 0;

    while (i != pos)
    {
        temp = temp->next;
        i += 1;
    }

    return *temp->data;
}


template<typename T>
constexpr T& Queue<T>::value(const size_t& pos) const
{
    Node* temp = head;
    size_t i = 0;

    while (i != pos)
    {
        temp = temp->next;
        i += 1;
    }

    return *temp->data;
}


template<typename T>
Queue<T>::Node::Node()
{
    data = nullptr;
    next = nullptr;
    prev = nullptr;
}


template<typename T>
Queue<T>::Node::~Node()
{
    if (data != nullptr) { delete data; }
}


#endif
