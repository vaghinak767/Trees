#ifndef RB_TREE_H
#define RB_TREE_H

#include <iostream>
#include <queue>
#include <initializer_list>

namespace my_std
{
    template <class T>
    class RB_tree
    {   
        public:
            using value_type = T;
            using size_type = size_t;
            using reference = T&;
            using const_reference = const T&;
            using pointer = T*;
            using const_pointer = const T*;
        public:
            enum color
            {
                RED, 
                BLACK
            };
            struct RB_Node
            {
                value_type m_val;
                RB_Node* m_left;
                RB_Node* m_right;
                RB_Node* m_parent;
                color m_color;
                RB_Node();
                RB_Node(value_type val);
            };
        public:
            RB_tree();
            ~RB_tree();
            RB_tree(const_reference val);
    
        public:
            void insert(value_type value);
            void inorder() const;
            void preorder() const;
            void postorder() const;
            void level_order() const;
            void RB_delete(value_type val);
            const RB_Node* get_min() const;
            const RB_Node* get_max() const;
            size_type get_height() const;
            bool contains(value_type val) const;
            const RB_Node* find(value_type val) const;
            void clear();

        private:
            RB_Node* NIL;
            RB_Node* m_root;

            void m_insert_fix_up(RB_Node* newNode);
            void m_RB_delete(RB_Node* root, value_type val);
            void m_RB_delete_fix_up(RB_Node* x);
            void m_transplant(RB_Node* parent, RB_Node* with);
            RB_Node* m_left_rotate(RB_Node* node);
            RB_Node* m_right_rotate(RB_Node* node);
            void m_inorder(RB_Node* node) const;
            void m_preorder(RB_Node* node) const;
            void m_postorder(RB_Node* node) const;
            void m_level_order(std::queue<RB_Node*>& q) const;
            RB_Node* m_get_min(RB_Node* root) const;
            RB_Node* m_get_max(RB_Node* root) const;
            RB_Node* m_find(RB_Node* node, value_type val) const;
            size_type m_height(RB_Node* node) const;
            void m_clear(RB_Node* root);

    };
}

#include "RB_tree.hpp"
#endif
