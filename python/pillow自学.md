# pillow 自学笔记
***
读取图片

```python
>>> from PIL import Image
#打开图像，仅打开图像头，读取图像格式，模式，大小等数据，操作较快，与图片大小和压缩方式无关，到必须调用时才加载所有内容
>>> im = Image.open('face.jpg')
#从打开的文件中读取
>>> with open('face.jpg','rb') as fp:
		im = Image.open(fp)
#从字符串中读取
>>> import StringIO
>>> im = Image.open(StringIO.StringIO(buffer))
#从压缩文件中读取
>>> from PIL import Image,TarIO
>>> fp = TarIO.TarIO('face.tar','face.jpg')
>>> im = Image.open(fp)
```
基本操作

```python
#图片格式，若不是从文件中读取，则为None
>>> im.format
	'JPEG'
#图片像素大小，长*宽
>>> im.size
	(775,348)
#图片模式:
1：1位像素，表示黑和白，但是存储的时候每个像素存储为8bit。
L：8位像素，表示黑和白。
P：8位像素，使用调色板映射到其他模式。
RGB：3x8位像素，为真彩色。
RGBA：4x8位像素，有透明通道的真彩色。
CMYK：4x8位像素，颜色分离。
YCbCr：3x8位像素，彩色视频格式。
I：32位整型像素。
F：32位浮点型像素
>>> im.mode
	'RGB'
'''
存储图像相关数据的字典。文件句柄使用该字典传递从文件中读取的各种非图像信息。
大多数方法在返回新的图像时都会忽略这个字典；因为字典中的键并非标准化的，
对于一个方法，它不能知道自己的操作如何影响这个字典。
如果用户需要这些信息，需要在方法open()返回时保存这个字典。
'''
>>> im.info
	{'exif': b'Exif\x00\x00II*\x00\x08\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00', 'dpi': (72, 72), 'adobe': 100, 'adobe_transform': 100}
#改变图片模式,任一支持格式可与'L','RGB'进行互转
>>> im.convert('L')
#保存临时文件并展示图片
>>> im.show()
#以另一种格式保存图像
>>> im.save('face_save.png','png')
```
拼接图像

```python
#图像中截取一个小框,参数为(left，upper，right，lower)
>>> box = (100,100,200,200)
>>> region = im.crop(box)
#执行剪裁操作，否则，到必要时才执行
>>> region.load()
#展示区域图像
>>> region.show()
#处理小区域，逆时针旋转90度，以下两种皆可,第一种可为90，180，270
>>> region = region.transpose(Image.ROTATE_90)
>>> region = region.rotate(90)
#处理小区域,第一个为竖轴轴对称，第二个为横轴轴对称
>>> region = region.transpose(Image.FLIP_LEFT_RIGHT)
>>> region = region.transpose(Image.FLIP_TOP_BOTTOM)
#
#把处理好的区域贴回去，大小必须精确匹配，透明度为可选参数，值为0～255之间的整数，其中0为透明
>>> im.paste(region,box)
#展示拼接好的图像
>>> im.show()
#分离rgb值，每一个都能展示为灰度图，对灰度图用split(),返回自身
>>> r, g, b = im.split()
#合成图像,此图rgb不对应
>>> im = Image.merge('RGB',(b,g,r))
'''
改变图片尺寸,默认使用nearest滤波器
Image.NEAREST：最近滤波。从输入图像中选取最近的像素作为输出像素。它忽略了所有其他的像素。
Image.BOX：源图像的每个像素贡献到具有相同权重的目的地图像的一个像素。3.4.0
Image.BILINEAR：双线性滤波。在输入图像的2x2矩阵上进行线性插值。注意：PIL的当前版本，做下采样时该滤波器使用了固定输入模板。
Image.HAMMING：比box精细一点，3.4.0
Image.BICUBIC：双立方滤波。在输入图像的4x4矩阵上进行立方插值。注意：PIL的当前版本，做下采样时该滤波器使用了固定输入模板。
Image.ANTIALIAS：平滑滤波。对所有可以影响输出像素的输入像素进行高质量的重采样滤波，以计算输出像素值。1.1.3（在官网文档中没有，但可以用？？？）
Image.LANCZOS:高质量滤波 1.1.3

质量 NEAREST<BOX<BILINEAR<HAMMING<BICUBIC<LANCZOS
'''
#默认使用Image.NEAREST滤波器
>>> im = im.resize((128,128))
#使用Image.ANTIALIAS滤波器
>>> im = im.resize((128,128),Image.ANTIALIAS)
```
图像处理

```python
#变白
>>> out = im.point(lambda i : i * 1.2)
>>> out.show()
#增红减绿
>>> source = im.split()
>>> mask = source[0].point(lambda i: i < 100 and 255)
>>> out = source[1].point(lambda i: i * 0.7)
>>> source[1].paste(out,None,mask)
>>> im = Image.merge(im.mode,source)
>>> im.show()
#图像序列处理，支持FLI/FLC/GIF等动图格式
>>> from PIL import ImageSequence
>>> for frame in ImageSequence.Iterator(im):
		# do something to frame 
```
ImageFile类库

```python
#用于网络流传输
from PIL import ImageFile
fp = open('face.jpg', 'rb')
p = ImageFile.Parser()
while 1:
    s = fp.read(1024)
    if not s:
        break
    p.feed(s)
im = p.close()
im.save('copy.jpg')
```
<a href = 'https://pillow.readthedocs.io/en/5.2.x/reference/ImageDraw.html'>
ImageDraw类库</a>

ImageEnhance类库

```python
>>> from PIL import ImageEnhance
#增强颜色
>>> enh = ImageEnhance.Color(im)
>>> enh.enhance(1.3).show('30% more color')
#增强对比度
>>> enh = ImageEnhance.Contrast(im)
>>> enh.enhance(1.3).show('30% more contrast')
#增强亮度
>>> enh = ImageEnhance.Brightness(im)
>>> enh.enhance(1.3).show('30% more bright')
#增强锐度
>>> enh = ImageEnhance.Sharpness(im)
>>> enh.enhance(1.3).show('30% sharper')
```
ImageFilter类库

```python
>>> from PIL import ImageFilter
#模糊化
>>> im.filter(ImageFilter.BLUR).show()
#白底黑轮廓，黑底白轮廓 
>>> im.filter(ImageFilter.CONTOUR).show()
>>> im.filter(ImageFilter.FIND_EDGES).show()
#细节加强
>>> im.filter(ImageFilter.DETAIL).show()
#边缘强化
>>> im.filter(ImageFilter.EDGE_ENHANCE).show()
>>> im.filter(ImageFilter.EDGE_ENHANCE_MORE).show()
#浮雕
>>> im.filter(ImageFilter.EMBOSS).show()
#锐度
>>> im.filter(ImageFilter.SHARPEN).show()
>>> im.filter(ImageFilter.SMOOTH).show()
>>> im.filter(ImageFilter.SMOOTH_MORE).show()
```

后记打印（用于postscript打印机,不明觉厉）

```python
from PIL import Image
from PIL import PSDraw

im = Image.open("face.jpg")
title = "hopper"
box = (1*72, 2*72, 7*72, 10*72) # in points

ps = PSDraw.PSDraw() # default is sys.stdout
ps.begin_document(title)

# draw the image (75 dpi)
ps.image(box, im, 75)
ps.rectangle(box)

# draw title
ps.setfont("HelveticaNarrow-Bold", 36)
ps.text((3*72, 4*72), title)

ps.end_document()
```

<a href = 'https://pillow.readthedocs.io/en/5.2.x/handbook/image-file-formats.html'>Image类支持的图片格式列表及操作</a>
