#include <iostream>
#include "header/CVUtils.hpp"

int main()
{
    std::string target_path = PROJECT_ROOT"/../DB/lena.jpg";
    cannyEdge(target_path);

    return 0;
}