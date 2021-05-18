// -*- coding: utf-8-unix; -*-
// Copyright (c) 2021 Tencent, Inc.
//     All rights reserved.
//
// Author: kricsqiao@tencent.com
// Date: 2021/5/16 15:39
// Description:
//

#pragma once
#include "../MyTinySTL/vector.h"
#include "test.h"

namespace MyTinySTL
{
    namespace test
    {
        void vector_test()
        {
            std::cout<< "==================================\n";
            std::cout<< "========= vector test ============\n";
            std::cout<< "==================================\n";
            std::cout<< int() << std::endl;
            // 测试构造函数
            MyTinySTL::vector<int> v1;
            MyTinySTL::vector<int> v2(10);
            MyTinySTL::vector<int> v3(10,1);
            MyTinySTL::vector<int> v4
        }
    }
}