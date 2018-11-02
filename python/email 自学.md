#email

##解析电子邮件

```python
>>> import email
# 解析从类文件对象f读取的电子邮件信息，f必须以文本模式打开。输入信息应该是一个完整的MIME编码的电子邮件信息，包含报头，文本和附件，返回Message()实例
>>> m = email.message_from_file(f)
#从文本字符串str读取电子邮件信息，返回Message()实例
>>> m = email.message_from_string(str)
#message对象支持以下查询数据信息数据的操作
#返回报头name的值
>>> m[name]
#返回所有消息报头名称组成的列表
>>> m.keys()
#返回所有消息报头值组成的列表
>>> m.values()
#返回所有消息报头名称和值的元组组成的列表
>>> m.items()
#返回名为name的报头值。def指定未找到值时返回的默认值
>>> m.get(name[,def])
#返回消息报头的数量
>>> len(m)
#将消息转换为字符串
>>> str(m)
```

##读邮件——例子
```python
from email.parser import Parser
from email.header import decode_header
from email.utils import parseaddr
import poplib

def print_info(msg, indent=0):
    if indent == 0:
        for header in ['From', 'To', 'Subject']:
            value = msg.get(header, '')
            if value:
                if header=='Subject':
                    value = decode_str(value)
                else:
                    hdr, addr = parseaddr(value)
                    name = decode_str(hdr)
                    value = u'%s <%s>' % (name, addr)
            print('%s%s: %s' % ('  ' * indent, header, value))
    if (msg.is_multipart()):
        parts = msg.get_payload()
        for n, part in enumerate(parts):
            print('%spart %s' % ('  ' * indent, n))
            print('%s--------------------' % ('  ' * indent))
            print_info(part, indent + 1)
    else:
        content_type = msg.get_content_type()
        if content_type=='text/plain' or content_type=='text/html':
            content = msg.get_payload(decode=True)
            charset = guess_charset(msg)
            if charset:
                content = content.decode(charset)
            print('%sText: %s' % ('  ' * indent, content + '...'))
        else:
            print('%sAttachment: %s' % ('  ' * indent, content_type))

def decode_str(s):
    value, charset = decode_header(s)[0]
    if charset:
        value = value.decode(charset)
    return value

def guess_charset(msg):
    charset = msg.get_charset()
    if charset is None:
        content_type = msg.get('Content-Type', '').lower()
        pos = content_type.find('charset=')
        if pos >= 0:
            charset = content_type[pos + 8:].strip()
    return charset

def link(email,password,pop3_server):
    # 连接到POP3服务器:
    server = poplib.POP3(pop3_server)
    #打开或关闭调试信息:
    #server.set_debuglevel(1)
    # 打印POP3服务器的欢迎文字
    print(server.getwelcome().decode('utf-8'))
    # 身份认证
    server.user(email)
    server.pass_(password)
    return server

email = 'liuyijian16@163.com'
password = 'lyj271271'
pop3_server = 'pop.163.com'

#得到可操作对象
server = link(email,password,pop3_server)
# stat()返回邮件数量和占用空间:
print('Messages: %s. Size: %s' % server.stat())
#list()返回所有邮件的编号:
resp, mails, octets = server.list()
# 可以查看mails返回的列表类似[b'1 82923', b'2 2184', ...]

# 获取最新一封邮件, 注意索引号从1开始,越大越新
index = len(mails)
# lines存储了邮件的原始文本的每一行
resp, lines, octets = server.retr(index)
# 获得整个邮件的原始文本:
msg_content = b'\r\n'.join(lines).decode('utf-8')
# 解析邮件
msg = Parser().parsestr(msg_content)
print_info(msg)
# 可以根据邮件索引号直接从服务器删除邮件:
# server.dele(index)
# 关闭连接:
server.quit()
```
##编写电子邮件

* 创建Message对象(在email.message模块定义)

```python
>>> import email
#新建一个Message()对象
>>> m = email.message.Message()
#添加消息报头，name是报头名称，value是报头值，可选参数params是关键字参数集,可添加如spam = 'major'
>>> m.add_header(name,value,**params)
#将整个消息转化为字符串，可选参数uniform是布尔标志，若为True，则第一行出现UNIX风格的‘FROM ……’行，默认为False
>>> m.as_string([uniform])
#向多部分消息添加一个附件
>>> m.attach(payload)
#从报头header中删除参数param，requote默认为True，表示将剩下的值重新写入报头，header默认为‘Content-type’的报头
>>> m.del_param(param[,header[,requote]])
#使用value替代首次出现的报头name的值，未找到报头出现KeyError
>>> m.replace_header(name,value) 
#将消息的边界参数设置为字符串boundary，作为边界参数添加到消息的‘Content-type’报头，若无此报头，则出现HeaderParseError
>>> m.set_boundary(boundary)
# 设置消息使用的默认字符集，将此内容添加到‘Content-type’报头
>>> m.set_charset(charset)
# 将默认消息内容类型设置为ctype，ctype是包含MIME类型的字符串，该类型不会存储在报头上
>>> m.set_default_type(ctype)
#设置报头参数的值,param是参数名，value是参数值，header指定报头的值且默认为‘Content-type’
>>>m.set_param(param,value[,header[,requote[,charset[,language]]]]])
#将整个消息负载设置为payload，payload可以是包含消息正文的字符串，对于多部分消息，则是Message对象组成的列表
>>> m.set_payload(payload[,charset])
```
* 创建MIME消息

