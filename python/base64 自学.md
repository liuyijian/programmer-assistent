#base64

* 用于二进制数据与文本的编码和解码

* base64将编码的数据分为n个24位组（3字节）
* 每个24位组被分成4个6位组件
* 若输入流中的字节数不是24位的倍数，则填充数据补齐
* 额外补充的数据将在编码的最后部分用‘=’字符表示
* 有效的base64编码后端只能包含0、1、2个填充字符
* 每个6位值的转换如下表

```
值		base64编码
0~25	 A~Z
26~51	 a~z
52~61	 0~9
62		 +
63		 /
填充		=

```
* base32将编码的数据分为n个40位组（5字节）
* 每个40位组被分成8个5位组件
* 若不是40位的倍数，则用=号填充，最多填充6个=号

```
值		base32编码
0~25	 A~Z
26~31	 2～7
```

* base16是标准的十六进制编码
* 表示每个4位组，无填充数字或字符

```
值		base16编码
0~9	     0~9
10~15    A~F
```
base64基本操作

```python
>>> from base64 import *
# 为二进制数据进行b64编码，可选参数altchars为双字符字符串，表示替换 + 和 / 的字符
>>> b64encode(b'lkajsfn','-_')
	 b'bGthanNmbg=='
# 为二进制数据进行b64解码，可选参数altchars为双字符字符串，表示替换 + 和 / 的字符,若出现无关字符，则报错TypeError,若不符合b64规则，则报错binascii.Error
>>> b64decode(b'NjI=')
	 b'62'
#url安全的编码解码，等价于b64encode(s,'-_')
>>> urlsafe_b64encode(b'lkajsfn')
    b'bGthanNmbg=='
>>> urlsafe_b64decode(b'bGthanNmbg==')
	 b'lkajsfn'
```

在线转换器

<http://www1.tc711.com/tool/BASE64.htm>

base64文件编码解码(旧版接口,已禁用)

```python
#input为进行读取而打开的文件名或文件对象，output为进行二进制写入而打开的文件名或文件对象
>>> decode(input,output)
#input为进行二进制读取而打开的文件名或文件对象，output为进行写入而打开的文件名或文件对象
>>> encode(input,output)
#字符串编码解码,返回二进制字符串
>>> decodestring(s)
>>> encodestring(s)
```
