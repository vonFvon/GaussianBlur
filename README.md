## Gaussian Blur with C Language

------

This programming file is for ==studying purpose==. Before reading in great details, you had better know the related algorithm about gaussian blur filter on images. The reference is enclosed as below.

### Preparatory Knowledge

1. a Simple Version of Introduction to Gaussian Blur - edited by Ruan

[Gaussian Blur Algorithm]: https://www.ruanyifeng.com/blog/2012/11/gaussian_blur.html

2. a Detailed Version of Introduction to Gaussian Blur - from Zhihu

[Gaussian Blur Theory]: https://zhuanlan.zhihu.com/p/373560257

### Bitmap Illustration

Before processing images, you had better be familiar with BMP file format. The below structure of the Bitmap Image File is for your reference. By the way, BMP is uncompressed. It is a good starting point to study.

<img src="I:\03_C++_名企研发工程师领航就业计划_kaikeba\bmp intro.png" alt="bmp intro" style="zoom:67%;" />

And you can read more via the below linkage.

[BMP file format]: https://en.wikipedia.org/wiki/BMP_file_format

### Results Display

- Original Picture

<img src="C:\Users\von\AppData\Roaming\Typora\typora-user-images\image-20210909151354976.png" alt="image-20210909151354976" style="zoom:50%;" />

- Processed Picture by C

<img src="C:\Users\von\AppData\Roaming\Typora\typora-user-images\image-20210909151138836.png" alt="image-20210909151138836" style="zoom:50%;" />

It is found that there exists obscure, but not significantly.

### Contrast Test

It is known that OpenCV provides a real-time optimized Computer Vision library and tools, including API - cv2.GaussianBlur(). The below python program also can create a Gaussian Blur image for check.

```python
import cv2

# read and show source image file
img = cv2.imread('rgb.bmp')
cv2.imshow('img', img)
cv2.waitKey(0)
cv2.destroyAllWindows()
# Gaussian Blur
aussian = cv2.GaussianBlur(img, (3, 3), 1.5)
# show destination image
cv2.imshow('aussian', aussian)
cv2.waitKey(0)
cv2.destroyAllWindows()
```

- Processed Picture by Python

<img src="C:\Users\von\AppData\Roaming\Typora\typora-user-images\image-20210909152549322.png" alt="image-20210909152549322" style="zoom:50%;" />