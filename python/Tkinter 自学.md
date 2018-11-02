# tkinter
***

## label

#### label:text,fg,bg,width,height
```python
from tkinter import *
#初始化Tk
root = Tk()
root.title('this is a title')
#创建一个label,指定它的master
l = Label(master=root, fg='red', bg='#FFC0FF', text='hello', width='50', height='30')
#显示label，必须含有此语句,root不需要pack()
l.pack()
#进入消息循环
root.mainloop()
```
#### label:bitmap,compound

```python
from tkinter import *

root = Tk()
Label(master=root, bitmap='error',text='hello world',compound='left').pack()
Label(master=root, bitmap='error',text='hello world',compound='right').pack()
Label(master=root, bitmap='error',text='hello world',compound='top').pack()
Label(master=root, bitmap='error',text='hello world',compound='bottom').pack()
Label(master=root, bitmap='error',text='hello world',compound='center').pack()
root.mainloop()

# 其他可用的位图：
    * error
    * hourglass
    * info
    * questhead
    * question
    * warning
    * gray12 
    * gray25 
    * gray50
    * gray75
    
# compound属性:    
	* 指定文本(text)与图像(bitmap/image)是如何在Label上显示
	* 缺省为None，当指定image/bitmap时，文本(text)将被覆盖，只显示图像了。可以使用的值：
    	left：     图像居左
    	right:     图像居右
    	top：      图像居上
    	bottom：   图像居下
    	center：   文字覆盖在图像上
```
####label:文本多行显示及对齐

```python
'''
使用width和heigth指定控件大小，如大小无法满足文本的要求，超出Label的那部分文本被截断了
    Label(root,bg = 'welcome to jcodeer.cublog.cn',width = 10,height = 3).pack()

常用的方法是：使用自动换行功能，当文本长度大于
控件的宽度时，文本应该换到下一行显示
Tk不会自动处理，但提供了属性

wraplength：    指定多少单位后开始换行
justify:        指定多行的对齐方式
anchor：        指定文本(text)或图像(bitmap/image)在Label中的显示位置
可用的值：		e,w,n,s,ne,se,sw,sn,center

布局如下图：
                nw        n        ne
                w      center    e
                sw        s        se
'''
```
```python
from tkinter import *
root = Tk()
#左对齐，文本居中
Label(root,text = 'welcome to jcodeer.cublog.cn',bg = 'yellow',width = 40,height = 3,wraplength = 80,justify = 'left').pack()
#居中对齐，文本居左
Label(root,text = 'welcome to jcodeer.cublog.cn',bg = 'red',width = 40,height = 3,wraplength = 80,anchor = 'w').pack()
#居中对齐，文本居右
Label(root,text = 'welcome to jcodeer.cublog.cn',bg = 'blue',width = 40,height = 3,wraplength = 80,anchor = 'e').pack()
root.mainloop()
```
```python
from tkinter import *

root = Tk()

for a in ['n','s','e','w','ne','nw','se','sw']:
    Button(root,text = 'anchor',anchor = a,width = 30,height = 4).pack()

root.mainloop()
```
##button


####button退化为label
```python
from tkinter import *
root = Tk()
#flat, groove, raised, ridge, solid, or sunken
Button(root,text = 'hello button',relief=FLAT).pack()
Button(root,text = 'hello button',relief=GROOVE).pack()
Button(root,text = 'hello button',relief=RAISED).pack()
Button(root,text = 'hello button',relief=RIDGE).pack()
Button(root,text = 'hello button',relief=SOLID).pack()
Button(root,text = 'hello button',relief=SUNKEN).pack()
root.mainloop()
```
####button回调函数

```python
from tkinter import *

#定义Button的回调函数
def helloButton():
    print('hello button')

root = Tk()

#通过command属性来指定Button的回调函数
Button(root,text = 'Hello Button',command = helloButton).pack()

root.mainloop()
```

####button绑定事件

```python
from tkinter import *
def printEventInfo(event):
    print('event.time = ' , event.time)
    print('event.type = ' , event.type)
    print('event.WidgetId = ', event.widget)
    print('event.KeySymbol = ',event.keysym)

root = Tk()

b = Button(root,text = 'Infomation')
b.bind("<Return>",printEventInfo)
b.pack()
b.focus_set()
root.mainloop() 
```
####button启用和禁用

```python
from tkinter import *

def statePrint():
    print ('state')

root = Tk()

for r in ['normal','active','disabled']:
    Button(root,text = r,state = r,width = 30,command = statePrint).pack()

root.mainloop()
```
####button绑定变量

```python
from tkinter import *
root = Tk()
def changeText():
    if b['text'] == 'text':
        v.set('change')
        print('change')
    else:
        v.set('text')
        print('text')

v = StringVar()
v.set('text')
b = Button(root,textvariable = v,command = changeText)
b.pack()
root.mainloop()

```

##Entry

####Entry输入单行文本
```python
from tkinter import *
root = Tk()
Entry(root).pack()
root.mainloop()
```

####Entry文本绑定(不能直接用text属性)
```python
from tkinter import *
root = Tk()
e = StringVar(root,'input here')
Entry(root,textvariable=e).pack()
root.mainloop()
```
####Entry输入状态及密码显示
```python
from tkinter import *
root = Tk()
e = StringVar(root,'input here')
Entry(root,textvariable=e, state='normal').pack()
Entry(root,textvariable=e, state='disabled').pack()
Entry(root,textvariable=e, state='readonly').pack()
# 密码框
Entry(root,textvariable=e, state='normal', show='*').pack()
root.mainloop()
```

####Entry输入验证
```python
from tkinter import *
'''
开启Entry对输入文本验证功能。
1、实现该功能，需要通过设置validate、validatecommand和invalidcommand三个选项。 
2、启用验证的开关是validate选项，该选项可以设置以下的值：
    focus：当entry组件获得或者失去焦点的时候验证 
    focusin：当entry组件获得焦点的时候验证 
    focusout:当entry组件失去焦点的时候验证 
    key:当输入框被编辑的时候验证 
    all:当出现上面任何一种情况时候验证 
    none:关闭验证功能。默认设置为该选项
3、validatecommand选项指定一个验证函数，该函数只能返回True或者False表示验证结果，一般情况下验证函数只需要知道输入框中的内容即可，
可以通过Entry组件的get()方法来获得该字符串。
4、invalidcommand选项指定的函数只有在validatecommand的返回值为False的时候才被调用。
'''
'''
validatecommand选项指定一个验证函数，该函数只能返回True或者False表示验证结果
invalidcommand选项指定的函数只有在validatecommand的返回值为False的时候才被调用。
'''
root = Tk()
def text():
    if e1.get() == '芝麻开门':
        print('正确')
        return True
    else:
        print('错误')
        return False
def text2():
    print('validatecommand的返回值为False的时候调用了我')
    return False
 
v = StringVar()
e1 = Entry(root,textvariable=v,validate='focusout',validatecommand=text,\
           invalidcommand=text2)
e2 = Entry(root)
e1.pack(padx=10,pady=10)
e2.pack(padx=10,pady=10)
mainloop()
```

#### Entry信息提取
```python
from tkinter import *
 
master = Tk()
 
frame = Frame(master)
frame.pack(padx=10,pady=10)
 
v1 = StringVar()
v2 = StringVar()
v3 = StringVar()
 
'''
注意在这里我们不能使用entry控件的get()方法来获取输入的内容
因为当validate选项指定为key的时候，有任何的输入操作都会被拦截
到这个函数当中，也就是说先拦截，只有这个函数返回True，那么输入的内容
才会到变量里面去，也就是说我们使用get函数并无法get到数据，get函数在这个
函数之后才会有效，get函数得到的是变量的值。
所以只有使用%P来获得最新的输入框的内容
'''
def test(content):
     if content.isdigit():
          return True
     else:
          return False
#使用了特殊技能的函数需要使用register将其封装起来才可以
testCMD = master.register(test)
e1 = Entry(frame,width=10,textvariable=v1,validate='key',\
           validatecommand=(testCMD,'%P')).grid(row=0,column=0)
Label(frame,text='+').grid(row=0,column=1)
 
e2 = Entry(frame,width=10,textvariable=v2,validate='key',\
           validatecommand=(testCMD,'%P')).grid(row=0,column=2)
Label(frame,text='=').grid(row=0,column=3)
#e3输入框是显示结果文本框，所以不允许修改里面的值。将state属性设置为state='readonly'只读
e3 = Entry(frame,width=10,textvariable=v3,state='readonly').grid(row=0,column=4)
 
def calc():
     result=int(v1.get())+int(v2.get())
     v3.set(str(result))

Button(frame,text='计算结果',command=calc).grid(row=1,column=2,padx=5)
 
mainloop()
```

##checkbutton

#### 简单例子

```python
from tkinter import *
root = Tk()
Checkbutton(root,text = 'python').pack()
root.mainloop()
```

#### 设置回调函数

```python
from tkinter import *
def callCheckbutton():
    print('you check this button')
    
root = Tk()
Checkbutton(root,text = 'check python',command = callCheckbutton).pack()
root.mainloop()
```

####原生variable属性（0和1）（与textvariable不同）

```python
from tkinter import *

def callCheckbutton():
    print(v.get())

root = Tk()
v=IntVar()
Checkbutton(root,text = 'check button',variable = v,command = callCheckbutton).pack()
root.mainloop()
```

####自定义variable属性

```python
from tkinter import *

def callCheckbutton():
    print(v.get())

root = Tk()
v=StringVar()
Checkbutton(root,
            text = 'check button',
            variable = v,
            command = callCheckbutton,
            onvalue='checked',
            offvalue='to check').pack()
root.mainloop()
```
##radiobutton

* Radiobutton为单选按钮，即在同一组内只能有一个按钮被选中，每当选中组内的一个按钮时，其它的按钮自动改为非选中态
* 如果同一个组中的按钮使用相同的value，则这两个按钮的工作方式完全相同，不同组的按钮互不影响

####radiobutton组绑定到同一个变量

```python
from tkinter import *
root = Tk()
#创建一个Radiobutton组，创建三个Radiobutton，并绑定到整型变量v
v = IntVar()
#选中value=1的按钮
v.set(1)

for i in range(3):
    Radiobutton(root,variable = v,text = 'python',value = i).pack()

root.mainloop()
```
####radiobutton组内行为交互实现

```python
from tkinter import *
root = Tk()
v = IntVar()
v.set(1)
for i in range(3):
    Radiobutton(root,
                variable = v,
                value = 1,
                text = 'python' + str(i)).pack()
for i in range(3):
    Radiobutton(root,
                variable = v,
                value = i,
                text = 'python' + str(2 + i)).pack()
root.mainloop()
```

####radiobutton的回调函数

```python
from tkinter import *

root = Tk()

v = IntVar()
v.set(0)
def r1():
    print('call r1')
def r2():
    print('call r2')
def r3():
    print('call r3')
def r4():
    print('call r4')

i = 0
#创建8个按钮，其中两个两个的value值相同
for r in [r1,r2,r3,r4]:
    Radiobutton(root,
                variable = v,
                text = 'radio button',
                value = i,
                command = r).pack()
    Radiobutton(root,
                variable = v,
                text = 'radio button',
                value = i,
                command = r).pack()
    i += 1
    
# 注意虽然同时可以选中两个按钮，但每次点击按钮，执行的代码只有一次
root.mainloop()
```

####radiobutton的外观修饰

