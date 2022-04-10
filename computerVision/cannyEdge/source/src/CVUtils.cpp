#include "CVUtils.hpp"
#include <limits>
#include <vector>
#include <algorithm>
#include <array>
#include <cmath>

static uchar magnitude_u08[512][512];
static int angle_u08[512][512];
static uchar nms_magnitude_u08[512][512];
static uchar canny_result[512][512];

void debug_inner_showImg(cv::Mat& img)
{
    cv::imshow("debug img", img);
    cv::waitKey(0);
}

void doNMS()
{
    for(int y=1; y<512-1; y++)
    {
        for(int x=1; x<512-1; x++)
        {
            uchar data = magnitude_u08[y][x];
            int direction = angle_u08[y][x];

            if(direction == 0)
            {
                if( data <magnitude_u08[y][x-1] || data <magnitude_u08[y][x+1] )
                    nms_magnitude_u08[y][x] = 0;
                else
                    nms_magnitude_u08[y][x] = data;
            }
            else if(direction == 1)
            {
                if( data <magnitude_u08[y-1][x-1] || data <magnitude_u08[y+1][x+1] )
                    nms_magnitude_u08[y][x] = 0;
                else
                    nms_magnitude_u08[y][x] = data;
            }
            else if(direction == 2)
            {
                if( data <magnitude_u08[y-1][x] || data <magnitude_u08[y+1][x] )
                    nms_magnitude_u08[y][x] = 0;
                else
                    nms_magnitude_u08[y][x] = data;
            }
            else
            {
                if( data <magnitude_u08[y-1][x+1] || data <magnitude_u08[y+1][x-1] )
                    nms_magnitude_u08[y][x] = 0;
                else
                    nms_magnitude_u08[y][x] = data;
            }
        }
    }
    return;
}

void find_canny_edge(int y, int x, int Tmin)
{
    // detect corner case
    if(y<0 || y>512 || x< 0 || x> 512)
    {
        return;
    }
    // recursively find all point that is higher than Tmin
    for(int y_offset=-1; y_offset<2; y_offset++)
    {
        for(int x_offset=-1; x_offset<2; x_offset++)
        {
            if( nms_magnitude_u08[y+y_offset][x+x_offset] > Tmin)
            {
                if( canny_result[y+y_offset][x+x_offset] != 0 )
                    continue;
                canny_result[y+y_offset][x+x_offset] = 255;
                find_canny_edge(y+y_offset, x+x_offset,Tmin);
            }
        }
    }
}
void hysteresis_threshold(int Tmax=150, int Tmin=100)
{
    for(int y=1; y<511; y++)
    {
        for(int x=1; x<511; x++)
        {
            // initialized edge must be higher then Tmax
            if( nms_magnitude_u08[y][x] >= Tmax)
            {
                find_canny_edge(y,x,Tmin);
            }
        }
    }
}
void cannyEdge(std::string target_path)
{
    // 1. load image as a gray scale
    cv::Mat gray_img = cv::imread(target_path, cv::IMREAD_GRAYSCALE);
    // 2. do gaussian    
    cv::Mat gauss_img;
    cv::GaussianBlur(gray_img, gauss_img, cv::Size(5,5), 1.5);
    // 3. sobel filtering
    cv::Mat Ix, Iy;
    cv::Sobel(gauss_img, Ix, CV_32F, 1, 0, 3);
    cv::Sobel(gauss_img, Iy, CV_32F, 0, 1, 3);
    // 4. calculate magnitude and angle
    cv::Mat magnitude;
    cv::magnitude(Ix,Iy,magnitude);    
    for(int y = 0; y<magnitude.cols; y++)
        for(int x = 0; x<magnitude.rows; x++)
            magnitude_u08[y][x]=(uchar)magnitude.at<float>(y,x);
    cv::Mat angle;
    cv::phase(Ix,Iy,angle);
    for(int y = 0; y<angle.cols; y++)
        for(int x = 0; x<angle.rows; x++)
            angle_u08[y][x]= (int)(angle.at<float>(y,x) / (M_PI/4)) % 4;
    // 5. do nms
    doNMS();
    // 6. hysteresis thresholing
    //cv::Mat test = cv::Mat(cv::Size(512,512),CV_8UC1, nms_magnitude_u08);
    //debug_inner_showImg(test);
    hysteresis_threshold(90,30);
    cv::Mat test = cv::Mat(cv::Size(512,512),CV_8UC1, canny_result);
    debug_inner_showImg(test);
    return;
}