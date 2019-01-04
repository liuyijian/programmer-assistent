# django-twilio

### 场景
* 在线电话会议
* 接收用户的短信，并用程序自动回复
* 对重要电话录音并保存，用于分析
* 交互式语音系统，像10086那种
* 等等

### 安装
```python
'简易安装'
>>> pip3 install django-twilio
'使用django1.7以下版本的，或用python3的，还要装'
>>> pip3 install --upgrade South
```

### django集成

* django1.7版本以下的：
	* 在项目的settings.py文件的INSTALLED\_APPS中，加上 'django_twilio' 和 'South' 两项
	* 运行 python3 manage.py syncdb
	* 运行 python3 manage.py migrate django_twilio

* django1.7版本及以上的：
	* python3 manage.py migrate

### 权限令牌管理

* 在twilio.com的account dashboard上找到自己的TWILIO\_ACCOUNT\_SID和TWILIO\_AUTH\_TOKEN  

* 必需属性加入的两个方法（第一种保密性较好）
	* 1、使用virtualenv虚拟环境，打开文件/bin/activate.sh，加下面两句话,然后将虚拟环境deactivate再activate，它才能生效
		* export TWILIO\_ACCOUNT\_SID = '自己的SID'
		* export TWILIO\_AUTH\_TOKEN = '自己的TOKEN'
	* 2、加入到项目的settings.py文件中
		* TWILIO\_ACCOUNT\_SID = '自己的SID' 
		* TWILIO\_AUTH\_TOKEN = '自己的TOKEN'

* 可选属性（字符串）加入 
	* TWILIO\_DEFAULT\_CALLERID = 'NNNNNNNNNN'
	* 则默认所有的电话短信，都由它发出
* 可选属性（bool）的加入 
	* DJANGO\_TWILIO\_FORGERY\_PROTECTION = False
	* 伪造保护状态，默认值跟settings.DEBUG相反
* 可选属性（bool）的加入 
	* DJANGO\_TWILIO\_BLACKLIST_CHECK = True
	* 黑名单检查，不允许黑名单的电话接入

### 装饰器
* 使页面返回twiML指令给twilio，不用build一个新的HTTPResponse，节约很多编码时间
* 防止伪造攻击
* 使黑名单机制生效，拒绝接入

```python
from twilio.twiml.messaging_response import MessagingResponse
from django_twilio.decorators import twilio_view


@twilio_view
def reply_to_sms_messages(request):
	'twilio会给发消息过来的人回复一个消息'
	r = MessagingResponse()
	r.message('Thanks for the SMS message!')
	return r
```

```python
from twilio.twiml.messaging_response import MessagingResponse

from django.views.generic import View
from django.utils.decorators import method_decorator

from django_twilio.decorators import twilio_view

class ThanksView(View):
	'与上一个例子的功能一样，实现方式不一样而已'
    @method_decorator(twilio_view)
    def dispatch(self, request, *args, **kwargs):
        return super(ResponseView, self).dispatch(request, *args, **kwargs)

    def post(self, request):
        r = MessagingResponse()
        r.message('Thanks for the SMS message!')
        return r
```

### 请求

#### decompose()
* 从django的HTTPRequest中提取出特定的twilio的POST参数，并作为TwilioRequest对象返回他们，可通过属性访问这些参数

```python
from twilio.twiml.messaging_response import MessagingResponse
from django_twilio.decorators import twilio_view
# include decompose in your views.py
from django_twilio.request import decompose

@twilio_view
def inbound_view(request):

    response = MessagingResponse()

    # Create a new TwilioRequest object
    twilio_request = decompose(request)

    # See the Twilio attributes on the class
    twilio_request.to
    # >>> '+44123456789'

    # Discover the type of request
    if twilio_request.type is 'message':
        response.message('Thanks for the message!')
        return response

    # Handle different types of requests in a single view
    if twilio_request.type is 'voice':
        return voice_view(request)

    return response
```

### 视图

* 为加快应用开发，django-twilio给出实用的views可以直接插入到项目的URL注册中，即插即用

##### “说话的职员”

* django_twilio.views.say提供你一个“说话的职员”
	* 可指定语言
	* 可指定性别，
	* 可指定语音内容
	* 可指定重复次数

