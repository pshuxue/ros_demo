#include "ros/ros.h"
#include "message_demo/Test.h"
#include "sensor_msgs/Image.h"
#include "opencv2/highgui.hpp"
#include <cv_bridge/cv_bridge.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "message_publisher");
    ros::NodeHandle n;
    ros::Publisher msg_pub = n.advertise<message_demo::Test>("/message_publisher/test_msg", 100);
    ros::Rate loop_rate(10);

    cv::Mat cvImg = cv::imread("/home/pengshuxue/Pictures/dog.jpeg");

    while (ros::ok())
    {
        message_demo::Test msg;

        msg.img = *(cv_bridge::CvImage(std_msgs::Header(), "bgr8", cvImg).toImageMsg());

        //用vector给float32[]数组赋值
        std::vector<float> array({1, 2, 3});
        msg.data = array;
        msg.data.push_back(4);
        //也可以通过下标赋值   msg.data[0] = 0.1;

        msg.name = "Bob";
        msg.id = 32;

        msg_pub.publish(msg);

        std::cout << "发布者" << std::endl;
        std::cout << "message name: " << msg.name << std::endl;
        std::cout << "message index: " << msg.id << std::endl;
        std::cout << "message data: ";
        for (auto &d : msg.data)
        {
            std::cout << d << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;

        ros::spinOnce();
        loop_rate.sleep();
    }

    ros::spin();
    return 0;
}