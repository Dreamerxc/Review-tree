//
// Created by 谯保林 on 2021/6/20.
//

#ifndef MYTINYSTL_RB_TREE_TEST_H
#define MYTINYSTL_RB_TREE_TEST_H

#endif //MYTINYSTL_RB_TREE_TEST_H
#include "rb_tree.h"
#include <functional>

void rbtree_print(MyTinySTL::rb_tree<int, std::less<int>> s)
{
   for (auto x = s.begin(); x!= s.end();x++) {
       std::cout << *x << " ";
   }
    std::cout << std::endl;
}

// stack 的遍历输出
#define Print_rbtree(t,s) do {                       \
    std::string s_name = #s;                     \
    std::cout << t << " " << s_name << " :";          \
    rbtree_print(s);                              \
} while(0)
namespace MyTinySTL
{
    namespace test {
        void rb_tree_test() {
            std::cout << "==================================\n";
            std::cout << "========= rb_tree test ============\n";
            std::cout << "==================================\n";

            /*rb_tree<int, std::less<int>> tree1;
            rb_tree<int, std::less<int>> tree2(tree1);
            rb_tree<int, std::less<int>> tree3(MyTinySTL::move(tree1));

            tree2 = tree1;
            tree3 = MyTinySTL::move(tree2);

            tree1.emplace_multi(2);
            tree1.emplace_multi(3);
            tree1.emplace_multi(1);

            tree1.emplace_multi_at_pos(tree1.begin(), 4);
            tree1.insert_multi(6);
            tree1.erase(tree1.begin());
            tree1.erase(tree1.begin());

            auto it = tree1.find(2);
            if (it != tree1.end()) {
                std::cout << "find value: " << *it << std::endl;
            }
            rbtree_print(tree1);*/

            rb_tree<int, std::less<int>> tree2;
            tree2.emplace_unique(2);
            tree2.emplace_unique(3);
            tree2.emplace_unique(1);
            tree2.emplace_unique(1);
            tree2.emplace_unique_at_pos(tree2.begin(), 4);
            rbtree_print(tree2);
        }
    }
}