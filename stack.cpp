#include "stack.h"

template <class T>
Stack<T>::Stack()
{

}

template <class T>
Stack<T>::Stack(const std::vector<T>& vector)
{
    stack = vector;
}


template <class T>
Stack<T>::Stack(const Stack<T>& other)
{
    stack = other.stack;
}

template <class T>
T& Stack<T>::top()
{
    return stack.back();
}

template <class T>
void Stack<T>::pop()
{
    stack.pop_back();
}

template <class T>
void Stack<T>::push(T& element)
{
    stack.push_back(element);
}

template <class T>
int Stack<T>::size()
{
    return stack.size();
}

template <class T>
bool Stack<T>::empty()
{
    return stack.empty();
}