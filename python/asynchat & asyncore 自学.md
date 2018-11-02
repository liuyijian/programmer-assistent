#asynchat & asyncore
***
##网络编程基础
* python网络编程主要支持 TCP 和 UDP 协议
* TCP协议：面向连接的可靠协议，建立机器之间的双向通信流
* UDP协议：较低级别，以数据包为基础的协议，无连接传输模式，由机器发送和接收分离的信息包，不可靠
* 套接字：类似于文件的对象，在通信前，双方都必须创建对象实例

```python
'''服务器端程序'''
from socket import *
import time

#创建TCP套接字
s = socket(AF_INET,SOCK_STREAM)
#绑定到端口8888
s.bind(('',8888))
#监听，但只能挂起5个以下的连接
s.listen(5)

while True:
    #连接
    client,addr = s.accept()
    print('Got a connection from %s' % str(addr))
    timestr = time.ctime(time.time()) + '\r\n'
    client.send(timestr.encode('ascii'))
    client.close()
```
```python
'''客户端程序'''
from socket import *
import time

#创建TCP套接字
s = socket(AF_INET,SOCK_STREAM)
#连接到服务器
s.connect(('localhost',8888))
#最多接受1024字节
tm = s.recv(1024)
s.close()
print('The time is %s' % tm.decode('ascii'))
```

##asynchat模块
* asynchat 简化 asyncore 模块实现异步网络应用程序的实现过程
* asynchat模块总是和asyncore模块一起使用，后者设置接受传入连接的高级服务器，前者实现每个连接的应用程序
* 通过定义继承async_chat的类使用模块
* 在类中，必须定义两个方法：
	* collect_incoming_data() : 在网络连接收到数据时调用
	* found_terminator() ： 检测到请求结束时调用

```python
#定义新处理程序的基类，async_chat继承自asyncore.dispatcher,提供的方法相同，sock是套接字对象
a = async_chat_sub([sock])
'''除基类提供的方法外，async_chat的实例a还具有以下方法'''
#将None推入生成函数FIFO队列，表示传出数据流已经到达文件结尾，写入程序收到信号时将关闭通道
a.close_when_done()
#通道收到数据时调用该方法，data是收到的数据，用户必须实现
a.collect_incoming_data()
#丢弃输入/输出缓冲区和生成函数FIFO队列中保存的所有数据
a.discard_buffers()
#set_terminator()设置终止状态时调用该方法，用户必须实现，通常，在collect_incoming_data()方法进行收集操作前处理数据
a.found_terminator()
#返回通道的终止符
a.get_terminator()
#将数据加入到通道的传出生成函数FIFO队列，data是包含要发送数据的字符串
a.push(data)
#将生成函数对象producer加入到生成函数FIFO队列，producer是任何具有简单方法more()的对象，每次调用more()方法生成一个字符串，返回空字符串表示到达数据末尾，重复调用push_with_producer()可以将多个生成函数对象推入FIFO队列
a.push_with_producer(producer)
#在通道上设置终止状态，term可以是字符串，整数 或None。若term是字符串，则在输入流出现该字符串时调用found_terminator()方法，若term是整数，则按字节计数，读取若干字节后，调用found_terminator()方法，若为None，则持续接受数据
a.set_terminator(term)
```
* 实现处理GET请求的微型web服务器

```python
import asynchat, asyncore, socket
import os
import mimetypes

try:
    from http.client import responses
except:
    from httplib import responses

#处理接受的事件的类
class async_http(asyncore.dispatcher):
    
    def __init__(self,port):
        asyncore.dispatcher.__init__(self)
        self.create_socket(socket.AF_INET,socket.SOCK_STREAM)
        self.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
        self.bind(('',port))
        self.listen(5)
    
    def handle_accept(self):
        client,addr = self.accept()
        return async_http_handler(client)


#处理异步http请求的类
class async_http_handler(asynchat.async_chat):
    
    def __init__(self,conn = None):
        asynchat.async_chat.__init__(self,conn)
        self.data = []
        self.got_header = False
        self.set_terminator(b'\r\n\r\n')

    def collect_incoming_data(self,data):
        if not self.got_header:
            self.data.append(data)
    
    def found_terminator(self):
        self.got_header = True
        header_data = b''.join(self.data)
        header_text = header_data.decode('latin-1')
        header_lines = header_text.splitlines()
        request = header_lines[0].split()
        op = request[0]
        url = request[1][1:]
        self.process_request(op,url)
    
    def push_text(self,text):
        self.push(text.encode('latin-1'))
    
    def process_request(self,op,url):
        if op == "GET":
            if not os.path.exists(url):
                self.send_error(404,'File %s not found\r\n')
            else:
                filetype, encoding = mimetypes.guess_type(url)
                size = os.path.getsize(url)
                self.push_text("HTTP/1.0 200 OK\r\n")
                self.push_text("Content-length: %s\r\n" % size)
                self.push_text("Content-type: %s\r\n" % filetype)
                self.push_text("\r\n")
                self.push_with_producer(file_producer(url))
        else:
            self.send_error(501,"%s method not implemented" % op)
        self.close_when_done()
    
    def send_error(self,code,message):
        self.push_text("HTTP/1.0 %s %s\r\n" % (code, responses[code]))
        self.push_text("Content-type: text/plain\r\n")
        self.push_text("\r\n")
        self.push_text(message)


class file_producer(object):

    def __init__(self,filename,buffer_size = 512):
        self.f = open(filename,'rb')
        self.buffer_size = buffer_size
    
    def more(self):
        data = self.f.read(self.buffer_size)
        if not data:
            self.f.close()
        return data

a = async_http(8080)
asyncore.loop()
```

##asyncore
* asyncore模块来构建网络应用程序，网络活动将作为一系列由事件循环分派的事件进行异步处理

```python
#自定义dispatcher类，继承自asyncore.dispatcher
d = dispatcher([sock])
#收到新连接时对监听的套接字调用该方法
d.handle_accept()
#关闭套接字时调用此方法
d.handle_close()
#进行连接时调用该方法
d.handle_connect()
#发生未捕获的python异常时调用该方法
d.handle_error()
#收到套接字带外数据时调用该方法
d.handle_expt()
#可以从套接字读取新数据时调用此方法
d.handle_read()
#尝试写入数据时调用此方法
d.handle_write()
#select()循环使用该函数查看对象是否准备读取数据，若是，返回True
d.readable()
#select()循环使用该函数查看对象是否想写入数据，若是，返回True
d.writable()

#低级别套接字操作
d.accept()
d.bind(address)
d.close()
d.connect(address)
d.create_socket(family,type)
d.listen([backlog])
d.recv(size)
d.send(data)

#无限轮询事件，使用select()函数轮询
#若use_poll参数为True，则使用poll()进行轮询，
#timeout表示超时期，默认为30秒
#map是一个字典，包含所有要监视的通道
# count指定返回之前要执行的轮询操作次数。若count为默认值None，则loop一直轮询，直到所有通道关闭，若count=1，则函数只执行一次事件轮询即返回
loop([timeout[,use_poll[,map[, count]]]])


```