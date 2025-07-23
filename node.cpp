#include "node.h"

Node::Node()
{
    data = 0;
    next = nullptr;
    previous = nullptr;
    small = nullptr;
    great = nullptr;
}

Node::Node(int value)
{
	data = value;
    next = nullptr;
    previous = nullptr;
    small = nullptr;
    great = nullptr;
}