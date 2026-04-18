#include <cstdlib>
#include <vector>
#include "gtest/gtest.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"
#include "test_helpers.h"

TEST(MakeSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {1,3,5,6,7};
    int leng = 5;

    make_sorted(arr, leng);

    int expected[] = {1,3,5,6,7};
    for (int i = 0 ; i < leng ; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(MakeSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {45,13,12,10,8};
    int leng = 5;

    make_sorted(arr, leng);

    int expected[] = {8,10,12,13,45};
    for (int i = 0; i < leng; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}


TEST(MakeSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {2,4,1,6,11,19,10,3};
    int leng = 8;

    make_sorted(arr, leng);

    int expected[] = {1,2,3,4,6,10,11,19};
    for (int i = 0; i < leng; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

TEST(MakeSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {1,4,3,2,6,2,1,3};
    int leng = 8;

    make_sorted(arr, leng);

    int expected[] = {1,1,2,2,3,3,4,6};
    for (int i = 0; i < leng; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

RC_GTEST_PROP(MakeSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Test that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    RC_PRE((int)values.size() >= 1);

    int* arr = new int[values.size()];
    for (size_t i = 0; i < values.size(); i++) arr[i] = values[i];

    make_sorted(arr, values.size());


    for (size_t i = 0; i + 1 < values.size(); i++) {
        RC_ASSERT(arr[i] <= arr[i + 1]);
    }

    delete[] arr;
}
