/**
 * @file path.h
 */
#ifndef INCLUDE_PATH_HPP_
#define INCLUDE_PATH_HPP_

#include <iostream>
#include <vector>

struct Position
{
    double x;
    double y;
};


/// attributes of the motion primitive
struct MotionPathAttribute {
    /// curve node of motion primitive
    std::vector<Position> primitive_node;
    /// time stamp of each curve node
    std::vector<double> timestamp;
    /// theta of each motion primitive node
    std::vector<double> theta;
};

#endif /* INCLUDE_PATH_HPP_ */
