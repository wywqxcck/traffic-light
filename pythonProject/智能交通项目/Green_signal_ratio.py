

# 驾驶员反应时间为1秒，汽车启动时间为2秒
REACTION_TIME = 1
START_TIME = 2

def optimize_green_ratio(north_south_traffic, east_west_traffic):
    # 总反应和启动时间
    total_setup_time = REACTION_TIME + START_TIME

    # 计算总车流量
    total_traffic = north_south_traffic + east_west_traffic

    # 计算绿信比
    north_south_green_ratio = north_south_traffic / total_traffic if total_traffic > 0 else 0.5
    east_west_green_ratio = east_west_traffic / total_traffic if total_traffic > 0 else 0.5

    # 最小周期时长，这里设为30秒
    min_cycle_time = 30

    # 计算每个方向的绿灯时长
    north_south_green_time = int(min_cycle_time * north_south_green_ratio - total_setup_time)
    east_west_green_time = int(min_cycle_time * east_west_green_ratio - total_setup_time)

    # 确保绿灯时长不为负
    north_south_green_time = max(0, north_south_green_time)
    east_west_green_time = max(0, east_west_green_time)

    # 调整剩余时间，保证总周期时间不变
    remaining_time = min_cycle_time - north_south_green_time - east_west_green_time - 2 * total_setup_time
    if remaining_time > 0:
        if north_south_green_time < east_west_green_time:
            north_south_green_time += remaining_time
        else:
            east_west_green_time += remaining_time

    return north_south_green_time, east_west_green_time