//
// Created by 谯保林 on 2021/6/2.
//

#ifndef MYTINYSTL_LIST_H
#define MYTINYSTL_LIST_H

#endif //MYTINYSTL_LIST_H

#include "util.h"
#include "iterator.h"
#include "allocator.h"
#include "memory.h"

namespace  MyTinySTL
{
    template <class T> class _list_node;

    template <class T>
    class list_traits
    {
    public:
        typedef _list_node<T>*   node_ptr;
    };

    template <class T>
    class _list_node
    {
    public:
        typedef typename list_traits<T>::node_ptr   node_ptr;

        node_ptr next;
        node_ptr prev;

        T value;
        _list_node() = default;
        explicit _list_node(const T& val) : value(val), next(nullptr), prev(nullptr) {};
        node_ptr self() {
            return static_cast<node_ptr >(&*this);
        }

        void init_list_node() {
            next = prev = self();
        }
    };

    template <class T>
    class list_iterator : public iterator<bidirectional_iterator_tag, T>
    {
    public:
        typedef typename list_traits<T>::node_ptr   node_ptr;
        typedef list_iterator<T>                    self;
        typedef T                                   value_type;
        typedef T*                                  pointer;
        typedef T&                                  reference;

        node_ptr _node;   // 指向当前节点

        list_iterator() = default;
        list_iterator(node_ptr rhs) : _node(rhs) {}
        list_iterator(const self& rhs) : _node(rhs._node) {}

        reference operator*()
        {
            return _node->value;
        }

        pointer operator->()
        {
            return &(operator*());
        }

        self operator+(int n)
        {
            for (; n > 0; n--) {
                _node = _node->next;
            }
            return *this;
        }

        self operator-(int n)
        {
            for (; n > 0; n--) {
                _node = _node->prev;
            }
            return *this;
        }

        self& operator++()        // 前置
        {
            _node = _node->next;
            return *this;
        }

        self operator++(int)     // 后置
        {
            self tmp = *this;
            _node = _node->next;
            return tmp;
        }

        self& operator--()        // 前置
        {
            _node = _node->prev;
            return *this;
        }

        self operator--(int)     // 后置
        {
            self tmp = *this;
            _node = _node->prev;
            return tmp;
        }

        bool operator==(const self& rhs) { return this->_node == rhs._node; };
        bool operator!=(const self& rhs) { return this->_node != rhs._node; };
    };

    template <class T>
    class const_list_iterator : public iterator<bidirectional_iterator_tag, T>
    {
    public:
        typedef typename list_traits<T>::node_ptr           node_ptr;
        typedef const_list_iterator<T>                      self;
        typedef T                                           value_type;
        typedef T*                                          pointer;
        typedef T&                                          reference;

        node_ptr _node;   // 指向当前节点

        const_list_iterator() = default;
        const_list_iterator(node_ptr rhs) : _node(rhs) {}
        const_list_iterator(const list_iterator<T>& rhs) : _node(rhs._node) {}
        const_list_iterator(const self& rhs) : _node(rhs._node) {}

        reference operator*()
        {
            return _node->value;
        }

        pointer operator->()
        {
            return &(operator*());
        }

        self& operator++()        // 前置
        {
            _node = _node->next;
            return *this;
        }

        self operator++(int)     // 后置
        {
            self tmp = *this;
            _node = _node->next;
            return tmp;
        }

        self& operator--()        // 前置
        {
            _node = _node->prev;
            return *this;
        }

        self operator--(int)     // 后置
        {
            self tmp = *this;
            _node = _node->prev;
            return tmp;
        }

        bool operator==(const self& rhs) { return this->_node == rhs._node; };
        bool operator!=(const self& rhs) { return this->_node != rhs._node; };
    };

    template <class T>
    class list
    {
    public:
        typedef MyTinySTL::allocator<T>                                allocator_type;
        typedef MyTinySTL::allocator<T>                                data_allocator;
        typedef MyTinySTL::allocator<_list_node<T>>                    list_allocator;

