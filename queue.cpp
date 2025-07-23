#include "queue.h"
// #ifndef FFFF
// #define FFFF
#include "Node.h"
#include "RBNode.h"
// #endif
template <class T>
T &Queue<T>::front()
{
    if (m_size == 0)
    {
        throw std::runtime_error("out of range");
    }
    return arr[(point + m_cap - m_size) % m_cap];
}

template <class T>
T &Queue<T>::back()
{
    if (m_size == 0)
    {
        throw std::runtime_error("out of range");
    }
    if (point == 0)
        return arr[m_cap - 1];
    return arr[point - 1];
}

template <class T>
bool Queue<T>::empty()
{
    return !m_size;
}

template <class T>
int Queue<T>::size()
{
    return m_size;
}

template <class T>
void Queue<T>::push(T element)
{
    if (m_cap == m_size)
    {
        resize();
    }
    arr[point] = element;
    ++m_size;
    ++point;
    if (point == m_cap)
        point = 0;
}

template <class T>
void Queue<T>::pop()
{
    arr[(point + m_cap - m_size) % m_cap] = 0;
    --m_size;
}

template <class T>
void Queue<T>::resize()
{
    if (m_cap == 0)
    {
        m_cap = 1;
        arr = new T[m_cap];
        return;
    }
    int k = m_cap;
    m_cap *= 2;
    T *tmp = new T[m_cap];
    for (int i = (point + k - m_size), j = 0; j < m_size; ++i, ++j)
    {
        tmp[j] = arr[i % k];
    }
    if (arr)
        delete arr;
    arr = tmp;
    point = m_size;
    tmp = nullptr;
}
template class Queue<RBNode<int> *>;
template class Queue<int>;
