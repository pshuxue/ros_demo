
#include <ros/ros.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("image", 1);

    cv::Mat frame = cv::imread("/home/psx/data/dog.jpeg");
    sensor_msgs::ImagePtr msg;

    ros::Rate loop_rate(10); //以10ms间隔发送图片
    while (nh.ok())
    {
        msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
        pub.publish(msg);
        ROS_INFO("run image ");
        ros::spinOnce();
        loop_rate.sleep(); //与ros::Rate loop_rate相对应,休息10ms
    }

    return 0;
}
