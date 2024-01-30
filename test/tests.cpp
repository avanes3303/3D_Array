#include <gtest/gtest.h>
#include "lib/Array.h"


TEST(ThreeDimensionalArrayTest, InputOutput) {
    ThreeDimensionalArray arr1 = ThreeDimensionalArray::make_array(1, 2, 2);

    arr1[0][0][0] = 1;
    arr1[0][0][1] = 2;
    arr1[0][1][0] = 3;
    arr1[0][1][1] = 4;

    std::ostringstream output;
    output << arr1;

    ASSERT_TRUE(output.str().find("1") != std::string::npos);
    ASSERT_TRUE(output.str().find("2") != std::string::npos);
    ASSERT_TRUE(output.str().find("3") != std::string::npos);
    ASSERT_TRUE(output.str().find("4") != std::string::npos);

    std::istringstream input(output.str());
    ThreeDimensionalArray arr2 = ThreeDimensionalArray::make_array(1,2,2);
    input >> arr2;

    ASSERT_EQ(arr1[0][0][0], arr2[0][0][0]);
    ASSERT_EQ(arr1[0][0][1], arr2[0][0][1]);
    ASSERT_EQ(arr1[0][1][0], arr2[0][1][0]);
    ASSERT_EQ(arr1[0][1][1], arr2[0][1][1]);
}
TEST(ThreeDimensionalArrayTest, Memory){
    ThreeDimensionalArray arr1 = ThreeDimensionalArray::make_array(5,5,5);
    ThreeDimensionalArray arr2 = ThreeDimensionalArray::make_array(1,7,3);
    ThreeDimensionalArray arr3 = ThreeDimensionalArray::make_array(10,8,100);

    ASSERT_TRUE(arr1.GetSize() <= ((5 * 5 * 5 * 17) / 8 + 1));
    ASSERT_TRUE(arr2.GetSize() <= ((1 * 7 * 3 * 17) / 8 + 1));
    ASSERT_TRUE(arr3.GetSize() <= ((10 * 8 * 100 * 17) / 8 + 1));
}

TEST(ThreeDimensionalArrayTest, RangeValues){
    ThreeDimensionalArray arr = ThreeDimensionalArray::make_array(1,1,3);

    arr[0][0][0] = 131071;
    arr[0][0][1] = -1;
    arr[0][0][2] = 10000000;

    ASSERT_EQ(arr[0][0][0], arr[0][0][1]);
    ASSERT_NE(arr[0][0][2], 10000000);
}

TEST(ThreeDimensionalArrayTest, Multiplication) {
    ThreeDimensionalArray arr = ThreeDimensionalArray::make_array(1, 1, 3);
    ThreeDimensionalArray result = ThreeDimensionalArray::make_array(1, 1, 3);

    arr[0][0][0] = 3;
    arr[0][0][1] = 2;
    arr[0][0][2] = 1;

   result = arr * 5;

   ASSERT_EQ(3 * 5, result[0][0][0]);
   ASSERT_EQ(2 * 5, result[0][0][1]);
   ASSERT_EQ(1 * 5, result[0][0][2]);
}

TEST(ThreeDimensionalArrayTest, Addition) {
    ThreeDimensionalArray arr1 = ThreeDimensionalArray::make_array(1, 1, 2);
    arr1[0][0][0] = 3;
    arr1[0][0][1] = 2;

    ThreeDimensionalArray arr2 = ThreeDimensionalArray::make_array(1, 1, 2);
    arr2[0][0][0] = 1;
    arr2[0][0][1] = 4;

    ThreeDimensionalArray result = arr1 + arr2;

    ASSERT_EQ(3 + 1, result[0][0][0]);
    ASSERT_EQ(2 + 4, result[0][0][1]);
}

TEST(ThreeDimensionalArrayTest, Subtraction) {
    ThreeDimensionalArray arr1 = ThreeDimensionalArray::make_array(1, 1, 2);
    arr1[0][0][0] = 3;
    arr1[0][0][1] = 5;

    ThreeDimensionalArray arr2 = ThreeDimensionalArray::make_array(1, 2, 2);
    arr2[0][0][0] = 1;
    arr2[0][0][1] = 4;

    ThreeDimensionalArray result = arr1 - arr2;

    ASSERT_EQ(3 - 1, result[0][0][0]);
    ASSERT_EQ(5 - 4, result[0][0][1]);
}
