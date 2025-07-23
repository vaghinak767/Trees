#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "Node.h"
#include <iostream>
#include "queue.h"
#include "stack.h"

template <class T>
class BST
{
public:
    BST() : root{nullptr} {}
    BST(const BST &obj);
    BST(BST &&obj);
    ~BST();
    const BST &operator=(const BST &obj);
    const BST &operator=(BST &&obj);
    void insert(const T &val);
    void remove(const T &val);
    Node<T> *getMin(Node<T> *node) const;
    Node<T> *getMax(Node<T> *node) const;
    Node<T> *search(T &val) const;
    void clear();
    void print();
    void BFS();

private:
    Node<T> *root = nullptr;

private:
    Node<T> *insert(Node<T> *node, const T val);
    Node<T> *rem(Node<T> *node, const T &val);
    void ins(const T &);
    Node<T> *rr(Node<T> *);
    Node<T> *lr(Node<T> *);
    Node<T> *balance(Node<T> *);
    T Max(T a, T b);
    int getBalance(Node<T> *);
    int getHeight(Node<T> *);
    void p(Node<T> *);
    void c(Node<T> *);
    Node<T> *copyTree(const Node<T> *other)
    {
        if (other == nullptr)
            return nullptr;
        Node<T> *node = new Node<T>(other->key);
        node->left = copyTree(other->left);
        node->right = copyTree(other->right);
        return node;
    }
};

#endif
