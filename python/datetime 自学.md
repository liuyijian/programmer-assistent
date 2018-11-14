## datetime

### date对象
* 表示年月日

```python
'创建date对象'
'范围是（1，1，1）～（9999，12，31）'
date(year,month,day)
date.today()
date.fromtimestamp(timestamp)
date.fromordinal(ordinal)
'date对象属性'
d.year
d.month
d.day
'返回一个字符串，表示的日期格式与time.ctime()函数一般使用的格式相同'
d.ctime()
'返回'YYYY-MM-DD''
d.isoformat()
'返回星期几，1～7'
d.isoweekday()
'返回星期几，0～6'
d.weekday()
'返回新的date对象'
d.replace([year[, month[, day]]])
'返回字符串，与time.strftime()函数格式相同，仅用于1900年以后的日期'
d.strftime(format)
'将d转换为一个序数值'
d.toordinal()
```

### time对象
* 表示包含小时，分，秒，微秒的时间

```python
'创建time对象,tzinfo提供时区信息'
time(hour[,minute[,second[,microsecond[,tzinfo]]]])
'返回'HH:MM:SS.mmmmmm+HH:MM',若微秒为0，则省略微秒部分,若省略时区，则省略时区部分'
t.isoformat()
'同理'
t.replace([hour[, minute[, second[, microsecond[, tzinfo]]]]])
```

### datetime对象
* 表示日期和时间，是date和time的综合

```python
'创建datetime对象'
datetime(year,month,day[,hour[,minute[,second[,microsecond[,tzinfo]]]]])
datetime.combine(date,time)
datetime.fromordinal(ordinal) #此处ordinal是自datetime.min以来的整数天数的datetime对象，时间组件均置0，时区置0
datetime.fromtimestamp(timestamp[,tz])
datetime.now([tz])
datetime.utcnow()
'方法'
'拆成date和time对象'
d.date()
d.time() #不带时区
d.timetz() #带时区
```

### timedelta对象
* 表示两个日期或时间之间的差值

```python
'创建对象'
timedelta([days[, seconds[, microseconds[, milliseconds[, minutes[, hours[, weeks]]]]]]])
```

### 日期的数学运算

* td = date1 - date2
* date1 = date2 + td
* date1 < date2

### 日期与时间解析
* 解析日期字符串'Aug 23,2008'
* d = datetime.datetime.strptime(s,"%b %d,%Y")