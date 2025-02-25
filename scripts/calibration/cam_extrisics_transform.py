import yaml
import numpy as np
from scipy.spatial.transform import Rotation as R
import sys

def load_yaml(file_path):
    """加载 YAML 文件并提取四元数和平移向量"""
    with open(file_path, 'r') as file:
        data = yaml.safe_load(file)
    quaternion = [
        data['transform']['rotation']['x'],
        data['transform']['rotation']['y'],
        data['transform']['rotation']['z'],
        data['transform']['rotation']['w']
    ]
    translation = [
        data['transform']['translation']['x'],
        data['transform']['translation']['y'],
        data['transform']['translation']['z']
    ]
    return quaternion, translation

def quaternion_to_matrix(quaternion, translation):
    """将四元数和平移向量转换为 4x4 变换矩阵"""
    rotation_matrix = R.from_quat(quaternion).as_matrix()
    transform_matrix = np.eye(4)
    transform_matrix[:3, :3] = rotation_matrix
    transform_matrix[:3, 3] = translation
    return transform_matrix

def format_output(inverse_matrix):
    """格式化输出 4x4 矩阵的逆矩阵"""
    output = []
    for i in range(3):  # 只取前 3 行
        output.extend(inverse_matrix[i, :3])  # 旋转矩阵部分
        output.append(inverse_matrix[i, 3])   # 平移部分
    return ' '.join(map(str, output))

def main(file_path):
    # 加载 YAML 文件
    quaternion, translation = load_yaml(file_path)
    
    # 构造 4x4 变换矩阵
    transform_matrix = quaternion_to_matrix(quaternion, translation)
    
    # 求逆矩阵
    inverse_matrix = np.linalg.inv(transform_matrix)
    
    # 格式化输出
    output_str = format_output(inverse_matrix)
    print(output_str)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <yaml_file>")
        sys.exit(1)
    
    # 获取传入的文件路径
    yaml_file = sys.argv[1]
    main(yaml_file)