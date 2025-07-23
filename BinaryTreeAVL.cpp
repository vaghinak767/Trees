#include "BinaryTreeAVL.h"
#include "queue.h"
template <class T>
void print(BST<T> &);
template <class T>
BST<T>::BST(const BST<T> &obj)
{
    this->root = copyTree(obj.root);
}

template <class T>
BST<T>::BST(BST<T> &&obj)
{
    root = obj.root;
    obj.root = nullptr;
}

template <class T>
BST<T>::~BST()
{
    c(this->root);
}

template <class T>
const BST<T> &BST<T>::operator=(const BST<T> &obj)
{
    root = copyTree(obj.root);
    return *this;
}
template <class T>
const BST<T> &BST<T>::operator=(BST<T> &&obj)
{
    root = obj.root;
    obj.root = nullptr;
    return *this;
}

template <typename T>
Node<T> *BST<T>::insert(Node<T> *node, const T val)
{
    if (!node)
    {
        return new Node<T>(val);
    }
    if (val > node->key)
    {
        node->right = insert(node->right, val);
    }
    else
    {
        if (val < node->key)
        {
            node->left = insert(node->left, val);
        }
        else
        {
            return node;
        }
    }
    node->h = getHeight(node);
    int balance = getBalance(node);
    if (balance > 1 && val < node->left->key)
    {
        return rr(node);
    }
    if (balance < -1 && val > node->right->key)
    {
        return lr(node);
    }
    if (balance > 1 && val > node->left->key)
    {
        node->left = lr(node->left);
        return rr(node);
    }
    if (balance < -1 && val < node->right->key)
    {
        node->right = rr(node->right);
        return lr(node);
    }
    return node;
}

template <class T>
void BST<T>::insert(const T &val)
{
    root = insert(root, val);
    return;
}

template <typename T>
void BST<T>::ins(const T &val)
{
    if (!root)
    {
        root = new Node<T>(val);
        root->key = val;
        root->h = 0;
        return;
    }
    Node<T> *p = nullptr;
    Node<T> *tmp = root;
    while (true)
    {
        if (val > tmp->key)
        {
            if (!tmp->right)
            {
                tmp->right = new Node<T>(val);
                break;
            }
            else
            {
                tmp = tmp->right;
            }
        }
        else
        {
            if (!tmp->left)
            {
                tmp->left = new Node<T>(val);
                break;
            }
            else
            {
                tmp = tmp->left;
            }
        }
    }
    tmp->h = 0;
    root->h = Max(getHeight(root->right), getHeight(root->left)) + 1;
}

template <typename T>
void BST<T>::remove(const T &val)
{
    // if (!root)
    //     return;
    // Node<T> *tmp = root;
    // Node<T> *p = nullptr;
    // while (tmp)
    // {
    //     if (tmp->key > val)
    //     {
    //         p = tmp;
    //         tmp = tmp->left;
    //     }
    //     else
    //     {
    //         if (tmp->key < val)
    //         {
    //             p = tmp;
    //             tmp = tmp->right;
    //         }
    //         else
    //         {
    //             if (!tmp->right && !tmp->left)
    //             {
    //                 delete tmp;
    //                 return;
    //             }
    //             if (!tmp->left)
    //             {
    //                 if (tmp == p->left)
    //                 {
    //                     p->left = tmp->right;
    //                     delete tmp;
    //                     return;
    //                 }
    //                 if (tmp == p->right)
    //                 {
    //                     p->right = tmp->right;
    //                     delete tmp;
    //                     return;
    //                 }
    //             }
    //             if (!tmp->right)
    //             {
    //                 if (tmp == p->left)
    //                 {
    //                     p->left = tmp->left;
    //                     delete tmp;
    //                     return;
    //                 }
    //                 if (tmp == p->right)
    //                 {
    //                     p->right = tmp->left;
    //                     delete tmp;
    //                     return;
    //                 }
    //             }
    //             Node<T>* t = tmp->right;
    //             p = tmp;
    //             while(t->left)
    //             {
    //                 p = t;
    //                 t = t->left;
    //             }
    //             tmp->key = t->key;
    //             if(t == p->left)
    //             {
    //                 p->left = nullptr;
    //                 delete t;
    //                 return;
    //             }
    //             else{
    //                 p->right = nullptr;
    //                 delete t;
    //                 return;
    //             }
    //         }
    //     }
    // }
    root = rem(root, val);
    // if (root)
    // {
    //     root->h = getBalance(root);
    //     root = balance(root);
    // }
}

