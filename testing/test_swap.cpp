#include <cstdlib>
#include <vector>
#include <algorithm>
#include "test_helpers.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"


TEST(SwapTests, SimpleSwapTwoValues) {
    int a = 5;
    int b = 10;

    swap(&a, &b);

    EXPECT_EQ(a, 10);
    EXPECT_EQ(b, 5);
    /*
     * Swap two values and see if the swap was successful.
     */
}

TEST(SwapTests, SimpleSwapValuesInArray) {
    /*
     * Swap a few values in an array.
     * Check that the ones that swapped did swap and the ones that didn't swap
     * are still at the same locations
     */
    int arr[] = {1,2,3,4,5,6,7,8};
    swap(&arr[0], &arr[1]);
    swap(&arr[2], &arr[3]);

    EXPECT_EQ(arr[0], 2);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 4);
    EXPECT_EQ(arr[3], 3);

    EXPECT_EQ(arr[4], 5);
    EXPECT_EQ(arr[5], 6);
    EXPECT_EQ(arr[6], 7);
    EXPECT_EQ(arr[7], 8);
}

RC_GTEST_PROP(SwapTests,
              PropertySwapTwoValues,
              (int a_start, int b_start)
) {
    /*
     * Swap two values and see if the swap was successful.
     */
    int a = a_start;
    int b = b_start;

    swap(&a, &b);
    RC_ASSERT(a == b_start);
    RC_ASSERT(b == a_start);
}

RC_GTEST_PROP(SwapTests,
              PropertySwapValuesInArray,
              (const std::vector<int>& values)
) {
    /*
     * Swap two values in an array. See that they swapped and the others did not
     */
    RC_PRE((int)values.size() >= 2);

    std::vector<int> arr =values;

    swap(&arr[0], &arr[1]);

    RC_ASSERT(arr[0] == values[1]);
    RC_ASSERT(arr[1] == values[0]);

    for (size_t i = 2;  i < arr.size(); i++) {
        RC_ASSERT(arr[i] == values[i]);
    }
}
