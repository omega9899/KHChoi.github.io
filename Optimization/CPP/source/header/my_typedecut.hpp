#include <type_traits>
#include <iostream>

#define value_category( ... ) \
        if( std::is_lvalue_reference_v<decltype((__VA_ARGS__))> )       \
            std::cout<<"lvalue"<<std::endl;                             \
        else if(std::is_rvalue_reference_v<decltype((__VA_ARGS__))>)    \
            std::cout<<"rvalue(xvalue)"<<std::endl;                     \
        else                                                            \
            std::cout<< "rvalue(prvalue)" <<std::endl;                  \
