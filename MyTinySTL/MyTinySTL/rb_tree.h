//
// Created by 谯保林 on 2021/6/17.
//

#ifndef MYTINYSTL_RB_TREE_H
#define MYTINYSTL_RB_TREE_H

#endif //MYTINYSTL_RB_TREE_H

#include<initializer_list>
#include "iterator.h"
#include "allocator.h"
#include "uninitialized.h"

namespace MyTinySTL
{
    typedef bool _rb_tree_color_type;
    const _rb_tree_color_type _rb_tree_red = false;
    const _rb_tree_color_type _rb_tree_black = true;

    class _rb_tree_node_base;
    template <class T> class _rb_tree_node;

    template <class T> class _rb_tree_base_iterator;

    class _rb_tree_node_base
    {
    public:
        typedef _rb_tree_color_type color_type;
        typedef _rb_tree_node_base* base_ptr;

        color_type color;   // 节点颜色
        base_ptr parent;    // 父节点
        base_ptr left;      // 指向左节点
        base_ptr right;     // 指向右节点
    };

    template <class T>
    class rb_tree_traits
    {
    public:
        typedef _rb_tree_node_base* base_ptr;
    };


    template <class T>
    class _rb_tree_node : public _rb_tree_node_base
    {
    public:
        typedef _rb_tree_node_base<T>* node_ptr;
        T value;
    };

    template <class T>
    class _rb_tree_base_iterator : public MyTinySTL::iterator<MyTinySTL::Forbidirectional_iterator_tag, T>
    {
    public:
        typedef typename rb_tree_traits<T>::base_ptr base_ptr;

        base_ptr node;

        void increment() {
            if (node->right != nullptr) {
                node = node->right;
                while (node->left != nullptr) {
                    node = node->left;
                }
            }
            else {
                base_ptr tmp = node->parent;
                while (node == tmp->right) {
                    node = tmp;
                    tmp = tmp->parent;
                }
                if (node->right != tmp) {
                    node = tmp;
                }
            }
        }

        void decrement() {
            if (node->color == _rb_tree_red &&
                node->parent->parent == node) {       // 指向end()时
                node = node->right;
            }
            else if (node->left != nullptr) {
                base_ptr tmp = node->left;
                while (tmp->right != nullptr) {
                    tmp = tmp->right;
                }
                node = tmp;
            }
            else {
                base_ptr tmp = node->parent;
                while (node == tmp->left) {
                    node = tmp;
                    tmp = tmp->parent;
                }
                node = tmp;
            }
        }
    };
}