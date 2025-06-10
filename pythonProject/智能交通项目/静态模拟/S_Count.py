
"""
EasyDL 物体检测 调用模型公有云API Python3实现
"""

import json
import base64
import requests
import cv2
"""
使用 requests 库发送请求
使用 pip（或者 pip3）检查我的 python3 环境是否安装了该库，执行命令
  pip freeze | grep requests
若返回值为空，则安装该库
  pip install requests
"""


def read():
    # 捕获摄像头，传入摄像头索引号，默认摄像头索引为0
    cap = cv2.VideoCapture(1)

    # 校验摄像头是否捕获成功，如果未成功则输出提示
    if not cap.isOpened():
        print("无法打开摄像头")
        exit()

    # 无限循环，直到触发break跳出
    # 获取摄像头捕获的画面帧，返回ret和frame
    # ret的True/False反映是否捕获成功，frame是画面
    i = 1
    while i > 0:
        i -= 1
        ret, frame = cap.read()

        # 检验画面帧是否正确捕获，如果未成功则输出提示，跳出循环
        if not ret:
            print("未获取画面帧")

        cv2.imwrite(str(1) + ".jpg", frame)
        cv2.destroyAllWindows()
        return S_Count()


def S_Count():
    # 目标图片的 本地文件路径，支持jpg/png/bmp格式
    IMAGE_FILEPATH = "./1.jpg"

    # 可选的请求参数
    # threshold: 默认值为建议阈值，请在 我的模型-模型效果-完整评估结果-详细评估 查看建议阈值
    PARAMS = {"threshold": 0.65}

    # 服务详情 中的 接口地址
    MODEL_API_URL = "https://aip.baidubce.com/rpc/2.0/ai_custom/v1/detection/Training_Model"

    # 调用 API 需要 ACCESS_TOKEN。若已有 ACCESS_TOKEN 则于下方填入该字符串
    # 否则，留空 ACCESS_TOKEN，于下方填入 该模型部署的 API_KEY 以及 SECRET_KEY，会自动申请并显示新 ACCESS_TOKEN
    ACCESS_TOKEN = ""  # 【您的ACESS_TOKEN】
    API_KEY = "d8a1bvzeD39b5HafeCwZNURL"
    SECRET_KEY = "IqtUNuU7FOF6gBZhJe2CcEskDFmaEHX4"

    # print("1. 读取目标图片 '{}'".format(IMAGE_FILEPATH))
    with open(IMAGE_FILEPATH, 'rb') as f:
        base64_data = base64.b64encode(f.read())
        base64_str = base64_data.decode('UTF8')
    # print("将 BASE64 编码后图片的字符串填入 PARAMS 的 'image' 字段")
    PARAMS["image"] = base64_str

    if not ACCESS_TOKEN:
        # print("2. ACCESS_TOKEN 为空，调用鉴权接口获取TOKEN")
        auth_url = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials""&client_id={}&client_secret={}".format(API_KEY, SECRET_KEY)
        auth_resp = requests.get(auth_url)
        auth_resp_json = auth_resp.json()
        ACCESS_TOKEN = auth_resp_json["access_token"]
        print("新 ACCESS_TOKEN: {}".format(ACCESS_TOKEN))
    else:
        print("2. 使用已有 ACCESS_TOKEN")
        pass

    # print("3. 向模型接口 'MODEL_API_URL' 发送请求")
    request_url = "{}?access_token={}".format(MODEL_API_URL, ACCESS_TOKEN)
    response = requests.post(url=request_url, json=PARAMS)
    response_json = response.json()
    response_str = json.dumps(response_json, indent=4, ensure_ascii=False)
    count = 0
    for i in range(len(response_str)):
        if response_str[i] == "C" and response_str[i + 1] == "a" and response_str[i + 2] == "r":
            count += 1
    print(count)

    print("结果:{}".format(response_str))
    return count