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
            int value = 101;
            deque<int> qu;
            Print("默认构造函数", qu);
            deque<int> qu1(10);
            Print("构造函数", qu1);
            deque<int> qu2(4,6);
            Print("构造函数", qu2);
            deque<int> qu3(qu2.begin(), qu2.end());
            Print("构造函数", qu3);
            deque<int> qu4(qu1);
            Print("拷贝构造函数", qu4);
            deque<int> qu5({1,2,3,4,5,6,7});
            Print("构造函数", qu5);
            deque<int> qu6(MyTinySTL::move(qu5));
            Print("移动构造函数", qu6);
            std::cout<< qu6.size() << std::endl;
            std::cout<< qu2.size() << std::endl;
            //qu6 = qu2;
            //Print("赋值构造函数", qu6);

            qu6.resize(10);
            Print("after resize: ", qu6);
            qu6.resize(12,10);
            Print("after resize: ", qu6);
            qu6.emplace_front(11);
            Print("after emplace_front: ", qu6);
            qu6.emplace_back(17);
            Print("after emplace_back: ", qu6);
            qu6.push_front(14);
            Print("after push_front: ", qu6);
            qu6.push_back(14);
            Print("after push_back: ", qu6);
            qu6.insert(qu6.begin() + 1, 18);
            Print("after insert at pos[1]: ", qu6);
            qu6.insert(qu6.begin() + 5, value);
            Print("after insert at pos[5]: ", qu6);
            qu6.insert(qu6.begin() + 12, qu3.begin(), qu3.end());
            Print("after insert deque qu6: ", qu6);

            qu3.assign(5,4);
            Print("after assign: ", qu3);
            qu3.assign({1,2,3,4,5,6,7,8,9,10});
            Print("after assign: ", qu3);
            qu3.assign(qu6.begin(), qu6.end());
            Print("after assign qu6: ", qu3);

            qu3.pop_front();
            Print("after pop_front(): ", qu3);
            qu3.pop_back();
            Print("after pop_back(): ", qu3);

            qu3.erase(qu3.begin() + 1);
            Print("after erase pos[1]: ", qu3);
            qu3.erase(qu3.begin(), qu3.begin() + 10);
            Print("after erase pos[1] - pos[10]: ", qu3);
        }
    }
}