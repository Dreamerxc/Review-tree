// -*- coding: utf-8-unix; -*-
// Copyright (c) 2021 Tencent, Inc.
//     All rights reserved.
//
// Author: kricsqiao@tencent.com
// Date: 2021/4/18 15:17
// Description:
//

#pragma once

namespace MyTinySTL
{
    // 获得对象地址
    template <class Tp>
    constexpr Tp* address_of(Tp& value) noexcept{
        return &value;
    }
}
