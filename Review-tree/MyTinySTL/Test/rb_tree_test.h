//
// Created by 谯保林 on 2021/6/20.
//

#ifndef MYTINYSTL_RB_TREE_TEST_H
#define MYTINYSTL_RB_TREE_TEST_H

#endif //MYTINYSTL_RB_TREE_TEST_H
#include "rb_tree.h"
#include <functional>

namespace MyTinySTL
{
    namespace test {
        void rb_tree_test() {
            std::cout << "==================================\n";
            std::cout << "========= rb_tree test ============\n";
            std::cout << "==================================\n";
            rb_tree<int, std::less<int>> tree1;
            rb_tree<int, std::less<int>> tree2(tree1);
            rb_tree<int, std::less<int>> tree3(MyTinySTL::move(tree1));

            tree2 = tree1;
            tree3 = MyTinySTL::move(tree2);
        }
    }
}