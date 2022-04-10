#include <iostream>
#include "header/CVUtils.hpp"

int main()
{
    std::string target_path = PROJECT_ROOT"/../DB/chair_2.png";
    HarrisonCornerSim(target_path,3, 0.05, (1.5e-05) ,"NONE");

    target_path = PROJECT_ROOT"/../DB/chair_1.png";
    HarrisonCornerSim(target_path,3, 0.05, (1.5e-05) ,"NONE");
    
    
    return 0;

} 