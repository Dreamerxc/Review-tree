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
    // uninitialized_copy_n
    // 把 [first, first + n) 上的内容复制到以 result 为起始处的空间，返回复制结束的位置
    /*****************************************************************************************/
    template <class InputIter, class size, class ForwardIter>
    ForwardIter unchecked_uninit_copy_n(InputIter first, size n,
                    ForwardIter value, std::true_type)
    {
        return MyTinySTL::copy_n(first, n, value).second;
    }

    template <class InputIter, class size, class ForwardIter>
    ForwardIter unchecked_uninit_copy_n(InputIter first, size n,
            ForwardIter value, std::false_type)
    {
        ForwardIter cur = value;
        try {
            for (; n>0 ; --n, ++cur, ++value) {
                MyTinySTL::construct(&*cur, *first);
            }
        }
        catch (...) {
            for ( ; cur!=value; ++cur){
                MyTinySTL::destroy(&*cur);
            }
        }
        return cur;
    }

    template <class InputIter, class size, class ForwardIter>
    ForwardIter uninitialized_fill_n(InputIter first, size n, ForwardIter value)
    {
        return MyTinySTL::unchecked_uninit_copy_n(first, n, value,
                                                    std::is_trivially_copy_assignable<
                                                    typename iterator_traits<InputIter>::
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