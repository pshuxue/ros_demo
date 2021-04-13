
#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <rosbag/query.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Image.h>
#include <pcl_conversions/pcl_conversions.h>
#include <string>
using namespace std;

const std::string path = "/home/pengshuxue/data/slam-data/KITTI_Odometry_Velodyne/2011_09_30_0027.bag";
const std::string lidar_topic = "velodyne_points";
const std::string image03_topic = "cam03/image_raw";
const std::string save_path = "/home/pengshuxue/tmp/data";

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;

    rosbag::Bag bag;
    bag.open(path, rosbag::bagmode::Read);

    std::vector<std::string> topics;
    topics.push_back(lidar_topic);
    topics.push_back(image03_topic);
    rosbag::View view(bag, rosbag::TopicQuery(topics));

    int cloudCount = 0;
    for (const rosbag::MessageInstance &m : view)
    {
        if (m.getTopic() == lidar_topic)
        {
            sensor_msgs::PointCloud2 livox_cloud;
            livox_cloud = *(m.instantiate<sensor_msgs::PointCloud2>()); // message type
            pcl::PointCloud<pcl::PointXYZI> cloud;
            pcl::PCLPointCloud2 pcl_pc;
            pcl_conversions::toPCL(livox_cloud, pcl_pc);
            pcl::fromPCLPointCloud2(pcl_pc, cloud);
            ++cloudCount;
            pcl::io::savePCDFile(save_path + "/lidar/" + to_string(m.getTime().toNSec()) + ".pcd", cloud);
            cout << m.getTime() << endl;
        }
        else if (m.getTopic() == image03_topic)
        {
            sensor_msgs::Image image = *(m.instantiate<sensor_msgs::Image>());
            cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(image);
            cv::Mat cvimg = cv_ptr->image;
            cv::imwrite(save_path + "/image/" + to_string(m.getTime().toNSec()) + ".jpg", cvimg);
            cout << "                                                       " << m.getTime() << endl;
        }
        else
        {
        }
    }

    return 0;
}
