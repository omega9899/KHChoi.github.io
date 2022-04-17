#include <iostream>
#include <string>
#include <new>
#include <memory>

#include "header/CVUtils.hpp"
//#include "header/my_max.hpp"
#include "header/my_typedecut.hpp"

class X
{
    public:
        int data;
};

void foo(X& x){ std::cout<<1<<std::endl;}
void foo(const X& x){ std::cout<<2<<std::endl;}
//void foo(X&& x){ std::cout<<3<<std::endl;}

int main()
{
    int n=10;
    
    value_category(n); // n = 10 -> ok so lvalue
    value_category(n+2); // n+2 = 10 -> error so rvalue
    value_category(++n); // ++n = 10 -> ok 
    value_category(n++); // n++ = 10 -> not okay because return temporal(rvalue)
    value_category(10); // 10 = 10 -> not okay so ravlue
    value_category("AA"); // literal is lvalue so lvalue

    X&& r_value = X{};
    value_category(r_value); // lvalue
    // ++n -> int&
    return 0;
}