```python
# 在email.mime.multipart中定义，新建多部分MIME消息。subtype指定要添加到‘Content-type:multipart/subtype’报头的可选子类型，默认为’mixed‘，boundary指定组成每个消息子部分的边界分隔符，默认为None，自适应。subparts是一系列组成消息内容的Message对象
>>> from email.mime.multipart import *
>>> m = MIMEMultipart([subtype[,boundary[,subparts[,**params]]]])

#在email.mime.application中定义，创建包含应用程序数据的信息，data为字节字符串，subtype指定数据子类型，默认为‘octet-stream’；encoder默认为base64，params表示添加到消息‘Content-type’报头的可选关键字参数和值
>>> from email.mime.application import *
>>> m = MIMEApplication(data,[,subtype[,encoder[,**params]]])

#在email.mime.audio中定义，创建包含音频数据的消息，subtype可为'mpeg','wav'等，若不提供，则使用sndhdr模块推测音频类型
>>> from email.mime.audio import *
>>> m = MIMEAudio(data[,subtype[,encoder[,**params]]])

#在email.mime.image中定义,创建包含图片数据的信息，subtype可为‘jpg’，‘png’等等，若无提供，将使用imghdr模块来猜测
>>> from email.mime.image import *
>>> m = MIMEImage(data[,subtype[,encoder[,**params]]])

#在email.mime.message中定义，创建非多部分MIME消息。msg是包含消息初始负载的消息对象，subtype是消息类型，默认为‘rfc822’
>>> from email.mime.message import *
>>> m = MIMEMessage(msg[,subtype])

# 在email.mime.text中定义，创建包含文本数据的消息。data是包含消息负载的字符串，subtype指定文本类型，如‘plain’‘html’等字符串。charset默认为‘us-ascii’
>>> from email.mime.text import *
>>> m = MIMETEXT(data[,subtype[,charset]])
```

##写邮件——例子

```python
import smtplib
from email.mime.application import MIMEApplication
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.image import MIMEImage
from email.mime.audio import MIMEAudio
from email.header import Header

#发送者
sender = 'liuyijian16@163.com'
#输入授权码，跟密码不是一个东西
pwd = 'lyj271271'
#接收者列表
receiver = ['846171107@qq.com']
#邮件主题
subject = 'love 爱'
#邮件正文
body = 'I will love you forever 爱'

#要发送的一些文件地址名称
pic = '课表.png'
aud = 'haha.m4a'
doc = 'Hi!\nHow are you? 爱'
html = """
<html>  
  <head></head>  
  <body>  
    <p>Hi!<br>  
       How are you?<br>  
       Here is the <a href="http://www.baidu.com">link</a> you wanted.<br> 
    </p> 
  </body>  
</html>  
"""
filesend = '成本收益分析.pages'

#创建MIME对象
m = MIMEMultipart('mixed')
m['to'] = Header(receiver,'utf-8')
m['from'] = Header(sender,'utf-8')
m['subject'] = Header(subject,'utf-8')

#添加正文
m.attach(MIMEText(body))
#添加附件
fileapart = MIMEApplication(open(filesend,'rb').read())
fileapart.add_header('Content-Disposition','attachment',filename = ('gbk','',filesend))
m.attach(fileapart)
#添加文本
docapart= MIMEText(doc,'plain', 'utf-8')    
docapart.add_header('Content-Disposition','attachment',filename=('gbk', '', doc))
m.attach(docapart) 
#添加图片附件
picapart = MIMEImage(open(pic,'rb').read(), 'png')
picapart.add_header('Content-Disposition','attachment',filename = ('gbk', '', pic))
m.attach(picapart)
#添加音频附件
audapart = MIMEAudio(open(aud,'rb').read(),'m4a')
audapart.add_header('Content-Disposition','attachment',filename = ('gbk', '', aud))
m.attach(audapart)
#添加html附件
htmlapart = MIMEText(html,'html','utf-8')
htmlapart.add_header('Content-Disposition','attachment',filename = ('gbk', '', html))
m.attach(htmlapart)
#邮箱登录
s = smtplib.SMTP_SSL('smtp.163.com',465)
s.login(sender,pwd)
#打印与SMTP的交互信息
# s.set_debuglevel(1)
#发送邮件
s.sendmail(sender,receiver,m.as_string())
#断开链接
s.quit()
#销毁对象
s.close()
```