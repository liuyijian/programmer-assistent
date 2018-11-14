# python高性能编程

## 理解高性能python
* GPU：图像处理的图形处理单元，自带并行特性，最初被设计用于加速计算机图像处理的图形处理单元，现在适用于大规模数值计算
* 矢量计算：一次提供多个数据给一个CPU并能同时被操作，这种类型的CPU指令称为SIMD（single instruction multiple data）
* python的全局解释器锁GIL，确保python进程一次只能执行一条指令，无论当前有多少核心；该特性可以通过multiprocessing，numexpr，cython，分布式计算模型等技术避免
* 存储单元一次读一大块数据的性能远远好于读多次小数据
* 异步IO和缓存预取技术可以在进行其他计算时独立运行，确保数据被需要时，它已经存在于对应地方

* 监视python运行时的耗时
	* <https://github.com/benfred/py-spy>

```python
pip3 install py-spy
sudo py-spy -- python3 test.py
```
* Cython : 将python代码进行编译并允许用户提示编译器，代码究竟有多动态

## 通过性能分析找到瓶颈

* 技术清单
	* IPython的%timeit魔法函数
	* time.time()
	* 计时装饰器
	* UNIX的time命令
		* /usr/bin/time -p python3 julial_nopil.py 
			* real : 整体耗时
			* user : 记录CPU花在任务上的时间，不包括内核函数耗费的时间
			* sys : 记录内核函数耗费的时间 
		* /usr/bin/time --verbose python3 julial_nopil.py 
			* 获取更多输出信息
	* cProfile
		* python3 -m cProfile -s cumulative test.py
			* 输出每个函数累计花费的时间的排序结果  
	* line_profiler
	* perf stat
	* heapy
	* memory_profiler
	* CPython

* julia集合：一个可以产生复杂的输出图像的分形数列
* 填坑

## 列表和元组
* bisect模块：
	* 提供一个函数让你可以在保持排序的同时往列表中添加元素
	* 提供高度优化的二分搜索算法函数来查找元素

* 列表是动态数组，可变，可重设长度
* 元组是静态数组，不可变，内部数据不可改，可以用加法将两个元组合并成为一个新元组
* 元组缓存于python运行时环境，无须访问内核去分配内存
* blist和array模块（自学填坑）

* 当列表第一次需要添加数据时，python会创建新列表，足够存放原来N个元素以及额外添加的元素，实际额外分配不是1个，而是M个，M = (N >> 3) + (N < 9 ? 3 : 6)
* 使用元组存储对于静态数据而言更轻量
* 对于长度1～20的元组，即使不再被使用，空间会保留，当未来再需要一个同样大小的元组时，不需要再向操作系统申请一块内存，因为已经有预留内存

```python
'申请列表和元组的性能差异'
'62.4ns'
l = [0,1,2,3,4,5,6,7,8,9]
'10ns'
l = (0,1,2,3,4,5,6,7,8,9)
```

## 字典和集合

* 字典和集合使用散列表获得O(1)的查询和插入

```python
'命名空间查询速度差异'
'函数本地化能提升性能，约10%'
import math
from math import sin

#需要调用,165ns
def test1(x):
	return math.sin(x)

#全局空间查询,133ns
def test2(x):
	return sin(x)

#本地变量无需字典查询,141ns
def test3(x,sin=math.sin)
	return sin(x)
```
## 迭代器和生成器

* for循环中，用生成器代替列表推导式，节约内存

```python
# 非波拉契数列奇数个数多种实现

def fibonacci():
	i, j = 0, 1
	while True:
		yield j
		i, j = j, i + j

def f_naive():
	i, j = 0, 1
	count = 0
	while j <= 5000:
		if j % 2:
			cpunt += 1
		i, j = j, i+j
	return count

# 使用规范：生成器负责创建数据，普通函数负责操作数据，在创建复杂程序时非常有用
def f_transform():
	count = 0
	for f in fibonacci():
		if f > 5000:
			break
		if f % 2:
			count += 1
	return count

from itertools import islice
def f_succinct():
	is_odd = lambda x : x % 2
	first_5000 = islice(fibonacci(), 0, 5000)
	return sum(1 for x in first_5000 if is_odd(x))
```
* itertools库，提供python内建函数map，reduce，filter，zip的生成器版本，分别是imap,ireduce,ifilter,izip,及其他函数
	* islice ： 允许对一个无穷生成器进行切片
	* chain ： 将多个生成器连接到一起
	* takewhile : 给生成器添加一个终止条件
	* cycle : 通过不断重复一个有穷生成器变成无穷 
* 使用迭代器组织算法，处理的数据远远超过内存限制，使用迭代器的性能好于使用列表，避免了昂贵的append操作

## 矩阵和矢量计算

```python
'性能测试'

from array import array
import numpy
import time

def norm1(source):
	norm = 0
	for v in source:
		norm += v * v
	return norm

def norm2(source):
	return sum([v*v for v in source])

def norm3(source):
	return sum(v*v for v in source)

def norm4(source):
	return numpy.sum(source * source)

def norm5(source):
	return numpy.dot(source,source)

vector = range(10000000)
myarray = array('l',range(10000000))
mynumpyarray = numpy.arange(10000000)

'0.709s'
norm1(vector)
'0.954s'
norm2(vector)
'0.818s'
norm3(vector)
'0.714s'
norm1(myarray)
'0.045s'
norm4(mynumpyarray)
'0.005s'
norm5(mynumpyarray)
```
* 使用array就地修改减少重新分配内存的耗时

