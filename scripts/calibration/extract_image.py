import os

import sys

#from cyber.python.cyber_py3.record import RecordReader
from cyber_record.record import Record
from record_msg.parser import ImageParser

#from modules.tools.sensor_calibration.sensor_msg_extractor import ImageParser   



def save_images_from_record(record_file, camera_topics, output_dirs):

    """

    从record文件中读取指定相机的图像并保存到指定文件夹中。



    :param record_file: record文件路径

    :param camera_topics: 相机topic列表

    :param output_dirs: 保存图像的文件夹路径列表

    """

    # 确保输出文件夹存在

    for output_dir in output_dirs:

        if not os.path.exists(output_dir):

            os.makedirs(output_dir)



    # 打开record文件

    reader = Record(record_file)








    # 遍历record文件中的消息

    for channel_name, msg, timestamp in reader.read_messages():

        if channel_name in camera_topics:

            # 解析图像
            output_dir = output_dirs[camera_topics.index(channel_name)]
            # 初始化ImageParser
            image_parser = ImageParser(output_path=output_dir)

            image = image_parser.parse(msg)

            # if image is not None:

            #     # 获取相机对应的输出文件夹

                

            #     # 保存图像

            #     image_path = os.path.join(output_dir, f"{timestamp}.jpg")

            #     image.save(image_path)

            #     print(f"Saved image to {image_path}")



    # 关闭record文件

    reader.close()



if __name__ == "__main__":

    # 定义record文件路径

    record_file = "/apollo_workspace/data/camera_calib/20250222101001.record.00000"



    # 定义相机topic和对应的输出文件夹

    camera_topics = [

        "/apollo/sensor/camera/front_6mm/image",

        "/apollo/sensor/camera/front_12mm/image"

    ]

    output_dirs = [

        "/apollo_workspace/data/camera_calib/output/front_6mm_images",

        "/apollo_workspace/data/camera_calib/output/front_12mm_images"

    ]



    # 保存图像

    save_images_from_record(record_file, camera_topics, output_dirs)
