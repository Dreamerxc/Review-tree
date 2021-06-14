//
// Created by 谯保林 on 2021/6/12.
//

#ifndef MYTINYSTL_DEQUE_TEST_H
#define MYTINYSTL_DEQUE_TEST_H

#endif //MYTINYSTL_DEQUE_TEST_H

#include "../MyTinySTL/deque.h"
#include "test.h"

namespace MyTinySTL
{
    namespace test
    {
        void deque_test() {
            std::cout<< "==================================\n";
            std::cout<< "========= deque test =============\n";
            std::cout<< "==================================\n";
            deque<int> qu;
            Print("默认构造函数", qu);
            deque<int> qu1(10);
            Print("构造函数", qu1);
            deque<int> qu2(10,6);
            Print("构造函数", qu2);
            deque<int> qu3(qu2.begin(), qu2.end());
            Print("构造函数", qu3);
            deque<int> qu4(qu1);
            Print("拷贝构造函数", qu4);
            deque<int> qu5({1,2,3,4,5,6,7});
            Print("构造函数", qu5);
            deque<int> qu6(MyTinySTL::move(qu5));
            Print("移动构造函数", qu6);
            // qu5 = qu2;
            // Print("赋值构造函数", qu5);
        }
    }
}