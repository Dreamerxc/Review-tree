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
#include "memory.h"

namespace MyTinySTL
{
    typedef bool _rb_tree_color_type;
    const _rb_tree_color_type _rb_tree_red = false;
    const _rb_tree_color_type _rb_tree_black = true;

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
            return value.first;
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
        // todo std::remove_cv
        typedef typename T::first_type  key_type;             // map中用作索引健类型
        typedef typename T::second_type mapped_type;          // map中健所关联值的类型
        typedef T                       value_type;           // map中具体值类型 pair<const v1, v2>

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
    class _rb_tree_base_iterator : public MyTinySTL::iterator<MyTinySTL::forward_iterator_tag, T>
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

        bool operator==(const _rb_tree_base_iterator& rhs) { return node == rhs.node; }
        bool operator!=(const _rb_tree_base_iterator& rhs) { return node == rhs.node; }
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
            return node_ptr(node)->value;
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
            return *this;
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
            self tmp = *this;
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
   public:
       void clear();

       bool empty() const { return node_count == 0; }
       bool size() const { return node_count; }

       template <class ...Args>
       iterator emplace_multi(Args&& ...args);

       template <class ...Args>
       std::pair<iterator, bool> emplace_unique(Args&& ...args);
   };


   template <class T, class Compare>
   void rb_tree<T, Compare>::rb_tree_init() {
        header = base_allocator::allocate(1);
        header->color = _rb_tree_red;
        root() == nullptr;
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
            parent = child;
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
        auto base_node = v.get_base_ptr();
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
            return std::make_pair(insert_at_node(res.first.first, node, res.first.second));
        }
        destroy_node(node);
        return std::make_pair(res.first.first, false);
    }
}