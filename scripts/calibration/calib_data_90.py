import numpy as np
from scipy.spatial.transform import Rotation as R

def quaternion_to_rotation_matrix(q):
    # 将四元数转换为旋转矩阵
    # 注意四元数的顺序是 [qx, qy, qz, qw]
    r = R.from_quat([q[0], q[1], q[2], q[3]])
    return r.as_matrix()

def convert_frd_to_flu_rotation_matrix(frd_matrix):
    # 定义 FRD 到 FLU 的转换矩阵
    frd_to_flu = np.array([
        [1, 0, 0],
        [0, -1, 0],
        [0, 0, -1]
    ])
    z_rotation = np.array([
        [0, -1, 0],
        [1, 0, 0],
        [0, 0, 1]
    ])
    # 将 FRD 旋转矩阵转换为 FLU 旋转矩阵
    #flu_matrix = np.dot(frd_matrix, frd_to_flu)
    flu_matrix_yaw90 = np.dot(frd_matrix, z_rotation)
    return flu_matrix_yaw90

def convert_odometry_to_lidar_calib(input_file, output_file):
    j = 0
    with open(input_file, 'r') as f:
        lines = f.readlines()
    with open(output_file, 'w') as f_out:
        for i, line in enumerate(lines):
            if (i % 10 != 0):
                continue
            else:    
                j += 1
                data = line.strip().split()
                index = j  # 第一列是从1开始的计数
                timestamp = float(data[1])
                x = float(data[2])  # UTM x
                y = float(data[3])  # UTM y
                z = float(data[4])  # UTM z
                qx = float(data[5])  # qx
                qy = float(data[6])  # qy
                qz = float(data[7])  # qz
                qw = float(data[8])  # qw

                # 将四元数转换为 FRD 旋转矩阵
                frd_rotation_matrix = quaternion_to_rotation_matrix([qx, qy, qz, qw])

                # 将 FRD 旋转矩阵转换为 FLU 旋转矩阵
                flu_rotation_matrix = convert_frd_to_flu_rotation_matrix(frd_rotation_matrix)

                # 提取 FLU 旋转矩阵的行
                row1 = flu_rotation_matrix[0]  # 第一行
                row2 = flu_rotation_matrix[1]  # 第二行
                row3 = flu_rotation_matrix[2]  # 第三行

                # 写入新文件
                f_out.write(f"{index} {row1[0]} {row1[1]} {row1[2]} {x} {row2[0]} {row2[1]} {row2[2]} {y} {row3[0]} {row3[1]} {row3[2]} {z}\n")

if __name__ == "__main__":
    input_file = "odometry_loc.txt"
    output_file = "lidar_calib.txt"
    convert_odometry_to_lidar_calib(input_file, output_file)
