//
// Created by Dreamer.c on 2021/6/23.
//

#ifndef MYTINYSTL_STACK_TEST_H
#define MYTINYSTL_STACK_TEST_H

#endif //MYTINYSTL_STACK_TEST_H
#include "stack.h"
#include "test.h"


namespace MyTinySTL {
    void stack_print(MyTinySTL::stack<int> s)
    {
        while (!s.empty())
        {
            std::cout << " " << s.top();
            s.pop();
        }
        std::cout << std::endl;
    }

// stack 的遍历输出
#define Print_stack(t,s) do {                       \
    std::string s_name = #s;                     \
    std::cout << t << " " << s_name << " :";          \
    stack_print(s);                              \
} while(0)
    namespace test {
        void stack_test() {
            std::cout << "==================================\n";
            std::cout << "========= stack test ============\n";
            std::cout << "==================================\n";
            stack<int> st;
            Print_stack("默认构造函数",st);
            stack<int> st1(10,6);
            Print_stack("构造函数",st1);
            stack<int> st3(st1);
            Print_stack("拷贝构造函数",st3);

            st = st1;
            Print_stack("赋值构造函数",st);

            st.push(1);
            st.push(2);
            Print_stack("After push",st);

            st.pop();
            Print_stack("After pop",st);
        }
    }
}