```python
from array import array
import numpy as np
import time
narray1= np.random.random((1000,100000))
narray2= np.random.random((1000,100000))

print(id(narray1))
'使用 +=，*= 将其中一个输入重用为输出,提高效率'
start = time.time()
'0.188s'
narray1 += narray2
end = time.time()
print(end-start)

print(id(narray1))

start = time.time()
'0.505s'
narray1 = narray1 + narray2
end = time.time()
print(end-start)

print(id(narray1))
```
* 在初始化阶段，先完成代码的管理性工作，包括内存分配，读取配置文件，预先计算程序所需要的数据等，在将来不需要付出什么代价就能使用这些资源

## 编译成c

* 工具
	* 提前编译工具（AOT）：
		* Cython（使用gcc编译器）
		* Shed Skin（使用g++编译器）
		* Pythran
	* 即时编译工具（JIT）：
		* Numba（专用于numpy代码）
		* PyPy
* 有待填坑

## 并行
* <https://www.cnblogs.com/niehaidong111/p/8335861.html>
* 串行爬虫
* gevent
* tornado(最快)
* asyncio
* 有待填坑

## multiprocessing
* 用进程或池对象来并行化一个CPU密集型任务
* 用哑元模块在线程池中并行化一个IO密集型任务
* 由队列来共享捎带的工作
* 在并行工作者之间共享状态，包括字节，原生数据类型

### 使用多进程和多线程来估算pi

* 若随机数生成使用np.random.uniform(0,1),则会受制于GIL锁，运行更慢

```python
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontManager, FontProperties
import multiprocessing as ml
import threading as th
import random
import math
import time

'若画图出现中文乱码，参考https://blog.csdn.net/kaizei_pao/article/details/80795377'

def multiprocessing_mock(x):
	'多进程蒙特卡罗模拟'
	n = 0
	for i in range(x):
		x = random.uniform(0,1)
		y = random.uniform(0,1)
		n += (x * x + y * y <= 1.0)
	return n

def multiprocessing_test(testtime,process_num):	
	'多进程测试函数'
	# 计时
	start = time.time()
	# 初始化资源
	p = ml.Pool(processes=process_num)
	my_list = [int(testtime//process_num)] * process_num
	# 运算	
	temp_list = p.map_async(multiprocessing_mock,my_list)
	temp_list.wait()
	end = time.time()
	# print('实验次数：%d' % testtime)
	print('进程数：%d' % process_num)
	print('耗时：%f' % (end-start))
	# print('估计值：%f' % (sum(temp_list.get())/testtime))
	# print('实际值：%f' % (math.pi / 4))
	return process_num, end-start

def multithreading_mock(x,ans):
	'多线程蒙特卡罗模拟'
	n = 0
	for i in range(x):
		x = random.uniform(0,1)
		y = random.uniform(0,1)
		n += (x * x + y * y <= 1.0)
	ans.append(n)

def multithreading_test(testtime,thread_num):
	'多线程测试函数'
	start = time.time()
	x = int(testtime/thread_num)
	li = []
	ans = []
	for i in range(thread_num):
		t = th.Thread(target=multithreading_mock,args=(x,ans))
		t.start()
		li.append(t)
	for t in li:
		t.join()
	end = time.time()
	# print('实验次数：%d' % testtime)
	print('线程数：%d' % thread_num)
	print('耗时：%f' % (end-start))
	# print('估计值：%f' % (sum(temp_list.get())/testtime))
	# print('实际值：%f' % (math.pi / 4))

	return thread_num, end-start

def draw(x1,y1,x2,y2):
	'绘制折线图'
	plt.rcParams['font.family']=['STFangsong']
	plt.rcParams['axes.unicode_minus'] = False
	plt.title('蒙特卡罗模拟投点计算pi——性能测试结果')
	plt.xlabel('进程数（线程数）')
	plt.ylabel('时间/秒')
	plt.xticks(x1,[i for i in range(1,21)])
	plt.plot(x1,y1,'r',label='多进程')
	plt.plot(x2,y2,'b',label='多线程')
	plt.grid()
	plt.legend()
	plt.show()

def test(operate_time=100000,paint=1):
	'性能测试函数'
	x_multiprocessing = []
	y_multiprocessing = []
	x_multithreading = []
	y_multithreading = []

	for i in range(1,21):
		temp = multiprocessing_test(operate_time,i)
		x_multiprocessing.append(temp[0])
		y_multiprocessing.append(temp[1])

	for i in range(1,21):
		temp = multithreading_test(operate_time,i)
		x_multithreading.append(temp[0])
		y_multithreading.append(temp[1])
	
	if paint:
		draw(x_multiprocessing,y_multiprocessing,x_multithreading,y_multithreading)

test(1000000)

'当pool的个数恰好为机器的CPU内核数时，性能最优'
```

### 寻找素数

* 寻找每个数所需要的时间是不一样的，判定质数和非质数的时间差别很大
* 让任务数量与物理CPU数量（六核）保持一致，尽管默认使用超线程（12），但不会提供额外性能收益
* 解决方案
	* 串行验证
	* naive_pool
	* less\_naive_pool
		* 先用小因子串行验证，再pool 
	* manager.value标记
	* redis标记
	* rawvalue标记
	* mmap标记（最快）

### multiprocessing 共享numpy大数组
* 填坑

## 集群和工作队列

## 使用更少的RAM

## 现场教训