#include "CVUtils.hpp"
#include <limits>
#include <vector>
#include <algorithm>
#include <array>

static int img_count;
void HarrisonCornerSim(std::string img_path
                        ,int window_size
                        ,float k
                        ,float threshold
                        ,float* score_ptr
                        ,int score_box)
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
    float max_score=0.0f;
    int target_y=0;
    int target_x=0;
    int debug_prev_pos=0;
    int debug_cur_pos =0;
    for(int idx=0; idx<500*500; idx++)
    {
        score_ptr[idx]=0.0f;
    }
    for(int y = 0; y<score.rows; y+=score_box)
    {
        for(int x = 0; x<score.cols; x+=score_box)
        {
            for(int inner_y = y; inner_y <y+score_box; inner_y++)
            {
                for(int inner_x = x; inner_x <x+score_box; inner_x++)
                {
                   if( score.at<float>(inner_y,inner_x) > max_f64*(threshold))
                   {
                       if( max_score <  score.at<float>(inner_y,inner_x))
                       {
                            max_score= score.at<float>(inner_y,inner_x);
                            target_y = inner_y;
                            target_x = inner_x;
                       }
                   }
                }
            }
            if( max_score != 0.0f)
            {
                score_ptr[target_y*score.cols+target_x]=max_score;

                cv::circle(original_img, cv::Point2d(target_x,target_y), 2, cv::Scalar(255,0,0),-1);
            }
            max_score=0.0f;
            target_y=0;
            target_x=0;
        }
    }
    cv::imshow("img"+std::to_string(img_count++), original_img);
    cv::waitKey(0);
    //cv::imwrite("/home/alpha/Desktop/project/DB/sample/output_.jpg",original_img);
}


float make_mean(std::vector<int> v)
{
    float sum = std::accumulate(v.begin(), v.end(), 0.0);
    float mean = sum / v.size();
    return mean;
}
float make_std(std::vector<int> v, float mean)
{
    float sq_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
    float stdev = std::sqrt(sq_sum / v.size() - mean * mean);
    return stdev;
}

void MatchingPoint(std::string prev_img_path
                    , std::string cur_img_path
                    , float* score_ptr_prev
                    , float* score_ptr_cur)
{
    
    std::vector<patch_type> img_prev_patch;
    std::vector<patch_type> img_cur_patch;

    cv::Mat prev_gray_img = cv::imread(prev_img_path, cv::IMREAD_GRAYSCALE);
    cv::resize(prev_gray_img,prev_gray_img,cv::Size(500,500));

    cv::Mat cur_gray_img = cv::imread(cur_img_path, cv::IMREAD_GRAYSCALE);
    cv::resize(cur_gray_img,cur_gray_img,cv::Size(500,500));

    cv::Mat prev_rgb_img = cv::imread(prev_img_path,cv::IMREAD_COLOR); 
    cv::resize(prev_rgb_img,prev_rgb_img,cv::Size(500,500));

    cv::Mat cur_rgb_img = cv::imread(cur_img_path,cv::IMREAD_COLOR); 
    cv::resize(cur_rgb_img,cur_rgb_img,cv::Size(500,500));

    // get patch
    for(int y=2; y<500-2; y++)
    {
        for(int x=2; x<500-2; x++)
        {
            std::vector<int> direction;
            int index = y*500+x;
            for(int inner_y=-2; inner_y<3; inner_y++)
            {
                for(int inner_x=-2; inner_x<3; inner_x++)
                {
                    direction.push_back( (y+inner_y)*500+(x+inner_x) );
                }
            }
            if(score_ptr_prev[index] !=0.0f)
            {
                std::vector<int> patch_data;
                for(auto img_index : direction)
                {
                    patch_data.push_back(prev_gray_img.data[img_index]);
                }
                img_prev_patch.push_back(std::make_pair(patch_data,std::vector<int>{y,x}));
            }
            if(score_ptr_cur[index] !=0.0f)
            {
                std::vector<int> patch_data;
                for(auto img_index : direction)
                {
                    patch_data.push_back(cur_gray_img.data[img_index]);
                }
                img_cur_patch.push_back(std::make_pair(patch_data,std::vector<int>{y,x}));
            }
        }
    }

    /* make mean and std each patch */
    float ncc_sum=0.0f;
    float max_ncc=-987654321.f;
    int target_y=0;
    int target_x=0;

    for(auto prev_vec : img_prev_patch)
    {
        std::cout<<"PREV Matching Start in "<<prev_vec.second[0] 
                            <<" : "<<prev_vec.second[1]<<std::endl;
        auto prev_patch_data = prev_vec.first;
        auto prev_mean = make_mean(prev_patch_data);
        auto prev_std = make_std(prev_patch_data, prev_mean);
        std::vector<float> ncc_prev;
        for(auto prev_ele : prev_patch_data)
        {
            float factor = (prev_ele-prev_mean)/prev_std;
            ncc_prev.push_back( factor );
        }

        for(auto cur_vec : img_cur_patch)
        {
            std::vector<float> ncc_cur;
            auto cur_patch_data = cur_vec.first;
            auto cur_mean = make_mean(cur_patch_data);
            auto cur_std = make_std(cur_patch_data, cur_mean);
            for(auto cur_ele : cur_patch_data)
            {
                float factor = (cur_ele-cur_mean)/cur_std;
                ncc_cur.push_back( factor );
            }
            for(int i=0; i<ncc_prev.size(); i++)        
            {
                ncc_sum+= ncc_prev[i]*ncc_cur[i];
            }
            ncc_sum /= ncc_prev.size();
            if( max_ncc < ncc_sum )
            {
                max_ncc = ncc_sum; 
                target_y = cur_vec.second[0];
                target_x = cur_vec.second[1];
                std::cout<<"Update value "<<std::endl;
                std::cout<<"ncc : "<< max_ncc<<" y_pos : "
                            <<target_y <<" x_pos : "<<target_x<<std::endl;
            }
            ncc_sum=0.0f;
        }

        cv::circle(prev_rgb_img, cv::Point2d(prev_vec.second[1],prev_vec.second[0]), 2, cv::Scalar(255,0,0),-1);
        cv::circle(cur_rgb_img, cv::Point2d(target_x,target_y), 2, cv::Scalar(255,0,0),-1);
        cv::imshow("prev", prev_rgb_img);
        cv::imshow("cur", cur_rgb_img);
        cv::waitKey(0);
        target_y=0;
        target_x=0;
        max_ncc=-987654321.f;
        cv::destroyAllWindows();
    }
}