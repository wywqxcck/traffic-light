import cv2
import numpy as np
def read(a):
    # 形态学识别车辆
    cap = cv2.VideoCapture(a)
    # 创建mog对象
    mog = cv2.createBackgroundSubtractorMOG2()
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))

    # 取框范围(*****更改*****)
    min_w = 100
    min_h = 90
    # 画线(*****更改*****)
    line_hight = 550
    # 偏移量
    offset = 6
    # 车辆数量
    carsum = 0

    # 计算外接矩形中心点
    def center(x, y, w, h):
        x1 = int(w / 2)
        y1 = int(h / 2)
        cx = x + x1
        cy = y + y1
        return cx, cy

    # 定义车辆数量的数组
    cars = []
    # 循环读取视频
    while True:
        ret, frame = cap.read()
        # 设置窗口大小
        # cv2.namedWindow("North_car", cv2.WINDOW_NORMAL)
        # cv2.resizeWindow("North_car", 800, 600)

        if ret == True:
            # 把读取的帧灰度化
            gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
            # 去噪
            gauss = cv2.GaussianBlur(gray, (3, 3), 5)  # 高斯滤波器，高斯内核5像素，
            # median = cv2.medianBlur(gray, 5)  # 中值滤波器，内核为5（适合处理比较均匀的噪声）
            # 应用mog
            capmask = mog.apply(gauss)

            # 腐蚀操作（将动态的也就是读到的白色景腐蚀掉5*5像素的外沿）
            erosion = cv2.erode(capmask, kernel)
            # 膨胀，还原回来（将腐蚀后的图片中的白色景边缘膨胀5*5）
            dialte = cv2.dilate(erosion, kernel, iterations=2)

            # 削去内部不连接的地方（闭运算）
            close = cv2.morphologyEx(dialte, cv2.MORPH_CLOSE, kernel)

            # 查找轮廓
            contours, result = cv2.findContours(close, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)  # 找外层轮廓（从大到小，从右至左），近似轮廓

            # 画出检测线（*****更改*****）
            cv2.line(frame, (0, line_hight), (1200, line_hight), (255, 0, 0))  # 起始点，颜色

            # 画出所有检测出来的轮廓
            for contour in contours:
                # 外接矩形
                (x, y, w, h) = cv2.boundingRect(contour)
                # 过滤小框（通过外接矩形的宽高来过滤掉小矩形）
                is_valid = (w >= min_w) and (h >= min_h)
                if not is_valid:
                    continue

                # 能走到这里来的都是符合要求的
                # 画矩形(要求全为整数)
                cv2.rectangle(frame, (int(x), int(y)), (int(x + w), int(y + h)), (0, 0, 255), 2)

                # 把车抽象为一点（外接矩形的中心点（通过外接矩形计算中心点））
                # 得到中点
                cpoint = center(x, y, w, h)
                cars.append(cpoint)  # 过来车放入数组
                # 画出来
                cv2.circle(frame, (cpoint), 5, (0, 0, 255), -1)
                # 判断汽车是否过检测线
                for (x, y) in cars:
                    if y > (line_hight - offset) and y < (line_hight + offset):
                        # 中心点在有效区间（计数加1）
                        carsum += 1
                        # 检测每辆车外接矩形坐标
                        print("North_car ",carsum,"x,y:",x,y)
                        # 记过的车从数组中去掉
                        cars.remove((x, y))

            # cv2.imshow('erosion',erosion)
            # cv2.imshow('dilate', dialte)
            # cv2.imshow('close', close)
            # 显示车辆计数信息
            cv2.putText(frame, 'North Count:' + str(carsum), (0, 60), cv2.FONT_HERSHEY_SIMPLEX, 2, (255, 0, 0),
                        5)  # 位置，字体，大小，颜色，线的粗细
            cv2.imshow('North_car', frame)

        Key = cv2.waitKey(10)
        if Key == ord('0'):
            print("南北方向车流量为",carsum,"辆")
            break
    # 释放资源
    cap.release()
    cv2.destroyAllWindows()
    return carsum
