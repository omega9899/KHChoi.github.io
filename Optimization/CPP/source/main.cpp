#include <iostream>
#include <fstream>
#include <vector>
#include <opencv4/opencv2/opencv.hpp>
int main()
{
    std::ifstream input_file;
    input_file.open("/home/alpha/Desktop/project/ORB_SLAM2/ORB_SLAM2/KeyFrameTrajectory.txt");
    char split=',';
    std::vector<float> keyframe_sub;
    std::vector<std::vector<float>> keyFrame;
    if( input_file.is_open() )
    {
        std::string line;
        while(getline(input_file, line, split))
        {
            keyframe_sub.push_back(std::stof(line));
            if( keyframe_sub.size()==8)
            {
                keyFrame.push_back(keyframe_sub);
                keyframe_sub.clear();
            }
        }
    }

    // time, cam_x, cam_y, cam_z, key_x, key_y, key_z, key_w


}


