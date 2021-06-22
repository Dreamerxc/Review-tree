// -*- coding: utf-8-unix; -*-
// Copyright (c) 2021 Tencent, Inc.
//     All rights reserved.
//
// Author: kricsqiao@tencent.com
// Date: 2021/4/14 20:54
// Description:
//

#pragma once
#include<initializer_list>
#include<algorithm>
#include "iterator.h"
#include "memory.h"
#include "util.h"
#include "algobase.h"


namespace MyTinySTL{

    template<class T>
    class vector {
    public:
        typedef MyTinySTL::allocator<T> allocator_type;
        typedef MyTinySTL::allocator<T> data_allocator;

        typedef typename allocator_type::value_type        value_type;
        typedef typename allocator_type::pointer           pointer;
        typedef typename allocator_type::const_pointer     const_pointer;
        typedef typename allocator_type::reference         reference;
        typedef typename allocator_type::const_reference   const_reference;
        typedef typename allocator_type::size_type         size_type;
        typedef typename allocator_type::difference_type   difference_type;

        typedef value_type* iterator;
        typedef const value_type* const_iterator;
        typedef MyTinySTL::reverse_iterator<iterator>       reverse_iterator;
        typedef MyTinySTL::reverse_iterator<const_iterator> const_reverse_iterator;

        allocator_type get_allocator() {
            return data_allocator();
        }

    private:
        iterator begin_;   // 表示当前使用空间的头部
        iterator end_;     // 表示当前使用空间的尾部
        iterator cap_;     // 表示目前存储空间的尾部

    public:
        // 构造函数
        vector() noexcept {
            try_init();
        }

        explicit vector(size_type n) {
            fill_init(n, value_type());
        }

        vector(size_type n, const value_type& value) {
            fill_init(n, value);
        }

        template<class Iter, typename std::enable_if<
                MyTinySTL::is_input_iterator<Iter>::value, int>::type = 0>
        vector(Iter first, Iter last){
            range_init(first, last);
        }

        // 拷贝构造函数
        vector(const vector& rhs) {
            range_init(rhs.begin_, rhs.end_);
        }

        // 移动构造函数
        vector(vector&& rhs) noexcept
                : begin_(rhs.begin_),
                  end_(rhs.end_),
                  cap_(rhs.cap_){
            rhs.begin_ = nullptr;
            rhs.end_ = nullptr;
            rhs.cap_ = nullptr;
        }

        // 利用初始化列表构造
        vector(std::initializer_list<value_type > ilist){
            range_init(ilist.begin(),ilist.end());
        }

        vector& operator= (const vector& rhs);
        vector& operator= (vector&& rhs) noexcept;

        vector& operator= (std::initializer_list<value_type > ilist){
            vector tmp(ilist.begin(), ilist.end());
            swap(tmp);
            return *this;
        }

        ~vector(){
            destroy_and_recover(begin_, end_, cap_ - begin_);
            begin_ = nullptr;
            end_ = nullptr;
            cap_ = nullptr;
        }


    private:
        void try_init();

        void fill_init(size_type,const value_type&);

        template <class Iter>
        void range_init(Iter first, Iter second);

        void init_space(size_type size, value_type cap);

        void destroy_and_recover(iterator first, iterator last, size_type n);

        void fill_assign(size_type n, const value_type& value);

        template <class IIter>
        void copy_assign(IIter first, IIter last, input_iterator_tag);

        template <class FIter>
        void copy_assign(FIter first, FIter last, forward_iterator_tag);

        size_type get_new_cap(size_type add_size);

        template <class... Args>
        void reallocate_emplace(iterator pos,  Args&& ...args);
        void reallocate_insert(iterator pos, const value_type& value);

        iterator fill_insert(iterator pos,const size_type n, const value_type& value);
        template <class Iter>
        void copy_insert(iterator pos, Iter first, Iter last);
    public:
        iterator begin() noexcept
        { return begin_; }
        iterator begin() const noexcept
        { return begin_; }
        iterator end() noexcept
        { return end_;   }
        iterator end() const noexcept
        { return end_;   }

        reverse_iterator       rbegin()        noexcept
        { return reverse_iterator(end()); }
        const_reverse_iterator rbegin()  const noexcept
        { return const_reverse_iterator(end()); }
        reverse_iterator       rend()          noexcept
        { return reverse_iterator(begin()); }
        const_reverse_iterator rend()    const noexcept
        { return const_reverse_iterator(begin()); }

        const_iterator         cbegin()  const noexcept
        { return begin(); }
        const_iterator         cend()    const noexcept
        { return end(); }
        const_reverse_iterator crbegin() const noexcept
        { return rbegin(); }
        const_reverse_iterator crend()   const noexcept
        { return rend(); }

