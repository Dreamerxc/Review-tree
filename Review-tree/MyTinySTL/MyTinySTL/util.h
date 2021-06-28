// -*- coding: utf-8-unix; -*-
// Copyright (c) 2021 Tencent, Inc.
//     All rights reserved.
//
// Author: kricsqiao@tencent.com
// Date: 2021/4/19 19:48
// Description:
//

#pragma once
#include <cstddef>

#include "type_traits.h"

namespace MyTinySTL
{
    // move
    template <class T>
    typename std::remove_reference<T>::type&& move(T&& arg) noexcept{
        return static_cast<typename std::remove_reference<T>::type&&>(arg);
    }

    // forward 完美转发
    template <class T>
    T&& forward(typename std::remove_reference<T>::type& arg) noexcept{
        return static_cast<T&&>(arg);
    }

    template <class T>
    T&& forward(typename std::remove_reference<T>::type&& arg) noexcept{
        return static_cast<T&&>(arg);
    }

    template <class T>
    void swap(T& lhs, T& rhs)
    {
        auto tmp(MyTinySTL::move(lhs));
        lhs = MyTinySTL::move(rhs);
        rhs = MyTinySTL::move(tmp);
    }

    template <class T>
    const T& max(const T& a, const T& b) {
        return a > b ? a : b;
    }

    template <class T>
    T& min(const T& a, const T& b) {
        return a < b ? a : b;
    }

    // pair 模板
    /*template <class Ty1, class Ty2>
    struct pair
    {
            typedef Ty1 first_type;
            typedef Ty2 second_type;

            first_type first;
            second_type second;
        template <class T1, class T2>
        pair(T1& other1, T2& other2) : first(other1), second(other2){}

    };*/

}