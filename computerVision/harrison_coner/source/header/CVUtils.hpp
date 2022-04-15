#ifndef CV_HPP
#define CV_HPP
#include <iostream>
#include <string>
#include <opencv4/opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>


cv::Mat ImgLoadingFromPath(std::string target_path);
cv::Mat GrayImgLoadingFromPath(std::string target_path);

void HarrisonCornerSim(std::string img_path
                        ,int window_size
                        ,float k
                        ,float threshold
                        ,std::string output_path
                        ,int score_box=5);
void MatchingPoint();

#endif