        // 容量相关操作
        bool  empty()  const noexcept
        { return begin_ == end_; };
        size_type size() const noexcept
        { return static_cast<size_type> (end_ - begin_);};
        size_type max_size() const noexcept
        { return static_cast<size_type> (-1)/sizeof(T);}
        size_type capacity() const noexcept
        { return static_cast<size_type > (cap_ - begin_);}

        reference operator[] (size_type n){
            return *(begin_ + n);
        }

        const_reference operator[] (size_type n) const{
            return *(begin_ + n);
        }

        reference at(size_type n){
            return (*this)[n];
        }

        const_reference at(size_type n) const{
            return (*this)[n];
        }

        reference front(){
            return *begin_;
        }

        const_reference front() const {
            return *begin_;
        }

        reference back(){
            return *(end_ - 1);
        }

        const_reference back() const{
            return *(end_ - 1);
        }

        pointer data() noexcept { return begin_; }
        const_pointer data() const noexcept { return begin_; }

        // 修改容器相关操作
        void assign(size_type n,const value_type& value){
            fill_assign(n, value);
        }

        template <class Iter, typename std::enable_if<
        MyTinySTL::is_input_iterator<Iter>::value, int>::type = 0>
        void assign (Iter first, Iter last){
            copy_assign(first, last, iterator_category(first));
        }

        void assign(std::initializer_list<value_type> il){
            copy_assign(il.begin(), il.end(), MyTinySTL::forward_iterator_tag{});
        }

        template <class... Args>
        iterator emplace(const_iterator pos, Args&& ...args);

        template <class... Args>
        void emplace_back(Args&& ...args);

        void push_back(const value_type& value);
        void push_back(value_type&& value)
        { emplace_back(MyTinySTL::move(value)); };

        void pop_back();

        iterator insert(const_iterator pos, const value_type& value);
        iterator insert(const_iterator pos, const value_type&& value)
        { return emplace(pos, MyTinySTL::move(value)); }

        iterator insert(const_iterator pos, size_type n, const value_type& value){
            return fill_insert(const_cast<iterator>(pos), n, value);
        }

        template <class Iter, typename std::enable_if<
                MyTinySTL::is_input_iterator<Iter>::value, int>::type = 0>
        void insert(const_iterator pos, Iter first, Iter last){
            copy_insert(const_cast<iterator>(pos), first, last);
        }

        // erase
        iterator erase(const_iterator pos);
        iterator erase(const_iterator first, const_iterator second);

        // clear
        void clear() { erase(begin(), end()); }

        // resize
        void resize(size_type new_size) { return resize(new_size, value_type()); }
        void resize(size_type new_size, const value_type& value);
        // 分配空间
        void reserve(size_type n);

        void swap(vector& rhs) noexcept;
    };

    /////////  工具函数   //////////////////////////////////////
    template <class T>
    void vector<T>::try_init() {
        try{
            // 默认分配16个单位
            begin_ = data_allocator::allocate(16);
            end_ = begin_;
            cap_ = begin_ + 16;
        }
        catch (...) {
            begin_ = nullptr;
            end_ = nullptr;
            cap_ = nullptr;
        }
    }

    template <class T>
    void vector<T>::fill_init(size_type n,const value_type& value){
        const size_type init_size = std::max(static_cast<size_type>(16),n);
        init_space(n,init_size);
        MyTinySTL::uninitialized_fill_n(begin_,n,value);
    }

    template <class T>
    template <class Iter>
    void vector<T>::range_init(Iter first, Iter last){
        const size_type init_size = std::max(static_cast<size_type>(last-first),
                                                   static_cast<size_type>(16));
        init_space(static_cast<size_type>(last - first), init_size);
        MyTinySTL::uninitialized_copy(first, last, begin_);
    }

    template <class T>
    void vector<T>::init_space(size_type size, value_type cap) {
        try{
            begin_ = data_allocator::allocate(cap);
            end_ = begin_ + size;
            cap_ = begin_ + cap;
        }
        catch (...) {
            begin_ = nullptr;
            end_ = nullptr;
            cap_ = nullptr;
            throw;
        }
    }

    template <class T>
    void vector<T>::destroy_and_recover(iterator first, iterator last, size_type n) {
        data_allocator::destroy(first, last);
        data_allocator::deallocate(first, n);
    }

