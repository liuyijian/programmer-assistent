###json

```python
>>> import json
'''
json.dump函数拥有常用可选参数如下：
cls:要使用的JSONEncoder的子类，若向dump提供其他关键字参数，则会作为参数传递到此类的构造函数
encoding：默认为‘utf-8’
default：序列化非基本支持类型的函数
'''
'''
json.load函数都拥有所有可选参数如下：
encoding：用于解释任何解码字符串值的编码，默认为‘utf-8’
strict：布尔标志，是否允许JSON字符串中出现未转义换行符，默认为True，表示会对该字符串生成异常
cls：用于解码JSONDecoder的子类
object_hook:解码每个JSON对象的结果而调用的函数
parse_float:解码JSON浮点值时调用的函数，默认为float()
parse_int:解码JSON整数值时调用的函数，默认为int()
parse_constant:解码JSON常数时调用的函数，如NaN，True
'''
# json格式的文件读写
>>> fout = open('test.txt','w')
>>> json.dump('haha',fout)
>>> fout.close()
# json格式的文件读写
>>> fin = open('test.txt','r')
>>> a = json.load(f)
#返回包含结果的字符串
>>> json.dumps('haha')
	'"haha"'
#从字符串反序列化对象
>>> json.loads('"haha"')
```
```python
#定义JSONEncoder的子类
>>> import json
>>> class ComplexEncoder(json.JSONEncoder):
...     def default(self, obj):
...         if isinstance(obj, complex):
...             return [obj.real, obj.imag]
...         # Let the base class default method raise the TypeError
...         return json.JSONEncoder.default(self, obj)
...
>>> json.dumps(2 + 1j, cls=ComplexEncoder)
'[2.0, 1.0]'
>>> ComplexEncoder().encode(2 + 1j)
'[2.0, 1.0]'
>>> list(ComplexEncoder().iterencode(2 + 1j))
['[2.0', ', 1.0', ']']
```