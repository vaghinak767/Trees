#pragma once
#include <vector>
#include <iostream>
#include <initializer_list>

template <typename T>
class MinHeap
{
    public:
        MinHeap();
        MinHeap(const MinHeap<T>&);
        MinHeap(MinHeap<T>&&);
        MinHeap(std::initializer_list<T>);
        void push(T);
        void pop();
        T& top();
        int size()const;
        bool empty()const;
        void clear();
        void print();
    private:
        void heapify(std::vector<T>&, int);
        int left(int);
        int right(int);
        void swap(T& a, T& b);
        std::vector<T> arr;
        int m_size = 0;
};

#include "minheap.h"


template <typename T>
MinHeap<T>::MinHeap(MinHeap<T>&& ob)
{
    this->arr = ob.arr;
    this->m_size = ob.m_size;

}

template <typename T>
MinHeap<T>::MinHeap()
{
}

template<typename T>
MinHeap<T>::MinHeap(const MinHeap<T>& ob)
{
    this->arr = ob.arr;
    this->m_size = ob.m_size;
}

template <typename T>
MinHeap<T>::MinHeap(std::initializer_list<T> li)
{
    for(T val : li)
    {
        this->push(val);
    }
}

template <typename T>
void MinHeap<T>::push(T val)
{
    arr.push_back(val);
    ++m_size;
    for(int i = m_size / 2 - 1; i >= 0; --i)
    {
        this->heapify(arr, i);
    }
}

template <typename T>
void MinHeap<T>::pop()
{
    if(m_size == 0)
    {
        return;
    }
    // swap(arr[0], arr[m_size - 1]);
    // std::cout << arr[m_size - 1] << " ";
    arr.pop_back();
    --m_size;
    for(int i = m_size / 2 - 1; i >= 0; --i)
    {
        heapify(arr, i);
    }
}

template <typename T>
T& MinHeap<T>::top()
{
    if(m_size == 0)
    {
        throw std::runtime_error("Heap is empty");
    }
    return arr[0];
}

template <typename T>
int MinHeap<T>::size()const
{
    return m_size;
}

template <typename T>
bool MinHeap<T>::empty()const
{
    return m_size == 0;
}

template <typename T>
void MinHeap<T>::clear()
{
    arr.clear();
}

template <typename T>
void MinHeap<T>::print()
{
    for(int i = 0; i < m_size; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void MinHeap<T>::heapify(std::vector<T>& arr, int i)
{
    int t = i;
    int l = left(i);
    int r = right(i);
    if(l < m_size && arr[t] > arr[l])
    {
        t = l;
    }
    if(r < m_size && arr[t] > arr[r])
    {
        t = r;
    }
    if(t != i)
    {
        swap(arr[i], arr[t]);
        heapify(arr, t);
    }
}

template <typename T>
void MinHeap<T>::swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
int MinHeap<T>::left(int i)
{
    return i * 2 + 1;
}

template <typename T>
int MinHeap<T>::right(int i)
{
    return i * 2 + 2;
}
