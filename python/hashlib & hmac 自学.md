#hashlib

```python
>>> from hashlib import *
#新建一个摘要对象，加密方式可选，'md5','sha1','sha224','sha256','sha384','sha512'
>>> d = new('md5')
#使用字节字符串更新散列值，重复调用会使一系列属性发生变化
>>> d.update(b'haha')
#将摘要值作为原始字节字符串返回
>>> d.digest()
	b"\xa9]\x1bf\x14't\xab\xf7\xeens/\xb6\xc05"
#将摘要值编码为十六进制数字序列，返回文本字符串
>>> d.hexdigest()
	'a95d1b66142774abf7ee6e732fb6c035'
#返回摘要副本，保留原摘要内部状态
>>> d.copy()
	<md5 HASH object @ 0x10bc76df0>
#散列的字节大小
>>> d.digest_size
	16
#散列算法内部块字节大小
>>> d.block_size
	64
```

#hmac

主要运用于需要验证消息发件人的应用程序中

```python
import hmac
#双方已经知道的密钥
secret_key = b'tsinghua'
#单方知道，且想传输的数据
data = b'helloworld'

#发送信息
h = hmac.new(secret_key)
h.update(data)
out.send(data)
out.send(h.digest())

#接收信息
h = hmac.new(secret_key)
data = in.receive()
h.update(data)
digest = in.receive()
if digest != h.digest()
	raise AuthenticationError('Message not authenticated')
```
