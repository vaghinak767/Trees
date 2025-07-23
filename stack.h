#ifndef STACK_H
#define STACK_H
#include <vector>

template <class T>
class Stack
{
    private:
        std::vector<T> stack;
    public:
        Stack();
        Stack(const std::vector<T>&);
        Stack(const Stack<T>&);
        T& top();
        void pop();
        void push(T&);
        int size();
        bool empty();
};

#endif