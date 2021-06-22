// -*- coding: utf-8-unix; -*-
// Copyright (c) 2021 Tencent, Inc.
//     All rights reserved.
//
// Author: kricsqiao@tencent.com
// Date: 2021/5/15 14:23
// Description:
//

#pragma once
#include "type_traits.h"
#include "iterator.h"
#include "algobase.h"

namespace MyTinySTL {
    /*****************************************************************************************/
    // uninitialized_copy
    // 把 [first, last) 上的内容复制到以 result 为起始处的空间，返回复制结束的位置
    /*****************************************************************************************/
    template <class InputIter, class ForwardIter>
    ForwardIter unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::true_type)
    {
       return MyTinySTL::copy(first, last, result);
    }

    template <class InputIter, class ForwardIter>
    ForwardIter unchecked_uninit_copy(InputIter first, InputIter last, ForwardIter result, std::false_type)
    {
        ForwardIter cur = result;
        for( ; first!=last ; ++first, ++cur) {
            MyTinySTL::construct(&*cur, *first);
        }
        return cur;
    }

    template <class InputIter, class ForwardIter>
    ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
    {
        return MyTinySTL::unchecked_uninit_copy(first, last, result,
                                std::is_trivially_copy_assignable<
                                typename iterator_traits<InputIter>::
                                value_type>{});
    }
    /*****************************************************************************************/
    // uninitialized_fill_n
    // 把 [first, first + n) 区间内填充元素值
    /*****************************************************************************************/
    template <class ForwardIter, class size, class T>
    ForwardIter unchecked_uninit_fill_n(ForwardIter first, size n,
                    const T& value, std::true_type)
    {
        return MyTinySTL::fill_n(first, n, value);
    }

    template <class ForwardIter, class size, class T>
    ForwardIter unchecked_uninit_fill_n(ForwardIter first, size n,
                   const T& value, std::false_type)
    {
        ForwardIter cur = first;
        try {
            for (; n>0 ; --n, ++cur) {
                MyTinySTL::construct(&*cur, value);
            }
        }
        catch (...) {
            for ( ; first!=cur; ++first){
                MyTinySTL::destroy(&*first);
            }
        }
        return cur;
    }

    template <class ForwardIter, class size, class T>
    ForwardIter uninitialized_fill_n(ForwardIter first, size n, const T& value)
    {
        return MyTinySTL::unchecked_uninit_fill_n(first, n, value,
                                                    std::is_trivially_copy_assignable<
                                                    typename iterator_traits<ForwardIter>::
                                                            value_type>{});
    }

    /*****************************************************************************************/
    // uninitialized_fill
    // 在 [first, last) 区间内填充元素值
    /*****************************************************************************************/
    template <class ForwardIter, class T>
    void
    unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T& value, std::true_type)
    {
        MyTinySTL::fill(first, last, value);
    }

    template <class ForwardIter, class T>
    void
    unchecked_uninit_fill(ForwardIter first, ForwardIter last, const T& value, std::false_type)
    {
        auto cur = first;
        try
        {
            for (; cur != last; ++cur)
            {
                MyTinySTL::construct(&*cur, value);
            }
        }
        catch (...)
        {
            for (;first != cur; ++first)
                MyTinySTL::destroy(&*first);
        }
    }

    template <class ForwardIter, class T>
    void  uninitialized_fill(ForwardIter first, ForwardIter last, const T& value)
    {
        MyTinySTL::unchecked_uninit_fill(first, last, value,
                                     std::is_trivially_copy_assignable<
                                             typename iterator_traits<ForwardIter>::
                                             value_type>{});
    }

    /*****************************************************************************************/
    // uninitialized_move
    // 把[first, last)上的内容移动到以 result 为起始处的空间，返回移动结束的位置
    /*****************************************************************************************/
    template <class InputIter, class ForwardIter>
    ForwardIter
    unchecked_uninit_move(InputIter first, InputIter last, ForwardIter result, std::true_type)
    {
        return MyTinySTL::move(first, last, result);
    }

    template <class InputIter, class ForwardIter>
    ForwardIter
    unchecked_uninit_move(InputIter first, InputIter last, ForwardIter result, std::false_type)
    {
        ForwardIter cur = result;
        try
        {
            for (; first != last; ++first, ++cur)
            {
                MyTinySTL::construct(&*cur, MyTinySTL::move(*first));
            }
        }
        catch (...)
        {
            MyTinySTL::destroy(result, cur);
        }
        return cur;
    }

    template <class InputIter, class ForwardIter>
    ForwardIter uninitialized_move(InputIter first, InputIter last, ForwardIter result)
    {
        return MyTinySTL::unchecked_uninit_move(first, last, result,
                std::is_trivially_move_assignable<
                        typename iterator_traits<InputIter>::
                        value_type>{});
    }
}