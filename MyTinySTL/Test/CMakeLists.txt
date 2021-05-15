include_directories(../MyTinySTL)
set(SOURCE_LIST test.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(stltest ${SOURCE_LIST})
