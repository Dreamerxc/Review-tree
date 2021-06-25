//
// Created by 谯保林 on 2021/6/16.
//

#ifndef MYTINYSTL_STACK_H
#define MYTINYSTL_STACK_H



#include "deque.h"

namespace MyTinySTL
{

    template <class T, class Container = MyTinySTL::deque<T> >
    class stack
    {
    public:
        typedef Container                                container_type;
        typedef typename Container::value_type           value_type;
        typedef typename Container::reference            reference;
        typedef typename Container::const_reference      const_reference;
        typedef typename Container::size_type            size_type;

    private:
        container_type _st;

    public:
        stack() = default;

        stack(const stack& rhs) : _st(rhs._st) {}
        stack(stack&& rhs) : _st(MyTinySTL::move(rhs._st)) {}

        stack(Container& rhs) : _st(rhs) {}
        stack(Container&& rhs) : _st(MyTinySTL::move(rhs)) {}

        explicit stack(size_type n) : _st(n) {}
        stack(size_type n, const value_type& value) : _st(n, value) {}

        template <class Iter>
        stack(Iter first, Iter last):_st(first, last) {}
        stack(std::initializer_list<value_type> ilist)
        :  _st(ilist.begin(), ilist.end())
        {}

        stack& operator=(const stack& rhs) {
            _st = rhs._st;
            return *this;
        }

        stack& operator=(const stack&& rhs) {
            _st = MyTinySTL::move(rhs._st);
            return *this;
        }

        stack& operator=(std::initializer_list<value_type> ilist) {
            _st = ilist;
            return *this;
        }

        ~stack() = default;

    public:
        reference top() { return _st.back(); }
        const_reference top() const { return _st.back(); }

        size_type size() {return _st.size(); }
        bool empty() {return _st.empty(); }

        template <class ...Args>
        void emplace(Args&& ...args) {
            _st.emplace_back(MyTinySTL::forward<Args>(args)...);
        }

        void push(const value_type& value) {
            _st.push_back(value);
        }
        void push(value_type&& value) {
            _st.push_back(MyTinySTL::move(value));
        }

        void pop() {
            _st.pop_back();
        }

        void clear() {
            _st.clear();
        }

        void swap(stack& rhs) {
            MyTinySTL::swap(_st, rhs._st);
        }
    public:
        friend bool operator==(const stack& lhs, const stack& rhs) { return lhs._st == rhs._st; }
        friend bool operator< (const stack& lhs, const stack& rhs) { return lhs._st <  rhs._st; }
    };


        template <class T, class Container>
        bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
        {
            return lhs == rhs;
        }

        template <class T, class Container>
        bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
        {
            return lhs < rhs;
        }

        template <class T, class Container>
        bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
        {
            return !(lhs == rhs);
        }

        template <class T, class Container>
        bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
        {
            return rhs < lhs;
        }

        template <class T, class Container>
        bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
        {
            return !(rhs < lhs);
        }

        template <class T, class Container>
        bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs)
        {
            return !(lhs < rhs);
        }
}
#endif //MYTINYSTL_STACK_H