/*
* Author: luyaomin
* time:2020.11.20
* github: https://github.com/YaominJun 
*/

#ifndef INCLUDE_RVIZ_VISUALIZATION_HPP_
#define INCLUDE_RVIZ_VISUALIZATION_HPP_

//related with ROS
#include <ros/ros.h>
#include <ros/package.h>
#include <visualization_msgs/MarkerArray.h>
#include <tf/transform_datatypes.h>

//important hpp - C++ STL
#include <sstream>
#include <iostream>
#include <fstream>

#include "motion_path.hpp"

class RvizVisualTool{
    protected:

    public:
    //函数接口
    /**
     * @Description: load path file
     * @Param: file name
     * @return: path data
     */
    void loadMpData(std::string packge_name, std::string filename, MotionPathAttribute &mp);

    /**
     * for draw motion path
     * @Param: motion path, ros publisher
     * @return: none
     */
    void publishMp2DPath(MotionPathAttribute const& mp, ros::Publisher &pub, std::string namespace_);

    /**
     * for draw points
     * @Param: motion path, ros publisher
     * @return: none
     */
    void publish3DPoints(MotionPathAttribute const& traj, 
                            ros::Publisher &pub, 
                            std::string namespace_);
};

#endif //INCLUDE_RVIZ_VISUALIZATION_HPP_
