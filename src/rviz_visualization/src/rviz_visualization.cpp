/*
* Author: luyaomin
* time:2020.11.20
* github: https://github.com/YaominJun 
*/

#include "rviz_visualization.hpp"

void RvizVisualTool::loadMpData(std::string packge_name, std::string filename, MotionPathAttribute &mp){
    /**
     * load data from .csv file
     */
    /**
     * atoi: string to integer
     * atol: string to long integer
     * atoll: string to long long integer
     * atof: string to double
     * atoff: string to float
     */

    mp.primitive_node.clear();
    mp.timestamp.clear();
    mp.theta.clear();

    std::string package_path = ros::package::getPath(packge_name);

    std::ifstream file(package_path + filename.c_str(), std::ifstream::in);
    if (!file) {
        ROS_INFO("No valid input file was given, please check the given filename and path.");
    }
    
    Position vec2d_;
    char separator = ',';
    std::string line, x_str, y_str, z_str, theta_str;
    //read one line
    while (getline(file, line)) {
        std::stringstream liness(line);
        getline(liness, x_str, separator);
        getline(liness, y_str, separator);
        getline(liness, z_str, separator);
        getline(liness, theta_str);
        if (!x_str.empty() && !y_str.empty() && !z_str.empty() && !theta_str.empty()) {
            vec2d_.x = atof(x_str.c_str());
            vec2d_.y = atof(y_str.c_str());
            mp.primitive_node.push_back(vec2d_);
            mp.timestamp.push_back(atof(z_str.c_str()));
            mp.theta.push_back(atof(theta_str.c_str()));
        }
    }
    file.close();
}

void RvizVisualTool::publishMp2DPath(MotionPathAttribute const& mp, ros::Publisher &pub, std::string namespace_){
    visualization_msgs::Marker path_marker;
    visualization_msgs::MarkerArray path_marker_group;
    path_marker.header.frame_id = "/map";
    path_marker.header.stamp = ros::Time();
    path_marker.ns = namespace_;
    path_marker.id = 0;
    path_marker.type = visualization_msgs::Marker::ARROW; //CUBE
    path_marker.action = visualization_msgs::Marker::ADD;
    path_marker.lifetime = ros::Duration(1.0);
    path_marker.scale.x = 1;
    path_marker.scale.y = 0.2;
    path_marker.scale.z = 0.2;
    path_marker.color.a = 0.5;

    if(namespace_ == "path_marker_a"){
        path_marker.color.r = 1;
        path_marker.color.g = 0;
        path_marker.color.b = 0;
    }else{
        path_marker.color.r = 0;
        path_marker.color.g = 0;
        path_marker.color.b = 1;
    }

    path_marker.frame_locked = true;
    geometry_msgs::Pose temp;
    tf::Quaternion temp_tf_quaternion;

    int len_path = mp.primitive_node.size();
    for (int i = 0; i < len_path; i++) {
        path_marker.pose.position.x = mp.primitive_node[i].x;
        path_marker.pose.position.y = mp.primitive_node[i].y;

        temp_tf_quaternion = tf::createQuaternionFromYaw(mp.theta[i]);
        temp.orientation.w = temp_tf_quaternion.w();
        temp.orientation.x = temp_tf_quaternion.x();
        temp.orientation.y = temp_tf_quaternion.y();
        temp.orientation.z = temp_tf_quaternion.z();
        path_marker.pose.orientation = temp.orientation;
        
        path_marker_group.markers.push_back(path_marker);
        path_marker.id += 1;
    }
    pub.publish(path_marker_group);
}

void RvizVisualTool::publish3DPoints(MotionPathAttribute const& mp, 
                                            ros::Publisher &pub, 
                                            std::string namespace_){
    visualization_msgs::Marker path_marker;
    visualization_msgs::MarkerArray path_marker_group;
    path_marker.header.frame_id = "/map";
    path_marker.header.stamp = ros::Time();
    path_marker.ns = namespace_;
    path_marker.id = 0;
    path_marker.type = visualization_msgs::Marker::POINTS;
    path_marker.action = visualization_msgs::Marker::ADD;
    path_marker.lifetime = ros::Duration(1.0);
    path_marker.scale.x = 0.5;
    path_marker.scale.y = 0.5;
    path_marker.scale.z = 0.5;
    path_marker.color.a = 1;

    path_marker.frame_locked = true;
    geometry_msgs::Point tmp_pt;
    path_marker.pose.orientation.w = 1.0;

    if(namespace_ == "points_marker_a"){
        path_marker.color.r = 1;
        path_marker.color.g = 0;
        path_marker.color.b = 0;
    }else{
        path_marker.color.r = 0;
        path_marker.color.g = 0;
        path_marker.color.b = 1;
    }
    int len_path = mp.primitive_node.size();
    for (int i = 0; i < len_path; i++) {
        tmp_pt.x = mp.primitive_node[i].x;
        tmp_pt.y = mp.primitive_node[i].y;
        tmp_pt.z = mp.timestamp[i];
        path_marker.points.push_back(tmp_pt);
    }
    path_marker_group.markers.push_back(path_marker);

    pub.publish(path_marker_group);
}

