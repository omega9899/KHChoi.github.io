#ifndef CV_HPP
#define CV_HPP
#include <iostream>
#include <string>
#include <opencv4/opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

void cannyEdge(std::string target_path);
void doNMS();
void hysteresis_threshold(int Tmax, int Tmin);
#endif