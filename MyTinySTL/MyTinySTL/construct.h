// -*- coding: utf-8-unix; -*-
// Copyright (c) 2021 Tencent, Inc.
//     All rights reserved.
//
// Author: kricsqiao@tencent.com
// Date: 2021/4/25 21:00
// Description:
//

#pragma once
#include<new>

#include "type_traits.h"
#include "iterator.h"
#include "util.h"
namespace MyTinySTL
{

    // construct 构造对象
    template <class T>
    void construct(T* ptr){
        ::new ((void*)ptr) T();
    }

    template <class T1, class T2>
    void construct(T1* ptr, const T2& value){
        ::new ((void*)ptr) T1(value);
    }

    template <class T, class... Args>
    void construct(T* ptr, Args&&... args){
        ::new ((void*)ptr) T(MyTinySTL::forward<Args>(args)...);
    }

    // destroy 将对象析构
    template <class T>
    void destroy_one(T*, std::true_type) {}

    template <class T>
    void destroy_one(T* pointer, std::false_type){
        if (pointer !=nullptr){
            pointer->~T();
        }
    }

    template <class ForwardIter>
    void destroy_cat(ForwardIter, ForwardIter, std::true_type) {}

    template <class ForwardIter>
    void destroy_cat(ForwardIter first, ForwardIter last, std::false_type) {
        for (; first != last; ++first)
        {
            destroy(&*first);
        }
    }

    template <class T>
    void destroy(T* pointer){
        destroy_one(pointer, std::is_trivially_destructible<T>{});
    }

    template <class ForwardIter>
    void destroy(ForwardIter first, ForwardIter last){
        destroy_cat(first, last, std::is_trivially_destructible<
                typename iterator_traits<ForwardIter>::value_type>{});
    }
}
