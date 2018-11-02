#queue
* queue模块实现了各种多生产者-多消费者队列，可用于执行的多个线程之间安全交换信息

##队列类

```python
import queue

#创建一个先进先出队列，maxsize是队列中可以放入的项的最大数量，省略参数或置为0，都将视为无穷大
q = queue.Queue([maxsize])
#创建一个后进先出队列
q = queue.LifoQueue([maxsize])
#创建一个优先级队列,其中项按照优先级从低到高依次排好，项是（priority，data）形式的元组，priority是一个数字
q = queue.PriorityQueue([maxsize])
```

##队列方法

```python
#返回队列大小，可能不准确
q.qsize()
#判空
q.empty()
#判满
q.full()
#将item放入队列，可选参数block默认为True，将阻塞至队列有空位能放进去为止，若设为False，则timeout默认为0，超时还没放进去，引发full异常
q.put(item[,block[,timeout]])
#从队列中删除一项，机制同put
q.get([block[,timeout]])
#队列中消费者用来指示对于项的处理结束
q.task_done()
#阻塞至队列所有项均被删除和处理为止
q.join()
```