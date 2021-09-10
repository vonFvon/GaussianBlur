## Gaussian Blur with C Language

------

This programming file is for studying purpose. Before reading in great details, you had better know the related algorithm about gaussian blur filter on images. The reference is enclosed as below.

Remark : Kernel size is 3 x 3. Sigma is 1.5.

### Preparatory Knowledge

1. a Simple Version of Introduction to Gaussian Blur - edited by Ruan

- Gaussian Blur Algorithm : https://www.ruanyifeng.com/blog/2012/11/gaussian_blur.html

2. a Detailed Version of Introduction to Gaussian Blur - from Zhihu

- Gaussian Blur Theory : https://zhuanlan.zhihu.com/p/373560257

### Bitmap Illustration

Before processing images, you had better be familiar with BMP file format. The below structure of the Bitmap Image File is for your reference. By the way, BMP is uncompressed. It is a good starting point to study.

< Please check bmp.png. >

And you can read more via the below linkage.

[BMP file format]: https://en.wikipedia.org/wiki/BMP_file_format

### How to Run in Ubuntu

1. In debug mode, please run the following command and get a.out. You can print results from intermediate process after execute a.out.
> gcc -DDEBUG codingFileName.c
- When 'error: undefined reference to ceil or floor or pow' shows, please run the below command.
> gcc -DDEBUG codingFileName.c -lm

2. In production environment, please run the following command and get a.out.
> gcc codingFileName.c
- When 'error: undefined reference to ceil or floor or pow' shows, please run the below command.
> gcc codingFileName.c -lm

3. After getting a.out, you can make gaussian blur operation.
> a.out souceImageFileName.bmp destinationImageFileName.bmp

### Results Display

- Original Picture

< Please check rgb.bmp. >

- Processed Picture by C

< Please check test.bmp. >

It is found that there exists obscure, but not significantly.

### Contrast Test

It is known that OpenCV provides a real-time optimized Computer Vision library and tools, including API - cv2.GaussianBlur(). The below python program also can create a Gaussian Blur image for check.

Remark : Kernel size is 3 x 3. Sigma is 1.5.

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

< The result is the same as test.bmp. >
