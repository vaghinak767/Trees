#ifndef RB_TREE_HPP
#define RB_TREE_HPP
#include "RB_tree.h"

namespace my_std
{
    template <class T>
    RB_tree<T>::RB_Node::RB_Node() : m_left(nullptr), m_right(nullptr), m_parent(nullptr), m_color{color::BLACK} {}

    template <class T>
    RB_tree<T>::RB_Node::RB_Node(value_type val) : m_val(val), m_left(nullptr), m_right(nullptr), m_parent(nullptr), m_color{color::RED} {}

    template <class T>
    RB_tree<T>::RB_tree() : NIL(new RB_Node()), m_root(NIL) {}

    template <class T>
    RB_tree<T>::RB_tree(const_reference val) : NIL(new RB_Node()), m_root(new RB_Node(val)) 
    {
        m_root->m_left = NIL;
        m_root->m_right = NIL;
        m_root->m_parent = NIL;
        m_root->m_color = color::BLACK;
    }

    template <class T>
    RB_tree<T>::~RB_tree()
    {
        clear();
        delete NIL;
    }

    template<class T>
    void RB_tree<T>::insert(value_type value)
    {
        RB_Node* prev = NIL;
        RB_Node* temp = m_root;
        while(temp != NIL)
        {
            prev = temp;           
            if(temp->m_val > value)
            {
                temp = temp->m_left;
            }
            else
            {
                temp = temp->m_right;
            }
        }
        RB_Node* newNode = new RB_Node(value);
        newNode->m_left = NIL;
        newNode->m_right = NIL;
        newNode->m_parent = prev;
        if(prev == NIL)
        {
            m_root = newNode;
        }
        else if(prev->m_val > newNode->m_val)
        {
            prev->m_left = newNode;
        }
        else
        {
            prev->m_right = newNode;
        }
        m_insert_fix_up(newNode);
    }

    template <class T>
    void RB_tree<T>::m_insert_fix_up(RB_Node* newNode)
    {
        while(newNode->m_parent->m_color == color::RED)
        {
            if(newNode->m_parent == newNode->m_parent->m_parent->m_left)
            {
                RB_Node* uncle = newNode->m_parent->m_parent->m_right;
                if(uncle->m_color == color::RED) // Case 1: Uncle is red
                {
                    newNode->m_parent->m_color = color::BLACK;
                    uncle->m_color = color::BLACK;
                    newNode->m_parent->m_parent->m_color = color::RED;
                    newNode = newNode->m_parent->m_parent;
                }
                else // Uncle is black
                {
                    if(newNode == newNode->m_parent->m_right)// Case 2: Node is right child
                    {
                        newNode = newNode->m_parent;
                        m_left_rotate(newNode);
                    }

                    // Case 3: Node is left child
                    newNode->m_parent->m_color = color::BLACK;
                    newNode->m_parent->m_parent->m_color = color::RED;
                    m_right_rotate(newNode->m_parent->m_parent);
                }
            }
            else// Same as above, mirror case
            {
                RB_Node* uncle = newNode->m_parent->m_parent->m_left;
                if(uncle->m_color == color::RED)
                {
                    newNode->m_parent->m_color = color::BLACK;
                    uncle->m_color = color::BLACK;
                    newNode->m_parent->m_parent->m_color = color::RED;
                    newNode = newNode->m_parent->m_parent;
                }
                else
                {
                    if(newNode == newNode->m_parent->m_left)
                    {
                        newNode = newNode->m_parent;
                        m_right_rotate(newNode);
                    }
                    newNode->m_parent->m_color = color::BLACK;
                    newNode->m_parent->m_parent->m_color = color::RED;
                    m_left_rotate(newNode->m_parent->m_parent);
                }
            }
        }
        m_root->m_color = color::BLACK;
    }

    template <typename T>
    void RB_tree<T>::RB_delete(value_type val)
    {
        m_RB_delete(m_root,val);
    }

    template <typename T>
    const typename RB_tree<T>::RB_Node* RB_tree<T>::get_max() const
    {
        return m_get_max(m_root);
    }

    template <typename T>
    const typename RB_tree<T>::RB_Node* RB_tree<T>::get_min() const
    {
        return m_get_min(m_root);
    }

    template <typename T>
    typename RB_tree<T>::size_type RB_tree<T>::get_height() const
    {
        return m_height(m_root);
    }

    template <typename T>
    bool RB_tree<T>::contains(value_type val) const
    {
        return m_find(m_root, val) != NIL ? true : false;
    }

    template <typename T>
    const typename RB_tree<T>::RB_Node* RB_tree<T>::find(value_type val) const
    {
        RB_Node* node = m_find(m_root,val);
        return node != NIL ? node : nullptr;
    }

    template <typename T>
    void RB_tree<T>::clear()
    {
        m_clear(m_root);
        m_root = NIL;
    }

