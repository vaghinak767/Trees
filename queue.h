#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include <iostream>
template <class T>
class Queue {
public:
    Queue(): arr{nullptr}, point{0}, m_size {0}, m_cap {0}{}
    ~Queue()
    {
        if(arr)
            delete arr;
    }
    T& front();
    T& back();
    bool empty();
    int size();
    void push(T element);
    void pop();

private:
    void resize();
    T* arr;
    int point;
    int m_size;
    int m_cap;
};

#endif