```python
# urls.py
urlpatterns = patterns(
    '',
    # ...
    url(r'^goodbye/$', 'django_twilio.views.say', {
        'text': 'Adios!',
        'voice': 'woman',
        'language': 'es',
        'loop': 0, #代表一直重复，直到挂电话
    }),
    # ...
)
```
##### “播放音频文件”

```python
# urls.py
'假定wav文件已经存在'
urlpatterns = patterns(
    '',
    # ...
    url(r'^play/$', 'django_twilio.views.play', {
        'url': 'http://mysite.com/greeting.wav',
        'loop': 3, # 默认为1
    })
    # ...
)
```
##### “接收来电”

```python
'接受来电输入'
# urls.py
urlpatterns = patterns(
    '',
    # ...
    url(r'^gather/$', 'django_twilio.views.gather'),
    # ...
)
```
```python
'接受来电后重定向'
# urls.py
urlpatterns = patterns(
    '',
    # ...
    url(r'^gather/$', 'django_twilio.views.gather', {
        'action': '/process_input/',
        'method': 'GET', # 可指定为get或post
    }),
    url(r'^process_input/$', 'mysite.myapp.views.process'),
    # ...
)

# mysite.myapp.views.py
from django.http import HttpResponse

def process(request):
    print(request.GET)  # Output GET data to terminal (for debug).
    return HttpResponse()
```

##### 控制输入模式
* timeout秒后没有新输入，或检测到输入finish_on_key（本例为#），或输入的数字达到num_digits上限，则会自动携带已经输入的数据，转跳到action里指定的那个URL

```python
# urls.py
urlpatterns = patterns(
    '',
    # ...
    url(r'^gather/$', 'django_twilio.views.gather', {
        'action': '/process_input/',
        'method': 'GET',
        'timeout': 5,
        'finish_on_key': '#',
        'num_digits': 10,
    }),
    # ...
)
```

##### 电话录音

* play_beep:在播放“逼”的一声后，开始录音
* action：录好后发到指定的url
* timeout：没有检测到声音之后的timeout秒结束录音
* transcribe: 是否将电话录音转为文本
* transcribe_callback : 将转好的文本发到指定的url

```python
# urls.py
urlpatterns = patterns(
    '',
    # ...
    url(r'^record/$', 'django_twilio.views.record', {
        'action': '/call_john/',
        'play_beep': True,
        'timeout': 5,
        'transcribe': True,
        'transcribe_callback':'/email_call_transcription',
    })
    # ...
)
```

##### 发送短信/多媒体信息
```python
'回复短信'
urlpatterns = patterns(
    '',
    # ...
    url(r'^message/$', 'django_twilio.views.message', {
        'message': 'Thanks for the SMS. Talk to you soon!',
    }),
    # ...
)
```
```python
'发送短信'
urlpatterns = patterns('',
    # ...
    url(r'^message/$', 'django_twilio.views.message', {
        'message': 'Yo!',
        'to': '+12223334444',
        'sender': '+18882223333',
        'status_callback': '/message/completed/', # 回调API
    }),
    # ...
)
```
```python
'发送多媒体信息'
urlpatterns = patterns(
    '',
    # ...
    url(r'^message/$', 'django_twilio.views.message', {
        'message': 'Oh my glob, amazing!',
        'media': 'http://i.imgur.com/UMlp0iK.jpg',
    }),
    # ...
)
```
##### 电话会议

* 简单的电话会议室

step1
	
```python
urlpatterns = patterns(
    '',
    # ...
    url(r'^conference/(?P<name>\w+)/$', 'django_twilio.views.conference'),
    # ...
)
```
step2

登录twilio dashboard 创造一个新的app，将自己app的voice url指向 http://yourserver.com/conference/business

step3

打你自己的twilio电话，twilio会发送HTTP POST请求到你的服务器的/conference/business/，然后，你就进入电话会议室了

* 进入会议室有问候

```python
# urls.py
urlpatterns = patterns(
    '',
    # ...
    url(r'^say_hi/$', 'mysite.views.say_hi'),
    url(r'^conference/(?P<name>\w+)/$', 'django_twilio.views.conference', {
        'wait_url': 'http://yoursite.com/say_hi/',
    })
    # ...
)

# views.py
from twilio.twiml.voice_response import VoiceResponse
from django_twilio.decorators import twilio_view

@twilio_view
def say_hi(request):
    r = VoiceResponse()
    r.say('Thanks for joining the conference! Django and Twilio rock!')
    return r
```






