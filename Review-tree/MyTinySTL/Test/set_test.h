//
// Created by Dreamer.c on 2021/6/29.
//

#ifndef MYTINYSTL_SET_TEST_H
#define MYTINYSTL_SET_TEST_H

#include "set.h"
namespace MyTinySTL
{
    namespace test
    {
        void set_test()
        {
            std::cout << "==================================\n";
            std::cout << "========= map test ============\n";
            std::cout << "==================================\n";
            set<int> st;
            set<int> st1(st);
           // set<int> st2({1,2,3,4,6});
            st.insert(1);
            st.insert(5);
            st.insert(3);
            st.insert(4);
            st.insert(2);
            st.insert(3);

            for (auto x: st) {
                std::cout<< x << " ";
            }
        }
    }
}









#endif //MYTINYSTL_SET_TEST_H
