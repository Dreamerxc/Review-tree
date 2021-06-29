// -*- coding: utf-8-unix; -*-
// Copyright (c) 2021 Tencent, Inc.
//     All rights reserved.
//
// Author: kricsqiao@tencent.com
// Date: 2021/5/15 20:30
// Description:
//

#include "vector_test.h"
#include "list_test.h"
#include "deque_test.h"
#include "rb_tree_test.h"
#include "stack_test.h"
#include "queue_test.h"
#include "map_test.h"
#include "set_test.h"
int main()
{
    using namespace MyTinySTL::test;

       vector_test();
       list_test();
       deque_test();
       rb_tree_test();
       stack_test();
       queue_test();
       map_test();
       set_test();
}