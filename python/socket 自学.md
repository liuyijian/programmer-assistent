#socket
***
##地址族
|常量|描述|
|------|------|
|AF_INET|IPV4协议（TCP，UDP）|
|AF_INET6|IPV6协议（TCP，UDP）|
|AF_BLUETOOTH|蓝牙协议，通常用于嵌入式系统|
|AF_PACKET|链接级别数据包|
|AF_NETLINK|Netlink进程间通信|
|AF_TIPC|透明进程间通信，用于Linux群集上的高性能IPC|
|AF_UNIX|UNIX域协议|

* Linux只支持最后三种

##套接字类型
|常量|描述|
|------|------|
|SOCK_STREAM|面向连接的可靠字节流（TCP）|
|SOCK_DRGAM|数据报（UDP）|
|SOCK_RDM|可靠数据报，保证交付数据但不保证顺序|
|SOCK_RAW|原始套接字|
|SOCK_SEQPACKET|序列化连接模式记录传输，使用面向数据流的连接发送数据包，保证顺序和数据包边界|

##寻址(简要)
####AF_INET
* 地址的形式为元组（host,port）  
如('www.python.org',80),('66.113.130.182',25)
* 若host为空字符串，含义与INADDR_ANY相同，表示任何地址，服务器通常在创建所有客户端都可以连接的套接字时使用
* 使用域名作为主机名时，python使用DNS将主机名解析为IP地址，由于DNS配置不同，导致每一次的IP地址可能不同

####AF_INET6
* 地址形式为元组（host,port,flowinfo,scopeid），不指定后两个参数，则沿用IPV4的格式
* IPV6主机地址由8个以分号分隔的十六进制数组成的字符串，省略代表0
* flowinfo是一个32位数字，低24位是流标签，中4位是属性优先级，高4位是保留位；通常在发送方需要支持路由器的特殊处理时使用，否则，设为0
* scopeid是一个32位数字，仅在处理本地链接和本地站点地址时使用

####AF_UNIX
* 地址包含路径名称的字符串，如'/tmp/myserver'

##函数

```python
import socket
#建立address的SOCK_STREAM连接并返回已连接的套接字对象
socket.create_connection(address[,timeout])
#给定关于主机的host和port信息，返回由元组组成的列表，port代表服务名称的数字或字符串，如80,‘http’‘ftp’,返回的元组为（family,socktype,proto,canonname,sockaddr）
socket.getaddrinfo(host,port[,family[,socktype[,proto[,flags]]]])
#展示连接
socket.getaddrinfo('www.python.org',80)
>>> [(<AddressFamily.AF_INET6: 30>, <SocketKind.SOCK_DGRAM: 2>, 17, '', ('2a04:4e42:12::223', 80, 0, 0)), (<AddressFamily.AF_INET6: 30>, <SocketKind.SOCK_STREAM: 1>, 6, '', ('2a04:4e42:12::223', 80, 0, 0)), (<AddressFamily.AF_INET: 2>, <SocketKind.SOCK_DGRAM: 2>, 17, '', ('151.101.76.223', 80)), (<AddressFamily.AF_INET: 2>, <SocketKind.SOCK_STREAM: 1>, 6, '', ('151.101.76.223', 80))]
#筛选
socket.getaddrinfo('www.python.org',80,socket.AF_INET,socket.SOCK_STREAM)
>>> [(<AddressFamily.AF_INET: 2>, <SocketKind.SOCK_STREAM: 1>, 6, '', ('151.101.76.223', 80))]
#将IPV4主机名转换为IP地址,以字符串形式返回
socket.gethostbyname(hostname)
#将主机名转换为IPV4地址，返回元组（hostname,aliaslist,ipaddrlist）,其中hostname是主机名，aliaslist是同一个地址的可选主机名列表，ipaddrlist是同一个主机上同一个接口的IPV4地址列表
socket.gethostbyname_ex(hostname)
#返回本地机器的主机名
socket.gethostbyaddr(ip_address)
#返回布尔值
socket.has_ipv6
#新建套接字,参数为地址族，套接字类型，协议编号通常默认为0
socket.socket(family,type[, proto])
#创建一对连接的套接字对象，仅适用family=AF_UNIX，若type是SOCK_STREAM，创建一个名为数据流管道的对象父进程调用该函数，再调用os.fork(),父子进程就可以使用套接字相互通信了
socket.socketpair([family[, type[, proto]]])

'''套接字对象s的方法'''
#接受连接并返回（conn，address），conn是新的套接字对象，用来通过连接发送和接收数据，address是另一个连接端的套接字地址
s.accept()
#将套接字绑定到地址
s.bind(address)
#连接到address处的远程套接字
s.connect(address)
#关闭套接字
s.close()
#返回套接字自己的地址,为元组(ipaddr,port)
s.getsockname()
#返回连接套接字的远程地址，为元组(ipaddr,port)
s.getpeername()
#开始监听传入连接，backlog指定再拒绝连接之前，操作系统应该列队的最大挂起连接数量,至少为1
s.listen(backlog)
#创建与套接字关联但独立关闭的文件对象
s.makefile([mode[,bufsize]])

#只读属性
#套接字地址族
s.family
#套接字协议
s.proto
#套接字类型
s.type

#flags提供有关消息的其他消息，通常默认为0
# MSG_DONTWAIT：非阻塞操作
# MSG_DONTROUTE：绕过路由表查询
# MSG_EOR ： 指示消息是记录中的最后一条，仅在SOCK_SEQPACKET套接字上发送数据时使用
# MSG_PEEK : 查看数据但是不丢弃（仅在接收时使用）
# MSG_OOB : 接收/发送带外数据
# MSG_WAITALL : 在读取请求的字节数之前不要返回(仅在接收时使用)
#接收套接字的数据，以字符串形式返回，bufsize指定要接受的最大数据量

s.recv(bufsize[, flags])
#数据写入支持缓冲区接口的对象buffer，nbytes是要接受的最大字节数，忽略此参数，则大小等于缓冲区大小
s.recv_into(buffer[, nbytes[, flags]])
#返回值为(data,address)对，data包含接收数据的字符串，address是发送数据的套接字地址
s.recvfrom(bufsize[, flags])
#同理
s.recvfrom_into(buffer[, nbytes[, flags]])
#将string中的数据发送到连接的套接字，返回要发送的字节数量，该数量可能小于string中的字节数，有错误会抛出异常
s.send(string[, flags])
#在返回之前会尝试发送所有数据，成功返回None，失败抛出异常
s.sendall(string[, flags])
#将数据发送到套接字，在此之前，套接字不应该被连接。返回发送的字节数，该函数用于UDP协议
s.sendto(string[, flags], address)
#flag = 0,将套接字设置为非阻塞模式，在该模式下，recv()和send()没有发现数据，则引发error
s.setblocking(flag)
#设置套接字操作的超时期，timeout单位是秒，值None表示无超时期
s.settimeout(timeout)
#关闭一个或两个半连接，若how=0，则可以继续接收，若how=1，则不允许后续发送，若how=2，则不允许后续发送和接收
s.shutdown(how)


```

