# 📘 Binary Search Tree in C++

This project implements a generic **Binary Search Tree (BST)** with support for insertions, deletions, balancing (likely AVL-style), search, and traversals using **C++ templates**.

## ✅ Features

- Templated BST class: works with any comparable data type.
- Recursive `insert()` and `remove()` operations.
- Search for a specific value.
- Print the tree using in-order traversal.
- Breadth-First Search (BFS) traversal.
- Tree balancing functions (suggests AVL-like behavior).
- Memory-safe: includes destructor, copy/move constructors and assignment operators.
- Supports custom `queue` and `stack` implementations.

## 📁 File Structure


## 🧱 Class Overview

### Template Class: `BST<T>`

| Method | Description |
|--------|-------------|
| `insert(const T&)` | Inserts a value into the tree. |
| `remove(const T&)` | Removes a value from the tree. |
| `search(T&)` | Searches for a value, returns pointer to the node or `nullptr`. |
| `getMin(Node<T>*)` | Returns the node with the minimum value in a subtree. |
| `getMax(Node<T>*)` | Returns the node with the maximum value in a subtree. |
| `BFS()` | Prints the tree using breadth-first traversal. |
| `print()` | Prints the tree using in-order traversal. |
| `clear()` | Deletes all nodes in the tree. |
| `operator=`, constructors | Deep copy and move support. |

> Internal helper functions include balancing methods like `rr()`, `lr()`, `balance()`, and `getBalance()` to keep the tree height-balanced (AVL style).

## 🧪 Example Usage (in `main.cpp`)

```cpp
#include "BST.h"

int main() {
    BST<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.print();  // In-order print
    tree.BFS();    // Level-order print

    tree.remove(5);
    tree.print();

    return 0;
}
