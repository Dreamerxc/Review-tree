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
#include "util.h"
#include <cstring>
#include <utility>
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
    template <class RandomIter, class OutputIter>
    OutputIter unchecked_copy_cat(RandomIter first, RandomIter last,
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
    template <class BidirectionalIter1, class BidirectionalIter2>
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
    bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2){
        for( ; first1 != last1;first1++,first2++){
            if (first1 != first2) return false;
        }
        return true;
    }

    // 重载版本，使用自定义函数判断
    template <class InputIter1, class InputIter2, class Compared>
    bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2, Compared comp){
        for( ; first1 != last1;first1++,first2++){
            if (!comp(*first1,*first2)) return false;
        }
        return true;
    }

    template <class InputIter1,class InputIter2>
    bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
                                    InputIter2 first2, InputIter2 last2){
        for( ; first1!=last1 && first2!=last2; ++first1, ++first2){
            if( *first1<*first2 ) return true;
            if( *first1>*first2 ) return false;
        }
        return first1 == last1 && first2 != last2;
    }

    template <class InputIter1,class InputIter2, class Compared>
    bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
            InputIter2 first2, InputIter2 last2, Compared comp){
        for( ; first1!=last1 && first2!=last2; ++first1, ++first2){
            if(comp(*first1,*first2)) return true;
            if(comp(*first2,*first1)) return false;
        }
        return first1 == last1 && first2 != last2;
    }

    /*****************************************************************************************/
    // fill_n
    // 从 first 位置开始填充 n 个值
    /*****************************************************************************************/
    template <class InputIterator, class size, class T>
    InputIterator unchecked_fill_n(InputIterator first, size n, const T& value)
    {
        for ( ; n>0 ; --n, ++first)
        {
            *first = value;
        }
        return first;
    }

    // 为one-byte提供特化版本
    template <class Tp, class Size, class Up>
    typename std::enable_if<
            std::is_integral<Tp>::value && sizeof(Tp) == 1 &&
                    !std::is_same<Tp, bool>::value &&
                    std::is_integral<Up>::value && sizeof(Up) == 1,
            Tp*>::type
     unchecked_fill_n(Tp* first, Size n, Up value)
    {
         if (n > 0)
         {
             std::memset(first, (unsigned char)value, (size_t)(n));
         }
         return first + n;
    }

    template <class InputIterator, class size, class T>
    InputIterator fill_n(InputIterator first, size n, const T& value)
    {
        return unchecked_fill_n(first, n, value);
    }

    /*****************************************************************************************/
    // copy_n
    // 把 [first, first + n)区间上的元素拷贝到 [result, result + n)上
    // 返回一个 pair 分别指向拷贝结束的尾部
    /*****************************************************************************************/
    template <class InputIter, class Size, class OutputIter>
    std::pair<InputIter, OutputIter>
    unchecked_copy_n(InputIter first, Size n, OutputIter result, MyTinySTL::input_iterator_tag)
    {
        for (; n > 0; --n, ++first, ++result)
        {
            *result = *first;
        }
        return std::pair<InputIter, OutputIter>(first, result);
    }

    template <class RandomIter, class Size, class OutputIter>
    std::pair<RandomIter, OutputIter>
    unchecked_copy_n(RandomIter first, Size n, OutputIter result,
            MyTinySTL::random_access_iterator_tag)
    {
        auto last = first + n;
        return std::pair<RandomIter, OutputIter>(last, MyTinySTL::copy(first, last, result));
    }

    template <class InputIter, class Size, class OutputIter>
    std::pair<InputIter, OutputIter>
    copy_n(InputIter first, Size n, OutputIter result)
    {
        return unchecked_copy_n(first, n, result, iterator_category(first));
    }

    /*****************************************************************************************/
    // fill
    // 为 [first, last)区间内的所有元素填充新值
    /*****************************************************************************************/
    template <class ForwardIter, class T>
    void fill_cat(ForwardIter first, ForwardIter last, const T& value,
                              MyTinySTL::forward_iterator_tag)
    {
        for (; first != last ; ++first) {
            *first = value;
        }
    }

    template <class ForwardIter, class T>
    void fill_cat(ForwardIter first, ForwardIter last, const T& value,
            MyTinySTL::random_access_iterator_tag)
    {
        fill_n(first, last - first, value);
    }

    template <class ForwardIter, class T>
    void fill(ForwardIter first, ForwardIter last, const T& value) {
        fill_cat(first, last, value, iterator_category(first));
    }

    /*****************************************************************************************/
// move
// 把 [first, last)区间内的元素移动到 [result, result + (last - first))内
/*****************************************************************************************/
// input_iterator_tag 版本
    template <class InputIter, class OutputIter>
    OutputIter
    unchecked_move_cat(InputIter first, InputIter last, OutputIter result,
                       MyTinySTL::input_iterator_tag)
    {
        for (; first != last; ++first, ++result)
        {
            *result = MyTinySTL::move(*first);
        }
        return result;
    }

// ramdom_access_iterator_tag 版本
    template <class RandomIter, class OutputIter>
    OutputIter
    unchecked_move_cat(RandomIter first, RandomIter last, OutputIter result,
                       MyTinySTL::random_access_iterator_tag)
    {
        for (auto n = last - first; n > 0; --n, ++first, ++result)
        {
            *result = MyTinySTL::move(*first);
        }
        return result;
    }

    template <class InputIter, class OutputIter>
    OutputIter
    unchecked_move(InputIter first, InputIter last, OutputIter result)
    {
        return unchecked_move_cat(first, last, result, iterator_category(first));
    }

// 为 trivially_copy_assignable 类型提供特化版本
    template <class Tp, class Up>
    typename std::enable_if<
            std::is_same<typename std::remove_const<Tp>::type, Up>::value &&
            std::is_trivially_move_assignable<Up>::value,
            Up*>::type
    unchecked_move(Tp* first, Tp* last, Up* result)
    {
        const size_t n = static_cast<size_t>(last - first);
        if (n != 0)
            std::memmove(result, first, n * sizeof(Up));
        return result + n;
    }

    template <class InputIter, class OutputIter>
    OutputIter move(InputIter first, InputIter last, OutputIter result)
    {
        return unchecked_move(first, last, result);
    }
}