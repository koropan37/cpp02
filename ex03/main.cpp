// #include "Point.hpp"
// #include <ios>

// #define MAX (2147483648.0f/256)
// #define MIN (1.0f/256)

// int main(){
//     Point a(0,0);
//     Point b(MAX,MAX);
//     Point c(MAX,0);
//     Point pt1(-1,-1);

//     std::cout<<std::boolalpha;
//     std::cout<< bsp(a,b,c,pt1) <<std::endl;
//     std::cout<< (Fixed(MAX-1)-Fixed(MIN) == Fixed(MAX-1)) <<std::endl;
//}
// どちらも false になるはずが float の精度により true になってしまう
