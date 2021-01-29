#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <assert.h>
#include <initializer_list>
#define en '\n'


template<typename T>
class List
{
    public:
        List();
        List(const List<T>& it);
        explicit List(const std::initializer_list<T>& it);
        constexpr List<T>& operator=(const List<T>& it);
        ~List();

        void add(const T& it);
        void add(const T& it, const size_t& pos);
        void remove();
        void remove(const size_t& pos);
        void clear();
        constexpr size_t size() const;
        constexpr T& operator[](const size_t& pos) const;
        constexpr T& value(const size_t& pos) const;

        friend std::ostream& operator<<(std::ostream& os, const List<T>& it)
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
                Node* prev;
                Node* next;
        };

        Node* head;
};


template<typename T>
List<T>::List()
{
    head = nullptr;
}


template<typename T>
List<T>::~List()
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
List<T>::List(const List<T>& it) : head(nullptr)
{
    Node* temp = it.head;
    while (temp != nullptr)
    {
        add(*temp->data);
    }
}


template<typename T>
List<T>::List(const std::initializer_list<T>& it) : head(nullptr)
{
    for (size_t i = 0; i < it.size(); i++)
    {
        add(*it.begin() + i);
    }
}


template<typename T>
constexpr List<T>& List<T>::operator=(const List<T>& it)
{
    if (head != nullptr) { clear(); }

    Node* temp = it.head;
    while (temp != nullptr)
    {
        add(*temp->data);
    }

    return *this;
}


template<typename T>
void List<T>::add(const T& it)
{
    if (head == nullptr)
    {
        Node* new_node = new Node;
        new_node->data = new T;
        *new_node->data = it;

        new_node->next = nullptr;
        new_node->prev = nullptr;
        head = new_node;
    }

    else
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
        new_node->prev = temp;
        temp->next = new_node;
    }
}


template<typename T>
void List<T>::add(const T& it, const size_t& pos)
{
    if (head == nullptr)
    {
        Node* new_node = new Node;
        new_node->data = new T;
        *new_node->data = it;

        new_node->next = nullptr;
        new_node->prev = nullptr;
        head = new_node;
    }

    else
    {
        Node* temp = head;
        size_t i = 0;

        while (i != (pos - 1))
        {
            temp = temp->next;
        }

        Node* new_node = new Node;
        new_node->data = new T;
        *new_node->data = it;

        Node* temp2 = temp->next;
        temp->next = new_node;
        new_node->next = temp2;
        new_node->prev = temp;
        temp2->prev = new_node;
    }
}



template<typename T>
void List<T>::remove()
{
    if (head == nullptr) { return; }

    else if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
    }

    else
    {
        Node* temp = head;
        while (temp->next->next != nullptr)
        {
            temp = temp->next;
        }

        Node* temp2 = temp->next;
        temp->next = nullptr;
        delete temp2;
    }
}


template<typename T>
void List<T>::remove(const size_t& pos)
{
    if (head == nullptr) { return; }

    else if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
    }

    else
    {
        if (pos == 0)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }

        else
        {
            Node* temp = head;
            size_t i = 0;

            while (i != (pos - 1))
            {
                temp = temp->next;
                i += 1;
            }

            Node* temp2 = temp->next;

            if (temp->next->next != nullptr)
            {
                temp->next->next->prev = temp;
                temp->next = temp->next->next;
            }

            else
            {
                temp->next = nullptr;
            }

            delete temp2;
        }
    }
}


template<typename T>
constexpr size_t List<T>::size() const
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
void List<T>::clear()
{
    Node* temp = nullptr;
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        delete temp;
    }

    head = nullptr;
}


template<typename T>
constexpr T& List<T>::operator[](const size_t& pos) const
{
    Node* temp = head;
    size_t i = 0;

    while (i != pos)
    {
        temp = temp->next;
        i += 1;
    }

    return (*temp->data);
}


template<typename T>
constexpr T& List<T>::value(const size_t& pos) const
{
    Node* temp = head;
    size_t i = 0;

    while (i != pos)
    {
        temp = temp->next;
        i += 1;
    }

    return (*temp->data);
}


template<typename T>
List<T>::Node::Node()
{
    data = nullptr;
    prev = nullptr;
    next = nullptr;
}


template<typename T>
List<T>::Node::~Node()
{
    if (data != nullptr) { delete data; }
}

#endif
