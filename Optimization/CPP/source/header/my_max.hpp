#include <iostream>
#include <functional>
#include <algorithm>
#include <string>

template <class T, class Compare = std::less<void> , class Proj = std::identity>
const T& mymax(const T& obj1
                , const T& obj2
                , Compare comp={}
                , Proj projection={})
{
    auto tag = comp;
    return std::invoke(comp, std::invoke( projection, obj1) ,std::invoke(projection, obj2))
                        ? obj1 : obj2;
}

#if 0
template <class T>
const T& dicional_max(const T& obj1, const T& obj2)
{
    return obj1 < obj2 ? obj2 : obj1;
}

template <class T, class Proj>
const T& sample0_max(const T& obj1, const T& obj2, Proj proj)
{
    return proj(obj1) < proj(obj2) ? obj2 : obj1;
};


template <class T, class Proj>
const T& sample1_max(const T& obj1, const T& obj2, Proj proj)
{
    return (obj1.*proj)()< (obj2.*proj)() ? obj2 : obj1;
};

template <class T, class Proj>
const T& sample2_max(const T& obj1, const T& obj2, Proj proj)
{
    return std::invoke(proj, obj1) < std::invoke(proj, obj2) ? obj2 : obj1;
};

template <class T, class Proj=std::identity> 
const T& sample3_max(const T& obj1, const T& obj2, Proj proj={}) 
// std::identity proj={} == std::identity proj;
{
    return std::invoke(proj, obj1) < std::invoke(proj, obj2) ? obj2 : obj1;
};

template <class T, class CMP, class Proj=std::identity> 
const T& sample4_max(const T& obj1, const T& obj2,CMP cmp, Proj proj={}) 
// std::identity proj={} == std::identity proj;
{
    return cmp(std::invoke(proj, obj1), std::invoke(proj, obj2)) ? obj2 : obj1;
//    return std::invoke(proj, obj1) < std::invoke(proj, obj2) ? obj2 : obj1;
};

template <class T, class CMP=std::less<void>, class Proj=std::identity> 
const T& sample5_max(const T& obj1, const T& obj2, CMP cmp={}, Proj proj={}) 
// std::identity proj={} == std::identity proj;
{
    return std::invoke(cmp, std::invoke(proj, obj1), std::invoke(proj, obj2)) ? obj2 : obj1;
};

class pointer
{
    public:
        pointer(){std::cout<<"TEST"<<std::endl;}
};

int main()
{
    std::string obj1="abcd";
    std::string obj2="xyz";

    std::cout<< dicional_max(obj1, obj2) <<std::endl;

    std::cout<< sample0_max(obj1,obj2, [](auto& a){return a.size();}) <<std::endl;
    std::cout<< sample0_max(obj1,obj2, [](auto& a)
                                            {
                                                std::size_t (std::string::*fp)() const =
                                                    &std::string::size;
                                                return (a.*fp)();
                                            }) <<std::endl;
    
    std::cout<<sample1_max(obj1, obj2, &std::string::size)<<std::endl;
    std::cout<<sample2_max(obj1, obj2, [](auto& a){return a.size();}) << std::endl;
    // in this case... invoke(fp , a);
    std::cout<<sample2_max(obj1, obj2, &std::string::size) << std::endl;
    // in this case... invoke(fp, obj, params...) // 이경우 params 가 없으니 공란
    std::cout<<sample3_max(obj1, obj2) << std::endl;
    std::cout<<sample4_max(obj1, obj2, std::less{} );
    std::cout<<sample5_max(obj1, obj2);

    
    return 0;
}
#endif
/*
    std::identity는 객체.
    std::identity projection={} -> std::identity projection과 동일
    prjection(obj)의 반환은 obj
*/