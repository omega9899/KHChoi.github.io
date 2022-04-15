#include "CVUtils.hpp"
#include <limits>
#include <vector>
#include <algorithm>
#include <array>

void HarrisonCornerSim(std::string img_path
                        ,int window_size
                        ,float k
                        ,float threshold
                        ,std::string output_path
                        ,int score_box=5)
{
    /* loading image */
    cv::Mat gray_img = cv::imread(img_path, cv::IMREAD_GRAYSCALE);
    cv::resize(gray_img,gray_img,cv::Size(500,500));

    /* get gradient of image */
    uchar* ptr = gray_img.data;

    cv::Mat Ix;
    cv::Mat Iy;
    cv::Sobel(gray_img,Ix,CV_32FC1, 1,0);
    cv::Sobel(gray_img,Iy,CV_32FC1, 0,1);

    cv::Mat Ixx;
    cv::Mat Iyy;
    cv::Mat Ixy;
    cv::multiply(Ix,Ix,Ixx);
    cv::multiply(Iy,Iy,Iyy);
    cv::multiply(Ix,Iy,Ixy);

    /* make weighted sum to gradient */
    cv::GaussianBlur(Ixx,Ixx,cv::Size(5,5),2);
    cv::GaussianBlur(Iyy,Iyy,cv::Size(5,5),2);
    cv::GaussianBlur(Ixy,Ixy,cv::Size(5,5),2);
    Ixx = Ixx + 0.000000001;
    Iyy = Iyy + 0.000000001;
    Ixy = Ixy + 0.000000001;

    /* make R score */
    // det(M)   =   Ixx*Iyy-Ixy*Ixy
    // trace(M) =   k(Ixx+Iyy)*(Ixx+Iyy)
    cv::Mat det;
    cv::Mat trace;
    cv::Mat imm0;
    cv::Mat imm1;
    
    cv::multiply(Ixx,Iyy,imm0);
    cv::multiply(Ixy,Ixy,imm1);
    cv::subtract(imm0,imm1,det);

    cv::add(Ixx,Iyy,imm0);
    trace = imm0;

    cv::Mat score;
    cv::divide(det, trace, score);

    double min_f64, max_f64;
    cv::minMaxLoc(score, &min_f64, &max_f64);

    cv::Mat original_img = cv::imread(img_path, cv::IMREAD_COLOR);  
    cv::resize(original_img, original_img, cv::Size(500,500));
    for(int y = 0; y<score.rows; y+=score_box)
    {
        for(int x = 0; x<score.cols; x+=score_box)
        {
            if( score.at<float>(y,x) > max_f64*(0.01))
            {
                cv::circle(original_img, cv::Point2d(x,y), 2, cv::Scalar(0,0,255),-1);
            }
        }
    }
    cv::imshow("output", original_img);
    cv::waitKey(0);
    //cv::imwrite("/home/alpha/Desktop/project/DB/sample/output_.jpg",original_img);
}

void MatchingPoint()
{

}