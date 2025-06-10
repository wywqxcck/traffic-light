import serial
import East
import Sorth
# import E_Count
# import S_Count

""" '#':代表南北   '*':代表东西 """



def n_s():  # 南北口检测
    num = Sorth.read()
    return num


def e_w():  # 东西口检测
    num = East.read()
    return num






















def asd(k):
    data_s = 0

    if k == 1:
        data_s = b'G05R05#'  # 绿5红5
    elif k == 2:
        data_s = b'G20R05#'  # 绿5红20
    elif k == 3:
        data_s = b'G05R20#'  # 绿20红5
    elif k == 4:
        data_s = b'G13R12#'  # 绿13红12
    # print("k:", k)
    ser.write(data_s)  # 串口写数据


def contrast(num_data):
    if (num_data[1] == 0 and num_data[0] == 0) or (num_data[1] < 5 and Num_Data[0] < 5):
        print("正常行驶")
        asd(1)
    elif num_data[1] >= 5 and num_data[0] < 5:
        print("东西路口车较多")
        asd(2)
    elif num_data[1] < 5 and num_data[0] >= 5:
        print("南北车较多")
        asd(3)
    elif num_data[1] >= 5 and num_data[0] >= 5:
        print("东西南北路口车都较多")
        asd(4)
    # print("num_data=")
    # print(num_data)




ser = serial.Serial('COM5', 115200)
if ser.isOpen():
    print("串口打开成功")
    Num_Data = [-1, -1]
    # time = 0
    # time1 = 0
else:
    print("串口打开失败")
    exit(0)

while True:
    data = ser.read(1)
    date_r = data.decode()
    if date_r == '#':  # 南北.
        # time += 1
        # print("time:", time)
        # if time == 2:
        print("开始检测南北")
        Num_Data[0] = n_s()
        # print("南北车辆：", Num_Data[0])
        # time = 0
    elif date_r == '*':  # 东西
        # time1 += 1
        # print("time1:", time1)
        # if time1 == 3:
        print("开始检测东西")
        Num_Data[1] = e_w()
        # print("东西车辆：", Num_Data[1])
            # time1 = 0


    if Num_Data[0] != -1 and Num_Data[1] != -1:
        # print("开始发送")
        contrast(Num_Data)
        Num_Data[0] = Num_Data[1] = -1
    date_r = 0
