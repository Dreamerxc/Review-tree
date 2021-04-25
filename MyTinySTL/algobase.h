// -*- coding: utf-8-unix; -*-
// Copyright (c) 2021 Tencent, Inc.
//     All rights reserved.
//
// Author: kricsqiao@tencent.com
// Date: 2021/4/18 14:09
// Description:
//

#pragma once
#include "iterator.h"

namespace MyTinySTL
{
    /*****************************************************/
    /* copy(first, last, result)
     * 把[first, last) 范围内的元素全部复制到以 result 开头中*/
    /*****************************************************/
    template <class InputIterator, class OutputIter>
    OutputIter unchecked_copy_cat(InputIterator first, InputIterator last,
               OutputIter result, MyTinySTL::input_iterator_tag){
        for( ; first != last; ++first, ++result){
            *result = *first;
        }
        return result;
    }

    // unchecked_copy_cat random_access_iterator版本
    template <class InputIterator, class OutputIter>
    OutputIter unchecked_copy_cat(InputIterator first, InputIterator last,
            OutputIter result, MyTinySTL::random_access_iterator_tag){
        for (auto n = last - first; n>0; --n, ++first, ++result){
            *result = *first;
        }
        return result;
    }

    template <class InputIterator,class OutputIterator>
    OutputIterator unchecked_copy(InputIterator first, InputIterator last, OutputIterator result){
        return unchecked_copy_cat(first, last, result, iterator_category(first));
    }

    //  unchecked_copy 特化版本, 指针版本
    template <class Tp, class Up>
    typename std::enable_if<
       std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
       std::is_trivially_copy_assignable<Up>::value, Up*>::type
       unchecked_copy(Tp* first, Tp* last, Up* result){
            const auto n = static_cast<size_t> (last - first);
            if (n != 0){
                std::memmove(result, first, n*sizeof(Up));
            }
            return result + n;
       }

    template <class InputIterator,class OutputIterator>
    OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result){
        return unchecked_copy(first, last, result);
    }

    /************************************************************************/
    /* copy_backward(first, last, result)
     * 将 [first, last)区间内的元素拷贝到 [result - (last - first), result)内*/
    /************************************************************************/
    template <class BidirectionalIter1, class BidirectionalIter2>
    BidirectionalIter2 unchecked_copy_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
            BidirectionalIter2 result, MyTinySTL::bidirectional_iterator_tag){
        while (first != last){
            *--result = *--last;
        }
        return result;
    }

    // unchecked_copy_backward_cat 的 random_access_iterator_tag 版本
    BidirectionalIter2 unchecked_copy_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
            BidirectionalIter2 result, MyTinySTL::random_access_iterator_tag){
        for (auto n = last - first; n>0;--n){
            *--result = *--last;
        }
        return result;
    }

    template <class BidirectionalIter1, class BidirectionalIter2>
    BidirectionalIter2 unchecked_copy_backward(BidirectionalIter1 first, BidirectionalIter1 last,
            BidirectionalIter2 result){
        return unchecked_copy_backward_cat(first, last, result, iterator_category(first));
    }

    template <class Tp, class Up>
    typename std::enable_if<
            std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
                    std::is_trivially_copy_assignable<Up>::value, Up*>::type
    unchecked_copy_backward(Tp* first, Tp* last, Up* result){
        const auto n = static_cast<size_t> (last - first);
        if (n != 0){
            result -= n;
            std::memmove(result, first, n*sizeof(Up));
        }
        return result;
    }
    template <class BidirectionalIter1, class BidirectionalIter2>
    BidirectionalIter2 copy_backward(BidirectionalIter1 first, BidirectionalIter1 last,
            BidirectionalIter2 result){
        return unchecked_copy_backward(first, last, result);
    }

    /************************************************************************/
    /* equal
     * 比较两个序列是否相同*/
    /************************************************************************/
    template <class InputIter1, class InputIter2>
    bool equal(InpuIter1 first1, InputIter1 last1, InputIter2 first2){
        for( ; first1 != last1;first1++,first2++){
            if (first1 != first2) return false;
        }
        return true;
    }

    // 重载版本，使用自定义函数判断
    template <class InputIter1, class InputIter2, class Compared>
    bool equal(InpuIter1 first1, InputIter1 last1, InputIter2 first2, Compared comp){
        for( ; first1 != last1;first1++,first2++){
            if (!comp(*first1,*first2)) return false;
        }
        return true;
    }

    template <class InputIter1,class InputIter2>
    bool lexicographical_compare(InputIter1 first1, InputInter1 last1,
                                    InputIter2 first2, InputIter2 lasr2){
        for( ; first1!=last1 && first2!=last2; ++first1, ++first2){
            if( *first1<*first2 ) return true;
            if( *first1>*first2 ) return false;
        }
        return first1 == last1 && first2 != last2;
    }

    template <class InputIter1,class InputIter2, class Compared>
    bool lexicographical_compare(InputIter1 first1, InputInter1 last1,
            InputIter2 first2, InputIter2 lasr2, Compared comp){
        for( ; first1!=last1 && first2!=last2; ++first1, ++first2){
            if(comp(*first1,*first2)) return true;
            if(comp(*first2,*first1)) return false;
        }
        return first1 == last1 && first2 != last2;
    }
}