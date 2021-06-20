include_directories(../MyTinySTL)
set(SOURCE_LIST test.cpp ../MyTinySTL/list.h list_test.h ../MyTinySTL/deque.h deque_test.h ../MyTinySTL/stack.h ../MyTinySTL/queue.h ../MyTinySTL/rb_tree.h rb_tree_test.h)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(stltest ${SOURCE_LIST})
