//
// Created by 谯保林 on 2021/6/17.
//

#ifndef MYTINYSTL_RB_TREE_H
#define MYTINYSTL_RB_TREE_H

#include<initializer_list>
#include "iterator.h"
#include "allocator.h"
#include "uninitialized.h"
#include "memory.h"

namespace MyTinySTL
{
    typedef bool _rb_tree_color_type;
    static constexpr _rb_tree_color_type _rb_tree_red = false;
    static constexpr _rb_tree_color_type _rb_tree_black = true;

    class _rb_tree_node_base;
    template <class T> class _rb_tree_node;
    template <class T> class _rb_tree_iterator;
    template <class T> class _rb_tree_const_iterator;

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

        base_ptr get_base_ptr() {
            return &*this;
        }
    };

    template <class T>
    class _rb_tree_node : public _rb_tree_node_base
    {
    public:
        typedef _rb_tree_node_base*                         base_ptr;
        typedef _rb_tree_node<T>*                           node_ptr;

        T value;

        base_ptr get_base_ptr() {
            return static_cast<base_ptr>(&*this);
        }

        node_ptr get_node_ptr() {
            return &*this;
        }
    };

    template <class T, bool>
    class rb_tree_value_traits_imp
    {
    public:
        typedef T key_type;
        typedef T value_type;
        typedef T mapped_type;

        template <class Ty>
        static const key_type get_key(const Ty& value) {
            return value;
        }

        template <class Ty>
        static const value_type get_value(const Ty& value) {
            return value;
        }
    };

    template <class T>
    class rb_tree_value_traits_imp<T, true>
    {
    public:
        typedef typename std::remove_cv<typename T::first_type>::type key_type;             // map中的键
        typedef typename T::second_type                               mapped_type;          // map中键所关联值的类型
        typedef T                                                     value_type;           // map中具体值类型 pair<const v1, v2>

        template <class Ty>
        static const key_type get_key(const Ty& value) {
            return value.first;
        }

        template <class Ty>
        static const value_type get_value(const Ty& value) {
            return value;
        }
    };

    template <class T>
    class rb_tree_value_traits
    {
    public:
        static constexpr bool is_map = MyTinySTL::is_pair<T>::value;

        typedef rb_tree_value_traits_imp<T, is_map>   value_traits_imp;

        typedef typename value_traits_imp::value_type  value_type;
        typedef typename value_traits_imp::key_type    key_type;
        typedef typename value_traits_imp::mapped_type mapped_type;

        template <class Ty>
        static const key_type get_key(const Ty& value) {
            return value_traits_imp::get_key(value);
        }

        template <class Ty>
        static const value_type get_value(const Ty& value) {
            return value_traits_imp::get_value(value);
        }
    };

    template <class T>
    class rb_tree_traits
    {
    public:
        typedef _rb_tree_color_type       color_type;

        typedef rb_tree_value_traits<T>   value_traits;

        typedef typename value_traits::key_type    key_type;
        typedef typename value_traits::value_type  value_type;
        typedef typename value_traits::mapped_type mapped_type;

        typedef value_type*               pointer;
        typedef value_type&               reference;
        typedef const value_type*         const_pointer;
        typedef const value_type&         const_reference;

        typedef _rb_tree_node_base        base_type;
        typedef _rb_tree_node<T>          tree_type;

        typedef base_type*                base_ptr;
        typedef tree_type*                node_ptr;
    };


    template <class T>
    class _rb_tree_base_iterator : public MyTinySTL::iterator<MyTinySTL::bidirectional_iterator_tag, T>
    {
    public:
        typedef typename rb_tree_traits<T>::base_ptr base_ptr;

        base_ptr node;

        _rb_tree_base_iterator() : node(nullptr) {}
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

        bool operator==(const _rb_tree_base_iterator& rhs) { return node == rhs.node; }
        bool operator!=(const _rb_tree_base_iterator& rhs) { return node != rhs.node; }
    };

    template <class T>
    class _rb_tree_iterator : public _rb_tree_base_iterator<T>
    {
    public:
        typedef rb_tree_traits<T>                           tree_traits;

        typedef typename tree_traits::pointer               pointer;
        typedef typename tree_traits::reference             reference;

        typedef typename tree_traits::base_type             base_type;
        typedef typename tree_traits::tree_type             tree_type;

        typedef typename tree_traits::base_ptr              base_ptr;
        typedef typename tree_traits::node_ptr              node_ptr;

        typedef _rb_tree_iterator<T>                        iterator;
        typedef _rb_tree_const_iterator<T>                  const_iterator;
        typedef iterator                                    self;

        using _rb_tree_base_iterator<T>::node;

        _rb_tree_iterator() = default;
        _rb_tree_iterator(base_ptr tmp) {
            node = tmp;
        }
        _rb_tree_iterator(node_ptr tmp) {
            node = tmp;
        }
        _rb_tree_iterator(const iterator& rhs) {
            node = rhs.node;
        }
        _rb_tree_iterator(const const_iterator& rhs) {
            node = rhs.node;
        }

        reference operator*() const {
            return static_cast<node_ptr>(node)->value;
        }

        pointer operator->() const {
            return &(operator*());
        }

        self& operator++() {
            this->increment();
            return *this;
        }

        self operator++(int) {
            self tmp = *this;
            ++*this;
            return tmp;
        }

        self& operator--() {
            this->decrement();
            return *this;
        }

        self operator--(int) {
            self tmp = *this;
            --*this;
            return tmp;
        }

    };

    template <class T>
    class _rb_tree_const_iterator : public _rb_tree_base_iterator<T>
    {
    public:
        typedef rb_tree_traits<T>                           tree_traits;

        typedef typename tree_traits::const_pointer               pointer;
        typedef typename tree_traits::const_reference             reference;

        typedef typename tree_traits::base_type             base_type;
        typedef typename tree_traits::tree_type             tree_type;

        typedef typename tree_traits::base_ptr              base_ptr;
        typedef typename tree_traits::node_ptr              node_ptr;

        typedef _rb_tree_iterator<T>                        iterator;
        typedef iterator                                    self;

        using _rb_tree_base_iterator<T>::node;

        _rb_tree_const_iterator() = default;
        _rb_tree_const_iterator(base_ptr tmp) {
            node = tmp;
        }
        _rb_tree_const_iterator(node_ptr tmp) {
            node = tmp;
        }
        _rb_tree_const_iterator(const iterator& rhs) {
            node = rhs.node;
        }
        _rb_tree_const_iterator(_rb_tree_const_iterator& rhs) {
            node = rhs.node;
        }

        reference operator*() const {
            return static_cast<node_ptr>(node)->value;
        }

        pointer operator->() const {
            return &(operator*());
        }

        self& operator++() {
            this->increment();
            return *this;
        }

        self operator++(int) {
            self tmp = *this;
            ++*this;
            return tmp;
        }

        self& operator--() {
            this->decrement();
            return *this;
        }

        self operator--(int) {
            self tmp(*this);
            --*this;
            return *this;
        }
    };

   // rb_tree 模板类型
   template <class T, class Compare>
   class rb_tree
   {
   public:
       typedef rb_tree_value_traits<T>                  value_traits;
       typedef rb_tree_traits<T>                        tree_traits;

       typedef typename tree_traits::base_type          base_type;
       typedef typename tree_traits::base_ptr           base_ptr;
       typedef typename tree_traits::tree_type          tree_type;
       typedef typename tree_traits::node_ptr           node_ptr;
       typedef typename tree_traits::value_type         value_type;
       typedef typename tree_traits::key_type           key_type;
       typedef typename tree_traits::mapped_type        mapped_type;

       typedef MyTinySTL::allocator<T>                  allocator_type;
       typedef MyTinySTL::allocator<T>                  data_allocator;
       typedef MyTinySTL::allocator<base_type>          base_allocator;
       typedef MyTinySTL::allocator<tree_type>          node_allocator;

       typedef typename MyTinySTL::allocator<T>::pointer              pointer;
       typedef typename MyTinySTL::allocator<T>::const_pointer        const_pointer;
       typedef typename MyTinySTL::allocator<T>::reference            reference;
       typedef typename MyTinySTL::allocator<T>::const_reference      const_reference;
       typedef typename MyTinySTL::allocator<T>::size_type            size_type;
       typedef typename MyTinySTL::allocator<T>::difference_type      difference_type;

       typedef _rb_tree_iterator<T>                                   iterator;
       typedef _rb_tree_const_iterator<T>                             const_iterator;
       typedef reverse_iterator<iterator>                             reverse_iterator;
       typedef MyTinySTL::reverse_iterator<const_iterator>            const_reverse_iterator;

       Compare key_comp() const { return key_compare; }
   private:
       size_type       node_count;            // 节点数量
       base_ptr        header;                // 和父节点互为父节点
       Compare         key_compare;           // 节点间大小比较规则

   private:
       base_ptr& root() const
       { return header->parent; }
       base_ptr& leftmost() const
       { return header->left; }
       base_ptr& rightmost() const
       { return header->right; }

   public:
       rb_tree()
       { rb_tree_init(); }
       rb_tree(const rb_tree& rhs);
       rb_tree(rb_tree&& rhs);

       rb_tree& operator=(const rb_tree& rhs);
       rb_tree& operator=(rb_tree&& rhs);

       ~rb_tree() { clear(); }

   public:
       iterator begin()
       { return leftmost(); }
       const_iterator begin() const
       { return leftmost(); }
       iterator end()
       { return header; }
       const_iterator end() const
       { return header; }

       reverse_iterator rbegin()
       { return reverse_iterator(end()); }
       const_reverse_iterator rbegin() const
       { return const_reverse_iterator(end()); }
       reverse_iterator rend()
       { return reverse_iterator(begin()); }
       const_reverse_iterator rend() const
       { return const_reverse_iterator(begin()); }

       const_iterator         cbegin()
       { return begin(); }
       const_iterator         cend()    const
       { return end(); }
       const_reverse_iterator crbegin()
       { return rbegin(); }
       const_reverse_iterator crend()   const
       { return rend(); }

   private:
       void rb_tree_init();
       base_ptr copy_tree_from(base_ptr root, base_ptr parent);     // 复制一个树
       node_ptr clone_node(base_ptr tmp);
       template <class ...Args>
       node_ptr create_node(Args&& ...args);
       void destroy_node(node_ptr node);
       void erase_since(base_ptr node);
       void reset();
       base_ptr rb_tree_min(base_ptr node);
       base_ptr rb_tree_max(base_ptr node);

       void rb_tree_set_red(base_ptr x);
       void rb_tree_set_black(base_ptr x);

       bool rb_tree_is_red(base_ptr node);
       bool rb_tree_is_black(base_ptr node);

       void _rb_tree_rotate_left(base_ptr node, base_ptr& root);
       void _rb_tree_rotate_right(base_ptr node, base_ptr& root);

       std::pair<base_ptr , bool> get_insert_multi(const key_type& key);
       std::pair<std::pair<base_ptr, bool>, bool> get_insert_unique(const key_type& key);

       iterator insert_at_node(base_ptr x, node_ptr v, bool add_to_left);
       void rb_tree_insert_rebalance(base_ptr node, base_ptr& root);
       base_ptr rb_tree_erase_rebalance(base_ptr z, base_ptr& root, base_ptr& leftmost, base_ptr& rightmost);

       iterator insert_multi_use_pos(iterator pos, key_type& key, node_ptr node);
       iterator insert_unique_use_pos(iterator pos, key_type& key, node_ptr node);

       iterator insert_at_value(base_ptr pos, const value_type& value, bool add_to_left);

       std::pair<iterator, iterator> equal_range_multi(const key_type& key);

       base_ptr rb_tree_next(base_ptr x);
   public:
       void clear();

       bool empty() const { return node_count == 0; }
       size_type size() const { return node_count; }

       template <class ...Args>
       iterator emplace_multi(Args&& ...args);

       template <class ...Args>
       std::pair<iterator, bool> emplace_unique(Args&& ...args);

       template <class ...Args>
       iterator emplace_multi_at_pos(iterator pos, Args&& ...args);
       template <class ...Args>
       iterator emplace_unique_at_pos(iterator pos, Args&& ...args);

        iterator insert_multi(const value_type& value);
        iterator insert_multi(value_type&& value)
        { emplace_multi(MyTinySTL::move(value)); }

        iterator insert_multi(iterator pos, const value_type& value)
        { emplace_multi_at_pos(pos, value); }
        iterator insert_multi(iterator pos, value_type&& value)
        { emplace_multi_at_pos(pos, MyTinySTL::move(value)); }

        template <class Iter>
        iterator insert_multi(Iter first, Iter last) {
            auto n = distance(first, last);
            for (; n>0; n--, first++) {
                emplace_multi(end(), *first);
            }
        }

       std::pair<iterator, bool> insert_unique(const value_type& value);
       std::pair<iterator, bool> insert_unique(value_type&& value)
       { return emplace_unique(MyTinySTL::move(value)); }

       iterator insert_unique(iterator pos, const value_type& value)
       { return emplace_unique_at_pos(pos, value); }
       iterator insert_unique(iterator pos, value_type&& value)
       { return emplace_unique_at_pos(pos, MyTinySTL::move(value)); }

       template <class Iter>
       iterator insert_unique(Iter first, Iter last) {
           auto n = distance(first, last);
           for (; n>0; n--, first++) {
               emplace_unique(end(), *first);
           }
       }


       iterator erase(iterator pos);
       size_type erase_multi(const key_type& value);
       size_type erase_unique(const key_type& value);
       void erase(iterator first, iterator last);

       iterator find(const key_type& key);
       const_iterator find(const key_type& key) const;

       iterator lower_bound(const key_type& key);
       const_iterator lower_bound(const key_type& key) const;

       iterator upper_bound(const key_type& key);
       const_iterator upper_bound(const key_type& key) const;
   };


   template <class T, class Compare>
   void rb_tree<T, Compare>::rb_tree_init() {
        header = base_allocator::allocate(1);
        header->color = _rb_tree_red;
        root() = nullptr;
        leftmost() = header;
        rightmost() = header;
        node_count = 0;
   }

   template <class T, class Compare>
   typename rb_tree<T, Compare>::node_ptr
   rb_tree<T, Compare>::clone_node(base_ptr tmp) {
        node_ptr node = create_node(static_cast<node_ptr>(tmp)->value);
        node->color = tmp->color;
        return node;
   }

   template <class T, class Compare>
   typename rb_tree<T, Compare>::base_ptr
   rb_tree<T, Compare>::copy_tree_from(base_ptr root, base_ptr parent) {
       auto node = clone_node(root);
       node->parent = parent;
       try {
           if (root->right != nullptr) {
               node->right = copy_tree_from(root->right, node);
           }
           parent = node;
           root = root->left;
           while (root != nullptr) {
                auto tmp = clone_node(root);
                parent->left = tmp;
                tmp->parent = node;
                if (root->right != nullptr) {
                    tmp->right = copy_tree_from(root->right, tmp);
                }
                parent = tmp;
                root = root->left;
           }
       }
       catch (...) {
           erase_since(node);
           throw;
       }
       return node;
   }

   template <class T, class Compare>
   template <class ...Args>
   typename rb_tree<T, Compare>::node_ptr
   rb_tree<T, Compare>::create_node(Args && ...args) {
        node_ptr node = node_allocator::allocate(1);
        try {
            data_allocator::construct(MyTinySTL::address_of(node->value), MyTinySTL::forward<Args>(args)...);
            node->parent = nullptr;
            node->left = nullptr;
            node->right = nullptr;
        }
        catch (...) {
            node_allocator::destroy(node);
            throw;
        }
        return node;
   }

   template <class T, class Compare>
   void rb_tree<T, Compare>::destroy_node(node_ptr node) {
       data_allocator::destroy(&node->value);
       node_allocator::deallocate(node);
   }

   template <class T, class Compare>
   void rb_tree<T, Compare>::erase_since(base_ptr node) {
       if (node != nullptr) {
           erase_since(node->left);
           erase_since(node->right);
           destroy_node(static_cast<node_ptr>(node));
       }
   }

   template <class T, class Compare>
   void rb_tree<T, Compare>::reset() {
        node_count = 0;
        header = nullptr;
   }

    template <class T, class Compare>
    typename rb_tree<T, Compare>::base_ptr
    rb_tree<T, Compare>::rb_tree_min(base_ptr node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    template <class T, class Compare>
    typename rb_tree<T, Compare>::base_ptr
    rb_tree<T, Compare>::rb_tree_max(base_ptr node) {
        while (node->right != nullptr) node = node->right;
        return node;
    }

    template <class T, class Compare>
    void rb_tree<T, Compare>::rb_tree_set_red(rb_tree<T, Compare>::base_ptr x) {
        x->color = _rb_tree_red;
    }

    template <class T, class Compare>
    void rb_tree<T, Compare>::rb_tree_set_black(rb_tree<T, Compare>::base_ptr x) {
        x->color = _rb_tree_black;
    }

    template <class T, class Compare>
    bool rb_tree<T, Compare>::rb_tree_is_red(rb_tree<T, Compare>::base_ptr x) {
        return x->color == _rb_tree_red;
    }

    template <class T, class Compare>
    bool rb_tree<T, Compare>::rb_tree_is_black(rb_tree<T, Compare>::base_ptr x) {
        return x->color == _rb_tree_black;
    }


    template <class T, class Compare>
    void rb_tree<T, Compare>::_rb_tree_rotate_left(rb_tree<T, Compare>::base_ptr node,
                                                   rb_tree<T, Compare>::base_ptr &root) {
        base_ptr y = node->right;                           // 令y为旋转节点的右子节点
        node->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = node;
        }
        y->parent = node->parent;
        if (node == root) {
            root = y;
        }
        else if (node == node->parent->left) {
            node->parent->left = y;
        }
        else node->parent->right = y;
        y->left = node;
        node->parent = y;
    }

    template <class T, class Compare>
    void rb_tree<T, Compare>::_rb_tree_rotate_right(rb_tree<T, Compare>::base_ptr node,
                                                    rb_tree<T, Compare>::base_ptr &root) {
        base_ptr y = node->left;                           // 令y为旋转节点的右子节点
        node->left = y->right;
        if (y->right != nullptr) {
            y->right->parent = node;
        }
        y->parent = node->parent;
        if (node == root) {
            root = y;
        }
        else if (node == node->parent->right) {
            node->parent->right = y;
        }
        else node->parent->left = y;
        y->right = node;
        node->parent = y;
    }

    template<class T, class Compare>
    std::pair<typename rb_tree<T, Compare>::base_ptr, bool>
    rb_tree<T, Compare>::get_insert_multi(const key_type &key) {
        auto child = root();
        auto parent = header;
        bool add_to_left = true;
        while (child != nullptr) {
            //std::cout << key << "  " << value_traits::get_key(static_cast<node_ptr>(child)->value) << std::endl;
            parent = child;
            //std::cout << key << std::endl;
            add_to_left = key_compare(key, value_traits::get_key(static_cast<node_ptr>(child)->value));
            child = add_to_left ? child->left : child->right;
        }
        return std::make_pair(parent, add_to_left);
    }

    template<class T, class Compare>
    std::pair<std::pair<typename rb_tree<T, Compare>::base_ptr, bool>, bool>
    rb_tree<T, Compare>::get_insert_unique(const key_type &key) {
        base_ptr y = header;
        base_ptr x = root();
        bool add_to_left = true;
        while (x != nullptr) {
            y = x;
            add_to_left = key_compare(key, value_traits::get_key(static_cast<node_ptr>(x)->value));
            x = add_to_left ? x->left : x->right;
        }
        iterator j = iterator(y);              // j指向插入点之父节点
        if (add_to_left) {
            if (y == header || j == begin()) {      // 如果树为空树或者插入位置为最左边
                return std::make_pair(std::make_pair(y, add_to_left), true);
            }
            else j--;
        }
        if (key_compare(value_traits::get_key(*j), key)) {
            return std::make_pair(std::make_pair(y, add_to_left), true);
        }
        return std::make_pair(std::make_pair(y, add_to_left), false);
    }

    template <class T, class Compare>
    typename rb_tree<T, Compare>::iterator
    rb_tree<T, Compare>::insert_at_node(typename rb_tree<T, Compare>::base_ptr x,
                   typename rb_tree<T, Compare>::node_ptr v, bool add_to_left) {
        v->parent = x;
        auto base_node = v->get_base_ptr();
        if (x == header) {
            root() = base_node;
            leftmost() = base_node;
            rightmost() = base_node;
        }
        else if (add_to_left) {
            x->left = base_node;
            if (leftmost() == x) {
                leftmost() = base_node;
            }
        }
        else {
            x->right = base_node;
            if (rightmost() == x) {
                rightmost() = base_node;
            }
        }
        rb_tree_insert_rebalance(base_node, root());
        node_count++;
        return iterator(v);
    }


    template <class T, class Compare>
    void rb_tree<T, Compare>::rb_tree_insert_rebalance(
            typename rb_tree<T, Compare>::base_ptr node, rb_tree<T, Compare>::base_ptr& root) {
        rb_tree_set_red(node);                                   // 新节点必为红
        while (node != root && rb_tree_is_red(node->parent)) {   // 父节点为红
            if (node->parent == node->parent->parent->left) {    // 父节点为祖父节点之左子节点
                base_ptr uncle = node->parent->parent->right;    // 取出伯父节点
                if (uncle && rb_tree_is_red(uncle)) {            // 伯父节点存在且为红
                    rb_tree_set_black(node->parent);             // 更改父节点为黑
                    rb_tree_set_black(uncle);                    // 更改伯父节点为黑
                    rb_tree_set_red(node->parent->parent);       // 更改祖父节点为红
                    node = node->parent->parent;                 // 上层继续检查
                }
                else {                                           // 无伯父节点或伯父节点为黑
                    if (node == node->parent->right) {           // 如果新节点为父节点之右子节点
                        node = node->parent;
                        _rb_tree_rotate_left(node, root);        // 第一参数为左旋点
                    }
                    rb_tree_set_black(node->parent);             // 更改父节点为黑
                    rb_tree_set_red(node->parent->parent);       // 更改祖父结点为红
                    _rb_tree_rotate_right(node->parent->parent, root);  // 右旋
                }
            }
            else {                                               // 父节点为祖父节点之右子节点
                base_ptr uncle = node->parent->parent->left;     // 取出伯父节点
                if (uncle && rb_tree_is_red(uncle)) {            // 伯父节点存在且为红
                    rb_tree_set_black(node->parent);             // 更改父节点为黑
                    rb_tree_set_black(uncle);                    // 更改伯父节点为黑
                    rb_tree_set_red(node->parent->parent);       // 更改祖父节点为红
                    node = node->parent->parent;                 // 上层继续检查
                }
                else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        _rb_tree_rotate_right(node, root);
                    }
                    rb_tree_set_black(node->parent);
                    rb_tree_set_red(node->parent->parent);
                    _rb_tree_rotate_left(node->parent->parent, root);
                }
            }
        }
        rb_tree_set_black(root);
    }


    template <class T, class Compare>
    typename rb_tree<T, Compare>::base_ptr
    rb_tree<T, Compare>::rb_tree_erase_rebalance(base_ptr z, base_ptr &root, base_ptr &leftmost,
                                                      base_ptr &rightmost) {
        // y 是可能的替换节点，指向最终要删除的节点
        auto y = (z->left == nullptr || z->right == nullptr) ? z : rb_tree_next(z);
        // x 是 y 的一个独子节点或 NIL 节点
        auto x = y->left != nullptr ? y->left : y->right;
        // xp 为 x 的父节点
        base_ptr xp = nullptr;

        // y != z 说明 z 有两个非空子节点，此时 y 指向 z 右子树的最左节点，x 指向 y 的右子节点。
        // 用 y 顶替 z 的位置，用 x 顶替 y 的位置，最后用 y 指向 z
        if (y != z)
        {
            z->left->parent = y;
            y->left = z->left;

            // 如果 y 不是 z 的右子节点，那么 z 的右子节点一定有左孩子
            if (y != z->right)
            { // x 替换 y 的位置
                xp = y->parent;
                if (x != nullptr)
                    x->parent = y->parent;

                y->parent->left = x;
                y->right = z->right;
                z->right->parent = y;
            }
            else
            {
                xp = y;
            }

            // 连接 y 与 z 的父节点
            if (root == z)
                root = y;
            else if (z == z->parent->left)
                z->parent->left = y;
            else
                z->parent->right = y;
            y->parent = z->parent;
            MyTinySTL::swap(y->color, z->color);
            y = z;
        }
            // y == z 说明 z 至多只有一个孩子
        else
        {
            xp = y->parent;
            if (x)
                x->parent = y->parent;

            // 连接 x 与 z 的父节点
            if (root == z)
                root = x;
            else if (z == z->parent->left)
                z->parent->left = x;
            else
                z->parent->right = x;

            // 此时 z 有可能是最左节点或最右节点，更新数据
            if (leftmost == z)
                leftmost = x == nullptr ? xp : rb_tree_min(x);
            if (rightmost == z)
                rightmost = x == nullptr ? xp : rb_tree_max(x);
        }

        // 此时，y 指向要删除的节点，x 为替代节点，从 x 节点开始调整。
        // 如果删除的节点为红色，树的性质没有被破坏，否则按照以下情况调整（x 为左子节点为例）：
        // case 1: 兄弟节点为红色，令父节点为红，兄弟节点为黑，进行左（右）旋，继续处理
        // case 2: 兄弟节点为黑色，且两个子节点都为黑色或 NIL，令兄弟节点为红，父节点成为当前节点，继续处理
        // case 3: 兄弟节点为黑色，左子节点为红色或 NIL，右子节点为黑色或 NIL，
        //         令兄弟节点为红，兄弟节点的左子节点为黑，以兄弟节点为支点右（左）旋，继续处理
        // case 4: 兄弟节点为黑色，右子节点为红色，令兄弟节点为父节点的颜色，父节点为黑色，兄弟节点的右子节点
        //         为黑色，以父节点为支点左（右）旋，树的性质调整完成，算法结束
        if (!rb_tree_is_red(y))
        { // x 为黑色时，调整，否则直接将 x 变为黑色即可
            while (x != root && (x == nullptr || !rb_tree_is_red(x)))
            {
                if (x == xp->left)
                { // 如果 x 为左子节点
                    auto brother = xp->right;
                    if (rb_tree_is_red(brother))
                    { // case 1
                        rb_tree_set_black(brother);
                        rb_tree_set_red(xp);
                        _rb_tree_rotate_left(xp, root);
                        brother = xp->right;
                    }
                    // case 1 转为为了 case 2、3、4 中的一种
                    if ((brother->left == nullptr || !rb_tree_is_red(brother->left)) &&
                        (brother->right == nullptr || !rb_tree_is_red(brother->right)))
                    { // case 2
                        rb_tree_set_red(brother);
                        x = xp;
                        xp = xp->parent;
                    }
                    else
                    {
                        if (brother->right == nullptr || !rb_tree_is_red(brother->right))
                        { // case 3
                            if (brother->left != nullptr)
                                rb_tree_set_black(brother->left);
                            rb_tree_set_red(brother);
                            _rb_tree_rotate_right(brother, root);
                            brother = xp->right;
                        }
                        // 转为 case 4
                        brother->color = xp->color;
                        rb_tree_set_black(xp);
                        if (brother->right != nullptr)
                            rb_tree_set_black(brother->right);
                        _rb_tree_rotate_left(xp, root);
                        break;
                    }
                }
                else  // x 为右子节点，对称处理
                {
                    auto brother = xp->left;
                    if (rb_tree_is_red(brother))
                    { // case 1
                        rb_tree_set_black(brother);
                        rb_tree_set_red(xp);
                        _rb_tree_rotate_right(xp, root);
                        brother = xp->left;
                    }
                    if ((brother->left == nullptr || !rb_tree_is_red(brother->left)) &&
                        (brother->right == nullptr || !rb_tree_is_red(brother->right)))
                    { // case 2
                        rb_tree_set_red(brother);
                        x = xp;
                        xp = xp->parent;
                    }
                    else
                    {
                        if (brother->left == nullptr || !rb_tree_is_red(brother->left))
                        { // case 3
                            if (brother->right != nullptr)
                                rb_tree_set_black(brother->right);
                            rb_tree_set_red(brother);
                            _rb_tree_rotate_left(brother, root);
                            brother = xp->left;
                        }
                        // 转为 case 4
                        brother->color = xp->color;
                        rb_tree_set_black(xp);
                        if (brother->left != nullptr)
                            rb_tree_set_black(brother->left);
                        _rb_tree_rotate_right(xp, root);
                        break;
                    }
                }
            }
            if (x != nullptr)
                rb_tree_set_black(x);
        }
        return y;
    }


   template <class T, class Compare>
   rb_tree<T,Compare>::rb_tree(const rb_tree& rhs) {
        rb_tree_init();
        if (rhs.node_count != 0) {
            root() = copy_tree_from(rhs.root(), header);
            leftmost() = rb_tree_min(root());
            rightmost() = rb_tree_max(root());
        }
        node_count = rhs.node_count;
        key_compare = rhs.key_compare;
   }

   template <class T, class Compare>
   rb_tree<T,Compare>::rb_tree(rb_tree&& rhs) {
       header = MyTinySTL::move(rhs.header);
       node_count = rhs.node_count;
       key_compare = rhs.key_compare;
       rhs.reset();
   }


   template <class T, class Compare>
   rb_tree<T, Compare>& rb_tree<T, Compare>::operator=(const rb_tree<T, Compare>& rhs) {
        if (this != &rhs) {
            clear();
            if (rhs.node_count != 0) {
                root() = copy_tree_from(rhs.root(), header);
                leftmost() = rb_tree_min(root());
                rightmost() = rb_tree_max(root());
            }
            node_count = rhs.node_count;
            key_compare = rhs.key_compare;
        }
   }

    template <class T, class Compare>
    rb_tree<T, Compare>& rb_tree<T, Compare>::operator=(rb_tree<T, Compare>&& rhs) {
        clear();
        header = MyTinySTL::move(rhs.header);
        node_count = rhs.node_count;
        key_compare = rhs.key_compare;
        rhs.reset();
    }


    template <class T, class Compare>
    void rb_tree<T, Compare>::clear() {
        if (node_count != 0) {
            erase_since(root());
            leftmost() = header;
            rightmost() = header;
            node_count = 0;
            root() = nullptr;
        }
    }

    template <class T, class Compare>
    template <class ...Args>
    typename rb_tree<T, Compare>::iterator
    rb_tree<T, Compare>::emplace_multi(Args && ...args) {
        node_ptr node = create_node(MyTinySTL::forward<Args>(args)...);
        auto res = get_insert_multi(value_traits::get_key(node->value));
        return insert_at_node(res.first, node, res.second);
    }

    template <class T, class Compare>
    template <class ...Args>
    std::pair<typename rb_tree<T, Compare>::iterator, bool>
    rb_tree<T, Compare>::emplace_unique(Args && ...args) {
        node_ptr node = create_node(MyTinySTL::forward<Args>(args)...);
        auto res = get_insert_unique(value_traits::get_key(node->value));
        if (res.second) {
            return std::make_pair(insert_at_node(res.first.first, node, res.first.second), true);
        }
        destroy_node(node);
        return std::make_pair(res.first.first, false);
    }

    template <class T, class Compare>
    template <class ...Args>
    typename rb_tree<T, Compare>::iterator
    rb_tree<T, Compare>::emplace_multi_at_pos(iterator pos, Args&& ...args) {
        node_ptr node = create_node(MyTinySTL::forward<Args>(args)...);
        if (node_count == 0) {
            return insert_at_node(header, node, true);
        }
        key_type key = value_traits::get_key(node->value);
        if (pos == begin()) {
            if (key_compare(key, value_traits::get_key(*pos))) {
                return insert_at_node(pos.node, node, true);
            }
            else {
                auto res = get_insert_multi(value_traits::get_key(node->value));
                return insert_at_node(res.first, node, res.second);
            }
        }
        else if (pos == end()) {
            if (!key_compare(key, value_traits::get_key(static_cast<node_ptr>(rightmost())->value))) {
                return insert_at_node(rightmost(), node, false);
            }
            else {
                auto res = get_insert_multi(value_traits::get_key(node->value));
                return insert_at_node(res.first, node, res.second);
            }
        }
        return insert_multi_use_pos(pos, key, node);
    }

    template <class T, class Compare>
    template <class ...Args>
    typename rb_tree<T, Compare>::iterator
    rb_tree<T, Compare>::emplace_unique_at_pos(iterator pos, Args&& ...args) {
        node_ptr node = create_node(MyTinySTL::forward<Args>(args)...);
        if (node_count == 0) {
            return insert_at_node(header, node, true);
        }
        key_type key = value_traits::get_key(node->value);
        if (pos == begin()) {
            if (key_compare(key, value_traits::get_key(*pos))) {
                return insert_at_node(pos.node, node, true);
            }
            else {
                auto res = get_insert_unique(key);
                if (!res.second) {
                    destroy_node(node);
                    return res.first.first;
                }
                return insert_at_node(res.first.first, node, res.first.second);
            }
        }
        else if (pos == end()) {
            if (!key_compare(key, value_traits::get_key(static_cast<node_ptr>(rightmost())->value))) {
                return insert_at_node(rightmost(), node, false);
            }
            else {
                auto res = get_insert_unique(key);
                if (!res.second) {
                    destroy_node(node);
                    return res.first.first;
                }
                return insert_at_node(res.first.first, node, res.first.second);
            }
        }
        return insert_unique_use_pos(pos, key, node);
    }

    template <class T, class Compare>
    typename rb_tree<T, Compare>::iterator
    rb_tree<T, Compare>::insert_multi(const value_type &value) {
        auto res = get_insert_multi(value_traits::get_key(value));
        return insert_at_value(res.first, value, res.second);
    }

    template <class T, class Compare>
    std::pair<typename rb_tree<T, Compare>::iterator, bool>
    rb_tree<T, Compare>::insert_unique(const value_type &value) {
        auto res = get_insert_unique(value_traits::get_key(value));
        if (res.second) {
            return std::make_pair(insert_at_node(res.first.first, value, res.first.second), true);
        }
        return std::make_pair(res.first.first, false);
    }

    template <class T, class Compare>
    typename rb_tree<T, Compare>::iterator
    rb_tree<T, Compare>::insert_multi_use_pos(iterator pos, key_type &key, node_ptr node) {
        auto x = pos.node;
        auto next = pos;
        next--;
        auto y = next.node;
        if (!key_compare(key, value_traits::get_key(*next)&&
          !key_compare(value_traits::get_key(*pos),key))) {
            if (y->right == nullptr) {
                return insert_at_node(y, node, false);
            }
            if (x->left == nullptr) {
                return insert_at_node(x, node, true);
            }
        }
        auto res = get_insert_multi(value_traits::get_key(key));
        return insert_at_node(res.first, node, res.second);
    }

    template <class T, class Compare>
    typename rb_tree<T, Compare>::iterator
    rb_tree<T, Compare>::insert_unique_use_pos(iterator pos, key_type &key, node_ptr node) {
        auto x = pos.node;
        auto next = pos;
        next--;
        auto y = next.node;
        if (!key_compare(key, value_traits::get_key(*next)&&
              !key_compare(value_traits::get_key(*pos),key))) {
            if (y->right == nullptr) {
                return insert_at_node(y, node, false);
            }
            if (x->left == nullptr) {
                return insert_at_node(x, node, true);
            }
        }
        auto res = get_insert_unique(key);
        if (!res.second) {
            destroy_node(node);
            return res.first.first;
        }
        return insert_at_node(res.first.first, node, res.first.second);
    }

    template <class T, class Compare>
    typename rb_tree<T, Compare>::iterator
    rb_tree<T, Compare>::insert_at_value(base_ptr pos, const value_type &value, bool add_to_left) {
        node_ptr node = create_node(value);
        node->parent = pos;
        auto base_node = node.get_base_ptr();
        if (pos == header) {
            root() = base_node;
            leftmost() = base_node;
            rightmost() = base_node;
        }
        else if (add_to_left) {
            pos->left = base_node;
            if (leftmost() == pos) {
                leftmost() = base_node;
            }
        }
        else {
            pos->right = base_node;
            if (rightmost() == pos) {
                rightmost() = base_node;
            }
        }
        rb_tree_insert_rebalance(base_node, root());
        node_count++;
        return iterator(node);
    }

    template <class T, class Compare>
    std::pair<typename rb_tree<T, Compare>::iterator, typename rb_tree<T, Compare>::iterator>
    rb_tree<T, Compare>::equal_range_multi(const key_type &key) {
        return std::make_pair(lower_bound(key), upper_bound(key));
    }

    template <class T, class Compare>
    typename rb_tree<T, Compare>::base_ptr
    rb_tree<T, Compare>::rb_tree_next(typename rb_tree<T, Compare>::base_ptr x) {
        if (x->right != nullptr) {
            return rb_tree_min(x->right);
        }
        while (!(x != x->parent->left)) {
            x = x->parent;
        }
        return x->parent;
    }

    template <class T, class Compare>
    typename rb_tree<T, Compare>::iterator
    rb_tree<T, Compare>::erase(iterator pos) {
        auto node = static_cast<node_ptr>(pos.node);
        iterator res(pos);
        res++;

        rb_tree_erase_rebalance(pos.node, root(), leftmost(), rightmost());
        destroy_node(node);
        node_count--;
        return res;
    }

    template <class T, class Compare>
    typename rb_tree<T, Compare>::size_type
    rb_tree<T, Compare>::erase_multi(const key_type &key) {
        auto range = equal_range_multi(key);
        auto n = MyTinySTL::distance(range.first, range.second);
        erase(range.first, range.second);
        return n;
    }

    template <class T, class Compare>
    typename rb_tree<T, Compare>::size_type
    rb_tree<T, Compare>::erase_unique(const key_type &key) {
        auto it = find(key);
        if (it != nullptr) {
            erase(it);
            return;
        }
        return 0;
    }

    template <class T, class Compare>
    void rb_tree<T, Compare>::erase(typename rb_tree<T, Compare>::iterator first,
                    typename rb_tree<T, Compare>::iterator last) {
        if (first == begin() && last == end()) {
            clear();
        }
        else {
            while (first != last) {
                erase(first++);
            }
        }
    }

    template <class T, class Compare>
    typename rb_tree<T, Compare>::iterator
    rb_tree<T, Compare>::find(const key_type &key) {
        auto y = header;
        auto x = root();
        while (x != nullptr) {
           // std::cout << value_traits::get_key(static_cast<node_ptr>(x)->value) << key << std::endl;
            if (!key_compare(value_traits::get_key(static_cast<node_ptr>(x)->value), key)) {
                y = x;
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        iterator v(y);
        return (v == end() || key_compare(key, value_traits::get_key(*v))) ? end() : v;
    }

    template <class T, class Compare>
    typename rb_tree<T, Compare>::const_iterator
    rb_tree<T, Compare>::find(const key_type &key) const {
        auto y = header;
        auto x = root();
        while (x != nullptr) {
            if (!key_compare(value_traits::get_key(static_cast<node_ptr>(x)->value), key)) {
                y = x;
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        iterator v(y);
        return (v == end() || key_compare(key, value_traits::get_key(*v))) ? end() : v;
    }

    template <class T, class Compare>
    typename rb_tree<T, Compare>::iterator
    rb_tree<T, Compare>::lower_bound(const key_type &key) {
        auto y = header;
        auto x = root();
        while (x != nullptr) {
            if (!key_compare(value_traits::get_key(static_cast<node_ptr>(x)->value), key)) {
                y = x;
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        return iterator(y);
    }

    template <class T, class Compare>
    typename rb_tree<T, Compare>::const_iterator
    rb_tree<T, Compare>::lower_bound(const key_type &key) const{
        auto y = header;
        auto x = root();
        while (x != nullptr) {
            if (!key_compare(value_traits::get_key(static_cast<node_ptr>(x)->value), key)) {
                y = x;
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        return const_iterator(y);
    }


    template <class T, class Compare>
    typename rb_tree<T, Compare>::iterator
    rb_tree<T, Compare>::upper_bound(const key_type &key) {
        auto y = header;
        auto x = root();
        while (x != nullptr) {
            if (key_compare(key, value_traits::get_key(static_cast<node_ptr>(x)->value))) {
                y = x;
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        return iterator(y);
    }

    template <class T, class Compare>
    typename rb_tree<T, Compare>::const_iterator
    rb_tree<T, Compare>::upper_bound(const key_type &key) const{
        auto y = header;
        auto x = root();
        while (x != nullptr) {
            if (key_compare(key, value_traits::get_key(static_cast<node_ptr>(x)->value))) {
                y = x;
                x = x->left;
            }
            else {
                x = x->right;
            }
        }
        return const_iterator(y);
    }
}

#endif //MYTINYSTL_RB_TREE_H
