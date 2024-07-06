#!/usr/bin/env python3

import jtop
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from jtop import jtop
import time
import sys

def cpu_gpu():
    global num_80_cpu, num_80_gpu
    with jtop() as jetson:
        total_cpu = jetson.cpu['total']
        print("------ TOTAL ------")
        for key, value in total_cpu.items():
            if key == 'idle':
                cpu_load = 100-value
                cpu.append(cpu_load)
                if cpu_load > 80:
                    num_80_cpu += 1
                print("cpu_load: ",cpu_load)
        gpu_load = jetson.gpu['ga10b']['status']
        for key, value in gpu_load.items():
            if key == 'load':
                gpu_load = value
                gpu.append(gpu_load)
                if gpu_load > 80:
                    num_80_gpu += 1
                print("gpu_load: ",gpu_load)
    return cpu, gpu

if __name__ == "__main__":
    model_name = sys.argv[1]
    time_test = int(sys.argv[2])
    plot_flag = 0
    if time_test is None:
        print("please input test time")
    cpu = []    
    gpu = []
    n = 0
    num_80_cpu = 0
    num_80_gpu = 0
    try:
        while True:
            n +=1
            # time.sleep(1)
            cpu,gpu= cpu_gpu()
            if n > time_test:

                break
    except KeyboardInterrupt:
        sys.exit(0)
    
    cpu_avg = round(sum(cpu)/len(cpu),2)
    gpu_avg = round(sum(gpu)/len(gpu),2)
    print("CPU avg load: ",cpu_avg)
    print("GPU avg load: ",gpu_avg)
    cpu_max = round(max(cpu),2)
    gpu_max = round(max(gpu),2)
    print("CPU max load: ",cpu_max)
    # if plot_flag =="on":
    plt.plot(cpu, label='CPU')
    plt.plot(gpu, label='GPU')
    plt.ylim(0,100)
    plt.title(f'{model_name} CPU and GPU load ')
    plt.xlabel('num')
    plt.ylabel('Load (%)')
    plt.legend(loc='upper left')
    plt.text(30,98,f"CPU 80%: {num_80_cpu},CPU avg:{cpu_avg}\nGPU 80%: {num_80_gpu},GPU avg:{gpu_avg}\nCPU max: {cpu_max}\nGPU max: {gpu_max}",horizontalalignment='left',verticalalignment='top',)
    plt.savefig(f"/home/nvidia/Desktop/{model_name}_cpu_gpu_load.png")
    plt.show()

   

