//
// Created by 谯保林 on 2021/6/10.
//

#ifndef MYTINYSTL_DEQUE_H
#define MYTINYSTL_DEQUE_H
#endif //MYTINYSTL_DEQUE_H

#ifndef DEQUE_MAP_INIT_SIZE
#define DEQUE_MAP_INIT_SIZE 8
#endif

#include<initializer_list>
#include "iterator.h"
#include "allocator.h"
#include "uninitialized.h"

namespace MyTinySTL
{
    static constexpr size_t _deque_buf_size(size_t n, size_t sz)
    {
        return n != 0 ? n : (sz < 512 ? size_t (512 / sz) : size_t(1));
    }

    template <class T, class Ref, class Ptr, size_t buf_size = 8>
    class deque_iterator : public iterator<random_access_iterator_tag, T> {
    public:
        typedef deque_iterator<T, T &, T *, buf_size> iterator;
        typedef deque_iterator<T, const T &, const T *, buf_size> const_iterator;

        static size_t _buf_size() { return _deque_buf_size(buf_size, sizeof(T)); }

        typedef T value_type;
        typedef Ref reference;
        typedef Ptr pointer;
        typedef ptrdiff_t difference_type;
        typedef deque_iterator self;

        typedef T *value_pointer;
        typedef T **map_pointer;

        value_pointer first;
        value_pointer last;
        value_pointer cur;
        map_pointer node;

        deque_iterator() : first(nullptr), cur(nullptr), last(nullptr), node(nullptr) {}

        deque_iterator(const iterator &qu) :
                first(qu.first), cur(qu.cur), last(qu.last), node(qu.node) {}

        deque_iterator(iterator &&qu) :
                first(qu.first), cur(qu.cur), last(qu.last), node(qu.node) {
            qu.first = nullptr;
            qu.last = nullptr;
            qu.cur = nullptr;
            qu.node = nullptr;
        }

        deque_iterator(const const_iterator &qu) :
                first(qu.first), cur(qu.cur), last(qu.last), node(qu.node) {}

        self& operator=(const iterator &rhs) {
            if (this != &rhs) {
                this->first = rhs.first;
                this->last = rhs.last;
                this->cur = rhs.cur;
                this->node = rhs.node;
            }
            return *this;
        }

        void set_node(map_pointer new_node) {
            node = new_node;
            first = *new_node;
            last = first + _buf_size();
        }

        reference operator*() { return *cur; }

        pointer operator->() { return &(operator*()); }

        difference_type operator-(const iterator &rhs) const {
            return difference_type(_buf_size()) * (node - rhs.node - 1)
                   + (cur - first) + (rhs.last - rhs.cur);
        }

        self &operator++() {
            cur++;
            if (cur == last) {
                set_node(node + 1);
                cur = first;
            }
            return *this;
        }

        self operator++(int) {
            self tmp = *this;
            ++*this;
            return tmp;
        }

        self &operator--() {
            if (cur == first) {
                set_node(node - 1);
                cur = last;
            }
            --cur;
            return *this;
        }

        self operator--(int) {
            self tmp = *this;
            --*this;
            return tmp;
        }

        self &operator+=(difference_type n) {
            difference_type offset = n + (cur - first);
            if (offset >= 0 && offset < difference_type(_buf_size())) {   // 还在同一个缓冲区
                cur += n;
            } else {
                difference_type offset_node = offset > 0 ? (offset / difference_type(_buf_size()))
                                                         : -difference_type((-offset - 1) / _buf_size()) - 1;
                set_node(node + offset_node);
                cur = first + (offset - offset_node * difference_type(_buf_size()));
            }
            return *this;
        }

        self operator+(difference_type n) {
            self tmp = *this;
            return tmp += n;
        }

        self &operator-=(difference_type n) {
            return *this += -n;
        }

        self operator-(difference_type n) {
            self tmp = *this;
            return tmp -= n;
        }

