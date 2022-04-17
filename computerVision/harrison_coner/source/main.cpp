#include <iostream>
#include "header/CVUtils.hpp"

int main()
{
    std::string target_path;

    target_path = PROJECT_ROOT"/../DB/chair_2.png";
    float prev_f_ptr[500*500];
    HarrisonCornerSim(target_path, 3, 0.05, 0.05 ,prev_f_ptr,25);

    float cur_f_ptr[500*500];
    target_path = PROJECT_ROOT"/../DB/chair_1.png";
    HarrisonCornerSim(target_path, 3, 0.05, 0.05 ,cur_f_ptr,25);

    //cv::destroyAllWindows();

    std::string prev_img =  PROJECT_ROOT"/../DB/chair_2.png";
    std::string cur_img = PROJECT_ROOT"/../DB/chair_1.png";

    MatchingPoint(prev_img,cur_img,prev_f_ptr,cur_f_ptr);

    return 0;

} 