        typedef typename MyTinySTL::allocator<T>::value_type           value_type;
        typedef typename MyTinySTL::allocator<T>::pointer              pointer;
        typedef typename MyTinySTL::allocator<T>::const_pointer        const_pointer;
        typedef typename MyTinySTL::allocator<T>::reference            reference;
        typedef typename MyTinySTL::allocator<T>::const_reference      const_reference;
        typedef typename MyTinySTL::allocator<T>::size_type            size_type;
        typedef typename MyTinySTL::allocator<T>::difference_type      difference_type;

        typedef list_iterator<T>                                       iterator;
        typedef const_list_iterator<T>                                 const_iterator;
        typedef MyTinySTL::reverse_iterator<iterator>                  reverse_iterator;
        typedef MyTinySTL::reverse_iterator<const_iterator>            const_reverse_iterator;

        typedef typename list_traits<T>::node_ptr                      node_ptr;

    private:
        node_ptr    _node;       // 指向尾节点
        size_type   _size;        // 保存节点个数

    public:
        // 构造，拷贝，移动构造函数，析构函数
        list()
        { fill_init(0, value_type()); }

        list(int n)
        { fill_init(n, value_type()); }

        list(int n, const value_type& value)
        { fill_init(n, value); }

        template <class Iter, typename std::enable_if<
                MyTinySTL::is_input_iterator<Iter>::value, int>::type = 0>
         list(Iter first, Iter last)
        { copy_init(first, last); }

        list(std::initializer_list<value_type > ilist)
        { copy_init(ilist.begin(), ilist.end()); }

        list(const list& rhs)
        { copy_init(rhs.begin(), rhs.end()); }

        list(list&& rhs) noexcept : _node(rhs._node), _size(rhs._size) {
            rhs._node = nullptr;
            rhs._size = 0;
        }

        list& operator=(const list& rhs) {
            if (this != &rhs) {
                assign(rhs.begin(), rhs.end());
            }
            return *this;
        }

        void clear();

    public:
        iterator begin()
        { return _node->next; }
        const_iterator begin() const
        { return _node->next; }
        iterator end()
        { return _node; }
        const_iterator end() const
        { return _node; }