    template <typename T>
    void RB_tree<T>::m_RB_delete(RB_Node* root, value_type val)
    {
        RB_Node* temp = root;
        while(temp != NIL)
        {
            if(temp->m_val > val)
            {
                temp = temp->m_left;
            }
            else if(temp->m_val < val)
            {
                temp = temp->m_right;
            }
            else
            {
                break;
            }
        }
       
        RB_Node* del = temp;
        color del_color = del->m_color;
        RB_Node* x = NIL;
        if(del->m_left == NIL)//Case 1: the node to delete has no left child
        {
            x = del->m_right;
            m_transplant(del, del->m_right);
        }
        else if(del->m_right == NIL)//Case 2: the node to delete has no right child
        {
            x = del->m_left;
            m_transplant(del, del->m_left);
        }
        else//Case 3: the node to delete has both children
        {
            RB_Node* node_to_be_del = m_get_min(del->m_right);
            del_color = node_to_be_del->m_color;
            x = node_to_be_del->m_right;
            if(node_to_be_del->m_parent == del)
            {
                x->m_parent = node_to_be_del;
            }   
            else 
            {
                m_transplant(node_to_be_del,node_to_be_del->m_right);
                node_to_be_del->m_right = del->m_right;
                node_to_be_del->m_right->m_parent = node_to_be_del;
            }
            m_transplant(del,node_to_be_del);
            node_to_be_del->m_left = del->m_left;
            node_to_be_del->m_left->m_parent = node_to_be_del;
            node_to_be_del->m_color = del->m_color;
        }
        if(del_color == color::BLACK)
        {
            m_RB_delete_fix_up(x);
        }
        delete del;
    }

    template <typename T>
    void RB_tree<T>::m_RB_delete_fix_up(RB_Node* x)
    {   
        while(x != m_root && x->m_color == color::BLACK)
        {
            if(x == x->m_parent->m_left)
            {
                RB_Node* sibling = x->m_parent->m_right;
                if(sibling->m_color == color::RED) // Case 1: x's sibling is red 
                {   
                    sibling->m_color = color::BLACK;
                    x->m_parent->m_color = color::RED;
                    m_left_rotate(x->m_parent);
                    sibling = x->m_parent->m_right;

                }
                if(sibling->m_left->m_color == color::BLACK && sibling->m_right->m_color == color::BLACK) // Case 2: sibling's children are black
                {
                    sibling->m_color = color::RED;
                    x = x->m_parent;
                }
                else
                {
                    if(sibling->m_right->m_color == color::BLACK) // Case 3 : sibling's right child is black, left child is red
                    {
                        sibling->m_left->m_color = color::BLACK;
                        sibling->m_color = color::RED;
                        m_right_rotate(sibling);
                        sibling = x->m_parent->m_right;
                    }
                    // Case 4: sibling's right child is red

                    sibling->m_color = x->m_parent->m_color;
                    x->m_parent->m_color = color::BLACK;
                    sibling->m_right->m_color = color::BLACK;
                    m_left_rotate(x->m_parent);
                    x = m_root;
                }
            }
            else// Mirror case
            {
                RB_Node* sibling = x->m_parent->m_left;
                if(sibling->m_color == color::RED)
                {
                    sibling->m_color = color::BLACK;
                    x->m_parent->m_color = color::RED;
                    m_right_rotate(x->m_parent);
                    sibling = x->m_parent->m_left;
                }
                if(sibling->m_left->m_color == color::BLACK && sibling->m_right->m_color == color::BLACK)
                {
                    sibling->m_color = color::RED;
                    x = x->m_parent;
                }
                else
                {
                    if(sibling->m_left->m_color == color::BLACK)
                    {
                        sibling->m_right->m_color = color::BLACK;
                        sibling->m_color = color::RED;
                        m_left_rotate(sibling);
                        sibling = x->m_parent->m_left;
                    }
                    sibling->m_color = x->m_parent->m_color;
                    x->m_parent->m_color = color::BLACK;
                    sibling->m_left->m_color = color::BLACK;
                    m_right_rotate(x->m_parent);
                    x = m_root;
                }
            }
        }
        x->m_color = color::BLACK;
    }

    template <typename T>
    void RB_tree<T>::m_transplant(RB_Node* parent, RB_Node* with)
    {
        if(parent->m_parent == NIL)
        {
            m_root = with;
        }
        else if(parent == parent->m_parent->m_left)
        {
            parent->m_parent->m_left = with;
        }
        else
        {
            parent->m_parent->m_right = with;
        }
        
        with->m_parent = parent->m_parent;
        
    }

        
    template <class T>
    void RB_tree<T>::inorder() const
    {
        if(m_root != NIL)
        {
            m_inorder(m_root);
            std::cout << "NIL" << std::endl;

        }
    }

    template <class T>
    void RB_tree<T>::preorder() const
    {
        if(m_root != NIL)
        {
            m_preorder(m_root);
            std::cout << "NIL" << std::endl;
        }
    }