        reference operator[](difference_type n) {
            return *(*this + n);
        }

        bool operator==(const iterator &rhs) { return cur == rhs.cur; }

        bool operator!=(const iterator &rhs) { return cur != rhs.cur; }

        bool operator>(const iterator &rhs) {
            return node == rhs.node ? (cur > rhs.cur) : (node > rhs.node);
        }

        bool operator<(const iterator &rhs) {
            return rhs > *this;
        }

        bool operator<=(const iterator &rhs) {
            return !(*this > rhs.node);
        }

        bool operator>=(const iterator &rhs) {
            return !(rhs.node > *this);
        }
    };

        template <class T>
        class deque
        {
        public:
            typedef MyTinySTL::allocator<T>                                allocator_type;
            typedef MyTinySTL::allocator<T>                                data_allocator;
            typedef MyTinySTL::allocator<T*>                               map_allocator;

            typedef typename MyTinySTL::allocator<T>::value_type           value_type;
            typedef typename MyTinySTL::allocator<T>::pointer              pointer;
            typedef typename MyTinySTL::allocator<T>::const_pointer        const_pointer;
            typedef typename MyTinySTL::allocator<T>::reference            reference;
            typedef typename MyTinySTL::allocator<T>::const_reference      const_reference;
            typedef typename MyTinySTL::allocator<T>::size_type            size_type;
            typedef typename MyTinySTL::allocator<T>::difference_type      difference_type;
            typedef T**                                                    map_pointer;

            typedef deque_iterator<T, T&, T*>                              iterator;
            typedef deque_iterator<T, const T&, const T*>                  const_iterator;
            typedef MyTinySTL::reverse_iterator<iterator>                  reverse_iterator;
            typedef MyTinySTL::reverse_iterator<const_iterator>            const_reverse_iterator;

            static const size_t _buf_size = _deque_buf_size(8,sizeof(T));

        private:
            iterator    _begin;
            iterator    _end;
            map_pointer _map;
            size_type   _size;

        public:
            deque()
            { fill_init(0, value_type()); }
            explicit deque(size_type n)
            { fill_init(n, value_type()); }
            deque(size_type n, const value_type& value)
            { fill_init(n, value); }
            template <class Iter, typename std::enable_if<
                    MyTinySTL::is_input_iterator<Iter>::value, int>::type = 0>
            deque(Iter first, Iter last)
            { copy_init(first, last, iterator_category(first)); }
            deque(const deque& rhs)
            { std::cout << "fuzhi" << std::endl;
                copy_init(rhs.begin(), rhs.end(), iterator_category(rhs.begin())); }
            deque(std::initializer_list<value_type > ilist)
            { copy_init(ilist.begin(), ilist.end(), iterator_category(ilist.begin())); }
            deque(deque&& rhs) :
            _begin(MyTinySTL::move(rhs._begin)), _end(MyTinySTL::move(rhs._end)), _size(rhs._size), _map(rhs._map) {
                rhs._size = 0;
                rhs._map = nullptr;
            }

            deque& operator=(const deque& rhs);
            deque& operator=(deque&& rhs);
            deque& operator=(std::initializer_list<value_type > ilist) {
                deque tmp(ilist);
                swap(tmp);
                return *this;
            }

            ~deque() {
                for (int i = 0;i<_size;i++) {
                    for (auto p = _map[i]; !p && p < _map[i] + _buf_size; p++) {
                        data_allocator::destroy(p);
                    }
                    if (!_map[i])
                    data_allocator::deallocate(_map[i], _buf_size);
                }
                delete[] _map;
            }

        public:
            iterator begin()
            { return _begin; }
            const_iterator begin() const
            { return _begin; }
            iterator end()
            { return _end; }
            const_iterator end() const
            { return _end; }