```python
from tkinter import *

root = Tk()

v = IntVar()
v.set(0)

# indicatoron属性为0对应sunken外观，缺省为1
for i in range(3):
    Radiobutton(root,
                variable = v,
                text = 'radio button',
                value = i,
                indicatoron=0).pack()

root.mainloop()
```

##listbox

####listbox的selectmode
```python
# Listbox为列表框控件
# 它可以包含一个或多个文本项(text item)
# 可以设置为单选或多选
 
'''1.创建一个Listbox，向其中添加三个item'''
from tkinter import *
 
root = Tk()
lb = Listbox(root)
for item in ['python', 'tkinter', 'widget']:
    lb.insert(END, item)
lb.pack()
 
'''2.创建一个可以多选的Listbox,使用属性selectmode'''
lb = Listbox(root,selectmode = MULTIPLE)
for item in ['python2','tkinter2','widget2']:
    lb.insert(END,item)
lb.pack()
 
'''3这个属性selectmode还可以设置为BROWSE,可以通过鼠标来移动Listbox中的选中位置（不是移动item），
这个属性也是Listbox在默认设置的值，这个程序与1.程序运行的结果的一样的。'''
lb = Listbox(root,selectmode = BROWSE)
for item in ['python','tkinter','widget']:
    lb.insert(END,item)
lb.pack()
# 与BROWSE相似 的为SINGLE，但不支持鼠标移动选中位置。
lb = Listbox(root,selectmode = SINGLE)
for item in ['python','tkinter','widget']:
    lb.insert(END,item)
lb.pack()
 
'''4.使用selectmode  = EXPANDED使用Listbox来支持Shift和Control。'''
lb = Listbox(root,selectmode = EXTENDED)
for item in ['python','tkinter','widget']:
    lb.insert(END,item)
lb.pack()
#运行程序，点中“python"，shift + 点击"widget"，会选中所有的item
#运行程序，点中"python"，control + 点击"widget"，会选中python和widget，第二项tkinter处于非选中状态
root.mainloop()
```

#### listbox添加item

```python
'''5.向Listbox中添加一个item'''
# insert函数有两个属性一个为添加的索引值，另一个为添加的项(item)
#  有两个特殊的值ACTIVE和END
# ACTIVE是向当前选中的item前插入一个（即使用当前选中的索引作为插入位置)
# END是向Listbox的最后一项添加插入一项

from tkinter import *
root = Tk()
lb = Listbox(root)
for item in ['python','tkinter','widget']:
    lb.insert(END,item)
#只添加一项将[]作为一个item
lb.insert(0,['linux','windows','unix'])
#添加三项，每个string为一个item
lb.insert(0,'linux','windows','unix')
lb.pack()
root.mainloop()
```

####listbox删除item

```python
'''6、使用delete函数,有两个参数，第一个为开始的索引值；
第二个为结束的索引值，如果不指定则只删除第一个索引项。'''
from tkinter import *
root = Tk()
lb = Listbox(root)
for i in range(10):
    lb.insert(END,str(i))
lb.delete(1,3)
lb.pack()
root.mainloop()
#运行程序，只有值0456789,1-3被删除
#删除全部内容,使用delete指定第一个索引值0和最后一个参数END，即可
#lb.delete(0,END)
```

####listbox选中item
```python
'''7.选中操作函数，使用函数实现。selection_set函数有两个参数第一个为开始的索引；
第二个为结束的索引，如果不指定则只选中第一个参数指定的索引项'''
from tkinter import *
root = Tk()
lb = Listbox(root)
for i in range(10):
    lb.insert(END,str(i))
lb.selection_set(0,10)
#  程序运行结果，选中了所有的项。 此代码并未指定Listbox为MULTIPLE或EXTENDED，查通过selection_set仍旧可以对Listbox进行操作。
#与之相对的便是取消选中的函数了，参数与selection_set在参数相同，如下代码取消索引从0－3在状态
lb.selection_clear(0,3)
 
'''8.得到当前Listbox中的item个数'''
print(lb.size()) #输出10
lb.pack()
'''9.返回指定索引的项'''
print(lb.get(3))  #输出3
#get也为两个参数的函数，可以返回多个项(item)，如下返回索引值3－7的值
print(lb.get(3,7))  #('3', '4', '5', '6', '7')，是一个tuple类型
 
'''10.返回当前返回的项的索引，不是item的值'''
print(lb.curselection()) #(4, 5, 6, 7, 8, 9)
 
'''11.判断 一个项是否被选中，使用索引。'''
print(lb.selection_includes(8))  #True
print(lb.selection_includes(0))  #False
root.mainloop()
```
####listbox与变量绑定

```python
'''12.Listbox与变量绑定'''
# -*- coding: utf-8 -*-
from tkinter import *
root = Tk()
v = StringVar()
lb = Listbox(root,listvariable = v)
for i in range(10):
    lb.insert(END,str(i*100))
#打印当前列表中的项值
print(v.get())
#输出：('0', '100', '200', '300', '400', '500', '600', '700', '800', '900')
#改变v的值,使用tuple可以与item对应
v.set(('1000','200'))
#结果只有两项了1000和200
lb.pack()
root.mainloop()
```

####listbox与事件绑定

```python
'''13.Listbox与事件绑定'''
# 不支持command属性来设置回调函数了
# 使用bind来指定回调函数,打印当前选中的值
# -*- coding: utf-8 -*-
from tkinter import *
root = Tk()
def printList(event):
    print(event)
    print(lb.get(lb.curselection()))
lb = Listbox(root)
#双击事件
lb.bind('<Double-Button-1>',printList)
for i in range(10):
    lb.insert(END,str(i*100))
lb.pack()
root.mainloop()
```

##scale

####scale的基础样式
```python
# Scale为输出限定范围的数字区间
# 可以为之指定最大值，最小值及步距值
'''1.创建一个Scale'''
from tkinter import *
 
root = Tk()
Scale(root).pack()
# 创建一个垂直Scale，最大值为100，最小值为0，步距值为1。这个参数设置也就是Scale的缺省设置了。
 
'''2.改变这三个参数，生成 一个水平Scale，最小值为－400，最大值为500，步距值为5'''
Scale(root,
      from_=-400,  # 设置最小值
      to=500,  # 设置最大值
      resolution=5,  # 设置步距值
      orient=HORIZONTAL  # 设置水平方向
      ).pack()
 
'''3.Scale绑定变量'''
v = StringVar()
Scale(root,
      from_=0,  # 设置最小值
      to=100.0,  # 设置最大值
      resolution=0.0001,  # 设置步距值
      orient=HORIZONTAL,  # 设置水平方向
      variable=v  # 绑定变量
      ).pack()
print(v.get())
#v的值与Scale的值一致
root.mainloop()
```
#### scale的回调函数

```python
'''4.使用回调函数打印当前的值'''
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
 
 
def printScale(text):
    print('text = ', text)
    print('v = ', v.get())
 
 
v = StringVar()
Scale(root,
      from_=0,  # 设置最小值
      to=100.0,  # 设置最大值
      resolution=1,  # 设置步距值
      orient=HORIZONTAL,  # 设置水平方向
      variable=v,  # 绑定变量
      command=printScale  # 设置回调函数
      ).pack()
print(v.get())
 
# 这个回调函数有一个参数，这个值是当前的Scale的值，每移动一个步距就会调用一次这个函数
# 只保证最后一个肯定会调用，中间的有可能不会调用,通过上例可以看到二者的值是完全一样的。
```

####scale的显示位数控制
```python 
'''5.控制显示位数，可以理解为：Scale的值为一整形，在输出显示时，它将会被转化为一字符串，如1.2转化为1.2或1.2000都是可以的'''

#属性digits是控制显示的数字位数,将上面的例子中的数据以8位形式显示，在最后一位会添加一个0
v = StringVar()
Scale(root,
      from_=0,  # 设置最小值
      to=100.0,  # 设置最大值
      resolution=0.0001,  # 设置步距值
      orient=HORIZONTAL,  # 设置水平方向
      variable=v,  # 绑定变量
      digits=8,  # 设置显示的位数为8
      command=printScale  # 设置回调函数
      ).pack()
print(v.get())
root.mainloop()
```

####scale的label属性
```python
'''6.设置Scale的标签属性label'''
# 由label设置的值会显示在水平Scale的上方，用于提示信息
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
sl=Scale(root,
      from_=0,  # 设置最大值
      to=100.0,  # 设置最小值
      orient=HORIZONTAL,  # 设置水平方向
      label='choice:',  # 设置标签值
      )
'''7.设置/取得Scale的值'''
sl.set(50)      #将Scale的值设置为50
print(sl.get())  #打印当前的Scale的值
sl.pack()
root.mainloop()
```
##spinbox

####spinbox基础样式

```python
# 与Entry类似，但可以指定输入范围值
'''1.创建一个Spinbox'''
from tkinter import *
 
root = Tk()
# 若只是创建一个Spinbox，其它的什么也做不了，与Scale不同，Scale使用缺省值就可以控制值的改变
Spinbox(root).pack()

'''2.设置Spinbox的最大、最小值和步距值'''
Spinbox(root,
        from_=0,  # 设置最小值
        to=100,  # 设置最大值
        increment=5  # 设置增量值为5，这个与Scale的resolution意思相同
        ).pack()
```

####spinbox自定义values属性及绑定变量
```python
'''3.设置Spinbox的值，设置属性values，设置此值后，每次更新值将使用values指定的值，'''
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
sb = Spinbox(root,
        	 values=(0, 2, 20, 40, -1),
             increment=2
             )
sb.pack()
# 打印当前的Spinbox的值，为一tuple
print(sb['values'])
 
# 显示的第一个值为0,up按钮则为2,20,40,-1，不再是增2操作，它会使用tuple的索引递增，至到tuple的最后一个项时，将不再增加；
# down按钮与up按钮恰好相反，它使用tuple的索引递减
 
'''4.Spinbox绑定变量 '''
v = StringVar()
sb = Spinbox(root,
             values = (0,2,20,40,-1),
             increment = 2,
             textvariable = v
             )
v.set(20)
print(v.get())
sb.pack()
#上面的代码将变量v与sb绑定，并将Spinbox的初始值设置为20，运行程序,Spinbox的值显示为20，再点击up按钮，此时值变为40，
#即tuple的下一个值，再看下面的代码，与这个不同的是设置的值不包含在tuple之内
v = StringVar()
sb = Spinbox(root,
             values = (0,2,20,40,-1),
             increment = 2,
             textvariable = v
             )
v.set(200)
print(v.get())
sb.pack()
#运行程序，显示的值为200，再次点击up按钮，显示的值为2，即虽然Spinbox能将值显示出来，但并不会将200添加到变量中，此时的
#索引值依旧为0，因为没有找到200的项。当点击up时，索引值变为1，即显示的值为2。
root.mainloop()
```

####spinbox回调函数

```python
'''5.设置Spinbox的回调函数'''
# 每次点击Spinbox按钮时就会调用回调函数
# 与Scale不同的是：它不需要参数
from tkinter import *
 
root = Tk()
 
 
def printSpin():
    print(sb.get())
    # 使用get()方法来得到当前的显示值
 
sb = Spinbox(root,
             from_=0,  # 最小值
             to=10,  # 最大值
             command=printSpin  # 回调函数
             )
 
sb.pack()
root.mainloop()
```

####spinbox删除

