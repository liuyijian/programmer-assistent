#csv
* csv文件由文本行组成，每一行由分隔符分隔的值组成，通常是逗号或制表符
* 处理数据库或电子表格常会用到csv格式

##csv.reader()
```python
'''
返回reader对象是一个迭代器，每次迭代生成一列字符串，生成输入文件csvfile中每一行输入的值
默认参数
dialect：目的是处理不同CSV编码之间的差异，仅支持两个内置语言——‘excel’（默认值），‘excel-tab’，但用户可自己定义其他方言
关键字参数
delimiter：定义用来分隔字段的字符，默认为','
doublequote：布尔标志，确定字段中出现引号如何处理，若为True，使用双引号，若为False，则在引号前添加转义字符，默认值为True
还有escapechar，lineterminator,quotechar,skipinitialspace这些参数
'''
>>> import csv
>>> r = csv.reader(f)
```
##csv.writer()

```python
>>> import csv
'''
除了csv.reader里面的参数外，还有quoting参数，控制输出数据的引号添加行为
'''
>>> w = csv.writer(f)
#将一个数据行写入文件，row必须是字符串序列或数字序列
>>> w.writerow(row)
#写入多行数据,rows是传递给writerow()方法的行序列
>>> w.writerows(rows)
```

##csv.DictReader()
```python
'''
返回一个字典对象，不是字符串列表
必选参数：csvfile
可选参数：
fieldnames：指定在返回的字典中作键的字段名称
restkey：提供用来存储超额数据的字典键名称，行的数据字段比字典名称多时可以指定该参数，默认为None
restval:指定输入中缺少值的字段的默认值，默认为None
dialect：指定方言
以及reader()中的参数
'''
```

##csv.DictWriter()
```python
'''
将字典写入输出行
fieldnames:定义写入文件的顺序和属性名称，若写入的字典缺少fieldnames指定的某个字段名称，则写入restval的值
extrasaction：字符串，指定写入字典中的键未在fieldnames中列出时该如何处理，默认为raise ValueError，可以使用‘ignore’，忽略字典中的其他值
dialect和其他参数与writer()的效果相同
'''
```
##csv.Sniff()
```python
>>> import csv
#创建sniff对象，可以尝试自动检测CSV文件格式
>>> s = csv.Sniff()
#查看sample中的数据，返回表示数据格式的相应Dialect对象,sample是至少包含一行数据的CSV文件的一部分，若提供delimiters，sample应该是包含字段分隔符的字符串
>>> s.sniff(sample,[delimeters])
#查看sample中的数据，若第一行是列标题的第一行，则返回True
>>> s.has_header(sample)
```
##例子
```python
import csv
#读取csv文件
f = open('test.csv','r')
for r in csv.reader(f):
	name,city = r
	print('{0} {1} {2} {3} {4}'.format(*r))
f.close()
#使用DictReader
f = open('test.csv')
r = csv.DictReader(f,['name','city'])
for a in r:
	print('{name} {city}'.format(**a))
f.close()
#写入基本的csv文件
data = [['blues','chicago'],['jack','newyork'],]
f = open('out.csv'.'w')
w = csv.writer(f)
w.writerows(data)
f.close()
```