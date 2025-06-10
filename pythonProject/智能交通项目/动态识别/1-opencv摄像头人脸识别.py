import numpy as np
import cv2

if __name__ == '__main__':
    cap = cv2.VideoCapture(0)#打开本地摄像头
    face_detecter = cv2.CascadeClassifier('./haarcascade_frontalface_alt.xml')
    while True:
        ret,frame = cap.read()
        if not ret:
            break
        gray = cv2.cvtColor(frame,code=cv2.COLOR_BGR2GRAY)
        faces = face_detecter.detectMultiScale(gray,scaleFactor=1.1,minNeighbors=10)
        for x,y,w,h in faces:
            cv2.rectangle(frame,
                          pt1=(x,y),
                          pt2=(x+w,y+h),
                          color=[0,0,255],
                          thickness=2)
        cv2.imshow('cap',frame)
        key = cv2.waitKey(1000//24)#等待时间整数，时间是毫秒，最小为1毫秒
        if key == ord('q'):
            break
    cap.release()
    cv2.destroyAllWindows()
