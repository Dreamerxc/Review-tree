// -*- coding: utf-8-unix; -*-
// Copyright (c) 2021 Tencent, Inc.
//     All rights reserved.
//
// Author: kricsqiao@tencent.com
// Date: 2021/4/18 15:17
// Description:
//

#include <cstddef>
#include <cstdlib>
#include <climits>

#include "algobase.h"
#include "allocator.h"
#include "construct.h"
#include "uninitialized.h"
#include "util.h"
#pragma once

namespace MyTinySTL
{
    // 获得对象地址
    template <class Tp>
    constexpr Tp* address_of(Tp& value) noexcept{
        return &value;
    }

    // 获取 、 释放 临时缓冲区
    template <class T>
    std::pair<T*, ptrdiff_t> get_buffer_helper(ptrdiff_t len, T*)
    {
        if (len > static_cast<ptrdiff_t>(INT_MAX / sizeof(T)))
            len = INT_MAX / sizeof(T);
        while (len > 0) {
            T* tmp = static_cast<T*>(malloc(static_cast<size_t>(len) * sizeof(T)));
            if (tmp)
                return std::pair<T*, ptrdiff_t> (tmp, len);
            len /= 2;
        }
        return std::pair<T*, ptrdiff_t>(nullptr, 0);
    }

    template <class T>
    std::pair<T*, ptrdiff_t> get_temporary_buffer(ptrdiff_t len)
    {
        return get_buffer_helper(len, static_cast<T*>(0));
    }

    template <class T>
    std::pair<T*, ptrdiff_t> get_temporary_buffer(ptrdiff_t len, T*)
    {
        return get_buffer_helper(len, static_cast<T*>(0));
    }

    template <class T>
    void release_temporary_buffer(T* ptr)
    {
        free(ptr);
    }

    // 类模板 ： temporary_buffer
    // 进行临时缓冲区的申请与释放
    template <class ForwardIterator, class T>
    class temporary_buffer
    {
    private:
        ptrdiff_t  original_size;     // 缓冲区申请的大小
        ptrdiff_t  len;               // 缓冲区实际大小
        T*         buffer;            // 指向缓冲区的指针
    public:
        temporary_buffer(ForwardIterator* first, ForwardIterator last);

        ~temporary_buffer()
        {
            MyTinySTL::destroy(buffer, buffer + len);
            free(buffer);
        }
    public:
        ptrdiff_t  size()  const noexcept { return len; };
        ptrdiff_t  requested_size() const noexcept { return original_size; };
        T*         begin() noexcept { return buffer; };
        T*         end()   noexcept { return buffer + len; };
    };

}
