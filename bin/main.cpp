#include <iostream>
#include "lib/Array.h"


int main() {
    ThreeDimensionalArray arr1 = ThreeDimensionalArray::make_array(2,1,1);
    ThreeDimensionalArray arr2 = ThreeDimensionalArray(1,2,1);
    ThreeDimensionalArray arr3(arr2);

    std::cin>>arr1;
    std::cin>>arr2;
    std::cin>>arr3;

    std::cout<<arr1<<std::endl;
    std::cout<<arr2<<std::endl;
    std::cout<<arr3<<std::endl;

    return 0;
}
