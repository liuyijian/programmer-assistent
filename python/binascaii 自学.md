#binascii

```python
>>> from binascii import *
#base64编码的文本字符串->二进制数据
>>> a2b_base64('haha')
	b'\x85\xa8Z'
#二进制数据->base64编码文本字符串
>>> b2a_base64(b'\x85\xa8Z')
	b'haha\n'
#十六进制数字字符串->二进制数据
>>> a2b_hex('haha')
	b'haha\n'
#二进制数据->十六进制数字字符串
>>> b2a_hex(b'haha\n')
	b'686168610a'
```
