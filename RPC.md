#### RPC:

##### RPC(远程过程调用)：解决远程调用服务的一种技术，使得调用者像调用本地服务一样方便透明



##### 为什么需要RPC协议：

- 相比与HTTP协议，RPC采用二进制字节码传输，更加高效也更加安全。
- RPC可以保证不同服务之间的互相调用，即使跨语言平台也不是问题，让构建分布式系统更加容易。
- RPC框架都有服务降级，流量控制的功能，保证服务的高可用。



