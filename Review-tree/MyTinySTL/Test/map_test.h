//
// Created by Dreamer.c on 2021/6/26.
//

#ifndef MYTINYSTL_MAP_TEST_H
#define MYTINYSTL_MAP_TEST_H
#include "map.h"

namespace MyTinySTL
{
    namespace test
    {
        void map_test()
        {
            std::cout << "==================================\n";
            std::cout << "========= map test ============\n";
            std::cout << "==================================\n";
            map<int, int> mp;

            mp.insert(std::pair<int,int>(1,2));
            mp[3]++;
            mp[4] = 2;
            auto it = mp.find(4);
            if (it != mp.end()) std::cout <<  it->second << std::endl;
        }
    }

}









#endif //MYTINYSTL_MAP_TEST_H
