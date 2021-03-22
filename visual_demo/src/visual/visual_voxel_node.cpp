
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

int main(int argc, char **argv)
{
	// ROS节点初始化
	ros::init(argc, argv, "voxel_publisher");

	// 创建节点句柄
	ros::NodeHandle n;

	std::string str;
	n.getParam("save", str);
	ROS_INFO("save ");
	std::cout << str << std::endl;

	ros::Publisher voxels_pub = n.advertise<visualization_msgs::MarkerArray>("visualization_voxels", 10);

	// 设置循环的频率
	ros::Rate loop_rate(1);

	int count = 0;
	while (ros::ok())
	{
		//发送体素，MarkerArray是方格的组合
		visualization_msgs::MarkerArray voxels_array;
		for (int i = 0; i < 5; ++i)
		{
			visualization_msgs::Marker marker;
			marker.header.frame_id = "/my_frame"; //很重要，跟rviz中的Fixed Frame要设置为一样的
			marker.header.stamp = ros::Time::now();
			marker.ns = "basic_shapes";
			marker.id = count * 5 + i;
			marker.type = visualization_msgs::Marker::CUBE;

			// Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
			marker.action = visualization_msgs::Marker::ADD;
			marker.pose.position.x = i;
			marker.pose.position.y = i;
			marker.pose.position.z = count;
			marker.pose.orientation.x = .00;
			marker.pose.orientation.y = 0.0;
			marker.pose.orientation.z = 0.0;
			marker.pose.orientation.w = 1.0;
			marker.scale.x = 1.0;
			marker.scale.y = 1.0;
			marker.scale.z = 1.0;
			marker.color.r = 0.0f;
			marker.color.g = 1.0f;
			marker.color.b = 0.0f;
			marker.color.a = 1.0;
			marker.lifetime = ros::Duration();
			voxels_array.markers.push_back(marker);
		}

		count++;
		voxels_pub.publish(voxels_array);

		ROS_INFO("Publsh voxels");

		// 按照循环频率延时
		loop_rate.sleep();
	}

	return 0;
}
