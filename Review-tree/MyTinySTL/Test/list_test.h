//
// Created by 谯保林 on 2021/6/7.
//

#ifndef MYTINYSTL_LIST_TEST_H
#define MYTINYSTL_LIST_TEST_H

#endif //MYTINYSTL_LIST_TEST_H
#include "../MyTinySTL/list.h"
#include "test.h"

namespace MyTinySTL
{
    namespace test {
        void list_test() {
            std::cout<< "==================================\n";
            std::cout<< "========= list test ============\n";
            std::cout<< "==================================\n";
            int value = 101;
            list<int> list1 = list<int>();
            Print_List("默认构造函数",list1);
            list<int> list2 = list<int>(10);
            Print_List("构造函数",list2);
            list<int> list3 = list<int>(4,5);
            Print_List("构造函数",list3);
            list<int> list4(list3.begin(), list3.end());
            Print_List("构造函数", list4);
            list<int> list5({1,2,3,4,5,6});
            Print_List("构造函数", list5);
            list<int> list6(list5);
            Print_List("拷贝构造函数",list6);

            list6.assign(6,5);
            Print_List("after assign", list6);
            list6.assign(list3.begin(), list3.end());
            Print_List("after assign", list6);
            list6.assign({1,1,2,2,6,5,4});
            Print_List("after assign", list6);

            list6.insert(list6.begin(), 10, 21);
            Print_List("after insert 10 value", list6);
            list6.insert(list6.begin() + 1, 11);
            Print_List("after insert 11", list6);
            list6.insert(list6.begin(), int());
            Print_List("after insert 11", list6);
            list6.insert(list6.begin() +3, list5.begin(), list5.end());
            Print_List("after insert 1sit5", list6);

            list6.erase(list6.begin() + 2);
            Print_List("after erase second pos", list6);
            list6.erase(list6.begin() + 1, list6.end());
            Print_List("after erase", list6);

            list6.emplace_back(14);
            Print_List("after emplace back", list6);
            list6.emplace_front(18);
            Print_List("after emplace front", list6);
            list6.emplace(list6.begin(), 19);
            Print_List("after emplace", list6);

            list6.push_back(value);
            Print_List("after push_back", list6);
            list6.push_back(102);
            Print_List("after push_back", list6);

            list6.push_front(value);
            Print_List("after push_front", list6);
            list6.push_front(102);
            Print_List("after push_front", list6);

            list6.pop_back();
            Print_List("after pop_back", list6);
            list6.pop_front();
            Print_List("after pop_front",list6);

            std::cout << "The size is : " << list6.size() <<std::endl;
            list6.resize(4);
            Print_List("after resize",list6);
            std::cout << "The size is : " << list6.size() <<std::endl;
            list6.resize(10,7);
            Print_List("after resize",list6);
            std::cout << "The size is : " << list6.size() <<std::endl;

            list6.reverse();
            Print_List("after reverse", list6);
        }
    }
}