            reverse_iterator rbegin()
            { return reverse_iterator(end()); }
            const_reverse_iterator rbegin() const
            { return const_reverse_iterator(end()); }
            reverse_iterator rend()
            { return reverse_iterator(begin()); }
            const_reverse_iterator rend() const
            { return const_reverse_iterator(begin()); }

            bool empty()
            { return  begin() == end(); }

            size_type size() const
            {return _end - _begin; }

            reference front()
            { return *begin(); }

            const_reference front() const
            { return *begin(); }

            reference back()
            { return *(--end()); }

            const_reference back() const
            { return *(--end()); }

        private:
            void fill_init(size_type n, const value_type& val);
            void create_map_and_nodes(size_type n);

            template <class Iter>
            void copy_init(Iter first, Iter last, input_iterator_tag);
            template <class Iter>
            void copy_init(Iter first, Iter last, forward_iterator_tag);

            void swap(const deque& rhs);

            iterator insert_aux(iterator pos, const value_type& value);

            void require_capacity(size_type n, bool front);
        public:
            void clear();
            void resize(size_type n, const value_type& value);
            void resize(size_type n)
            { return resize(n, value_type()); }

            void push_front(const value_type& value);
            void push_front(value_type&& value);

            void push_back(const value_type& value);
            void push_back(value_type&& value);

            iterator insert(iterator pos, const value_type& value);
            iterator insert(iterator pos, value_type&& value);
            iterator insert(iterator pos, size_type n, const value_type& value);
            template <class Iter, typename std::enable_if<
                    MyTinySTL::is_input_iterator<Iter>::value, int>::type = 0>
            iterator insert(iterator pos, Iter first, Iter last);
        };

        template <class T>
        void deque<T>::fill_init(size_type n, const value_type &value) {
            create_map_and_nodes(n);
            if (n != 0) {
                for (auto cur = _begin.node; cur < _end.node; cur++) {
                    MyTinySTL::uninitialized_fill(*cur, *cur + _buf_size, value);
                }
                MyTinySTL::uninitialized_fill(_end.first, _end.cur, value);
            }
        }

        template <class T>
        void deque<T>::create_map_and_nodes(size_type n) {
            size_type num_nodes = n / _buf_size + 1;
            _size = MyTinySTL::max(static_cast<size_type>(DEQUE_MAP_INIT_SIZE), num_nodes + 2);   // 前后各预留一个缓冲区，扩充时可用

            try {
                _map = map_allocator::allocate(_size);
            }
            catch(...) {
                _map = nullptr;
                _size = 0;
                throw;
            }

            map_pointer nstart = _map + (_size - num_nodes) / 2;
            map_pointer nfinish = nstart + num_nodes - 1;

            map_pointer cur;
            try {
                for (cur = nstart; cur <= nfinish; cur++) {
                    *cur = data_allocator::allocate(_buf_size);
                }
            }
            catch(...) {
                while (nstart != cur) {
                    map_pointer tmp = nstart + 1;
                    data_allocator::destroy(*nstart, *nstart + _buf_size);
                    nstart = tmp;
                }
            }

            _begin.set_node(nstart);
            _end.set_node(nfinish);
            _begin.cur = _begin.first;
            _end.cur = _end.first + n % _buf_size;
        }

        template <class T>
        template <class Iter>
        void deque<T>::copy_init(Iter first, Iter last, input_iterator_tag) {
            auto n = MyTinySTL::advance(first, last);
            create_map_and_nodes(n);
            for (; first != last; first++) {
                // TODO
            }
        }

        template <class T>
        template <class Iter>
        void deque<T>::copy_init(Iter first, Iter last, forward_iterator_tag) {
            auto n = MyTinySTL::distance(first, last);
            create_map_and_nodes(n);

            for (auto cur = _begin.node; cur < _end.node; cur++) {
                auto tmp = first;
                MyTinySTL::advance(tmp, _buf_size);
                MyTinySTL::uninitialized_copy(first, tmp, *cur);
                first = tmp;
            }
            MyTinySTL::uninitialized_copy(first, last, _end.first);
        }

