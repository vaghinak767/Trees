#ifndef NODE_H
#define NODE_H
#include <iostream>

struct Node
{
	Node(int value);
        Node();
        int data;
        Node *next;
        Node *previous;
        Node *great;
        Node *small;
};

#endif