#ifndef CV_HPP
#define CV_HPP
#include <iostream>
#include <string>
#include <opencv4/opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <numeric>
#include <algorithm>

                                // patch info   //coordinate
using patch_type = std::pair<std::vector<int>, std::vector<int>>;

cv::Mat ImgLoadingFromPath(std::string target_path);
cv::Mat GrayImgLoadingFromPath(std::string target_path);

void HarrisonCornerSim(std::string img_path
                        ,int window_size
                        ,float k
                        ,float threshold
                        ,float* score_ptr
                        ,int score_box);

void MatchingPoint(std::string prev_img_path
                    , std::string cur_img_path
                    , float* score_ptr_prev
                    , float* score_ptr_cur);


#endif