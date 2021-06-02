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
            int a[] = {1,2,3,4,5};
            // 测试构造函数
            std::cout<< " 构造函数测试："<<std::endl;
            MyTinySTL::vector<int> v1;
            MyTinySTL::vector<int> v2(10);
            Print_Vector(v2);
            MyTinySTL::vector<int> v3(10,1);
            Print_Vector(v3);
            MyTinySTL::vector<int> v4(a,a+5);
            Print_Vector(v4);
            MyTinySTL::vector<int> v5(v3);
            Print_Vector(v5);
            MyTinySTL::vector<int> v6(std::move(v3));
            Print_Vector(v6);
            MyTinySTL::vector<int> v7({9,8,7,6,5,4});
            Print_Vector(v7);

            // 容量相关操作
            std::cout<< "==================================\n";
            std::cout<< "容量相关操作："<<std::endl;
            vector<int> v({1,2,3,4,5});
            std::cout<< " size :" << v.size() << std::endl;
            std::cout<< " capacity :" << v.capacity() << std::endl;
            std::cout<< " empty :" << v.empty() << std::endl;
            std::cout<< " front :" << v.front() << std::endl;
            std::cout<< " back :" << v.back() << std::endl;

            // 修改容器相关操作
            std::cout<< "==================================\n";
            std::cout<< "修改容器相关操作："<<std::endl;
            vector<int> tmp1(v);
            tmp1.assign(10,1);
            std::cout<< "after assign :";
            Print_Vector(tmp1);

            vector<int> tmp2(v);
            tmp2.emplace(tmp2.begin(),10);
            std::cout<< "after emplace :";
            Print_Vector(tmp2);

            vector<int> tmp3(v);
            tmp3.emplace_back(10);
            std::cout<< "after emplace_back :";
            Print_Vector(tmp3);

            vector<int> tmp4(v);
            tmp4.push_back(11);
            std::cout<< "after push_back :";
            Print_Vector(tmp4);

            tmp4.pop_back();
            std::cout<< "after pop_back :";
            Print_Vector(tmp4);

            vector<int> tmp5(v);
            tmp5.insert(tmp5.begin(), 14);
            std::cout<< "after insert :";
            Print_Vector(tmp5);

            vector<int> tmp6(v);
            tmp6.erase(tmp6.begin() + 1);
            std::cout<< "after erase :";
            Print_Vector(tmp6);

        }
    }
}