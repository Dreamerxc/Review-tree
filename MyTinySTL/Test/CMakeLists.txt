include_directories(../MyTinySTL)
set(SOURCE_LIST test.cpp ../MyTinySTL/list.h list_test.h ../MyTinySTL/deque.h deque_test.h)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(stltest ${SOURCE_LIST})
