//
// Created by Dreamer.c on 2021/6/24.
//

#ifndef MYTINYSTL_QUEUE_TEST_H
#define MYTINYSTL_QUEUE_TEST_H

#include "queue.h"

namespace MyTinySTL
{
    void queue_print(MyTinySTL::queue<int> s)
    {
        while (!s.empty())
        {
            std::cout << " " << s.front();
            s.pop();
        }
        std::cout << std::endl;
    }

// stack 的遍历输出
#define Print_queue(t,s) do {                       \
    std::string s_name = #s;                     \
    std::cout << t << " " << s_name << " :";          \
    queue_print(s);                              \
} while(0)

    namespace test
    {
        void queue_test() {
            std::cout << "==================================\n";
            std::cout << "========= queue test ============\n";
            std::cout << "==================================\n";
            queue<int> qu;
            Print_queue("默认构造函数",qu);
            queue<int> qu1(3,1);
            Print_queue("构造函数",qu1);
            queue<int> qu2(qu1);
            Print_queue("拷贝构造函数",qu2);
            qu = qu2;
            Print_queue("赋值构造函数",qu);

            qu.push(2);
            qu.push(3);
            qu.push(4);
            qu.push(5);
            Print_queue("after push some elems", qu);

            qu.pop();
            qu.pop();
            Print_queue("after pop two elems", qu);
        }
    }
}
#endif //MYTINYSTL_QUEUE_TEST_H