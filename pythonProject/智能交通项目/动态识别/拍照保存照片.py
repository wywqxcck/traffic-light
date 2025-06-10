import cv2
import time
import numpy as np
#保存的路径
path = 'E:' #图像保存路径

def GetPicture():
    #拍照保存图像
    #打开一个窗口
    cv2.namedWindow('car')
    #调用摄像头
    car = cv2.VideoCapture(0)
    #将读取到的数据保存起来
    ret,frame = car.read()
    cv2.imwrite(path + '/123.jpg',frame)
    #释放摄像头
    car.release()







