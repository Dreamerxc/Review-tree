#### CMake:

定义：CMake是一个跨平台的安装（编译）工具，可以用简单的语句来描述所有平台的安装（编译）过程。他能够输出各种各样的makefile或者project文件，能测试编译器所支持的C++特性。（可以编译源代码，制作程序库，产生适配器，还可以用任意的顺序构建执行档）



##### 常用命令：

##### 1，指定cmake的最小版本

```
camke_minimum_required(VERSION 3.2.0)
```

##### 2，设置项目名称

```
project(MyTinySTL)

会自动引入两个变量  PROJECT_BINARY_DIR 和 PROJECT_SOURCE_DIR
```

##### 3，设置编译类型

```
# 生成可执行文件
add_executable(MyTinySTL MyTinySTL.cpp)
# 生成静态库
add_library(common STATIC util.cpp)
# 生成动态库或共享库
add_library(comon SHARED util.cpp)
```

##### 在linux下：以上命令生成：

demo

libcommon.a

libcommon.so

##### 在windows：以上命令生成：

demo.exe

common.lib

common.all

##### 4，指定编译包含的源文件

4.1 明确指定包含哪些源文件

```
add_library(demo demo.cpp test.cpp util.cpp)
```

4.2 搜索所有的cpp文件

```
# 把当前目录下所有cpp文件存储在一个变量中（SRC_LIST)
aux_source_directory(. SRC_LIST)
add_library(demo ${SRC_LIST})
```

4.3 自定义搜索规则

```
file(GLOB SRC_LIST "*.cpp" "protocol/*.cpp")
add_library(demo ${SRC_LIST})
# 或者
file(GLOB SRC_LIST "*.cpp")
file(GLOB SRC_PROTOCOL_LIST "protocol/*.cpp")
add_library(demo ${SRC_LIST} ${SRC_PROTOCOL_LIST})
# 或者
aux_source_directory(. SRC_LIST)
aux_source_directory(protocol SRC_PROTOCOL_LIST)
add_library(demo ${SRC_LIST} ${SRC_PROTOCOL_LIST})
```

##### 5，查找指定的库文件

```
# 查找指定的预编译库
find_library(name path)
```

##### 6，设置包含的目录

```
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}  # 当前处理的CMakeLists.txt所在的目录 
    ${CMAKE_CURRENT_BINARY_DIR}  # 当前二进制目录
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
```

Linux还可以使用以下方法：

```
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${CMAKE_CURRENT_SOURCE_DIR}")
```

##### 7，设置链接库的搜索目录

```
link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/libs
)
```

Linux还可以使用以下方法：

```
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_CURRENT_SOURCE_DIR}/libs")
```

##### 8，设置target需要链接的库

```
target_link_libraries(demo ${log-lib})
```

8.1，指定链接动态库或静态库

```
# 链接libface.a
target_link_libraries(demo libface.a)
# 链接libface.so
target_link_libraries(demo libface.so)
```

8.2，指定全路径

```
target_link_libraries(demo ${CMAKE_CURRENT_SOURCE_DIR}/libs/libface.a)
target_link_libraries(demo ${CAMKE_CURRENT_SOURCE_DIR}/libs.libface.so)
```

8.3，指定链接多个库

```
target_link_libraries(demo
				${CMAKE_CURRENT_SOURCE_DIR}/libs/face.so
				pthread)
```

##### 9，设置变量

9.1，set直接设置变量的值

```
set(SRC_LIST main.cpp test.cpp)
# 为工程引入可执行文件
add_executable(demo ${SRC_LIST})  
```

9.2， set追加变量的值

```
set(SRC_LIST main.cpp)
set(SRC_LIST ${SRC_LIST} test.cpp)
add_executable(demo ${SRC_LIST})
```

9.3，lsit追加或者删除变量的值

```
set(SRC_LIST main.cpp)
list(APPEND SRC_LIST test.cpp)
list(REMOVE_ITEM SRC_LIST main.cpp)
add_executable(demo ${SRC_LIST})
```

##### 10，条件控制

10.1 逻辑判断和比较

```
if (expression) :
```

10.2 数据比较

```
if (variable LESS number) :LESS 小于
GREATER : 大于
EQUAL : 等于
```

10.3，while...endwhile

```
while(condition)
	...
endwhile()
```

10.4，foreach...endforeach

```
foreach(loop_var RANGE start stop [step])
	...
endforeach(loop_var)
```

##### 11,打印信息

```
message(${PROJECT_SOURCE_DIR})
message("build with debug mode")
```

##### 12，包含其他cmake文件

```
# 指定包含文件的全路径
include(./common.cmake)  
# 设置include的搜索路径
Set（CMAKE_MOUDULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
```



##### 常用变量

##### 1，预定义变量

PROJECT_SOURCE_DIR：工程的根目录
PROJECT_BINARY_DIR：运行 cmake 命令的目录，通常是 ${PROJECT_SOURCE_DIR}/build
PROJECT_NAME：返回通过 project 命令定义的项目名称
CMAKE_CURRENT_SOURCE_DIR：当前处理的 CMakeLists.txt 所在的路径
CMAKE_CURRENT_BINARY_DIR：target 编译目录
CMAKE_CURRENT_LIST_DIR：CMakeLists.txt 的完整路径
CMAKE_CURRENT_LIST_LINE：当前所在的行
CMAKE_MODULE_PATH：定义自己的 cmake 模块所在的路径，SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)，然后可以用INCLUDE命令来调用自己的模块
EXECUTABLE_OUTPUT_PATH：重新定义目标二进制可执行文件的存放位置
LIBRARY_OUTPUT_PATH：重新定义目标链接库文件的存放位置



##### 2，环境变量

使用环境变量

```
$ENV{Name}
```

写入环境变量

```
set(ENV{Name} value)
```



##### 3，主要开关选项

```
BUILD_SHARED_LIBS：这个开关用来控制默认的库编译方式，如果不进行设置，使用 add_library 又没有指定库类型的情况下，默认编译生成的库都是静态库。如果 set(BUILD_SHARED_LIBS ON) 后，默认生成的为动态库
CMAKE_C_FLAGS：设置 C 编译选项，也可以通过指令 add_definitions() 添加
CMAKE_CXX_FLAGS：设置 C++ 编译选项，也可以通过指令 add_definitions() 添加

# 设置C++编译选项
add_definitions(-DENABLE_DEBUG -DABC)
```













