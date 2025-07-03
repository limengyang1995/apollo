import time
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from jtop import jtop

# 初始化数据
cpu_usage = []
gpu_usage = []
timestamps = []
avg_cpu_usage = []
max_cpu_usage = []
avg_gpu_usage = []
max_gpu_usage = []
memory_usage = []

# 创建一个包含三个横向排列子图的图表
fig, (ax1, ax2, ax3) = plt.subplots(1, 3, figsize=(15, 5))

# 更新数据的函数
def update_data(frame):
    current_time = time.time()
    
    with jtop() as jetson:
        # 获取 CPU 和 GPU 使用率
        cpu = 100-jetson.cpu['total']['idle']  # 根据实际的 jtop 数据结构调整
        gpu = jetson.gpu['ga10b']['status']['load']  # 根据实际的 jtop 数据结构调整
        memory = jetson.memory['RAM']['used'] / jetson.memory['RAM']['tot'] * 100  # 计算内存使用率百分比

    cpu_usage.append(cpu)
    gpu_usage.append(gpu)
    memory_usage.append(memory)
    timestamps.append(current_time)

    # 只保留最近 60 秒的数据
    if len(timestamps) > 60:
        cpu_usage.pop(0)
        gpu_usage.pop(0)
        memory_usage.pop(0)
        timestamps.pop(0)

    # ���新图表
    ax1.clear()
    ax2.clear()
    ax3.clear()

    ax1.plot(timestamps, cpu_usage, label='CPU Usage (%)', marker='o')
    ax2.plot(timestamps, gpu_usage, label='GPU Usage (%)', marker='o')
    ax3.plot(timestamps, memory_usage, label='Memory Usage (%)', color='purple', marker='o')

    # 只在最新的数据点上标注数值
    if len(timestamps) > 0:
        i = -1  # 最后一个数据点的索引
        ax1.annotate(f'{cpu_usage[i]:.1f}', (timestamps[i], cpu_usage[i]), textcoords="offset points", xytext=(0,10), ha='center')
        ax2.annotate(f'{gpu_usage[i]:.1f}', (timestamps[i], gpu_usage[i]), textcoords="offset points", xytext=(0,10), ha='center')
        ax3.annotate(f'{memory_usage[i]:.1f}', (timestamps[i], memory_usage[i]), textcoords="offset points", xytext=(0,10), ha='center')

    # 设置坐标轴范围和标签
    for ax in [ax1, ax2, ax3]:
        ax.set_ylim(0, 100)
        ax.set_xlabel('Time (s)')
        ax.set_ylabel('Usage (%)')
        ax.legend()

    ax1.set_title('CPU Usage Over Time')
    ax2.set_title('GPU Usage Over Time')
    ax3.set_title('Memory Usage Over Time')

    plt.tight_layout()

# 创建动画
ani = FuncAnimation(fig, update_data, interval=1000)  # 每秒更新一次

# 显示图表
plt.show()
