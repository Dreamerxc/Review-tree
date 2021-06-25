// -*- coding: utf-8-unix; -*-
// Copyright (c) 2021 Tencent, Inc.
//     All rights reserved.
//
// Author: kricsqiao@tencent.com
// Date: 2021/5/16 14:13
// Description:
//

#pragma once
#include <ctime>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

namespace MyTinySTL {
    namespace test {
        // TestCase 类
        // 封装单个测试案例
        class TestCase {
        public:
            TestCase(const char *case_name) : testcase_name(case_name) {}

            virtual void Run() = 0;

        public:
            const char *testcase_name;   // 测试案例名称
            int Result;          // 测试案例执行结果
            int PassResult;      // 测试通过的案例数
            int FailResult;      // 测试成功的案例数
        };

        // 单元测试类 把所有测试案例加入到 Vector 中，依次执行测试案例
        class UnitTest {
        public:
            // 获得一个案例
            static UnitTest *GetInstance();

            // 将案例依次加入 std::vector
            TestCase *RegisterTestCase(TestCase *testcase);

            void Run();

        public:
            TestCase *CurrentTestCase;  // 当前执行的测试案例
            int PassResult;       // 测试通过的案例数
            int FailResult;       // 测试通过案例数

        protected:
            std::vector<TestCase *> testcases;  // 保存案例集合
        };

        UnitTest *UnitTest::GetInstance() {
            static UnitTest instance;
            return &instance;
        }

        TestCase *UnitTest::RegisterTestCase(TestCase *testcase) {
            testcases.push_back(testcase);
            return testcase;
        }

        void UnitTest::Run() {
            for (auto it : testcases) {
                TestCase *testcase = it;
                CurrentTestCase = testcase;
                testcase->Result = 1;
                testcase->PassResult = 0;
                testcase->FailResult = 0;
                testcase->Run();
            }
        }

#define Print_Vector(v) {                \
    std::cout<<#v<<":";      \
    for (auto x : v) {                   \
       std::cout<< x << " ";             \
    }                                    \
    std::cout<<std::endl;                \
}

#define Print_List(t, v) {                  \
    std::cout<< t << #v << ":";                  \
    for (auto x : v) {                   \
       std::cout<< x << " ";             \
    }                                    \
    std::cout<<std::endl;               \
}

#define Print(t, v) {                  \
    std::cout<< t << #v << ":";                  \
    for (auto x : v) {                   \
       std::cout<< x << " ";             \
    }                                    \
    std::cout<<std::endl;               \
}

#define Print_stack1(t, v) { \
   std::cout<< t << #v << ":";   \
   while (!v.empty()) {              \
        std::cout << v.top() << " "; \
        v.pop();                     \
   }                       \
   std::cout<<std::endl;   \
   }                    \

    }
}