template <typename T>
Node<T> *BST<T>::rem(Node<T> *node, const T &val)
{
    if (!node)
    {
        return nullptr;
    }
    if (node->key > val)
    {
        node->left = rem(node->left, val);
        return node;
    }
    else
    {
        if (node->key < val)
        {
            node->right = rem(node->right, val);
            return node;
        }
        else if (node->key == val)
        {
            if (!node->left)
            {
                Node<T> *tmp = node->right;
                delete node;
                return tmp;
            }
            if (!node->right)
            {
                Node<T> *tmp = node->left;
                delete node;
                return tmp;
            }
            Node<T> *tmp = node->left;
            while (tmp->right)
            {
                tmp = tmp->right;
            }
            node->key = tmp->key;
            node->left = rem(tmp, tmp->key);
            return node;
        }
    }
    if (!node)
        return node;
    node->h = getHeight(node);
    int balance = getBalance(node);
    if (balance > 1 &&
        getBalance(node->left) >= 0)
        return rr(root);
    if (balance > 1 &&
        getBalance(node->left) < 0)
    {
        node->left = lr(node->left);
        return rr(node);
    }
    if (balance < -1 &&
        getBalance(node->right) <= 0)
        return lr(node);
    if (balance < -1 &&
        getBalance(node->right) > 0)
    {
        node->right = rr(node->right);
        return lr(node);
    }

    return node;
}

// template <class T>
// void BST<T>::remove(const T &val)
// {
//     if (!this->root)
//         return;
//     if (this->root->key == val && !this->root->left && !this->root->right)
//     {
//         delete this->root;
//         return;
//     }
//     if (this->root->key == val && this->root->right)
//     {
//     }
//     Node<E> *parent = this->root;
//     Node<E> *tmp = nullptr;
//     while (parent)
//     {
//         if (parent->left && parent->left->key == val)
//         {
//             if (!parent->left->left && !parent->left->right)
//             {
//                 delete parent->left;
//                 parent->left = nullptr;
//                 return;
//             }
//             if (!parent->left->left && parent->left->right)
//             {
//                 tmp = parent->left->right;
//                 delete parent->left;
//                 parent->left = tmp;
//                 return;
//             }
//             if (!parent->left->right && parent->left->left)
//             {
//                 tmp = parent->left->left;
//                 delete parent->left;
//                 parent->left = tmp;
//                 return;
//             }
//         }
//         if (parent->right && parent->right->key == val)
//         {
//             if (!parent->right->left && !parent->right->right)
//             {
//                 delete parent->right;
//                 parent->left = nullptr;
//                 return;
//             }
//             if (!parent->right->left && parent->right->right)
//             {
//                 tmp = parent->left->right;
//                 delete parent->right;
//                 parent->right = tmp;
//                 return;
//             }
//             if (!parent->left->right && parent->left->left)
//             {
//                 tmp = parent->left->left;
//                 delete parent->left;
//                 parent->left = tmp;
//                 return;
//             }
//         }
//     }
// }

template <class T>
Node<T>* BST<T>::getMin(Node<T> *node) const
{
    if (!node)
    {
        throw std::runtime_error("BST is empty");
    }
    while (node->left)
    {
        node = node->left;
    }
    return node;
}

template <class T>
Node<T>* BST<T>::getMax(Node<T> *node) const
{
    if (!node)
    {
        throw std::runtime_error("BST is empty");
    }
    while (node->right)
    {
        node = node->right;
    }
    return node;
}

