#include "ros/ros.h"
#include "message_demo/Test.h"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/Image.h"
#include "sensor_msgs/image_encodings.h"
#include "opencv2/highgui.hpp"

void msgCallback(const message_demo::Test::ConstPtr &msg)
{
    //test_msgs::Test类型里的float32[]数据传到vector
    std::vector<float> array = msg->data;
    std::cout << "订阅者" << std::endl;
    std::cout << "message name: " << msg->name << std::endl;
    std::cout << "message index: " << msg->id << std::endl;
    std::cout << "message data: ";
    for (auto &d : msg->data)
    {
        std::cout << d << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;

    cv_bridge::CvImagePtr cv_ptr;
    cv_ptr = cv_bridge::toCvCopy(msg->img, "bgr8");
    cv::imshow("view", cv_ptr->image);
    cv::waitKey(100);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "message_sublisher");
    ros::NodeHandle n;

    ros::Subscriber msg_sub = n.subscribe("/message_publisher/test_msg", 100, msgCallback);

    ros::spin();
    return 0;
}