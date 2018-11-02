#html.parser

```python
from html.parser import HTMLParser
from html.entities import name2codepoint

# 必须自定义继承自HTMLParser的类，并重新定义相应方法来运用数据
class MyHTMLParser(HTMLParser):
    
    '''
    遇到起始标签自动调用，tag为标签名称，如p,script,span等等，
    attrs是包含属性信息的列表，列表项为形如(name,value)的元组，如链接标签中，name = 'href',value = 'www.baidu.com'
    可定义self.flag，检测到特定标签时置为True，在handle_data()函数中先判断self.flag,再做特定处理，完成对特定标签内容物的操作
    因解析html的方法为顺序解析，使用结束后，记得重置self.flag
    '''
    def handle_starttag(self, tag, attrs):
        print("Start tag:", tag)
        for attr in attrs:
            print("     attr:", attr)
	#遇到结束标签自动调用，tag为不含/的标签名字
    def handle_endtag(self, tag):
        print("End tag  :", tag)
	#处理标签之间的数据，data为标签之间的数据
    def handle_data(self, data):
        print("Data     :", data)
	#遇到注释时自动调用，当解析'<!-- a comment -->'时，data为'a-comment'
    def handle_comment(self, data):
        print("Comment  :", data)
	 #遇到实体引用时会自动调用解析，name为包含引用名称的字符串，当解析'&lt;'时，name应设置为'lt'
    def handle_entityref(self, name):
        c = chr(name2codepoint[name])
        print("Named ent:", c)
	#遇到字符引用的时候就会自动调用来解析，name为包含引用名称的字符串，当解析'&#229;'时，name应该设置为'229'
    def handle_charref(self, name):
        if name.startswith('x'):
            c = chr(int(name[1:], 16))
        else:
            c = chr(int(name))
        print("Num ent  :", c)
	#处理<! DOCTYPE HTML ... >之类的声明，decl方法处理后，除去前面的'<! '和 后面的'>'
    def handle_decl(self, data):
        print("Decl     :", data)

parser = MyHTMLParser()
```
```python
#feed()函数：将新数据提供给解析器，立即解析，若数据不完整，将缓存不完整的部分，在下次调用feed()的时候重新解析

>>> parser.feed('<script type="text/javascript">alert("<strong>hello!</strong>");</script>')

Start tag: script
     attr: ('type', 'text/javascript')
     Data: alert("<strong>hello!</strong>");
  End tag: script

>>> parser.feed('<!-- a comment --><!--[if IE 9]>IE-specific content<![endif]-->')
Comment  :  a comment
Comment  : [if IE 9]>IE-specific content<![endif]

>>> for chunk in ['<sp', 'an>buff', 'ered ', 'text</s', 'pan>']:
		parser.feed(chunk)

Start tag: span
Data     : buff
Data     : ered
Data     : text
End tag  : span

#reset()函数，重置解析器，丢弃所有未处理的数据
>>> parser.reset()
#close()函数，关闭解析器并强制处理剩下的未解析数据
>>> parser.close()

```