```python
'''7.删除Spinbox指定位置的字符'''
#delete函数
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
 
def printSpin():
    print(sb.get())
 
 
sb = Spinbox(root,
             from_=1234,  # 最小值
             to=9999,  # 最大值
             increment=1,
             command=printSpin  # 回调函数
             )
sb.delete(0)
print(sb.get())
sb.pack()
root.mainloop()
```

####spinbox插入

```python
'''8.在Spinbox指定位置插入文本'''
# 在每项后面添加.00表示精度，同样使用回调函数实现，代码如下：
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
 
 
def printSpin():
    # 使用get()方法来得到当前的显示值
    sb.insert(END, '.00')
    print(sb.get())
 
 
sb = Spinbox(root,
             from_=1234,  # 最小值
             to=9999,  # 最大值
             increment=1,
             command=printSpin  # 回调函数
             )
sb.pack()
root.mainloop()
# 每次点击Spinbox按钮时就会调用printSpin函数，当前的显示值均添加了两个有数字".00"。这个与delete不同，倒是可以正确显示。
```
##scrollbar

####scrollbar基础样式
```python
#Scrollbar（滚动条），可以单独使用
# 但最多的还是与其它控件（Listbox,Text,Canva等)结合使用
'''1创建一个Scrollbar'''
from tkinter import *
root = Tk()
Scrollbar(root).pack()
#显示了一个Scrollbar，但什么也做不了，无法拖动slider。
 
'''2.通过set方法来设置slider的位置'''
#使用水平滚动条，通过set将值设置为(0.5,1),即slider占整个Srollbar的一半
sl = Scrollbar(root,orient = HORIZONTAL)
sl.set(0.5,1)
sl.pack()
 
root.mainloop()
```
####scrollbar回调函数

```python
'''3.使用回调函数（不建议这样使用）'''
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
 
def scrollCall(moveto, pos):
    # 如何得到两个参数：使用如下打印中的信息，可以看到解释器传给scrollCall函数的两个参数，一个为
    # moveto,参考手册可以得知，它是当拖动slider时调用的函数；另一个参数为slider的当前位置，我们
    # 可以通过set函数来设置slider的位置，因此使用这个pos就可以完成控制slider的位置。
    print(moveto,pos)
    sl.set(pos, 0)
    print(sl.get())
 
 
sl = Scrollbar(root, orient=HORIZONTAL, command=scrollCall)
sl.pack()
root.mainloop()
# 这样还有一个严重问题，只能对其进行拖动。对两个按钮及pagedwon/pageup的响应，由于up按钮响应的为三个参数，故会出现异常。这个例子只是用来说明command属性是可用的，如果喜欢自己可以处理所有的消息，将scrollCall是否可以改为变参数函数？
# 对于不同的输入分别进行不同的处理。
```
####scrollbar与listbox绑定

```python
from tkinter import *
 
root = Tk()
lb = Listbox(root)
sl = Scrollbar(root)
sl.pack(side=RIGHT, fill=Y)
# 滑动listbox，在scrollbar中有体现变化
lb['yscrollcommand'] = sl.set
for i in range(100):
    lb.insert(END, str(i * 100))

lb.pack(side=LEFT)
# 滑动Scrollbar，在Listbox中有体现变化
sl['command'] = lb.yview
root.mainloop()
```
##menu

####添加下拉菜单

```python
from tkinter import *

def hello():
    print('hello menu')

root = Tk()
 
menubar = Menu(root)
 
filemenu = Menu(menubar, tearoff=0)

for item in ['Python', 'PHP', 'CPP', 'C', 'Java', 'JavaScript', 'VBScript']:
    filemenu.add_command(label=item, command=hello)

# 将menubar的menu属性指定为filemenu，即filemenu为menubar的下拉菜单
menubar.add_cascade(label='Language', menu=filemenu)
root['menu'] = menubar

root.mainloop()
```

####向菜单添加checkbutton项

```python
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
 
# 每次打印出各个变量的当前值
def printItem():
    print('Python = ', vPython.get())
    print('PHP = ', vPHP.get())
    print('CPP = ', vCPP.get())
    print('C = ', vC.get())
    print('Java = ', vJava.get())
    print('JavaScript = ', vJavaScript.get())
    print('VBScript = ', vVBScript.get())
 
menubar = Menu(root)
 
vPython = StringVar()
vPHP = StringVar()
vCPP = StringVar()
vC = StringVar()
vJava = StringVar()
vJavaScript = StringVar()
vVBScript = StringVar()
 
filemenu = Menu(menubar, tearoff=0)
for k, v in {'Python': vPython,
             'PHP': vPHP,
             'CPP': vCPP,
             'C': vC,
             'Java': vJava,
             'JavaScript': vJavaScript,
             'VBScript': vVBScript}.items():
    # 绑定变量与回调函数
    filemenu.add_checkbutton(label=k, command=printItem, variable=v)
# 将menubar的menu属性指定为filemenu，即filemenu为menubar的下拉菜单
menubar.add_cascade(label='Language', menu=filemenu)
root['menu'] = menubar
root.mainloop()
# 程序运行，使用了Checkbutton，并通过printItem将每个Checkbutton在当前值打印出来。
```
####向菜单添加radiobutton项

```python
# -*- coding: utf8 -*-
from tkinter import *
 
root = Tk()
 
menubar = Menu(root)
vLang = StringVar()
 
 
# 每次打印出当前选中的语言
def printItem():
    print('vLang = ', vLang.get())
 
filemenu = Menu(menubar, tearoff=0)

for k in ['Python', 'PHP', 'CPP', 'C', 'Java', 'JavaScript', 'VBScript']:
    # 绑定变量与回调函数，指定的变量vLang将这几项划为一组
    filemenu.add_radiobutton(label=k, command=printItem, variable=vLang)
# 将menubar的menu属性指定为filemenu，即filemenu为menubar的下拉菜单
menubar.add_cascade(label='Language', menu=filemenu)
root['menu'] = menubar
root.mainloop()
# 程序每次打印出当前选中的语言
# 与Checkbutton不同的是，同一个组内只有一个处于选中状态。
```
####为菜单项添加分隔符
```python
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
menubar = Menu(root)
 
 
# 每次打印出当前选中的语言
def printItem():
    print('add_separator')
 
filemenu = Menu(menubar, tearoff=0)

for k in ['Python', 'PHP', 'CPP', 'C', 'Java', 'JavaScript', 'VBScript']:
    filemenu.add_command(label=k, command=printItem)
    # 将各个菜单项使用分隔符隔开
    filemenu.add_separator()
    
menubar.add_cascade(label='Language', menu=filemenu)
root['menu'] = menubar
root.mainloop()
# 分隔符将相关的菜单项进行分组，只是UI上的实现，程序上没有任何改变，它也不执行任何的命令
```
####右键弹出菜单
```python
# -*- coding: utf-8 -*-
from tkinter import *
 
def printItem():
    print('popup menu')

def popup(event):
    # 显示菜单
    menubar.post(event.x_root, event.y_root)

root = Tk()

menubar = Menu(root)
filemenu = Menu(menubar, tearoff=0)

for k in ['Python', 'PHP', 'CPP', 'C', 'Java', 'JavaScript', 'VBScript']:
    filemenu.add_command(label=k, command=printItem)
    filemenu.add_separator()

menubar.add_cascade(label='Language', menu=filemenu)
 
# 在这里相应鼠标的右键事件，右击时调用popup,此时与菜单绑定的是root，可以设置为其它的控件，在绑定的控件上右击就可以弹出菜单
root.bind('<Button-2>', popup)

root.mainloop()
# 运行测试一个，可以看到各个菜单 项的功能都是可以使用的，所以弹出菜单与一般的菜单功能是一样的，只是弹出的方式不同而已。
```
####菜单项增删

```python
# -*- coding: utf-8 -*-
from tkinter import *

def printItem():
    print('add_separator')
 
root = Tk()

menubar = Menu(root)
filemenu = Menu(menubar, tearoff=0)

for k in range(5):
    filemenu.add_command(label=str(k), command=printItem)

menubar.add_cascade(label='Language', menu=filemenu)
 
'''以下为向菜单中添加项的操作(覆盖))'''
# 在索引1添加一菜单command项
filemenu.insert_command(1, label='1000', command=printItem)
# 在索引2添加一菜单checkbutton项
filemenu.insert_checkbutton(2, label='2000', command=printItem)
# 在索引3添加一菜单radiobutton项
filemenu.insert_radiobutton(3, label='3000', command=printItem)
# 将新添加的菜单项使用分隔符隔开
filemenu.insert_separator(1)
filemenu.insert_separator(5)
 
'''以下为删除菜单项的操作'''
# 删除索引6-9的菜单项
filemenu.delete(6, 9)
# 删除索引为0的菜单项
filemenu.delete(0)
 
root['menu'] = menubar
root.mainloop()
# 分隔符将相关的菜单项进行分组，只是UI上的实现，程序上没有任何改变，它也不执行任何的命令
```
##message

```python
# Message也是用来显示文本的，用法与Label基本一样
from tkinter import *
 
root = Tk()
# 运行程序，可以看到Hello之后，Message显示在它的下一行。
# 这是Message的一个特性。Label没有。

'''1.简单message'''
Message(root, text='hello Message').pack()
 
'''2.如果不让它换行的话，指定足够大的宽度'''
Message(root, text='hello Message', width=100).pack()
 
'''3.使用aspect属性指定宽高比例'''
for i in range(10):
    Message(root, text='A' * i, aspect=400).pack()

'''4.绑定变量比原设优先级高'''
 
root.mainloop()
```
##optionmenu

#### 创建optionmenu
```python
from tkinter import *
 
root = Tk()
v = StringVar(root)
'''1.创建OptionMenu'''
v.set('Python')
om = OptionMenu(root, v, 'Python', 'PHP', 'CPP')
om.pack()
print(v.get())
root.mainloop()
```
#### 打印optionmenu的值
```python
from tkinter import *
 
root = Tk()
v = StringVar(root)
v.set('Tkinter')
 
def printOption(event):
    print(v.get())
 
# 创建一个OptionMenu控件
om=OptionMenu(root,v,'Python','PHP','CPP')
om.bind('<Button-1>', printOption)
om.pack()
 
root.mainloop()
```
##panewindow

#### 向panewindow中添加pane
```python
from tkinter import *
 
root = Tk()
panes = PanedWindow(orient=VERTICAL)
panes.pack(fill=BOTH, expand=1)
for w in [Label, Button, Checkbutton, Radiobutton]:
	# 使用add方法
    panes.add(w(panes, text='hello'))
root.mainloop()
```
#### 删除panewindow指定的pane
```python
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
ws = []
panes = PanedWindow(orient=VERTICAL)
panes.pack(fill=BOTH, expand=1)
# 创建四个pane
for w in [Label, Button, Checkbutton, Radiobutton]:
    ws.append(w(panes, text='hello'))
for w in ws:
    panes.add(w)
# 从panes中删除包含子Button的pane,使用remove与forget相同
panes.forget(ws[1])
# panes.remove(ws[1])
root.mainloop()
# 只有三个widget，Button已被删除。
```
#### 向panewindow添加pane
```python
# 使用paneconfig方法
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
ws = []
ps = PanedWindow(orient=VERTICAL)
ps.pack(fill=BOTH, expand=1)
# 创建四个pane
for w in [Label, Button, Checkbutton, Radiobutton]:
    ws.append(w(ps, text='hello'))
for w in ws:
    ps.add(w)
# 在0之后添加一个Lable，出错！！！
# ps.after(ws[0],Label(ps,text = 'world'))
# 注意被添加的widget是第一个参数，after指定是位于那一个widget之后
# 不要与after方法混淆了
ps.paneconfig(Label(ps, text='world'), after=ws[0])
root.mainloop()
# 这个widget主要也是用来做Container的，使用了大量的gm方法。
```

