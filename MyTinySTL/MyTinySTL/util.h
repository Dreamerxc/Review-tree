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
}