    template <class T>
    void RB_tree<T>::postorder() const
    {
        if(m_root != NIL)
        { 
            m_postorder(m_root);
            std::cout << "NIL" << std::endl;
        }
    }

    template <class T>
    void RB_tree<T>::level_order() const
    {   
        if(m_root != NIL)
        {
            std::queue<RB_Node*> q;
            q.push(m_root);
            m_level_order(q);
            std::cout << "NIL" << std::endl;

        }
    }

    template<class T>
    typename RB_tree<T>::RB_Node* RB_tree<T>::m_left_rotate(RB_Node* node)
    {
        RB_Node* temp = node->m_right;
        node->m_right = temp->m_left;

        if(temp->m_left != NIL)
        {
            temp->m_left->m_parent = node;
        }

        temp->m_parent = node->m_parent;

        if(node->m_parent == NIL)
        {
            m_root = temp;
        }
        else if(node == node->m_parent->m_left)
        {
            node->m_parent->m_left = temp;
        }
        else
        {
            node->m_parent->m_right = temp;
        }
        temp->m_left = node;
        node->m_parent = temp;
        return temp;
    }

    template<class T>
    typename RB_tree<T>::RB_Node* RB_tree<T>::m_right_rotate(RB_Node* node)
    {
        RB_Node* temp = node->m_left;
        node->m_left = temp->m_right;

        if(temp->m_right != NIL)
        {
            temp->m_right->m_parent = node;
        }

        temp->m_parent = node->m_parent;

        if(node->m_parent == NIL)
        {
            m_root = temp;
        }
        else if(node == node->m_parent->m_left)
        {
            node->m_parent->m_left = temp;
        }
        else
        {
            node->m_parent->m_right = temp;
        }

        temp->m_right = node;
        node->m_parent = temp;
        return temp;
    }

    template <class T>
    void RB_tree<T>::m_inorder(RB_Node* node) const
    {
        if(node != NIL)
        {
            m_inorder(node->m_left);
            std::string col = node->m_color == color::RED ? "RED" : "BLACK";
            std::cout << node->m_val << " " << col << "-> ";
            m_inorder(node->m_right);
        }
    }

    template <class T>
    void RB_tree<T>::m_preorder(RB_Node* node) const
    {
        if(node != NIL)
        {
            std::string col = node->m_color == color::RED ? "RED" : "BLACK";
            std::cout << node->m_val << " " << col << "-> ";
            m_preorder(node->m_left);
            m_preorder(node->m_right);
        }
    }

    template <class T>
    void RB_tree<T>::m_postorder(RB_Node* node) const
    {
        if(node != NIL)
        {
            m_postorder(node->m_left);
            m_postorder(node->m_right);
            std::string col = node->m_color == color::RED ? "RED" : "BLACK";
            std::cout << node->m_val << " " << col << "-> ";
        }
    }

    template <typename T>
    void RB_tree<T>::m_clear(RB_Node* root)
    {
        if(root != NIL)
        {
            m_clear(root->m_left);
            m_clear(root->m_right);
            delete root;
        }
    }

    template <class T>
    void RB_tree<T>::m_level_order(std::queue<RB_Node*>& q) const
    {
        if(q.empty())
        {
            return;
        }
        RB_Node* temp = q.front();
        q.pop();
        std::string col = temp->m_color == color::RED ? "RED" : "BLACK";
        std::cout << temp->m_val << " " << col << "-> ";
        if(temp->m_left != NIL)
        {
            q.push(temp->m_left);
        }
        if(temp->m_right != NIL)
        {
            q.push(temp->m_right);
        }
        m_level_order(q);
    }

    template <typename T>
    typename RB_tree<T>::RB_Node* RB_tree<T>::m_get_min(RB_Node* root) const
    {
        if(root == NIL)
        {
            return NIL;
        }

        while (root->m_left != NIL)
        {
            root = root->m_left;
        }
        
        return root;
    }

    template <typename T>
    typename RB_tree<T>::RB_Node* RB_tree<T>::m_get_max(RB_Node* root) const
    {
        if(root == NIL)
        {
            return NIL;
        }

        while (root->m_right != NIL)
        {
            root = root->m_right;
        }
        
        return root;
    }

    template <typename T>
    typename RB_tree<T>::RB_Node* RB_tree<T>::m_find(RB_Node* root, value_type val)const
    {
        if(root == NIL)
        {
            return NIL;
        }
        else if(root->m_val > val)
        {
            return m_find(root->m_left, val);
        }
        else if(root->m_val < val)
        {
            return m_find(root->m_right, val);
        }
        return root;
        
    }

    template <typename T>
    typename RB_tree<T>::size_type RB_tree<T>::m_height(RB_Node* root) const
    {
        if(root == NIL)
        {
            return 0;
        }
        size_type left = m_height(root->m_left);
        size_type right = m_height(root->m_right);

        return std::max(left, right) + 1;
    }
}

#endif
