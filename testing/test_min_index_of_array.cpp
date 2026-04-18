#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "rapidcheck/gtest.h"
#include "sorting.h"

TEST(MinIndexOfArrayTests, SimpleMinIndexAtFrontOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the front of the array
     */
    int arr[] = {9,10,7,11,14,17};
    int leng = 6;

    int result = min_index_of_array(arr, leng);

    ASSERT_EQ(arr[2], arr[result]);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtEndOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the end of the array
     */
    int arr[] = {9,10,12,11,14,6};
    int leng = 6;

    int result = min_index_of_array(arr, leng);

    ASSERT_EQ(arr[5], arr[result]);
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtMiddleOfArray) {
    /*
     * See if we can find the index of the minimum value when it is somewhere
     * in the "middle" of the array.
     */
    int arr[] = {9,10,12,11,5,17,14,18};
    int leng = 8;

    int result = min_index_of_array(arr, leng);

    ASSERT_EQ(arr[4], arr[result]);
}

TEST(MinIndexOfArrayTests, SimpleDuplicateMinimums) {
    /*
     * See if we return the index of the first minimum in the array
     * When there are multiple values that are the minimum.
     */
    int arr[] = {9,5,5,5,5,17,14};
    int leng = 7;

    int result = min_index_of_array(arr, leng);

    ASSERT_EQ(1, result);

}

TEST(MinIndexOfArrayTests, SimpleArrayDoesNotChange) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    int arr[] = {1,2,3,4,5,6};
    int leng = 6;

    int original[] = {1,2,3,4,5,6};

    int result = min_index_of_array(arr, leng);

    for (int i = 0 ; i < leng ; i++) {
        RC_ASSERT(arr[result] <= arr[i]);
        ASSERT_EQ(arr[i], original[i]);
    }
}


RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyFindMinIndex,
              (std::vector<int> values)) {
    /* Check that the value at the location of the minimum index
     * is not larger than any of the other values in the array
     */
    RC_PRE((int)values.size() >= 1);

    int* arr = new int[values.size()];
    for (size_t i = 0; i < values.size(); i++) arr[i] = values[i];

    int result = min_index_of_array(arr, values.size());


    RC_ASSERT(result >= 0);
    RC_ASSERT((size_t)result < values.size());


    for (size_t i = 0; i < values.size(); i++) {
        RC_ASSERT(arr[result] <= arr[i]);
    }

    delete[] arr;

}

RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyArrayDoesNotChange,
              (std::vector<int> values)) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
    RC_PRE((int)values.size() >= 1);

    int* arr      = new int[values.size()];
    int* original = new int[values.size()];
    for (size_t i = 0; i < values.size(); i++) {
        arr[i]      = values[i];
        original[i] = values[i];
    }

    min_index_of_array(arr, values.size());

    for (size_t i = 0; i < values.size(); i++) {
        RC_ASSERT(arr[i] == original[i]);
    }

    delete[] arr;
    delete[] original;
}
