#re

```python
import re

#根据string的顺序找pattern，成功找到一个匹配pattern的，就是m.group()的值,若没找到pattern，返回的匹配对象m为None，关于m的一切方法都不存在
#当m不是None值时，m.groups()的值是一个列表，有多少个分组括号，列表就对应有多少项，且顺序是基于左括号的
pattern = '32(ab(?P<cd>c(?:d(e))))|f'
string = '23a12abcdeff'

```
###re.compile()函数

```python
#编译一个正则对象，以后用pat直接调用match(),serach(),findall(),finditer()函数，可省略pattern参数,flags参数re.I表示忽略大小写，re.M表示将^和$应用到整个字符串的开始和结尾的每一行，不仅是开头和结尾
pat = re.compile(string,flags = re.I)
```
###re.match()函数

```python
#从字符串一开始匹配，若一开始就不对，则返回None
mm = re.match(pattern,string)
```
###re.search()函数

```python
m = re.search(pattern,string)
```
###re.findall()函数

```python
#从字符串中找到所有匹配pattern的，返回一个列表，列表每一项是一个元组，元组元素相当于每个m.groups()中的元素
lf = re.findall(pattern,string)
print('lf',lf)
```
###re.finditer()函数

```python
#返回一个迭代器，迭代的是匹配对象m
iterator = re.finditer(pattern,string)
for m in iterator:
    pass
```
###match对象的用法

```python
#以下属性，仅当匹配成功，m不为None时才存在，且下列属性都是基于匹配回来的东西去讨论，如此次匹配中的是第一个f，就不包含分组，所以分组为[None,None,None]

#根据string的顺序找pattern，成功找到最先能匹配pattern的，就是m.group()的值
print('m.group()',m.group())
#m.groups()的值是一个列表，有多少个分组括号，列表就对应有多少项，且顺序是基于左括号的，
print('m.groups()',m.groups())
#第2个分组在string中的起始位置，若省略参数，则选用m.group()在string中的起始位置
print('m.start(2)',m.start(2))
#第3个分组在string中的结束位置，若省略参数，则选用m.group()在string中的结束位置
print('m.end(3)',m.end(3))
#第2个分组在string的起末位置的元组，若省略参数，则选用m.group()在string中的起末位置的元组
print('m.span()',m.span())
#传递给search()或match()函数的pos值
print('m.pos', m.pos)
#传递给search()或match()函数的endpos值
print('m.endpos', m.endpos)
#匹配对象所对应的正则对象
print('m.re',m.re)
#匹配对象所对应的输入字符串
print('m.string', m.string)
#返回标注了名称的分组的字典，key为组名，value为分组的字符串
print('m.groupdict()',m.groupdict())
```
###re.split()函数

```python
#根据pattern出现的位置拆分string，返回字符串列表，包括pattern中任何分组匹配的文本
ls = re.split(pattern,string)
#例子
'''
>>> print line
abc aa;bb,cc | dd(xx).xxx 12.12'	xxxx
按空格切
>>> re.split(r' ',line)
['abc', 'aa;bb,cc', '|', 'dd(xx).xxx', "12.12'\txxxx"]
加将空格放可选框内[]内
>>> re.split(r'[ ]',line)
['abc', 'aa;bb,cc', '|', 'dd(xx).xxx', "12.12'\txxxx"]
按所有空白字符来切割：\s（[\t\n\r\f\v]）\S（任意非空白字符[^\t\n\r\f\v]
>>> re.split(r'[\s]',line)
['abc', 'aa;bb,cc', '|', 'dd(xx).xxx', "12.12'", 'xxxx']
多字符匹配
>>> re.split(r'[;,]',line)
['abc aa', 'bb', "cc | dd(xx).xxx 12.12'\txxxx"]
>>> re.split(r'[;,\s]',line)
['abc', 'aa', 'bb', 'cc', '|', 'dd(xx).xxx', "12.12'", 'xxxx']
使用括号捕获分组的适合，默认保留分割符
re.split('([;])',line)
['abc aa', ';', "bb,cc | dd(xx).xxx 12.12'\txxxx"]
去掉分隔符，加?:
>>> re.split(r'(?:;)',line)
['abc aa', "bb,cc | dd(xx).xxx 12.12'\txxxx"]
'''
```
###re.sub()用法

```python
def deal(matched):
    intStr=matched.group("number")
    intValue=int(intStr)
    addValue=intValue+111
    addValueStr=str(addValue)
    return addValueStr

inputStr="hello 123 world 456"
replacedStr=re.sub("hello 123 world 456",deal,inputStr)
print(replacedStr)

```
