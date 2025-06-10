import cv2
import datetime

def read():
    # 捕获外接摄像头
    cap = cv2.VideoCapture(1)

    # 校验摄像头是否捕获成功，如果未成功则输出提示
    if not cap.isOpened():
        print("无法打开摄像头")
        exit()
    # 获取摄像头中的每一帧
    i = 5
    while i>0:
        i -= 1
        ret, frame = cap.read()

        # 检验画面帧是否正确捕获，如果未成功则输出提示，跳出循环
        if not ret:
            print("未获取画面帧")

        cv2.imwrite(str(3) + '.jpg', frame)

    # # 创建mog对象
    # mog = cv2.createBackgroundSubtractorMOG2()
    # 形态学kernel（返回指定形状和尺寸（RECT是矩形、ELLIPSE椭圆））
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 5))


    # # 画线(*****更改*****)
    # line_hight = 550
    # # 偏移量
    # offset = 6

    # 定义车辆数量的数组
    cars = []
    # 统计车辆数量
    carsum = 0
    # 把读取的帧灰度化
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    # 二值分类
    ret, frame = cv2.threshold(gray, 60, 255, cv2.THRESH_BINARY)  # 二值分类调整这里
    # 高斯去噪
    gauss = cv2.GaussianBlur(frame, (3, 3), 5)  # 高斯滤波器，高斯内核5像素，
    # 应用mog
    # mask = mog.apply(gauss)
    # 腐蚀操作（将动态的也就是读到的白色景腐蚀掉5*5像素的外沿）
    erosion = cv2.erode(gauss, kernel)
    # 膨胀，还原回来（将腐蚀后的图片中的白色景边缘膨胀5*5）
    dialte = cv2.dilate(erosion, kernel, 3)
    # 闭运算（削去内部不连接的地方）
    close = cv2.morphologyEx(dialte, cv2.MORPH_CLOSE, kernel)
    close = cv2.morphologyEx(close, cv2.MORPH_CLOSE, kernel)
    cv2.imwrite(str(4) + ".jpg", close)
    # 查找轮廓
    contours, _ = cv2.findContours(close, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)  # 找外层轮廓（从大到小，从右至左），近似轮廓
    # # 画出检测线（*****更改*****）
    # cv2.line(frame, (0, line_hight), (1200, line_hight), (255, 0, 0))  # 起始点，颜色

    # 画出所有检测出来的轮廓
    for contour in contours:
        # 外接矩形
        (x, y, w, h) = cv2.boundingRect(contour)
        # 过滤小框（通过外接矩形的宽高来过滤掉小矩形）
        is_valid = (w >= 30) and (h >= 30) and (w<200) and (h<200)
        if not is_valid:
            continue

        # 能走到这里来的都是符合要求的
        # 画矩形(要求全为整数)
        cv2.rectangle(frame, (int(x), int(y)), (int(x + w), int(y + h)), (0, 0, 255), 2)
        # 把车抽象为一点（外接矩形的中心点（通过外接矩形计算中心点））
        # 得到中点
        cpoint = (x + int(w / 2), y + int(h / 2))
        cars.append(cpoint)  # 过来车放入数组
        # 画出中心点来
        cv2.circle(frame, (cpoint), 5, (0, 0, 255), -1)
        for (x, y) in cars:
            # if y > (line_hight - offset) and y < (line_hight + offset):
            # 中心点在有效区间（计数加1）
            carsum += 1
            print('sorth.x,y:', carsum, x, y)
            # 记过的车从数组中去掉
            cars.remove((x, y))
    cap.release()
    return carsum
    cv2.destroyAllWindows()
