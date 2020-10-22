import numpy as np
from PIL import Image

with open("Lena(512x512).RGB", 'rb') as fid:
    data_array=np.fromfile(fid, np.uint8, count=512*512*3)

print(data_array.shape)

RGB=np.zeros(shape=(512*512, 3))
for i in range(0, 512*512):
    RGB[i][0]=data_array[i]
    RGB[i][1]=data_array[512*512+i]
    RGB[i][2]=data_array[512*512*2+i]

print(RGB.shape)

RGB3D=np.zeros(shape=(512, 512, 3))
for i in range(0, 512):
    for j in range(0, 512):
        RGB3D[i][j][0]=RGB[(512*i)+j][0]
        RGB3D[i][j][1]=RGB[(512*i)+j][1]
        RGB3D[i][j][2]=RGB[(512*i)+j][2]

print(RGB3D.shape)

Image.fromarray(RGB3D.astype('uint8'), mode='RGB').save('./RGB3D.png')

RGB3D=RGB3D.transpose(2, 0, 1)

r=RGB3D[0]
g=RGB3D[1]
b=RGB3D[2]

y=0.299*r+0.587*g+0.114*b
cb=-0.168636*r+0.232932*g-0.064296*b
cr=0.499813*r-0.418531*g-0.081282*b
c=y-16
d=cb-128
e=cr-128
r2=1*y+1.13983*cr
g2=1*y-0.39465*cb-0.5806*cr
b2=1*y+2.03211*cb

RGBtoYUV=np.zeros(shape=(3, 512, 512))

RGBtoYUV[0]=y
RGBtoYUV[1]=cb
RGBtoYUV[2]=cr

YUVtoRGB=np.zeros(shape=(3, 512, 512))

YUVtoRGB[0]=r2
YUVtoRGB[1]=g2
YUVtoRGB[2]=b2

RGBtoYUV=RGBtoYUV.transpose(1, 2, 0)
YUVtoRGB=YUVtoRGB.transpose(1, 2, 0)

RGBtoYUV[RGBtoYUV<0]=0
RGBtoYUV[RGBtoYUV>255]=255

YUVtoRGB[YUVtoRGB<0]=0
YUVtoRGB[YUVtoRGB>255]=255

print(RGBtoYUV.shape)
print(YUVtoRGB.shape)

Image.fromarray(RGBtoYUV.astype('uint8'), mode='RGB').save('./RGBtoYUV.png')
Image.fromarray(YUVtoRGB.astype('uint8'), mode='RGB').save('./YUVtoRGB.png')