        template <class T>
        void deque<T>::require_capacity(size_type n, bool front) {
            if (front && static_cast<size_type>(_begin.cur - _begin.first) < n) {


            }
        }

        template <class T>
        deque<T>& deque<T>::operator=(const deque& rhs) {
            if (this != &rhs) {
                auto len = size();
                if (len >= rhs.size()) {
                    erase(MyTinySTL::copy(rhs._begin, rhs._end, _begin), _end);
                } else {
                    iterator mid = rhs.begin() + static_cast<difference_type>(len);
                    MyTinySTL::copy(rhs._begin, mid, _begin);
                    insert(_end, mid, rhs._end);
                }
            }
            return *this;
        }

        template <class T>
        deque<T>& deque<T>::operator=(deque&& rhs) {
            *this->_begin = MyTinySTL::move(rhs._begin);
            *this->_end = MyTinySTL::move(rhs._end);
            *this->_size = rhs._size;
            *this->_map = rhs._map;
            {
                rhs->_size = 0;
                rhs->_map = nullptr;
            }
            return *this;
        }

        template <class T>
        void deque<T>::swap(const deque<T> &rhs) {
            if (rhs != this) {
                MyTinySTL::swap(_begin, rhs->_begin);
                MyTinySTL::swap(_end, rhs._end);
                MyTinySTL::swap(_size, rhs->_size);
                MyTinySTL::swap(_map, rhs->_map);
            }
        }

        template <class T>
        void deque<T>::clear() {
            for (int i = 0;i<_size;i++) {
                for (auto p = _map[i]; !p && p < _map[i] + _buf_size; p++) {
                    data_allocator::destroy(p);
                }
            }
            _size = 0;
            map_pointer index = _map + _size / 2;
            _begin.set_node(index);
            _end.set_node(index);
            _begin.cur = _begin.first;
            _end.cur = _end.first;
        }

        template <class T>
        void deque<T>::resize(size_type n, const value_type& value) {
            const auto len = size();
            if (n > len) {
                insert(_end, n - len, value);
            }
            if (n < len) {
                erase(_begin + n, _end);
            }
        }

        template <class T>
        void deque<T>::push_front(const value_type &value) {
            if (_begin.cur != _begin.first) {
                _begin.cur--;
                data_allocator::construct(_begin.cur, value);
                return;
            }
            else {
                require_capacity(1, true);
                _begin--;
                data_allocator::construct(_begin.cur, value);
                return;
            }
        }

        template <class T>
        void deque<T>::push_back(const value_type &value) {
            if (_end.cur != _end.last) {
                _end.cur++;
                data_allocator::construct(_end.cur, value);
                return;
            }
            else {
                require_capacity(1, false);
                _end++;
                data_allocator::construct(_end.cur, value);
                return;
            }
        }

        template <class T>
        typename deque<T>::iterator
        deque<T>::insert_aux(iterator pos, const value_type &value) {

        }

        template <class T>
        typename deque<T>::iterator
        deque<T>::insert(iterator pos, const value_type &value) {
            if (pos.cur == _begin.cur) {
                push_front(value);
                return _begin;
            }
            else if (pos.cur == _end.cur) {
                push_back(value);
                auto tmp = end();
                tmp--;
                return tmp;
            }
            else {
                return insert_aux(pos, value);
            }
        }

        template <class T>
        typename deque<T>::iterator
        deque<T>::insert(iterator pos, value_type &&value) {

        }

        template <class T>
        typename deque<T>::iterator
        deque<T>::insert(iterator pos, size_type n, const value_type &value) {

        }
        template <class T>
        template <class Iter, typename std::enable_if<
            MyTinySTL::is_input_iterator<Iter>::value, int>::type = 0>
        typename deque<T>::iterator
        deque<T>::insert(iterator pos, Iter first, Iter last) {

        }
}