    template <class T>
    void vector<T>::fill_assign(size_type n, const value_type& value) {
        if (n > capacity()){
            vector tmp(n, value);
            swap(tmp);
        }
        else if (n > size()){
            MyTinySTL::fill(begin(), end(), value);
            end_  = MyTinySTL::uninitialized_fill_n(end_, n - size(), value);
        }
        else{
            erase(MyTinySTL::fill_n(begin_, n, value), end_);
        }
    }

    template <class T>
    template <class IIter>
    void vector<T>::copy_assign(IIter first, IIter last, input_iterator_tag) {
        auto cur = begin_;
        for(;first != last && cur != end_; first++,cur++){
            *cur = *first;
        }
        if (first == last){
            erase(cur, end_);
        }
        else{
            insert(end_, first, last);
        }
    }

    template <class T>
    template <class FIter>
    void vector<T>::copy_assign(FIter first, FIter last, forward_iterator_tag) {
        const size_type len = MyTinySTL::distance(first, last);
        if (len > capacity()){
            vector tmp(first, last);
            swap(tmp);
        }
        else if (size() > len){
            auto new_end = MyTinySTL::copy(first, last, begin_);
            data_allocator::destroy(new_end, end_);
            end_ = new_end;
        }
        else{
            auto tmp = first;
            MyTinySTL::advance(tmp, size());
            MyTinySTL::copy(first, tmp, begin_);
            auto new_end = MyTinySTL::uninitialized_copy(tmp, last, end_);
            end_ = new_end;
        }
    }

    template <class T>
    typename vector<T>::size_type
    vector<T>::get_new_cap(size_type add_size) {
        const auto old_size = capacity();
        if (old_size > max_size() - old_size / 2){
            return old_size + add_size > max_size() - 16
            ? old_size + add_size : old_size + add_size + 16;
        }
        const size_type new_size = old_size == 0
                ? std::max(add_size,static_cast<size_type>(16))
                : std::max(old_size + old_size/2, old_size + add_size);
        return new_size;
    }

    // 重新分配空间并在 pos 处就地的构造元素
    template <class T>
    template <class ...Args>
    void vector<T>::reallocate_emplace(iterator pos, Args&& ...args) {
        const auto new_size = get_new_cap(1);
        auto new_begin = data_allocator::allocate(new_size);
        auto new_end = new_begin;
        try{
            new_end = MyTinySTL::uninitialized_move(begin_, pos, new_begin);
            data_allocator::construct(MyTinySTL::address_of(*new_end), MyTinySTL::forward<Args>(args)...);
            ++new_end;
            new_end = MyTinySTL::uninitialized_move(pos, end_, new_end);
        }
        catch (...){
            data_allocator::deallocate(new_begin, new_size);
            throw;
        }
        destroy_and_recover(begin_, end_, cap_ - begin_);
        begin_ = new_begin;
        end_ = new_end;
        cap_ = new_begin + new_size;
    }

    template <class T>
    void vector<T>::reallocate_insert(iterator pos, const value_type& value) {
        const auto new_size = get_new_cap(1);
        auto new_begin = data_allocator::allocate(new_size);
        auto new_end = new_begin;
        try{
            new_end = MyTinySTL::uninitialized_move(begin_, pos, new_begin);
            data_allocator::construct(MyTinySTL::address_of(*new_end), value);
            ++new_end;
            new_end = MyTinySTL::uninitialized_move(pos, end_, new_end);
        }
        catch (...){
            data_allocator::deallocate(new_begin, new_size);
            throw;
        }
        destroy_and_recover(begin_, end_, cap_ - begin_);
        begin_ = new_begin;
        end_ = new_end;
        cap_ = new_begin + new_size;
    }

    template <class T>
    typename vector<T>::iterator
    vector<T>::fill_insert(iterator pos, const size_type n, const value_type& value) {
        if (n == 0)
            return pos;
        const size_type len = pos - begin_;
        const value_type value_copy = value;
        if (static_cast<size_type>(cap_ - end_) >= n){
            // 如果容量充足
            const size_type after_pos = end_ - pos;
            auto old_end = end_;
            if (after_pos > n){
                MyTinySTL::uninitialized_copy(end_ - n, end_, end_);
                end_ += n;
                MyTinySTL::copy_backward(pos, old_end - n, old_end);
                MyTinySTL::uninitialized_fill_n(pos, n, value_copy);
            }
            else{
                end_ = MyTinySTL::uninitialized_fill_n(end_, n - after_pos, value_copy);
                end_ = MyTinySTL::uninitialized_move(pos, old_end, end_);
                MyTinySTL::uninitialized_fill_n(pos, after_pos, value_copy);
            }
        }
        else{
            // 备用空间不足
            const auto new_size = get_new_cap(n);
            auto new_begin = data_allocator::allocate(new_size);
            auto new_end = new_begin;
            try{
                new_end = MyTinySTL::uninitialized_move(begin_, pos,new_begin);
                new_end = MyTinySTL::uninitialized_fill_n(new_end, n, value_copy);
                new_end = MyTinySTL::uninitialized_move(pos, end_, new_end);
            }
            catch (...){
                dastroy_and_recover(new_begin, new_end, new_size);
                throw;
            }
            data_allocator::deallocate(begin_, cap_ - begin_);
            begin_ = new_begin;
            end_ = new_end;
            cap_ = begin_ + new_size;
        }
        return begin_ + len;
    }


