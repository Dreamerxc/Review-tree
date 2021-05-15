// -*- coding: utf-8-unix; -*-
// Copyright (c) 2021 Tencent, Inc.
//     All rights reserved.
//
// Author: kricsqiao@tencent.com
// Date: 2021/5/14 19:22
// Description:
//

#pragma once
#include "construct.h"
#include "util.h"

namespace MyTinySTL {

    // 模板类 allocator
    template <class T>
    class allocator
    {
    public:
        typedef T         value_type;
        typedef T*        pointer;
        typedef const T*  const_pointer;
        typedef T&        reference;
        typedef const T&  const_reference;
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;

    public:
        static T*  allocate();
        static T*  allocate(size_type n);

        static void deallocate(T* ptr);
        static void deallocate(T* ptr, size_type n);

        static void construct(T* ptr);
        static void construct(T* ptr, const T& value);
        static void construct(T* ptr, const T&& value);

        template <class... Args>
        static void construct(T* ptr, Args&& ...args);

        static void destroy(T* ptr);
        static void destroy(T* first, T* last);
    };

    template <class T>
    T* allocator<T>::allocate()
    {
        return static_cast<T*>(::operator new(sizeof(T)));
    }

    template <class T>
    T* allocator<T>::allocate(size_type n) {
        if (n==0) return nullptr;
        return static_cast<T*>(::operator new(n*sizeof(T)));
    }

    template <class T>
    void allocator<T>::deallocate(T* ptr) {
        if (ptr==nullptr) return;
        ::operator delete(ptr);
    }

    template <class T>
    void allocator<T>::deallocate(T* ptr, size_type n) {
        if (ptr == nullptr) return;
        ::operator delete(ptr);
    }

    template <class T>
    void allocator<T>::construct(T* ptr) {
        MyTinySTL::construct(ptr);
    }

    template <class T>
    void allocator<T>::construct(T* ptr, const T& value) {
        MyTinySTL::construct(ptr, value);
    }

    template <class T>
    void allocator<T>::construct(T* ptr, const T&& value) {
        MyTinySTL::construct(ptr, MyTinySTL::move(value));
    }

    template <class T>
    template <class... Args>
    void allocator<T>::construct(T* ptr, Args&& ...args){
        MyTinySTL::construct(ptr, MyTinySTL::forward<Args>(args)...);
    }

    template <class T>
    void allocator<T>::destroy(T* ptr) {
        MyTinySTL::destroy(ptr);
    }

    template <class T>
    void allocator<T>::destroy(T* first, T* last) {
        MyTinySTL::destroy(first, last);
    }
}













