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

        deque_iterator(value_type v, map_pointer u) :
        first(*u), cur(v), last(*u + _buf_size()), node(u) {}

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
            void create_buffer(map_pointer nstart, map_pointer nfinish)
            template <class Iter>
            void copy_init(Iter first, Iter last, input_iterator_tag);
            template <class Iter>
            void copy_init(Iter first, Iter last, forward_iterator_tag);

            void swap(const deque& rhs);

            iterator insert_aux(iterator pos, const value_type& value);

            void require_capacity(size_type n, bool front);

            void realloc_at_front(size_type n);
            void realloc_at_back(size_type n);

            void insert_aux_n(iterator pos, size_type n, const value_type& value);

            template <class Iter>
            void insert_dispatch(iterator pos, Iter first, Iter last);

            template <class Iter>
            void copy_assign(Iter first, Iter last);

            void destroy_buffers(map_pointer first, map_pointer last);
        public:
            void clear();
            void resize(size_type n, const value_type& value);
            void resize(size_type n)
            { return resize(n, value_type()); }

            template <class ...Args>
            void emplace_front(Args&& ...args);
            template <class ...Args>
            void emplace_back(Args&& ...args);

            void push_front(const value_type& value);
            void push_front(value_type&& value)
            { emplace_front(value); }

            void push_back(const value_type& value);
            void push_back(value_type&& value)
            { emplace_back(value); }

            iterator insert(iterator pos, const value_type& value);
            iterator insert(iterator pos, value_type&& value);
            iterator insert(iterator pos, size_type n, const value_type& value);
            template <class Iter, typename std::enable_if<
                    MyTinySTL::is_input_iterator<Iter>::value, int>::type = 0>
            iterator insert(iterator pos, Iter first, Iter last);

            void assign(size_type n, const value_type& value);
            template <class Iter, typename std::enable_if<
                    MyTinySTL::is_input_iterator<IIter>::value, int>::type = 0>
            void assign(Iter first, Iter last)
            { copy_assign(first, last); }
            void assign(std::initializer_list<value_type > ilist)
            { copy_assign(ilist.begin(), ilist.edn()); }

            void pop_front();
            void pop_back();

            iterator erase(iterator pos);
            iterator erase(iterator first, iterator last);
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
        void deque<T>::realloc_at_front(size_type n) {
            const auto new_map_size = MyTinySTL::max(_size << 1,
                                          static_cast<size_type>(_size + n + DEQUE_MAP_INIT_SIZE));
            map_pointer new_map = create_map_and_nodes(new_map_size);

            size_type old_map_buffers = _end.node - _begin.node + 1;
            size_type new_map_buffers = old_map_buffers + n;

            map_pointer begin = new_map + (new_map_size - new_map_buffers) / 2;
            map_pointer mid = begin + n;
            map_pointer end = mid + old_map_buffers;

            create_buffer(begin, mid - 1);
            for (auto cur = mid, tmp = _begin.node; cur != end && tmp != _end.node; cur++, tmp++) {
                *cur = *tmp;
            }
            map_allocator::deallocate(_map, _size);
            _map = new_map;
            _size = new_map_size;
            _begin = iterator(*mid + (_begin.cur - _begin.first), mid);
            _end = iterator((*(end - 1) + (_end.cur - _end.first), end - 1));
        }

        template <class T>
        void deque<T>::realloc_at_back(size_type n) {
            const auto new_map_size = MyTinySTL::max(_size << 1,
                                                     static_cast<size_type>(_size + n + DEQUE_MAP_INIT_SIZE));
            map_pointer new_map = create_map_and_nodes(new_map_size);

            size_type old_map_buffers = _end.node - _begin.node + 1;
            size_type new_map_buffers = old_map_buffers + n;

            map_pointer begin = new_map + (new_map_size - new_map_buffers) / 2;
            map_pointer mid = begin + old_map_buffers;
            map_pointer end = mid + n;

            create_buffer(mid, end - 1);
            for (auto cur = begin, tmp = _begin.node; cur != mid && tmp != _end.node; cur++, tmp++) {
                *cur = *tmp;
            }
            map_allocator::deallocate(_map, _size);
            _map = new_map;
            _size = new_map_size;
            _begin = iterator(*begin + (_begin.cur - _begin.first), begin);
            _end = iterator((*(mid - 1) + (_end.cur - _end.first), mid - 1));
        }

        template <class T>
        vodi deque<T>::insert_aux_n(iterator pos, size_type n, const value_type &value) {
            const size_type front_elems = pos - _begin;
            const size_type back_elems = _end - pos;
            const size_type len = size();

            if (front_elems < len/2) {
                require_capacity(n, true);
                auto old_begin = _begin;
                auto new_begin = _begin - n;
                if (front_elems >= n) {
                    auto end = old_begin + n;
                    MyTinySTL::uninitialized_copy(old_begin, end, new_begin);
                    MyTinySTL::copy(end, pos, old_begin);
                    MyTinySTL::fill(pos - n, pos, value);
                    _begin = new_begin;
                }
                else {
                    auto end2 = MyTinySTL::uninitialized_copy(old_begin, pos, new_begin);
                    MyTinySTL::uninitialized_fill_n(end2, old_begin, value);
                    MyTinySTL::fill(old_begin, pos, value);
                    _begin = new_begin;

                }
            }
            else {
                require_capacity(n, false);
                auto old_end = _end;
                auto new_end = _end + n;
                if (back_elems >= n) {
                    auto end = _end - n;
                    MyTinySTL::uninitialized_copy(end, _end, _end);
                    MyTinySTL::copy_backward(pos, end, _end);
                    MyTinySTL::fill(pos, pos + n, value);
                    _end = new_end;
                }
                else {
                    MyTinySTL::uninitialized_copy(pos, old_end, pos + n);
                    MyTinySTL::uninitialized_fill(old_end, pos + n, value);
                    MyTinySTL::fill(pos ,old_end, value);
                    _end = new_end;
                }
            }
        }

        template <class T>
        template <class Iter>
        void deque<T>::insert_dispatch(iterator pos, Iter first, Iter last) {
            if (first >= last) return;
            const size_type n = MyTinySTL::distance(first, last);
            const size_type len = pos - _begin;
            if (len < size()/2) {
                require_capacity(n, true);
            }
            else {
                require_capacity(n, false);
            }
            for (auto cur = first; cur != last; cur++) {
                insert(pos, *cur);
            }
        }

        template <class T>
        template <class Iter>
        void deque<T>::copy_assign(Iter first, Iter last) {
            auto first1 = begin();
            auto last1 = end();
            for (; first1 != last1 && first != last; first1++, first++) {
                *first1 = *first;
            }
            if (first1 != last1) {
                erase(first1, last1);
            }
            else {
                insert_dispatch(first1, first, last);
            }
        }

        template <class T>
        void deque<T>::destroy_buffers(map_pointer first, map_pointer last) {
            for (auto tmp = first; tmp != last; tmp++) {
                map_allocator::deallocate(*tmp, _buf_size);
                *tmp = nullptr;
            }
        }

        template <class T>
        void deque<T>::require_capacity(size_type n, bool front) {
            if (front && static_cast<size_type>(_begin.cur - _begin.first) < n) {
                const size_type need_buffer = (n - (_begin.cur - _begin.first))/ _buf_size + 1;
                if (need_buffer > _begin.node - _map) {
                    realloc_at_front(need_buffer);
                    return;
                }
                create_buffer(_begin.node - need_buffer, _begin - 1);
            }
            if (!front && static_cast<size_type>(_end.last - _end.cur - 1) < n) {
                const size_type need_buffer = (n - (_end.last - _end.cur - 1))/ _buf_size + 1;
                if (need_buffer > _map[_size - 1] - _end.node) {
                    realloc_at_back(need_buffer);
                    return;
                }
                create_buffer(_end.node + 1, _end.node + need_buffer);
            }
        }

        template <class T>
        void deque<T>::
        create_buffer(map_pointer nstart, map_pointer nfinish)
        {
            map_pointer cur;
            try
            {
                for (cur = nstart; cur <= nfinish; ++cur)
                {
                    *cur = data_allocator::allocate(_buf_size);
                }
            }
            catch (...)
            {
                while (cur != nstart)
                {
                    --cur;
                    data_allocator::deallocate(*cur, _buf_size);
                    *cur = nullptr;
                }
                throw;
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
        template <class ...Args>
        void deque<T>::emplace_front(Args&& ...args) {
            if (_begin.cur != _begin.first) {
                _begin.cur--;
                data_allocator::construct(_begin.cur, MyTinySTL::forward<Args>(args)...);
                return;
            }
            else {
                require_capacity(1, true);
                _begin--;
                data_allocator::construct(_begin.cur, MyTinySTL::forward<Args>(args)...);
                return;
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
        template <class ...Args>
        void deque<T>::emplace_back(Args&& ...args) {
            if (_end.cur != _end.last) {
                _end.cur++;
                data_allocator::construct(_end.cur, MyTinySTL::forward<Args>(args)...);
                return;
            }
            else {
                require_capacity(1, false);
                _end++;
                data_allocator::construct(_end.cur, MyTinySTL::forward<Args>(args)...);
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
            const auto elems = pos - _begin;
            if (elems < size()/2) {
                emplace_front(front());
                auto begin1 = _begin;
                begin1++;
                auto begin2 = begin1;
                begin1++;
                auto end1 = begin1 + elems;
                end1++;
                MyTinySTL::copy(begin1, end1, begin2);
            }
            else {
                emplace_back(back());
                auto begin1 = pos;
                auto end2 = back();
                end2--;
                auto end1 = end2;
                end1--;
                MyTinySTL::copy_backward(begin1, end1, end2);
            }
            *pos = std::move(value);
            return pos;
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
            if (pos.cur == _begin.cur) {
                emplace_front(value);
                return _begin;
            }
            else if (pos.cur == _end.cur) {
                emplace_back(value);
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
        deque<T>::insert(iterator pos, size_type n, const value_type &value) {
            if (pos.cur == _begin.cur) {
                require_capacity(n, true);
                auto new_begin = _begin - n;
                MyTinySTL::uninitialized_fill_n(new_begin, n, value);
                _begin = new_begin;
            }
            if (pos.cur == _end.cur) {
                require_capacity(n, false);
                auto new_end = _end + n;
                MyTinySTL::uninitialized_fill_n(_end, n, value);
                _end = new_end;
            }
            else insert_pos_n(pos, n, value);
        }

        template <class T>
        template <class Iter, typename std::enable_if<
                MyTinySTL::is_input_iterator<Iter>::value, int>::type = 0>
        typename deque<T>::iterator
        deque<T>::insert(iterator pos, Iter first, Iter last) {
            insert_dispatch(pos, first, last);
        }

        template <class T>
        void deque<T>::assign(size_type n, const value_type &value) {
            if (n > size()) {
                MyTinySTL::fill(begin(), end(), value);
                insert(end(), n - size(), value);
            }
            else {
                erase(begin() + n, end());
                MyTinySTL::fill(begin(), end(), value);
            }
        }

        template <class T>
        typename deque<T>::iterator
        deque<T>::erase(iterator pos) {
            const auto len = pos - begin();
            if (len < size() /2) {
                MyTinySTL::copy_backward(_begin, pos, pos + 1);
                pop_front();
            }
            else {
                MyTinySTL::copy(pos + 1, _end, pos);
                pop_back();
            }
            return _begin + len;
        }

        template <class T>
        typename deque<T>::iterator
        deque<T>::erase(iterator first, iterator last) {
            if (first == begin() && last == end()) {
                clear();
                return;
            }
            const size_type len = last - first;
            const size_type elems = first - begin();
            if (elems < (size() - len) / 2) {
                MyTinySTL::copy_backward(_begin, first, last);
                auto tmp = _begin + len;
                data_allocator::destroy(tmp.cur, first.cur);
                _begin = tmp;
            }
            else {
                MyTinySTL::copy(last, _end, first);
                auto tmp = _end - len;
                data_allocator::destroy(tmp.cur, _end.cur);
                _end = tmp;
            }
            return _begin + elems;
        }

        template <class T>
        void deque<T>::pop_front() {
            if (_begin.cur != _begin.last - 1) {
                data_allocator::destroy(_begin.cur);
                _begin.cur++;
            }
            else {
                data_allocator::destroy(_begin.cur);
                _begin++;
                destoroy_buffers(_begin.node-1, _begin.node-1);
            }
        }

        template <class T>
        void deque<T>::pop_back() {
            if (_end.cur != _end.first) {
                data_allocator::destroy(_end.cur);
                _end.cur--;
            }
            else {
                _end--;
                data_allocator::destroy(_end.cur);
                destroy_buffers(_end.node + 1, _end.node + 1);
            }
        }
}