    template <class T>
    template <class Iter>
    void vector<T>::copy_insert(iterator pos, Iter first, Iter last) {
        if (first == last)
            return;
        const auto n = MyTinySTL::distance(first,last);
        if ((cap_ - end_) >= n){
            const auto after_pos = end_ - pos;
            auto old_end = end_;
            if (after_pos > n){
                end_ = MyTinySTL::uninitialized_copy(end_ - n, end_, end_);
                MyTinySTL::copy_backward(pos, old_end - n, old_end);
                MyTinySTL::uninitialized_copy(first, last, pos);
            }
            else{
                auto mid = first;
                MyTinySTL::advance(mid, after_pos);
                end_ = MyTinySTL::uninitialized_copy(mid, last, end_);
                end_ = MyTinySTL::uninitialized_move(pos, old_end, end_);
                MyTinySTL::uninitialized_copy(first, mid, pos);
            }
        }
        else{
            const auto new_size = get_new_cap(n);
            auto new_begin = data_allocator::allocate(new_size);
            auto new_end = new_begin;
            try{
                new_end = MyTinySTL::uninitialized_move(begin_, pos, new_begin);
                new_end = MyTinySTL::uninitialized_copy(first, last, new_end);
                new_end = MyTinySTL::uninitialized_move(pos, end_, new_end);
            }
            catch (...){
                destroy_and_recover(new_begin, new_end, new_size);
                throw;
            }
            data_allocator::deallocate(begin_, cap_ - begin_);
            begin_ = new_begin;
            end_ = new_end;
            cap_ = new_begin + new_size;
        }
    }

    ///////////////////////////  vector 方法函数  /////////////////////////

    // 当原容量小于要求大小时，才会重新分配空间
    template <class T>
    void vector<T>::reserve(size_type n) {
        if(capacity() < n){
            const auto old_size = size();
            auto tmp = data_allocator::allocate(n);
            MyTinySTL::uninitialized_move(begin_, end_, tmp);
            data_allocator::deallocate(begin_, cap_ - begin_);
            begin_ = tmp;
            end_ = tmp + old_size;
            cap_ = begin_ + n;
        }
    }

    template <class T>
    void vector<T>::resize(size_type new_size, const value_type& value) {
        if (new_size < size()){
            erase(begin() + new_size, end());
        }
        else{
            insert(end(), new_size - size(), value);
        }
    }

    //////////////////////////  构造函数  ////////////////////////////////
    template <class T>
    vector<T>& vector<T>::operator= (const vector& rhs){
        if(this != &rhs){
            const auto len = rhs.size();
            // 容量过大
            if(len > capacity()){
                vector tmp(rhs.begin(),rhs.end());
                swap(tmp);
            }
            else if(size() > len){
                auto i = MyTinySTL::copy(rhs.begin_, rhs.end_, begin());
                data_allocator::fdestory(i, end_);
                end_ = begin_ + len;
            }
            else{
                MyTinySTL::copy(rhs.begin(), rhs.begin() + size(), begin_);
                MyTinySTL::uninitialized_copy(rhs.begin() + size(),rhs.end(), end_);
                cap_ = end_ = begin_ + len;
            }
        }
        return *this;
    }

    // 移动赋值操作符
    template <class T>
    vector<T>& vector<T>::operator= (vector&& rhs) noexcept{
        destroy_and_recover(begin_, end_, cap_ - begin_);
        begin_ = rhs.begin_;
        end_ = rhs.end_;
        cap_ = rhs.cap_;
        rhs.begin_ = nullptr;
        rhs.end_ = nullptr;
        rhs.cap_ = nullptr;
        return *this;
    }

    template <class T>
    void vector<T>::swap(vector& rhs) noexcept{
        if(this != &rhs){
            MyTinySTL::swap(begin_, rhs.begin_);
            MyTinySTL::swap(end_, rhs.end_);
            MyTinySTL::swap(cap_, rhs.cap_);
        }
    }

