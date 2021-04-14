#### GDB调试：

​       GDB的主要功能是监控程序的执行流程，也就是说，只有当源程序文件编译为可执行文件的时候，GDB才会排上用场。并且需要添加调试信息。

##### 一，添加调试信息

```
g++ -g test.cpp test
```

##### 二，常用调试信息

- **显示图形化代码 Ctrl+x+a**
- 启动程序 r (run)
- 断点 b (breakpoint)
- 清除/禁用/启用断点 delete/disable/enable
- 单步 s (step 碰到函数会进入)
- 单行 n (next 碰到函数不会进行, 而是整条执行)
- 执行到下一个断点 c (continue)
- 查看变量 p (print)
- 显示变量 display
- 查看当前调用堆栈 bt (backtrace)
- 查看某一层调用代码 f (frame)

##### 三，调试core dump文件

```
gdb core.XXXX
```