        reverse_iterator rbegin()
        { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const
        { return const_reverse_iterator(end()); }
        reverse_iterator rend()
        { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const
        { return const_reverse_iterator(begin()); }

        bool empty()
        { return  _size == 0; }

        size_type size()
        {return _size; }

        reference front()
        { return *begin(); }

        const_reference front() const
        { return *begin(); }

        reference back()
        { return *(--end()); }

        const_reference back() const
        { return *(--end()); }

    public:
        void assign(size_type n, const value_type& value);

        template <class Iter, typename std::enable_if<
                MyTinySTL::is_input_iterator<Iter>::value, int>::type = 0>
        void assign(Iter first, Iter last)
        { copy_assign(first, last); }

        void assign(std::initializer_list<value_type > ilist)
        { copy_assign(ilist.begin(), ilist.end()); }

        void insert(const_iterator pos, const value_type& value) {
            node_ptr node = create_node(value);
            _size++;
            link_list_at_pos(pos._node, node, node);
        }

        void insert(const_iterator pos, const value_type&& value) {
            std::cout << "右值" << value << std::endl;
            node_ptr node = create_node(MyTinySTL::move(value));
            _size++;
            link_list_at_pos(pos._node, node, node);
        }

        void insert(const_iterator pos, size_type n, const value_type& value) {
            for (; n > 0; n--) {
                insert(pos, value);
            }
        }

        template <class Iter, typename std::enable_if<
                MyTinySTL::is_input_iterator<Iter>::value, int>::type = 0>
        void insert(const_iterator pos, Iter first, Iter last) {
            for (; first != last; first++) {
                insert(pos, *first);
            }
        }

        iterator erase(const_iterator pos);
        iterator erase(const_iterator first, const_iterator last);

        template <class ...Args>
        void emplace_front(Args&& ...args);

        template <class ...Args>
        void emplace_back(Args&& ...args);

        template <class ...Args>
        void emplace(const_iterator pos, Args&& ...args);

        void push_back(const value_type& value);
        void push_back(const value_type&& value);

        void push_front(const value_type& value);
        void push_front(const value_type&& value);

        void pop_front();
        void pop_back();

        void resize(size_type n)
        { return resize(n, value_type()); }
        void resize(size_type n, const value_type& value);

        /*void sort()
        { return sort(less<T>()); } */
        template <class Compare>
        void sort(Compare com);

        /*void merge(list& l)
        { return merge(l, less<T>()); }*/
        template <class Compare>
        void merge(list& l, Compare com);


        void reverse();
    private:
        void fill_init(int n, const value_type& value);

        template <class ...Args>
        node_ptr create_node(Args&& ...args);
        void destroy_node(node_ptr node);

        void link_list_at_back(node_ptr first, node_ptr last);
        void link_list_at_front(node_ptr first, node_ptr last);

        template <class Iter>
        void copy_init(Iter first, Iter last);

        void link_list_at_pos(node_ptr pos, node_ptr first, node_ptr last);

        template <class Iter>
        void copy_assign(Iter first, Iter last);
    };

    template <class T>
    void list<T>::fill_init(int n, const value_type &value) {
        _node = list_allocator::allocate(1);
        _node->init_list_node();
        _size = n;
        try {
            for ( ; n > 0; n--) {
                node_ptr node = create_node(value);
                link_list_at_back(node, node);
            }
        }
        catch (...) {
            clear();
            list_allocator::deallocate(_node);
            _node = nullptr;
            throw;
        }
    }

    template <class T>
    template <class ...Args>
    typename list<T>::node_ptr list<T>::create_node(Args&& ...args) {
        node_ptr new_node = list_allocator::allocate();

        try {
            data_allocator::construct(MyTinySTL::address_of(new_node->value), MyTinySTL::forward<Args>(args)...);
            new_node->next = nullptr;
            new_node->prev = nullptr;
        }
        catch (...) {
            list_allocator::deallocate(new_node);
            throw;
        }
        return new_node;
    }

    template <class T>
    void list<T>::link_list_at_back(node_ptr first, node_ptr last) {
        first->prev = _node->prev;
        _node->prev->next = first;
        last->next = _node;
        _node->prev = last;
    }

    template <class T>
    void list<T>::link_list_at_front(node_ptr first, node_ptr last) {
        last->next = _node->next;
        _node->next->prev = last;
        first->prev = _node;
        _node->next = first;
    }

    template <class T>
    void list<T>::link_list_at_pos(node_ptr pos, node_ptr first, node_ptr last) {
        pos->prev->next = first;
        first->prev = pos->prev;
        last->next = pos;
        pos->prev = last;
    }

    template <class T>
    void list<T>::clear() {
        if (_size == 0) return;
        node_ptr cur = _node->next;
        for (node_ptr first = _node->next; first != _node; first = first->next) {
            node_ptr temp = first->next;
            destroy_node(cur);
            cur = temp;
        }
        _size = 0;
        _node->init_list_node();
    }

    template <class T>
    void list<T>::destroy_node(node_ptr node) {
        list_allocator::deallocate(node);
    }

    template <class T>
    template <class Iter>
    void list<T>::copy_init(Iter first, Iter last) {
        _node = list_allocator::allocate(1);
        _node->init_list_node();
        auto n = MyTinySTL::distance(first,last);
        _size = n;

        try{
            for ( ; n > 0;n--) {
                node_ptr node = create_node(*first);
                link_list_at_back(node, node);
                first ++;
            }
        }
        catch (...) {
            clear();
            list_allocator::destroy(_node);
            _node = nullptr;
            throw;
        }
    }

    template <class T>
    void list<T>::assign(size_type n, const value_type& value) {
        iterator first = begin();
        iterator last = end();

        for (; n > 0 && first != last; n--, first++) {
            *first = value;
        }
        if (n > 0) {
            insert(first, n ,value);
        }
        if (first != last) {
            erase(first, last);
        }
    }

    template <class T>
    template <class Iter>
    void list<T>::copy_assign(Iter first2, Iter last2) {
        iterator first1 = begin();
        iterator last1 = end();

        for ( ;first1 != last1 && first2 != last2; first1++, first2++) {
            *first1 = *first2;
        }

        if (first1 == last1 && first2 != last2) {
            insert(first1, first2, last2);
        }

        if (first1 != last1 && first2 == last2) {
            erase(first1,last1);
        }
    }

    // 删除[first, last) 上的元素
    template <class T>
    typename list<T>::iterator
    list<T>::erase(const_iterator first, const_iterator last){
        if (first != last) {
            node_ptr f1 = first._node, l1 = last._node->prev;
            f1->prev->next = l1->next;
            l1->next->prev = f1->prev;

            while (first != last) {
                auto cur = first;
                --_size;
                destroy_node(cur._node);
                first++;
            }
        }
        return iterator(last._node);
    }

    template <class T>
    typename list<T>::iterator
    list<T>::erase(const_iterator pos) {
        auto cur = pos._node->next;
        if (pos._node != _node) {
            node_ptr f1 = pos._node, l1 = pos._node;
            f1->prev->next = l1->next;
            l1->next->prev = f1->prev;

            --_size;
            destroy_node(pos._node);
        }
        return iterator(cur);
    }

    template <class T>
    template <class ...Args>
    void list<T>::emplace_front(Args&& ...args) {
        auto node = create_node(MyTinySTL::forward<Args>(args)...);
        link_list_at_front(node, node);
        _size++;
    }

    template <class T>
    template <class ...Args>
    void list<T>::emplace_back(Args&& ...args) {
        auto node = create_node(MyTinySTL::forward<Args>(args)...);
        link_list_at_back(node, node);
        _size++;
    }

    template <class T>
    template <class ...Args>
    void list<T>::emplace(const_iterator pos, Args&& ...args) {
        auto node = create_node(MyTinySTL::forward<Args>(args)...);
        link_list_at_pos(pos._node, node, node);
        _size++;
    }

    template <class T>
    void list<T>::push_back(const value_type &value) {
        auto node = create_node(value);
        link_list_at_back(node, node);
        _size++;
    }

    template <class T>
    void list<T>::push_back(const value_type &&value) {
        emplace_back(value);
    }

    template <class T>
    void list<T>::push_front(const value_type &value) {
        auto node = create_node(value);
        link_list_at_front(node, node);
        _size++;
    }

    template <class T>
    void list<T>::push_front(const value_type &&value) {
        emplace_front(value);
    }

    template <class T>
    void list<T>::pop_front() {
        if (_size != 0) {
            auto node = _node->next;
            node->next->prev = _node;
            _node->next = node->next;
            destroy_node(node);
            --_size;
        }
    }

    template <class T>
    void list<T>::pop_back() {
        if (_size != 0) {
            auto node = _node->prev;
            node->prev->next = _node;
            _node->prev = node->prev;
            destroy_node(node);
            --_size;
        }
    }

    template <class T>
    void list<T>::resize(size_type n, const value_type& value) {
        auto first = begin();
        auto last = end();
        while (first != last && n > 0) {
            first++;
            n--;
        }
        if (n == 0 && first != last) {
            erase(first, last);
        }
        if (n != 0) {
            insert(first, n, value);
        }
    }

    template <class T>
    template <class Compare>
    void list<T>::sort(Compare com) {
       // TODO
    }

    template <class T>
    template <class Compare>
    void list<T>::merge(list& l, Compare com) {
        // TODO
    }

    template <class T>
    void list<T>::reverse() {
        iterator first = begin();
        iterator last = end();

        while (first != last) {
            MyTinySTL::swap(first._node->next, first._node->prev);
            first--;
        }
        MyTinySTL::swap(last._node->next, last._node->prev);
    }
}