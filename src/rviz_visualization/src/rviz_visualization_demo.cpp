/*
* Author: luyaomin
* time:2020.11.20
* github: https://github.com/YaominJun 
*/

#include "rviz_visualization.hpp"

int main(int argc, char **argv) {
    // Initialize the node, publishers and subscribers.
    std::string node_name = "bvh_checker_demo_node";
    ros::init(argc, argv, node_name);
    ros::NodeHandle nh_;

    MotionPathAttribute mp_a;
    MotionPathAttribute mp_b;

    std::string package_name = "rviz_visualization";
    std::string path_a_file_path = "/src/mp_1.csv";
    std::string path_b_file_path = "/src/mp_2.csv";
    //加载csv文件
    RvizVisualTool show_two_path;
    show_two_path.loadMpData(package_name, path_a_file_path, mp_a);
    show_two_path.loadMpData(package_name, path_b_file_path, mp_b);

    //related with ros
    ros::Publisher mp1_2dpath_pub;
    ros::Publisher mp2_2dpath_pub;
    ros::Publisher mp1_3dpoints_pub;
    ros::Publisher mp2_3dpoints_pub;

    //for visual
    mp1_2dpath_pub = nh_.advertise<visualization_msgs::MarkerArray>("/motion_path_a", 1, false);
    mp2_2dpath_pub = nh_.advertise<visualization_msgs::MarkerArray>("/motion_path_b", 1, false);
    mp1_3dpoints_pub = nh_.advertise<visualization_msgs::MarkerArray>("/points_a", 1, false);
    mp2_3dpoints_pub = nh_.advertise<visualization_msgs::MarkerArray>("/points_b", 1, false);


    //循环pub路径
    ros::Rate loop_rate(10);
    while (ros::ok)
    {
        show_two_path.publishMp2DPath(mp_a, mp1_2dpath_pub, "path_marker_a");
        show_two_path.publishMp2DPath(mp_b, mp2_2dpath_pub, "path_marker_b");

        show_two_path.publish3DPoints(mp_a, mp1_3dpoints_pub, "points_marker_a");
        show_two_path.publish3DPoints(mp_b, mp2_3dpoints_pub, "points_marker_b");

        ros::spinOnce();
        loop_rate.sleep();
    }
}