template <class T>
Node<T>* BST<T>::search(T& val) const
{
    Node<T>* tmp = root;
    while(tmp)
    {
        if(tmp->key > val)
        {
            tmp = tmp->left;
        }
        if(tmp->key < val)
        {
            tmp = tmp->right;
        }
        if(tmp->key == val)
        {
            return tmp;
        }
    }
    return nullptr;
} 

template <class T>
void BST<T>::print()
{
    p(this->root);
    std::cout << std::endl;
}

template <class T>
void BST<T>::p(Node<T> *tmp)
{
    if (!tmp)
        return;
    p(tmp->left);
    std::cout << tmp->key << " ";
    p(tmp->right);
    // this->BFS();
}

template <class T>
void BST<T>::clear()
{
    if (!this->root)
    {
        return;
    }
    c(this->root);
}

template <class T>
void BST<T>::c(Node<T> *node)
{
    if (!node)
        return;
    c(node->left);
    c(node->right);
    delete node;
}

template <class T>
void BST<T>::BFS()
{
    if (!root)
    {
        return;
    }
    Queue<Node<T> *> q;
    q.push(root);
    while (!q.empty())
    {
        Node<T> *tmp = q.front();
        q.pop();
        std::cout << tmp->key << " ";
        if (tmp->left)
        {
            q.push(tmp->left);
        }
        if (tmp->right)
        {
            q.push(tmp->right);
        }
    }
    std::cout << std::endl;
}

template <class T>
Node<T> *BST<T>::rr(Node<T> *node)
{
    Node<T> *x = node->left;
    Node<T> *tmp = x->right;
    x->right = node;
    node->left = tmp;
    x->h = getBalance(x);
    node->h = getBalance(node);
    return x;
}
template <class T>
Node<T> *BST<T>::lr(Node<T> *node)
{
    Node<T> *x = node->right;
    Node<T> *tmp = x->left;
    x->left = node;
    node->right = tmp;
    x->h = getBalance(x);
    node->h = getBalance(node);
    return x;
}

template <class T>
Node<T> *BST<T>::balance(Node<T> *node)
{
    if (!node)
    {
        return nullptr;
    }
    if (node->left)
        node->left->h = getBalance(node->left);
    if (node->right)
        node->right->h = getBalance(node->right);
    node->h = getBalance(node);
    if (node->h == 0 || node->h == -1 || node->h == 1)
    {
        node->left = balance(node->left);
        node->right = balance(node->right);
        return node;
    }
    if (node->h < -1 && node->right && node->right->h < -1)
    {
        node->right = balance(node->right);
        return node;
    }
    if (node->h > 1 && node->left && node->left->h > 1)
    {
        node->left = balance(node->left);
        return node;
    }
    if (node->h < -1 && node->right && (node->right->h == -1 || node->right->h == 0 || node->left->h == 1))
    {
        Node<T> *tmp = node->right;
        Node<T> *x = nullptr;
        while (tmp->left)
        {
            x = tmp;
            tmp = tmp->left;
        }
        tmp->left = node;
        if (x)
            x->left = tmp->right;
        if (x)
            tmp->right = node->right;
        node->right = nullptr;
        tmp->right = balance(tmp->right);
        tmp->left = balance(node);
        return tmp;
    }
    if (node->h > 1 && node->left && (node->left->h == -1 || node->left->h == 0 || node->left->h == 1))
    {
        Node<T> *tmp = node->left;
        Node<T> *x = nullptr;
        while (tmp->right)
        {
            x = tmp;
            tmp = tmp->right;
        }
        tmp->right = node;
        if (x)
            x->right = tmp->left;
        if (x)
            tmp->left = node->left;
        node->left = nullptr;
        tmp->right = balance(node);
        tmp->left = balance(tmp->left);
        return tmp;
    }
    return node;
}

template <class T>
T BST<T>::Max(T a, T b)
{
    return a > b ? a : b;
}

template <class T>
int BST<T>::getHeight(Node<T> *node)
{
    if (!node)
        return -1;
    return Max(getHeight(node->left), getHeight(node->right)) + 1;
}

template <class T>
int BST<T>::getBalance(Node<T> *node)
{
    if (!node)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// template class Queue<Node<int> *>;
template class BST<int>;
