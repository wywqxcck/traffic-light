import cv2
import datetime

def read():
    # 捕获摄像头，传入摄像头索引号，默认摄像头索引为0
    cap = cv2.VideoCapture(0)

    # 校验摄像头是否捕获成功，如果未成功则输出提示
    if not cap.isOpened():
        print("无法打开摄像头")
        exit()

    # 无限循环，直到触发break跳出
    # 获取摄像头捕获的画面帧，返回ret和frame
    # ret的True/False反映是否捕获成功，frame是画面
    i = 5
    while i > 0:
        i -= 1
        ret, frame = cap.read()

        # 检验画面帧是否正确捕获，如果未成功则输出提示，跳出循环
        if not ret:
            print("未获取画面帧")

        cv2.imwrite(str(1) + ".jpg", frame)
    # 定义车辆数量的数组
    cars = []
    # 统计车的数量
    car_sum = 0
    numbcar = 0

    # 形态学kernel
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))  # 返回指定形状和尺寸（RECT是矩形、ELLIPSE椭圆）

    # 灰度处理
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # 二值分类调整这里
    ret, frame = cv2.threshold(gray, 80, 255, cv2.THRESH_BINARY)

    # 高斯去噪
    gauss = cv2.GaussianBlur(frame, (3, 3), 5)  # 高斯滤波：原图像、高斯核、标准差5

    erode = cv2.erode(gauss, kernel)

    # 膨胀
    dilate = cv2.dilate(erode, kernel, 3)
    # 闭操作=膨胀+腐蚀（去除图形内部噪声）
    close = cv2.morphologyEx(dilate, cv2.MORPH_CLOSE, kernel)
    close = cv2.morphologyEx(close, cv2.MORPH_CLOSE, kernel)
    cv2.imwrite(str(2) + ".jpg", close)

    # cv2.imshow('window_title', frame)
    # key=cv2.waitKey()
    # 查找轮廓
    contours, _ = cv2.findContours(close, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)  # CV_RETR_TREE ：返回所有轮廓，建立完整的层次结构
    # # 画出检测线（*****更改*****）
    # cv2.line(frame, (0, line_hight), (1200, line_hight), (255, 0, 0))  # 起始点，颜色
    # 画出所有检测出来的轮廓
    for (i, c) in enumerate(contours):
        (x, y, w, h) = cv2.boundingRect(c)  # 计算轮廓的垂直边界最小矩形
        # 过滤小的检测框
        is_valid = (w >= 10) and (h >= 30) and (w<200) and (h<200)
        if (not is_valid):
            continue
        # 能走到这里来的都是符合要求的
        # 画矩形(要求全为整数)
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 0, 255), 2)
        # 中心点位置
        cpoint = (x + int(w / 2), y + int(h / 2))
        cars.append(cpoint)  # 存入矩形
        cv2.circle(frame, (cpoint), 5, (0, 0, 255), -1)  # 画圆
        # print("当天该方向总共通过车辆", numbcar, "个")
        for (x, y) in cars:
            # if y > (line_hight - offset) and y < (line_hight + offset):
            # 中心点在有效区间（计数加1）
            car_sum += 1
            numbcar += 1
            print('east_car.x,y::',car_sum,x,y)
            # 记过的车从数组中去掉
            cars.remove((x, y))
    cap.release()
    return numbcar
    cv2.destroyAllWindows()