##frame

####frame基础

```python
# Frame就是屏幕上的一块矩形区域，多是用来作为容器（container）来布局窗体。
'''1.创建Frame'''
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
# 以不同的颜色区别各个frame
# 添加不同颜色的Frame，大小均为20*400
for fm in ['red', 'blue', 'yellow', 'green', 'white', 'black']:
    # 注意这个创建Frame的方法与其它创建控件的方法不同，第一个参数不是root
    Frame(height=20, width=400, bg=fm).pack()
root.mainloop()
```
####向frame中添加widget
```python
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
fm = []
# 以不同的颜色区别各个frame
for color in ['red', 'blue']:
    # 注意这个创建Frame的方法与其它创建控件的方法不同，第一个参数不是root
    fm.append(Frame(height=200, width=400, bg=color))
# 向下面的Frame中添加一个Label
Label(fm[1], text='Hello label').pack()
fm[0].pack()
fm[1].pack()
root.mainloop()
# Label被添加到下面的Frame中了，而不是root默认的最上方。
# 大部分的方法来自gm,留到后面gm时再介绍
```
####labelframe,添加了对title的支持
```python
from tkinter import *
 
root = Tk()
for lf in ['red', 'blue', 'yellow']:
    # 可以使用text属性指定Frame的title
    LabelFrame(height=200, width=300, text=lf).pack()
root.mainloop()
```

##toplevel

####创建简单的toplevel
```python
# TopLevel与Frame类似，但它包含窗体属性（如Title）
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
tl = Toplevel()
# 为了区别root和tl，我们向tl中添加了一个Label
Label(tl, text='hello label').pack()
root.mainloop()
# 运行结果生成了两个窗体，一个是root启动的，另一个则是Toplevel创建的，它包含有一个label;
# 关闭tl则没有退出程序，Tk仍旧工作；若关闭Tk，整个Tk结束tl也结束，它不能单独存在。
```
####设置toplevel属性
```python
# title设置标题
# geometry设置宽和高
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
tl = Toplevel()
# 设置tl的title
tl.title('hello Toplevel')
# 设置tl在宽和高
tl.geometry('400x300')
# 为了区别root和tl，我们向tl中添加了一个Label
Label(tl, text='hello label').pack()
root.mainloop()
```
####使用toplevel制造提示框
```python
'''3.使用Toplevel自己制作提示框'''
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
mbYes, mbYesNo, mbYesNoCancel, mbYesNoAbort = 0, 1, 2, 4
 
 
# 定义一个消息对话框，依据传入的参数不同，弹出不同的提示信息
def MessageBox():  # 没有使用使用参数
    mbType = mbYesNo
    textShow = 'Yes'
    if mbType == mbYes:
        textShow = 'Yes'
    elif mbType == mbYesNo:
        textShow = 'YesNo'
    elif mbType == mbYesNoCancel:
        textShow = 'YesNoCancel'
    elif mbType == mbYesNoAbort:
        textShow = 'YesNoAbort'
    tl = Toplevel(height=200, width=400)
    Label(tl, text=textShow).pack()
 
 
# 由Button来启动这个消息框，因为它使用了空的回调函数，故MessageBox改为了无参数形式，使用了固定
# 值mbYesNo
Button(root, text='click me', command=MessageBox).pack()
root.mainloop()
```

##text

####创建text，向内部添加文本
```python
from tkinter import *
root = Tk()
t = Text(root)
# 向第一行,第一列添加文本0123456789
t.insert(1.0, '0123456789')
# 向第一行第一列添加文本ABCDEFGHIJ
t.insert(1.0, 'ABCDEFGHIJ')
# insert是强制在该区域插入，原来的后退
t.insert(1.1, 'ABCDEFGHIJ')
t.pack()
root.mainloop()
# root中含有一Text控件,可以在这个控件内输入文本,可以使用Ctrl+C/V向Text内添加剪切板上的内容(文本),不接受Ctrl+Z执行操作
```

####使用line.col索引
```python
# 使用indexes来添加Text的内容
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
t = Text(root)
# 向第一行,第一列添加文本0123456789
t.insert(1.0, '0123456789')
t.insert(1.0, ' ')
# 向第一行第一列添加文本ABCDEFGHIJ
t.insert(1.0, 'ABCDEFGHIJ')
t.pack()
root.mainloop()
# 可以看到使用indexes时，如果其值超过了Text的buffer值，程序不会抛出异常，它会使用向给定值靠近。
```

#### 使用tag来指定文本属性
```python
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
t = Text(root)
# 创建一个TAG，其前景色为红色
t.tag_config('a', foreground='red')
# 使用TAG 'a'来指定文本属性
t.insert(1.0, '0123456789', 'a')
t.pack()
root.mainloop()
# 结果是文本颜色改变为红色了
```
```python
'''文本指定冲突属性'''
# 没有特别设置的话，最后创建的那个会覆盖掉其它所有的设置
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
t = Text(root)
# 创建一个TAG，其前景色为红色
t.tag_config('a', foreground='red')
t.tag_config('b', foreground='blue')
# 使用TAG 'a'来指定文本属性
t.insert(1.0, '0123456789', ('b', 'a'))
t.pack()
root.mainloop()
# 结果是文本的颜色不是按照insert给定的顺序来设置，而是按照tag的创建顺序来设置的。
```
```python
'''控制tag的级别'''
# 使用tag_lower/tag_raise来降低或提高tag的级别
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
t = Text(root)
# 创建一个TAG，其前景色为红色
t.tag_config('a', foreground='red')
t.tag_config('b', foreground='blue')
# 使用tag_lower来降低a的级别
t.tag_lower('a')
# 使用TAG 'a'来指定文本属性
t.insert(1.0, '0123456789', ('b', 'a'))
t.pack()
root.mainloop()
# 结果：文本内容颜色变为了蓝色，蓝色的作用级别大于红色了，即使是先创建了蓝色。
```
```python
'''对文本块添加tag'''
# tag_add方法的使用
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
t = Text(root)
# 创建一个TAG，其前景色为蓝色
t.tag_config('b', foreground='blue')
for i in range(10):
    t.insert(1.0, '0123456789\n')
t.tag_add('b', '2.5', '2.end')
t.pack()
root.mainloop()
# 先向Text中添加了10行文本，创建一tag，将第2行第6列至第二行行尾使用使用此tag
```
```python
'''自定义mark对文本块添加tag'''
# -*- coding: utf-8 -*-
# tag_add方法的使用
from tkinter import *
 
root = Tk()
t = Text(root)
# 创建一个TAG，其前景色为蓝色
t.tag_config('b', foreground='blue')
for i in range(10):
    t.insert(1.0, '0123456789\n')
# 自定义两个mark，并使用它们来指定添加tag的文本块
t.mark_set('ab', '3.1')
t.mark_set('cd', END)
t.tag_add('b', 'ab', 'cd')
 
t.pack()
root.mainloop()
# 先向Text中添加了10行文本，创建两个mark('ab'和'cd')，将使用这两个tag指定文本的文本块使用此tag
```
####获取text中的内容
```python
'''使用indexes获得Text中的内容'''
# -*- coding: utf-8 -*-
# 分别使用内置的indexes和自定义mark来获取文本
# get方法的使用
from tkinter import *
 
root = Tk()
t = Text(root)
for i in range(10):
    t.insert(1.0, str(i) + ' 0123456789\n')
# 获得1.0-2.3的文本
print(t.get('1.0', '2.3'))
# 自定义两个mark，并使用它们来获得文本块
t.mark_set('ab', '3.1')
t.mark_set('cd', END)
print(t.get('ab', 'cd'))
t.pack()
root.mainloop()
```
####delete对tag的影响
```python
# -*- coding: utf-8 -*-
# delete方法不会对tag造成影响，也就是说删除文本与tag没有任何关系
from tkinter import *
 
root = Tk()
t = Text(root)
# 创建一个TAG，其前景色为蓝色
t.tag_config('b', foreground='blue')
for i in range(10):
    t.insert(1.0, str(i) + ' 0123456789\n')
# 自定义两个mark，并使用它们来指定添加tag的文本块
t.mark_set('ab', '3.1')
t.mark_set('cd', END)
t.tag_add('b', 'ab', 'cd')
# 删除(1.0 - 4.0)的文本
t.delete('1.0', '4.0')
t.pack()
root.mainloop()
# (1.0-4.0)的文本全部初始删除了，剩余的文本全部以蓝色显示，即还保留tag的属性
```
####tag_delete对tag的影响
```python
'''13.使用tag_delete对文本属性的影响'''
# -*- coding: utf-8 -*-
# 使用tag_delete方法操作tag
from tkinter import *
 
root = Tk()
t = Text(root)
# 创建一个TAG，其前景色为蓝色
t.tag_config('b', foreground='blue')
for i in range(10):
    t.insert(1.0, str(i)+' 0123456789\n')
# 自定义两个mark，并使用它们来指定添加tag的文本块
t.mark_set('ab', '3.1')
t.mark_set('cd', END)
t.tag_add('b', 'ab', 'cd')
# 删除tag 'b'，注意这个操作是在tag_add之后进行的。
t.tag_delete('b')
t.pack()
root.mainloop()
# 结果所有的文本没有了tag('b')属性，即tag_delete会清除所有与此tag相关的属性，不论是之前还是之后
```
####tag的两个内置属性
```python
# tag.first:tag之前插入文本，此文本不包含在这个tag中
# tag.last:tag之后插入文本，此文本包含在这个tag中
# -*- coding: utf-8 -*-
# 使用tag的内置属性来插入文本
from tkinter import *
 
root = Tk()
t = Text(root)
# 创建一个TAG，其前景色为蓝色
t.tag_config('b', foreground='blue')
for i in range(10):
    t.insert(1.0, str(i) + ' 0123456789\n')
# 自定义两个mark，并使用它们来指定添加tag的文本块
t.mark_set('ab', '3.1')
t.mark_set('cd', END)
t.tag_add('b', 'ab', 'cd')
# 删除tag 'b'，注意这个操作是在tag_add之后进行的。
# 在tag('b')之前插入'first'
t.insert('b.first', 'first')
# 在tag('b')之后插入'last'
t.insert('b.last', 'last')
t.pack()
root.mainloop()
# 注意：first没有使用tag('b')属性，last使用了tag('b')属性
```
####在text中创建按钮
```python
# -*- coding: utf-8 -*-
# 使用window_create在Text内创建一widget
from tkinter import *
 
root = Tk()
t = Text(root)
for i in range(10):
    t.insert(1.0, '0123456789 ')
 
 
def printText():
    print('buttin in text')
 
 
bt = Button(t, text='button', command=printText)
# 在Text内创建一个按钮
t.window_create('2.0', window=bt)
# 没有调用pack()
# bt.pack()
t.pack()
root.mainloop()
# 注意：使用window_create，而不是使用insert('2.0',bt);pack()也不用调用;
# 点击这个按钮，打印出'button in text'，证明这个按钮是可以正常工作的。
```
####tag与事件绑定
```python
# -*- coding: utf-8 -*-
# 使用tag_bind方法
from tkinter import *
 
root = Tk()
t = Text(root)
for i in range(10):
    t.insert(1.0, '0123456789\n')
# 创建一个tag
t.tag_config('a', foreground='blue', underline=1)
 
 
# Enter的回调函数
def enterTag(event):
    print('Enter event')
 
 
# 绑定tag('a')与事件('<Enter>')
t.tag_bind('a', '<Enter>', enterTag)
t.insert(2.0, 'Enter event ', 'a')
t.pack()
root.mainloop()
# 注意：使用tag_bind绑定tag与事件，当此事件在tag上发生时便就会调用这个tag的回调函数
# 因为使用了Enter事件，此事件含有一个参数，故将enterTag加了一个参数，程序中不使用此参数
```
##canvas

