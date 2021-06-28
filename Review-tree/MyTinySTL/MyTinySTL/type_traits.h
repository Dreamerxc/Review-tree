// -*- coding: utf-8-unix; -*-
// Copyright (c) 2021 Tencent, Inc.
//     All rights reserved.
//
// Author: kricsqiao@tencent.com
// Date: 2021/4/17 14:58
// Description:
//

#pragma once
#include <type_traits>

namespace MyTinySTL{

    template <class T,T v>
    struct m_integral_constant{
        static constexpr T value = v;
    };

    template <bool b>
    using m_bool_constant = m_integral_constant<bool,b>;

    typedef m_bool_constant<true> m_true_type;
    typedef m_bool_constant<false> m_false_type;



   /* // pair traits
    template <class T1, class T2>
    struct pair;*/

    template <class T>
    struct is_pair : MyTinySTL::m_false_type {};

    template <class T1, class T2>
    struct is_pair<std::pair<T1, T2>>: MyTinySTL::m_true_type {};
}