    // 在 pos 位置就地构造元素，避免额外的复制和移动开销
    template <class T>
    template <class ...Args>
    typename vector<T>::iterator
    vector<T>::emplace(const_iterator pos, Args&& ...args){
        iterator Iterpos = const_cast<iterator>(pos);
        const size_type n = Iterpos - begin_;
        if (end_ != cap_ && Iterpos == end_){
            data_allocator::construct(MyTinySTL::address_of(*end_), MyTinySTL::forward<Args>(args)...);
            ++end_;
        }
        else if (end_ != cap_){
            auto new_end = end_;
            data_allocator::construct(MyTinySTL::address_of(*end_), *(end_ - 1));
            ++ new_end;
            MyTinySTL::copy_backward(Iterpos, end_ - 1, end_);
            *Iterpos = value_type(MyTinySTL::forward<Args>(args)...);
            end_ = new_end;
        }
        else{
            reallocate_emplace(Iterpos, MyTinySTL::forward<Args>(args)...);
        }
        return begin() + n;
    }

    // 在尾部添加元素，避免额外复制和移动开销
    template <class T>
    template <class ...Args>
    void vector<T>::emplace_back(Args&& ...args) {
        if (end_ < cap_){
            data_allocator::construct(MyTinySTL::address_of(*end_), MyTinySTL::forward<Args>(args)...);
            end_++;
        }
        else{
            reallocate_emplace(end_, MyTinySTL::forward<Args>(args)...);
        }
    }

    // 在尾部添加元素
    template <class T>
    void vector<T>::push_back(const value_type& value) {
        if (end_ != cap_){
            data_allocator::construct(MyTinySTL::address_of(*end_), value);
            ++end_;
        }else{
            reallocate_insert(end_, value);
        }
    }

    // 取出尾部元素
    template <class T>
    void vector<T>::pop_back() {
        if (begin_ != end_){
            data_allocator::destroy(end_ - 1);
            --end_;
        }
    }

    // 在指定位置插入元素
    template <class T>
    typename vector<T>::iterator
    vector<T>::insert(const_iterator pos, const value_type& value) {
        iterator Iterpos = const_cast<iterator>(pos);
        const size_type n = pos - begin_;
        if (end_ != cap_ && Iterpos == end_){
            data_allocator::construct(MyTinySTL::address_of(*end_), value);
            ++end_;
        }
        else if (end_ != cap_){
            auto new_end = end_;
            data_allocator::construct(MyTinySTL::address_of(*end_), *(end_ - 1));
            ++new_end;
            auto value_copy = value;
            MyTinySTL::copy_backward(Iterpos, end_ - 1, end_);
            *Iterpos = MyTinySTL::move(value_copy);
            end_ = new_end;
        }
        else{
            reallocate_insert(Iterpos, value);
        }
        return begin_ + n;
    }

    template <class T>
    typename vector<T>::iterator
    vector<T>::erase(const_iterator pos){
        iterator xpos = begin_ + (pos - begin_);
        MyTinySTL::move(xpos+1, end_, xpos);
        data_allocator::destroy(end_ - 1);
        --end_;
        return xpos;
    }

    template <class T>
    typename vector<T>::iterator
    vector<T>::erase(const_iterator first, const_iterator last) {
        const auto n = first - begin_;
        iterator pos = begin_ + n;
        data_allocator::destroy(MyTinySTL::move(pos + (last - first), end_, pos), end_);
        end_ = end_ - (last - first);
        return begin_ + n;
    }

    //////////////////////////  重载比较操作符  ////////////////////////////////
    template <class T>
    bool operator == (const vector<T>& lhs, const vector<T>& rhs){
        return lhs.size() == rhs.size() &&
             MyTinySTL::equal(lhs.begin(),lhs.end(),rhs.begin());
    }

    template <class T>
    bool operator < (const vector<T>& lhs, const vector<T>& rhs){
        return MyTinySTL::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class T>
    bool operator!=(const vector<T>& lhs, const vector<T>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T>
    bool operator>(const vector<T>& lhs, const vector<T>& rhs)
    {
        return rhs < lhs;
    }

    template <class T>
    bool operator<=(const vector<T>& lhs, const vector<T>& rhs)
    {
        return !(rhs < lhs);
    }

    template <class T>
    bool operator>=(const vector<T>& lhs, const vector<T>& rhs)
    {
        return !(lhs < rhs);
    }

    // 重载 mystl 的 swap
    template <class T>
    void swap(vector<T>& lhs, vector<T>& rhs)
    {
        lhs.swap(rhs);
    }
}