####创建canvas
```python
# 提供可以用来进行绘图的Container，支持基本的几何元素
# 使用Canvas进行绘图时，所有的操作都是通过Canvas，不是通过它的元素
# 元素的表示可以使用handle或tag。

# -*- coding: utf-8 -*-
# 指定画布的颜色为白色
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为黄色
cv = Canvas(root, bg='yellow')
cv.pack()
root.mainloop()
```
####创建一个item
```python
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()

# 创建一个Canvas
cv = Canvas(root, bg='yellow')

# 创建一个矩形，坐标为(10,10,110,110)
cv.create_rectangle(10, 10, 110, 110)
 
# 指定矩形的填充色为红色
cv.create_rectangle(120, 10, 220, 110, fill='red')
 
# 指定矩形的边框颜色为红色
cv.create_rectangle(10,120,110,220,outline = 'red')
 
# 指定矩形的边框颜色为红色，设置线宽为5，注意与Canvas的width是不同的。
cv.create_rectangle(120,120,220,220,outline = 'red',width = 5)

cv.pack()
root.mainloop()
```
####虚线与画刷
```python
# -*- coding: utf-8 -*-
# 指定画布的背景色为白色
# 使用属性dash,这个值只能为奇数
from tkinter import *
 
root = Tk()

cv = Canvas(root, bg='white')
# 指定矩形的边框颜色为红色,画虚线
cv.create_rectangle(10, 10, 110, 110,
                    outline='red',
                    dash=10,
                    fill='green')
 
'''使用画刷填充'''
cv.create_rectangle(120, 10, 220, 110,
                    outline = 'red',
                    stipple = 'gray12',
                    fill = 'green')
cv.pack()
root.mainloop()
```
####定位一个item
```python
# -*- coding: utf-8 -*-
# 指定画布的背景色为白色
# 使用Canvas的方法来重新设置item的坐标
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
rt = cv.create_rectangle(10, 10, 110, 110,
                         outline='red',
                         stipple='gray12',
                         fill='green')
cv.pack()
# 重新设置rt的坐标（相当于移动一个item）
cv.coords(rt, (40, 40, 80, 80))
root.mainloop()
# 动态修改item的坐标
```
####创建item的tags
```python
# -*- coding: utf-8 -*-
# 使用属性tags设置item的tag
# 使用Canvas的方法gettags获取指定item的tags
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
# 使用tags指定一个tag('r1')
rt = cv.create_rectangle(10, 10, 110, 110,
                         tags='r1'
                         )
cv.pack()
 
print(cv.gettags(rt))
# 使用tags属性指定多个tags,即重新设置tags的属性
cv.itemconfig(rt, tags=('r2', 'r3', 'r4'))
print(cv.gettags(rt))
root.mainloop()
```
####通过tags访问item
```python
# -*- coding: utf-8 -*-
# 得到了tag值也就得到了这个item，可以对这个item进行相关的设置。
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
# 使用tags指定一个tag('r1')
rt = cv.create_rectangle(10, 10, 110, 110,
                         tags=('r1', 'r2', 'r3')
                         )
cv.pack()
 
cv.create_rectangle(20, 20, 80, 80, tags='r3')
# 将所有与tag('r3')绑定的item边框颜色设置为蓝色
for item in cv.find_withtag('r3'):
    print(item)
    cv.itemconfig(item, outline='blue')
root.mainloop()
# 动态修改与tag('r3')绑定的item边框颜色
```
```python
# -*- coding: utf-8 -*-
# 使用find_xxx查找上一个或下一个item
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
# 创建三个rectangle
rt1 = cv.create_rectangle(
    10, 10, 110, 110,
    tags=('r1', 'r2', 'r3'))
rt2 = cv.create_rectangle(
    20, 20, 80, 80,
    tags=('s1', 's2', 's3'))
rt3 = cv.create_rectangle(
    30, 30, 70, 70,
    tags=('y1', 'y2', 'y3'))
# 查找rt2的上一个item,并将其边框颜色设置为红色
cv.itemconfig(cv.find_above(rt2), outline='red',width='5')
# 查找rt2的下一个item,并将其边框颜色设置为绿色
cv.itemconfig(cv.find_below(rt2), outline='green',width='2')
 
cv.pack()
root.mainloop()
# Canvas使用了stack的技术，新创建的item总是位于前一个创建的item之上，故调用above时，
# 它会查找rt2上面的item为rt3,故rt3中边框颜色设置为红色，同样add_below会查找下面的item。
```
####为item添加tag
```python
# -*- coding: utf-8 -*-
# 使用addtag_来向上一个或下一个item添加tag
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
# 创建三个rectangle
rt1 = cv.create_rectangle(
    10, 10, 110, 110,
    tags=('r1', 'r2', 'r3'))
rt2 = cv.create_rectangle(
    20, 20, 80, 80,
    tags=('s1', 's2', 's3'))
rt3 = cv.create_rectangle(
    30, 30, 70, 70,
    tags=('y1', 'y2', 'y3'))
# 向rt2的上一个item添加r4
cv.addtag_above('r4', rt2)
# 向rt2的下一个item添加r5
cv.addtag_below('r5', rt2)
 
for item in [rt1, rt2, rt3]:
    print(cv.gettags(item))
 
cv.pack()
root.mainloop()
# Canvas使用了stack的技术，新创建的item总是位于前一个创建的item之上，故调用above时，它会查找rt2上面的item为rt3,故rt3中添加了tag('r4')，
# 同样add_below会查找下面的item。
```
####移动item
```python
# -*- coding: utf-8 -*-
# move指定x,y在偏移量
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
# 创建两个同样的rectangle，比较移动前后的不同
rt1 = cv.create_rectangle(
    10, 10, 110, 110,
    tags=('r1', 'r2', 'r3'))
cv.create_rectangle(
    10, 10, 110, 110,
    tags=('r1', 'r2', 'r3'))
# 移动rt1
cv.move(rt1, 20, -10)
cv.pack()
root.mainloop()
# move可以指定x,y在相对偏移量，可以为负值
```
####删除item
```python
# -*- coding: utf-8 -*-
# delete删除给定的item
from tkinter import *
 
root = Tk()
cv = Canvas(root, bg='white')
# 创建两个rectangle
rt1 = cv.create_rectangle(
    10, 10, 110, 110,
    tags=('r1', 'r2', 'r3'))
r2 = cv.create_rectangle(
    20, 20, 110, 110,
    tags=('s1', 's2', 's3'))
# 使用id删除rt1
cv.delete(rt1)
# 使用tag删除r2
cv.delete('s1')
 
cv.pack()
root.mainloop()
# 两种方法删除item(id/tag)
```
####缩放item
```python
# -*- coding: utf-8 -*-
# scale缩放item,计算公式:(coords - offset)*scale + offset
from tkinter import *
 
root = Tk()
cv = Canvas(root, bg='white')
# 创建两个rectangle
rt1 = cv.create_rectangle(
    10, 10, 110, 110,
    tags=('r1', 'r2', 'r3'))
# 将y坐标放大为原来的2位，x坐标值不变
cv.scale(rt1, 0, 0, 1, 2)
cv.pack()
root.mainloop()
# scale的参数为(self,xoffset,yoffset,xscale,yscale)
```
####绑定item和event
```python
'''19.绑定item与event'''
# -*- coding: utf-8 -*-
# 使用tag_bind来绑定item与事件
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
# 创建三个rectangle
rt1 = cv.create_rectangle(
    10, 10, 110, 110,
    width=8,
    tags=('r1', 'r2', 'r3'))
 
 
def printRect(event):
    print('rectangle')
 
 
# 绑定item与事件
cv.tag_bind('r1', '<Button-1>', printRect)
cv.pack()
root.mainloop()
# 只有点击到矩形的边框时才会触发事件
```
####添加绑定事件
```python
'''20.添加绑定事件'''
# -*- coding: utf-8 -*-
# 使用tag_bind来绑定item与事件，与参考上测试结果不一致。
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
# 创建三个rectangle
rt1 = cv.create_rectangle(
    10, 10, 110, 110,
    width=8,
    tags=('r1', 'r2', 'r3'))
 
 
def printRect(event):
    print('rectangle')
 
 
def printLine(event):
    print('line')
 
 
# 绑定item与左键事件
cv.tag_bind('r1', '<Button-1>', printRect)
# 绑定item与右键事件
cv.tag_bind('r1', '<Button-2>', printLine)
cv.pack()
root.mainloop()
# 只有点击到矩形的边框时才会触发事件,不使用add参数，默认就是向这个item添加一个处理函数，它不会替换原来的事件函数，例子结果：既响应左键又响应右键
```
####绘制弧形
```python
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white',height='400')
# 使用默认参数创建一个ARC，结果为90度的扇形
cv.create_arc((10, 10, 110, 110), )
'''设置弧形的样式'''
d = {1: PIESLICE, 2: CHORD, 3: ARC}
for i in d:
    cv.create_arc((10, 10 + 60 * i, 110, 110 + 60 * i), style=d[i])
    print(i, d[i])
cv.pack()
root.mainloop()
```
```python
'''设置弧形的角度'''
# -*- coding: utf-8 -*-
# 使用start/extent指定起始角度与偏移角度
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
d = {1: PIESLICE, 2: CHORD, 3: ARC}
for i in d:
    cv.create_arc(
        (10, 10 + 60 * i, 110, 110 + 60 * i),
        style=d[i],  # 指定样式
        start=30,  # 指定起始角度
        extent=30  # 指定角度偏移量
    )
cv.pack()
root.mainloop()
# 使用三种样式，start指定起始角度；extent指定角度偏移
```
####绘制位图
```python
# -*- coding: utf-8 -*-
# 使用bitmap创建位图create_bitmap
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
d = {1: 'error', 2: 'info', 3: 'question', 4: 'hourglass'}
for i in d:
    cv.create_bitmap((20 * i, 20 * i), bitmap=d[i])
cv.pack()
root.mainloop()
# 使用bitmap属性来指定位图的名称，这个函数的第一个参数为一个点(x,y)指定位图存放位置的左上位置。
```
####绘制gif图像
```python
# -*- coding: utf-8 -*-
# 创建gif图像create_image
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
img = PhotoImage(file='d:/1.png')
cv.create_image((150, 150), image=img)
cv.pack()
root.mainloop()
# 先使用PhotoImage创建GIF图像，再将image属性来设置为新创建的img
```
####绘制直线
```python
# -*- coding: utf-8 -*-
# 创建带箭头的直线create_line
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
d = [(0, 'none'), (1, 'first'), (2, 'last'), (3, 'both')]
for i in d:
    cv.create_line(
        (10, 10 + i[0] * 20, 110, 110 + i[0] * 20),  # 设置直线的起始、终点
        arrow=i[1],  # 设置直线是否使用箭头
        arrowshape='40 40 10'  # 设置箭头的形状(填充长度，箭头长度，箭头宽度
    )
cv.pack()
root.mainloop()
# 使用arrow属性来控制是否显示箭头
```
```python
'''直线的joinstyle属性'''
# -*- coding: utf-8 -*-
# 创建直线，使用joinstyle属性
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
d = [(0, 'none', 'bevel'), (1, 'first', 'miter'), (2, 'last', 'round'), (3, 'both', 'round')]
for i in d:
    cv.create_line(
        (10, 10 + i[0] * 20, 110, 110 + i[0] * 20),  # 设置直线的起始、终点
        arrow=i[1],  # 设置直线是否使用箭头
        arrowshape='8 10 3',  # 设置箭头的形状(填充长度，箭头长度，箭头宽度
        joinstyle=i[2],
    )
cv.pack()
root.mainloop()
# 将直线的属性joinstyle分别设置为bevel/miter/round，测试其效果。
```
####绘制椭圆
```python
# -*- coding: utf-8 -*-
# 绘制椭圆，使用create_oval属性
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
# 创建一个长200，宽100的椭圆
cv.create_oval((10, 10, 210, 110), fill='red')
cv.pack()
root.mainloop()
# 指定椭圆的长和宽，圆是长和宽相等的特殊情况。
```
####绘制多边形
```python
# -*- coding: utf-8 -*-
# 创建多边形（三角形）
from tkinter import *
 
root = Tk()
# 绘制一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
# 创建一个直角三角形
cv.create_polygon((10, 10, 10, 200, 100, 200), fill='red')
cv.pack()
root.mainloop()
# 指定三个点的坐标，三个点坐标必须满足三角形的定义。
```
####绘制文字
```python
# -*- coding: utf-8 -*-
# 使用文字create_text
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
# 创建一个文字对象，默认设置为居中对齐
cv.create_text((10, 10), text='Hello Text',
               anchor=W
               )
cv.pack()
root.mainloop()
# 使用anchor控制文字的位置，使用justify控制对齐方式
```
####选中文字
```python
# -*- coding: utf-8 -*-
# 使用文字create_text
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
# 创建一个文字对象，默认设置为居中对齐
txt = cv.create_text((10, 10), text='Hello Text',
                     anchor=W
                     )
# 设置文本的选中起始位置
cv.select_from(txt, 2)
# 设置文本的选中结束位置
cv.select_to(txt, 5)
 
cv.pack()
root.mainloop()
# 使用anchor控制文字的位置，使用justify控制对齐方式
```
####创建组件
```python
# -*- coding: utf-8 -*-
# 使用子组件create_window
from tkinter import *
 
root = Tk()
# 创建一个Canvas，设置其背景色为白色
cv = Canvas(root, bg='white')
 
 
# 创建一个Button对象，默认设置为居中对齐
def printWindow():
    print('window')
 
 
bt = Button(cv, text='ClickMe', command=printWindow)
# 修改button在canvas上的对齐方式
cv.create_window((10, 10), window=bt, anchor=W)
# 新创建的line对象与button有重叠
cv.create_line(10, 10, 20, 20)
# 新创建的line不在button之上，即没有重叠
cv.create_line(30, 30, 100, 100)
cv.pack()
root.mainloop()
# 使用anchor组件在Canvas上的位置，默认情况下为居中对齐,这样使用后其它的item将不能再使用button战胜的那块区域
```
##pack
####pack基础
```python
# Pack为一布局管理器，可将它视为一个弹性的容器
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
# 查看当前root下的子组件,解释器没有报异常，说明Pack已创建，并可以使用,此时的输出为空，即root没有任何子组件。
print(root.pack_slaves())
# 向root中pack一个Label
Label(root, text='pack').pack()
# 再次打印出root的子组件，可以看到已经包含一个组件，即刚才创建的Label，说明Label调用pack()是将自己加入到了root中。
print(root.pack_slaves())
root.mainloop()
# pack_salves打印当前组件包拥有的子组件，通过这个函数可以查看各个组件是否有包含关系。
```
####fill控制子组件布局
```python
'''5.fill如何控制子组件的布局'''
# -*- coding: utf-8 -*-
# 不设置root的大小，使用默认
from tkinter import *
 
root = Tk()
# 改变root的大小为80x80
root.geometry('80x80+0+0')
print(root.pack_slaves())
# 创建三个Label分别使用不同的fill属性
Label(root, text='pack1', bg='red').pack(fill=Y)
Label(root, text='pack2', bg='blue').pack(fill=BOTH)
Label(root, text='pack3', bg='green').pack(fill=X)
print(root.pack_slaves())
root.mainloop()
# 第一个只保证在Y方向填充，第二个保证在XY两个方向上填充，第三个不使用填充属性,
# 注意Pack只会吝啬地给出可以容纳这三个组件的最小区域，它不允许使用剩余的空间了，故下方留有“空白”。
```
####expand控制子组件布局
```python
# -*- coding: utf-8 -*-
# 这个属性指定如何使用额外的空间，即上例中留下来的“空白”
from tkinter import *
 
root = Tk()
# 改变root的大小为80x80
root.geometry('80x80+0+0')
print(root.pack_slaves())
# 创建三个Label分别使用不同的fill属性
Label(root, text='pack1', bg='red').pack(fill=Y, expand=1)
Label(root, text='pack2', bg='blue').pack(fill=BOTH, expand=1)
Label(root, text='pack3', bg='green').pack(fill=X, expand=0)
print(root.pack_slaves())
root.mainloop()
# 第一个只保证在Y方向填充，第二个保证在XY两个方向上填充，第三个不使用填充属性,
# 这个例子中第一个Label和第二个Label使用了expand = 1属性，而第三个使用expand = 0属性，改变root的大小，
# 可以看到Label1和Label2是随着root的大小变化而变化（严格地它的可用空间在变化），第三个只中使用fill进行X方向上的填充，不使用额外的空间。
```
####side控制子组件布局
```python
'''7.改变组件的排放位置'''
# 使用side属性改变放置位置
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
# 改变root的大小为80x80
root.geometry('80x80+0+0')
print(root.pack_slaves())
# 创建三个Label分别使用不同的fill属性,改为水平放置
# 将第一个Label居左放置
Label(root, text='pack1', bg='red').pack(fill=Y, expand=1, side=LEFT)
# 将第二个Label居右放置
Label(root, text='pack2', bg='blue').pack(fill=BOTH, expand=1, side=RIGHT)
# 将第三个Label居左放置，靠Label放置，注意它不会放到Label1的左边
Label(root, text='pack3', bg='green').pack(fill=X, expand=0, side=LEFT)
print(root.pack_slaves())
root.mainloop()
# 第一个只保证在Y方向填充，第二个保证在XY两个方向上填充，第三个不使用填充属性,这个例子中第一个Label和第二个Label使用了expand = 1属性，
# 而第三个使用expand = 0属性，改变root的大小，可以看到Label1和Label2是随着root的大小变化而变化（严格地它的可用空间在变化），
# 第三个只中使用fill进行X方向上的填充，不使用额外的空间。
```
####设置组件间隙大小
```python
# ipadx设置内部间隙
# padx设置外部间隙
# -*- coding: utf-8 -*-
# 不设置root的大小，使用默认
from tkinter import *
 
root = Tk()
# 改变root的大小为80x80
# root.geometry('80x80+0+0')
print(root.pack_slaves())
# 创建三个Label分别使用不同的fill属性,改为水平放置
# 将第一个LabelFrame居左放置
L1 = LabelFrame(root, text='pack1', bg='red')
# 设置ipadx属性为20
L1.pack(side=LEFT, ipadx=20)
Label(L1,
      text='inside',
      bg='blue'
      ).pack(expand=1, side=LEFT)
L2 = Label(root,
           text='pack2',
           bg='blue'
           ).pack(fill=BOTH, expand=1, side=LEFT, padx=10)
L3 = Label(root,
           text='pack3',
           bg='green'
           ).pack(fill=X, expand=0, side=LEFT, pady=10)
print(root.pack_slaves())
root.mainloop()
# 为了演示ipadx/padx，创建了一个LabelFrame设置它的ipadx为20,即内部间隔值为20，
# 它的子组件若使用则会留出20个单位；Label2和Label3分别设置x和y方向上的外部间隔值，所有与之排列的组件会与之保留10个单位值的距离
```
##place
####绝对坐标
```python
# 不设置root的大小，使用默认
from tkinter import *
 
root = Tk()
lb = Label(root, text='hello Place')
# 使用绝对坐标将Label放置到(0,0)位置上
lb.place(x=0, y=0, anchor=NW)
root.mainloop()
# x,y指定组件放置的绝对位置
```
####相对坐标
```python
from tkinter import *
 
root = Tk()
lb = Label(root, text='hello Place')
# 使用相对坐标(0.5,0.5)将Label放置到(0.5*sx,0.5.sy)位置上
lb.place(relx=0.5, rely=0.5, anchor=CENTER)
root.mainloop()
# relx,rely指定组件放置的绝对位置,范围为(0-1.0)
```
####绝对坐标与相对坐标同时使用
```python
# 同时设置relx,rely和x,y的值
# -*- coding: utf-8 -*-
# 不设置root的大小，使用默认
from tkinter import *
 
root = Tk()
root.geometry('800x600')
lb1 = Label(root, text='hello Place', fg='green')
lb2 = Label(root, text='hello Place', fg='red')
# 先设置相对坐标为(0.5,0.5),再使用(-200,-200)将坐标作偏移(-200,-200)
lb1.place(relx=0.5, rely=0.5, anchor=CENTER, x=-200, y=-200)
# 先设置相对坐标为(0.5,0.5),再使用(-300,-300)将坐标作偏移(-300,-300)
lb2.place(relx=0.5, rely=0.5, anchor=CENTER, x=-300, y=-300)
root.mainloop()
# 同时使用相对和绝对坐标时，相对坐标优先操作，然后是在这个相对坐标的基础上进行偏移
```
####in来指定放置的容器
```python
# -*- coding: utf-8 -*-
# 使用in属性来指定放置到的容器是那一个
from tkinter import *
 
root = Tk()
root.geometry('800x600')
lb1 = Label(root, text='hello Place Label', fg='green')
bt1 = Button(root, text='hello Place Button', fg='red')
# 创建一个Label
lb1.place(relx=0.5, rely=0.5, anchor=CENTER)
 
# 在root同创建一个Button，目的是与bt1相比较
bt2 = Button(root, text='button in root', fg='yellow')
bt2.place(anchor=W)
# 在Label中创建一个Button
bt1.place(in_=lb1, anchor=W)
root.mainloop()
# 注意bt2放置的位置是在root的(0,0)处，而button1放置的位置是在lb1的(0,0)处，原因是由于bt1使用了in来指定放置的窗口为lb1
```
####结合事件使用
```python
# -*- coding: utf-8 -*-
# 最后使用两个place方法来动态改变两个Frame的大小。
from tkinter import *
root = Tk()
split = 0.5
fm1 = Frame(root,bg = 'red')
fm2 = Frame(root,bg = 'blue')
# 单击fm1时增大它的占有区域0.1
def incFm1(event):
    global split
    if split < 1:
        split += 0.1
    fm1.place(rely = 0,relheight = split,relwidth = 1)
    fm2.place(rely = split,relheight = 1 - split,relwidth = 1)
# 单击fm2时增大它的占有区域0.1
def incFm2(event):
    global split
    if split > 0:
        split -= 0.1
    fm1.place(rely = 0,relheight = split,relwidth = 1)
    fm2.place(rely = split,relheight = 1 - split,relwidth = 1)
 
# 这两语句要使用，不然开始看不到两个frame，也就没法点击它们了
fm1.place(rely = 0,relheight = split,relwidth = 1)
fm2.place(rely = split,relheight = 1 - split,relwidth = 1)
# 绑定单击事件
fm1.bind('<Button-1>',incFm1)
fm2.bind('<Button-1>',incFm2)
 
root.mainloop()
# 为SplitWindow的原型了，再改动一下就可以实现一个SplitWindow了。
```
##grid
####使用row和column来指定位置
```python
# -*- coding: utf-8 -*-
# 使用grid来布局组件
from tkinter import *
 
root = Tk()
# 创建两个Label
lb1 = Label(root, text='Hello')
lb2 = Label(root, text='Grid')
 
lb1.grid()
# 指定lb2为第一行（使用索引0开始），第二列（使用索引0开始）
lb2.grid(row=0, column=1)
 
root.mainloop()
# grid有两个最为重要的参数，用来指定将组件放置到什么位置，一个是row,另一个是column。如果不指定row,会将组件放置到第一个可用的行上，
# 如果不指定column，则使用第一列。注意这里使用grid时不需要创建，直接使用行列就可以。
```
####为组件预留位置
```python
# -*- coding: utf-8 -*-
from tkinter import *
 
root = Tk()
# 创建两个Label
Label(root, text='1').grid()
Label(root, text='2').grid(row=0, column=10)
Label(root, text='3').grid(row=0, column=5)
root.mainloop()
# 可以看到Label('3')是位置Label('1')和Label('2')之间了，即Label('2')是在11列，Label('3')位于第3列
```
####同行同列组件覆盖
```python
# -*- coding: utf-8 -*-
# 多个组件同时grid到同一个表格位置
from tkinter import *
 
root = Tk()
# 创建两个Label
lb1 = Label(root, text='1')
lb2 = Label(root, text='2')
 
# 将lb1和lb2均grid到(0,0)位置
lb1.grid(row=0, column=0)
lb2.grid(row=0, column=0)
 
 
def forgetLabel():
    # grid_slaves返回grid中(0,0)位置的所有组件
    # grid_forget将这个组件从grid中移除（并未删除，可以使用grid再将它显示出来)
    print(root.grid_slaves(0, 0))
    root.grid_slaves(0, 0)[0].grid_forget()
 
 
# 我测试时grid_salves返回的第一个值为lb2，最后grid的那一个
Button(root, text='forget last', command=forgetLabel).grid(row=1)
 
root.mainloop()
# 这段代码是用来证明，多个组件同时放置到同一个位置上会产生覆盖的问题。对于grid_slaves返回的组件list如何排序，
# 我没有去查想着资料，在这个例子中使用索引0，返回的正好是lb2,然后再使用grid_forget将这个删除从grid中移除，可以看到lb1显示出来了。
```
####指定行列属性值
```python
'''6.改变列（行）的属性值'''
# -*- coding: utf-8 -*-
# 设置column的属性(columnconfigure)
from tkinter import *
 
root = Tk()
# 创建两个Label
lb1 = Label(root, text='1', bg='red')
lb2 = Label(root, text='2', bg='blue')
 
# 将lb1和lb2分别放置到第1行的1,2列位置上
lb1.grid(row=0, column=0)
lb2.grid(row=0, column=1)
 
# 指定列的最小宽度为100
root.columnconfigure(0, minsize=100)
root.mainloop()
# 1与2的距离变的远一些了。
# 但如果这个位置没有组件存在的话这个值是不起作用的.
# 设置列或行(rowconfigure)的属性时使用父容器的方法,不是自己调用。
```
####组件使用多行多列
```python
# -*- coding: utf-8 -*-
# 使用多行（多列)
from tkinter import *
 
root = Tk()
# 创建如下布局（一个字符占用一个grid位置）
# A  E
# B C
# D
# A占用(0,0)(0,1),B占用(1,0),C占用(1,1),D占用(2,0),E占用(0,2)
# 创建5个Label，分别以背景色区别
lbA = Label(root, text='A', bg='red')
lbB = Label(root, text='B', bg='blue')
lbC = Label(root, text='C', bg='red')
lbD = Label(root, text='D', bg='blue')
lbE = Label(root, text='E', bg='blue')
# 以下为布局参数设置
lbA.grid(row=0, column=0, columnspan=2)
lbB.grid(row=1, column=0)
lbC.grid(row=1, column=1)
lbD.grid(row=2)
lbE.grid(row=0, column=2)
 
root.mainloop()
# A与B、D的区别，它左边已改变，由于使用了两个表格；
# C与E的区别：C的右边与E的左边对齐，也就是说E被放置到第2列的下一个位置了，原因由于A已使用了第2列。
```
####设置表格对齐属性
```python
# -*- coding: utf-8 -*-
# 使用sticky设置对齐方式
from tkinter import *
 
root = Tk()

Label(root,text='hello1').grid(sticky=N)
Label(root, text='hello2').grid(sticky=S)
Label(root, text='hello3').grid(sticky=E)
Label(root, text='hello4').grid(sticky=W)
 
root.mainloop()
# 默认属性下，组件的对齐方式为居中，设置sticky属性可以控制对齐方式，可用的值（N,S,E,W)及其组合值
```
##Font
####字体使用
```python
# -*- coding: utf-8 -*-
# 改变组件的显示字体
from tkinter import *
 
root = Tk()
# 创建一个Label
for ft in ('Arial', ('Courier New',), ('Comic Sans MS',), 'Fixdsys', ('MS Sans Serif',), ('MS Serif',), 'Symbol', 'System',
           ('Times New Roman',), 'Verdana'):
    Label(root, text='hello sticky', font=ft).grid()
 
root.mainloop()
# 在Windows上测试字体显示，注意字体中包含有空格的字体名称必须指定为tuple类型。
```
```python
# -*- coding: utf-8 -*-
# Font来创建字体
# 如果font指定了，有几个参数将不再起作用，如：family,size,weight,slant,underline,overstrike
from tkinter import *
# 引入字体模块
import tkinter.font as tkFont
 
root = Tk()
# 创建一个Label
# 指定字体名称、大小、样式
ft = tkFont.Font(family='Fixdsys', size=20, weight=tkFont.BOLD)
Label(root, text='hello sticky', font=ft).grid()
 
root.mainloop()
# 使用tkFont.Font来创建字体。
```
####获取字体属性
```python
# -*- coding: utf-8 -*-
# 测试measure和metrics属性
from tkinter import *
import tkinter.font as tkFont
 
root = Tk()
# 创建一个Label
ft1 = tkFont.Font(family='Fixdsys', size=20, weight=tkFont.BOLD)
Label(root, text='hello font', font=ft1).grid()
 
ft2 = tkFont.Font(font=('Fixdsys', '10', tkFont.NORMAL), size=40)
Label(root, text='hello font', font=ft2).grid()
 
# 得到字体的宽度
print(ft1.measure('hello font'))
print(ft2.measure('hello font'))
 
# 打印两个字体的属性
for metric in ('ascent', 'descent', 'linespace', 'fixed'):
    print(ft1.metrics(metric))
    print(ft2.metrics(metric))
root.mainloop()
# 使用这两个方法得到已创建字体的相关属性值
```
##tkCommonDialog
####tkSimpleDialog
```python
# askinteger：输入一个整数值
# askfloat：输入一个浮点数
# askstring：输入一个字符串
from tkinter import *
# 引入SimpleDialog模态对话框
from tkinter.simpledialog import *
 
root = Tk()
# 输入一个整数，
# initialvalue指定一个初始值
# prompt提示信息
# title提示框标题
print(askinteger(title='prompt', prompt='input a integer:', initialvalue=100))
# 输入一浮点数
# minvalue指定最小值
# maxvalue指定最大值，如果不在二者指定范围内则要求重新输入
print(askfloat(title='float', prompt='input a float', minvalue=0, maxvalue=11))
# 输入一字符串
print(askstring(title='string', prompt='input a string'))
root.mainloop()
# 返回值为各自输入的值。
```
####tkfiledialog
```python
'''打开文件对话框'''
from tkinter import *
from tkinter.filedialog import *
 
root = Tk()
# 指定master就可以了。
# title属性用来指定标题
fd = LoadFileDialog(root)
# go方法的返回值即为选中的文本路径，如果选择取返回值则为None
print(fd.go())
root.mainloop()
# 返回选中的文件名称
```
```python
'''保存文件对话框'''
# SaveFileDialog：保存对话框
# 与LoadFileDialog正好操作相反，这个类是用来保存文件。
# 各个 参数的意义都  一样，只是ok的返回值为保存的文件名称；如果取消则为None
from tkinter import *
from tkinter.filedialog import *
 
root = Tk()
# 指定master就可以了。
# title属性用来指定标题
fd = SaveFileDialog(root)
# go方法的返回值即为选中的文本路径，如果选择取返回值则为None
print(fd.go())
root.mainloop()
# 返回选中的文件名称
```
####tkmessagebox
```python
# -*- coding: utf-8 -*-
# showinfo：信息对话框
# showwarning：警告对话框
# showerror：错误对话框
# showquestion：询问对话框
# showokcancel：显示确定/取消对话框
# showyesno：是/否对话框
# showretrycancel：重试/取消对话框
# 使用提示对话框模块tkMessageBox
from tkinter import *
# 引入tkMessageBox模块
from tkinter.messagebox import *
 
root = Tk()
stds = [
    showinfo,  # 显示信息消息框
    showwarning,  # 显示警告消息框
    showerror,  # 显示错误消息框
    askquestion,  # 显示询问消息框
    askokcancel,  # 显示确认/取消消息框
    askyesno,  # 显示是/否消息框
    askretrycancel  # 显示重试/取消消息框
]
for std in stds:
    print(str(std), std(title=str(std), message=str(std)))
# 程序打印输出结果如下（与点击的按钮得到不同其值）
# <function showinfo at 0x00D589F0> ok
# <function showwarning at 0x00D58A30> ok
# <function showerror at 0x00D58A70> ok
# <function askquestion at 0x00D58AB0> yes
# <function askokcancel at 0x00D58AF0> False
# <function askyesno at 0x00D58B30> True
# <function askretrycancel at 0x00D58B70> True
root.mainloop()
# 如果要确认点击的是那一个按钮，则可以判断这个消息框的返回值，注意各个值有所不同
# 返回值有ok/yes/True
```
##event
####鼠标点击事件
```python
# 事件的使用方法
'''1.测试鼠标点击(Click)事件'''
# -*- coding: utf-8 -*-
# <Button-1>：鼠标左击事件
# <Button-2>：鼠标中击事件
# <Button-3>：鼠标右击事件
# <Double-Button-1>：双击事件
# <Triple-Button-1>：三击事件
from tkinter import *
 
root = Tk()
 
 
def printCoords(event):
    print(event.x, event.y)
 
 
# 创建第一个Button,并将它与左键事件绑定
bt1 = Button(root, text='leftmost button')
bt1.bind('<Button-1>', printCoords)
 
# 创建二个Button，并将它与中键事件绑定
bt2 = Button(root, text='middle button')
bt2.bind('<Button-2>', printCoords)
 
# 创建第三个Button，并将它与右击事件绑定
bt3 = Button(root, text='rightmost button')
bt3.bind('<Button-3>', printCoords)
 
# 创建第四个Button,并将它与双击事件绑定
bt4 = Button(root, text='double click')
bt4.bind('<Double-Button-1>', printCoords)
 
# 创建第五个Button，并将它与三击事件绑定
bt5 = Button(root, text='triple click')
bt5.bind('<Triple-Button-1>', printCoords)
 
bt1.grid()
bt2.grid()
bt3.grid()
bt4.grid()
bt5.grid()
 
root.mainloop()
# 分别测试鼠标的事件，回调函数的参数event中(x,y)表示当前点击的坐标值
```
####鼠标的移动事件
```python
# -*- coding: utf-8 -*-
# <Bx-Motion>：鼠标移动事件,x=[1,2,3]分别表示左、中、右鼠标操作。
from tkinter import *
 
root = Tk()
 
 
def printCoords(event):
    print(event.x, event.y)
 
 
# 创建第一个Button,并将它与左键移动事件绑定
bt1 = Button(root, text='leftmost button')
bt1.bind('<B1-Motion>', printCoords)
 
# 创建二个Button，并将它与中键移动事件绑定
bt2 = Button(root, text='middle button')
bt2.bind('<B2-Motion>', printCoords)
 
# 创建第三个Button，并将它与右击移动事件绑定
bt3 = Button(root, text='rightmost button')
bt3.bind('<B3-Motion>', printCoords)
 
bt1.grid()
bt2.grid()
bt3.grid()
 
root.mainloop()
# 分别测试鼠标的移动事件，只有当鼠标被按下后移动才回产生事件
```
####鼠标的释放事件
```python
# -*- coding: utf-8 -*-
# <ButtonRelease-x>鼠标释放事件,x=[1,2,3],分别表示鼠标的左、中、右键操作
from tkinter import *
 
root = Tk()
 
 
def printCoords(event):
    print(event.x, event.y)
 
 
# 创建第一个Button,并将它与左键释放事件绑定
bt1 = Button(root, text='leftmost button')
bt1.bind('<ButtonRelease-1>', printCoords)
 
# 创建二个Button，并将它与中键释放事件绑定
bt2 = Button(root, text='middle button')
bt2.bind('<ButtonRelease-2>', printCoords)
 
# 创建第三个Button，并将它与右击释放事件绑定
bt3 = Button(root, text='rightmost button')
bt3.bind('<ButtonRelease-3>', printCoords)
 
bt1.grid()
bt2.grid()
bt3.grid()
 
root.mainloop()
# 分别测试鼠标的Relase事件，只有当鼠标被Relase后移动才回产生Relase事件
```
####鼠标的进入事件
```python
# -*- coding: utf-8 -*-
# <Enter>：鼠标移入事件
from tkinter import *
 
root = Tk()
 
 
def printCoords(event):
    print(event.x, event.y)
 
 
# 创建第一个Button,并将它与Enter事件绑定
bt1 = Button(root, text='leftmost button')
bt1.bind('<Enter>', printCoords)
 
bt1.grid()
 
root.mainloop()
# 分别测试Enter事件，只是在第一次进入进回产生事件，在组件中移动不会产生Enter事件
```
####鼠标的离开事件
```python
# -*- coding: utf-8 -*-
# leave：鼠标离开时产生此事件
from tkinter import *
 
root = Tk()
 
 
def printCoords(event):
    print(event.x, event.y)
 
 
# 创建第一个Button,并将它与Leave事件绑定
bt1 = Button(root, text='leftmost button')
bt1.bind('<Leave>', printCoords)
 
bt1.grid()
 
root.mainloop()
# 分别测试Leave事件，只是在离开组件是会产生此事件。
```
####响应特殊事件
```python
# -*- coding: utf-8 -*-
# 键盘特殊键事件
from tkinter import *
 
root = Tk()
 
 
def printCoords(event):
    print('event.char = ', event.char)
    print('event.keycode = ', event.keycode)
 
 
# 创建第一个Button,并将它与BackSpace键绑定
bt1 = Button(root, text='Press BackSpace')
bt1.bind('<BackSpace>', printCoords)
 
# 创建二个Button，并将它与回车键绑定
bt2 = Button(root, text='Press Enter')
bt2.bind('<Return>', printCoords)
 
# 创建第三个Button，并将它与F5键绑定
bt3 = Button(root, text='F5')
bt3.bind('<F5>', printCoords)
 
# 创建第4个Button，并将它与左Shift键绑定，与参考上说法一致
bt4 = Button(root, text='Left Shift')
bt4.bind('<Shift_L>', printCoords)
 
# 创建第5个Button，并将它与右Shift键绑定，与参考上说法一致
bt5 = Button(root, text='Right Shift')
bt5.bind('<Shift_R>', printCoords)
 
# 将焦点设置到第1个Button上
bt1.focus_set()
bt1.grid()
bt2.grid()
bt3.grid()
bt4.grid()
bt5.grid()
 
root.mainloop()
# 各个组件间焦点的切换可以使用TAB键。
# 特殊键    Cancel/Break/BackSpace/Tab/Return/Sift_L/Shift_R/Control_L/Control_R/Alt_L/Alt_R/Pause
#        Caps_Loack/Escape/Prior(Page Up)/Next(Page Down)/End/Home/Left/Up/Right/Down/Print/Insert/Delete/
#        F1-12/Num_Lock/Scroll_Lock
# 这些键的char是不可打印的，可以使用event.keycode查看。
```
```python
'''7.响应所有的按键(Key)事件'''
# -*- coding: utf-8 -*-
# Key：处理所有的键盘事件
from tkinter import *
 
root = Tk()
 
 
def printCoords(event):
    print('event.char = ', event.char)
    print('event.keycode = ', event.keycode)
 
 
# 创建第一个Button,并将它与Key键绑定
bt1 = Button(root, text='Press BackSpace')
bt1.bind('<Key>', printCoords)
 
# 将焦点设置到第1个Button上
bt1.focus_set()
bt1.grid()
 
root.mainloop()
# 处理所有的按键事件，如果是上例的特殊键，event.char返回为空；其它情况下为这个键的值。
# 如果输入大写字母（即上档键值），按下Shift键时就会有Key的事件触发。即回将用两次：一次为Shift本身，另一次为Shift+ Kye的实际键值。
```
```python
'''9.使用组合键响应事件'''
# -*- coding: utf-8 -*-
# 组合键(Control/Alt/Shift)
from tkinter import *
 
root = Tk()
 
 
def printCoords(event):
    print('event.char = ', event.char)
    print('event.keycode = ', event.keycode)
 
 
# 创建第一个Button,并将它与键Shift - Up绑定
bt1 = Button(root, text='Press Shift - Up')
bt1.bind('<Shift-Up>', printCoords)
 
# 创建二个Button，并将它与按下Control-Alt-b时触发事件
bt2 = Button(root, text='Control-Alt-b')
bt2.bind('<Control-Alt-b>', printCoords)
 
# 下面的按键处理将无法接受
# 创建第三个Button，并将它与'Control-Alt'键绑定
# bt3 = Button(root,text = 'Control-Alt')
# bt3.bind('<Control-Alt>',printCoords)
 
 
# 将焦点设置到第1个Button上
bt1.focus_set()
bt1.grid()
bt2.grid()
 
root.mainloop()
# 使用Control/Alt/Shift与其它按键组合,但不能单独的使用Control/Alt组合。
```
####改变组件大小事件
```python
# -*- coding: utf-8 -*-
# configure：改变组件大小事件
from tkinter import *
 
root = Tk()
 
 
def printSize(event):
    print((event.width, event.height))
 
 
root.bind('<Configure>', printSize)
 
root.mainloop()
# 当组件的大小改变时触发。evnet.width/height分别返回改变后的宽度和高度。
```
####事件绑定的覆盖
```python
# -*- coding: utf-8 -*-
# bind：将事件与处理函数
# 将两个事件绑定为同一个组件
# 为root绑定两个事件
from tkinter import *
 
root = Tk()
 
 
# Key事件处理函数
def printEvent(event):
    print('<Key>', event.keycode)
 
 
# Return事件处理函数
def printReturn(event):
    print('<Return>', event.keycode)
 
 
root.bind('<Key>', printEvent)
root.bind('<Return>', printReturn)
 
root.mainloop()
# 当按键除了Return之外，都是由printEvent来处理
# 当按键为Return时，由printReturn来处理,即由最“近”的那个事件处理。
```
####事件级别传递
```python
'''13.事件各个级别音传递'''
# -*- coding: utf-8 -*-
# bind：绑定instance与toplevel
# bind_class：绑定类处理函数
# bind_all：绑定应用所有事件
# 事件级别间”传递"
from tkinter import *
 
root = Tk()
 
 
# Key事件处理函数
def printEvent(event):
    print('<instance>', event.keycode)
 
 
# Return事件处理函数
def printToplevel(event):
    print('<toplevel>', event.keycode)
 
 
def printClass(event):
    print('<bind_class>', event.keycode)
 
 
def printAppAll(event):
    print('<bind_all>', event.keycode)
 
 
# 在instance级别与printEvent绑定
bt1 = Button(root, text='instance event')
bt1.bind('<Return>', printEvent)
 
# 在bt1的Toplevel级别与printToplevel绑定
bt1.winfo_toplevel().bind('<Return>', printToplevel)
 
# 在class级别绑定事件printClass
root.bind_class('Button', '<Return>', printClass)
 
# 在application all级别绑定printAppAll
bt1.bind_all('<Return>', printAppAll)
 
# 将焦点定位到bt1上，回车一下，结果有4个打印输出。
bt1.focus_set()
bt1.grid()
 
root.mainloop()
# 输出结果：
# <instance> 13
# <bind_class> 13
# <toplevel> 13
# <bind_all> 13
# Return向高级别进行了“传递",调用顺序为instance/class/toplevel/all
```
```python
'''14.使用bind_class的后果'''
# -*- coding: utf-8 -*-
# bind_class：绑定整个类的事件处理函数，将影响所有这个类的instance
from tkinter import *
 
root = Tk()
 
 
def printClass(event):
    print('<bind_class>', event.keycode)
 
 
# 改变button类的事件绑定
root.bind_class('Button', '<Return>', printClass)
# 创建两个Button
bt1 = Button(root, text='a button')
bt2 = Button(root, text='another button')
 
bt1.focus_set()
bt1.grid()
bt2.grid()
 
root.mainloop()
# 回车，bt1打印结果
# TAB切换到bt2,回车同样打印出结果，即所有的Button对Return事件进行响应。
```
####protocal绑定
```python
# -*- coding: utf-8 -*-
# protocol：与WM交互，绑定事件处理函数。
from tkinter import *
 
root = Tk()
 
 
def printProtocol():
    print('WM_DELETE_WINDOW')
    root.destroy()
 
 
# 使用protocol将WM_DELETE_WINDOW与printProtocol绑定
root.protocol('WM_DELETE_WINDOW', printProtocol)
root.mainloop()
# 程序在退出时打印'WM_DELETE_WINDOW'
```
# 参考链接

<https://blog.csdn.net/sofeien/article/details/50982208>
<https://www.cnblogs.com/aland-1415/p/6849193.html>