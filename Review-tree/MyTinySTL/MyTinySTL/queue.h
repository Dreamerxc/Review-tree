//
// Created by 谯保林 on 2021/6/16.
//

#ifndef MYTINYSTL_QUEUE_H
#define MYTINYSTL_QUEUE_H

#endif //MYTINYSTL_QUEUE_H

#include "deque.h"

namespace MyTinySTL
{
    template <class T, class Container = deque<T> >
    class queue
    {
    public:
        typedef Container                                container_type;
        typedef typename Container::value_type           value_type;
        typedef typename Container::const_pointer        const_pointer;
        typedef typename Container::reference            reference;
        typedef typename Container::const_reference      const_reference;
        typedef typename Container::size_type            size_type;
        typedef typename Container::difference_type      difference_type;

    private:
        container_type _qu;

    public:
        queue() = default;

        queue(const queue& rhs) : _qu(rhs._qu) {}
        queue(queue&& rhs) : _qu(MyTinySTL::move(rhs._qu)) {}

        queue(Container& rhs) : _qu(rhs) {}
        queue(Container&& rhs) : _qu(MyTinySTL::move(rhs)) {}

        explicit queue(size_type n) : _qu(n) {}
        queue(size_type n, const value_type& value) : _qu(n, value) {}

        template <class Iter>
        queue(Iter first, Iter last) : _qu(first, last) {}
        queue(std::initializer_list<value_type> ilist) : _qu(ilist.begin(), ilist.end()) {}

        queue& operator=(const queue& rhs) {
            _qu = rhs._qu;
            return *this;
        }

        queue& operator=(const queue&& rhs) {
            _qu = MyTinySTL::move(rhs._qu);
            return *this;
        }

        queue& operator=(std::initializer_list<value_type> ilist) {
            _qu = ilist;
            return *this;
        }

        ~queue() = default;
    public:
        reference front() { return _qu.front(); }
        const_reference front() const { return _qu.front(); }

        reference back() { return _qu.back(); }
        const_reference back() const { return _qu.back(); }

        size_type size() { return _qu.size(); }
        bool empty() {return _qu.empty(); }

        template <class ...Args>
        void emplace(Args&& ...args) {
            _qu.emplace_back(MyTinySTL::forward<Args>(args)...);
        }

        void push(const value_type& value) {
            _qu.push_back(value);
        }
        void push(value_type&& value) {
            _qu.push_back(MyTinySTL::move(value));
        }

        void pop() {
            _qu.pop_front();
        }

        void clear() {
            _qu.clear();
        }

        void swap(queue& rhs) {
            MyTinySTL::swap(_qu, rhs._qu);
        }
    public:
        friend bool operator==(const queue& lhs, const queue& rhs) { return lhs._qu == rhs._qu; }
        friend bool operator< (const queue& lhs, const queue& rhs) { return lhs._qu <  rhs._qu; }
    };


    template <class T, class Container>
    bool operator==(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
    {
        return lhs == rhs;
    }

    template <class T, class Container>
    bool operator<(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
    {
        return lhs < rhs;
    }

    template <class T, class Container>
    bool operator!=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T, class Container>
    bool operator>(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
    {
        return rhs < lhs;
    }

    template <class T, class Container>
    bool operator<=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
    {
        return !(rhs < lhs);
    }

    template <class T, class Container>
    bool operator>=(const queue<T, Container>& lhs, const queue<T, Container>& rhs)
    {
        return !(lhs < rhs);
    }
}
