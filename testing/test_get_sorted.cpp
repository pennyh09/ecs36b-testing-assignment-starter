#include <cstdlib>
#include "gtest/gtest.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(GetSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {8,10,12,13,45};
    int leng = 5;

    int* sorted = get_sorted(arr, leng);

    for ( int i = 0 ; i < leng ; i++) {
        EXPECT_EQ(arr[i], sorted[i] );
    }

    delete[] sorted;
}

TEST(GetSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int arr[] = {45,13,12,10,8};
    int leng = 5;

    int* result = get_sorted(arr, leng);

    int sorted[] = {8,10,12,13,45};


    for (int i = 0 ; i < leng ; i++) {
        EXPECT_EQ(result[i], sorted[i]);
    }

    delete[] result;


}

TEST(GetSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {2,4,1,6,11,19,10,3};

    int leng = 8;

    int sorted [] = {1,2,3,4,6,10,11,19};

    int* result = get_sorted(arr, leng);

    for ( int i = 0 ; i < leng ; i++) {
        EXPECT_EQ(result[i], sorted[i]);
    }

    delete[] result;

}

TEST(GetSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {1,4,3,2,6,2,1,3};
    int leng = 8;
    int* result = get_sorted(arr, leng);

    int sorted[] = {1,1,2,2,3,3,4,6};

    for (int i = 0 ; i < leng ; i++) {
        EXPECT_EQ(result[i], sorted[i]);
    }

    delete[] result;


}

TEST(GetSortedTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */

    int arr[] = {1,4,3,2,6,2,1,3};
    int leng = 8;
    int original[] = {1,4,3,2,6,2,1,3};
    int* result = get_sorted(arr, leng);

    for (int i = 0 ; i < leng ; i++) {
        EXPECT_EQ(original[i], arr[i]);
    }

    delete[] result;


}

TEST(GetSortedTests, SimpleCopyWasMade) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {1,4,3,2,6,2,1,3};
    int leng = 8;

    int* result = get_sorted(arr, leng);


    EXPECT_NE(arr, result);


    for (int i = 0; i < leng; i++) {
        EXPECT_NE(&arr[i], &result[i]);
    }

    delete[] result;
}


RC_GTEST_PROP(GetSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Check that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    int* arr = new int[values.size()];
    for (size_t i = 0; i < values.size(); i++) arr[i] = values[i];

    int* result = get_sorted(arr, values.size());


    for (size_t i = 0; i + 1 < values.size(); i++) {
        RC_ASSERT(result[i] <= result[i + 1]);
    }

    delete[] arr;
    delete[] result;

}

RC_GTEST_PROP(GetSortedTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int* arr      = new int[values.size()];
    int* original = new int[values.size()];
    for (size_t i = 0; i < values.size(); i++) {
        arr[i]      = values[i];
        original[i] = values[i];
    }

    int* result = get_sorted(arr, values.size());

    for (size_t i = 0; i < values.size(); i++) {
        RC_ASSERT(arr[i] == original[i]);
    }

    delete[] arr;
    delete[] original;
    delete[] result;
}

RC_GTEST_PROP(GetSortedTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int* arr = new int[values.size()];
    for (size_t i = 0; i < values.size(); i++) arr[i] = values[i];

    int* result = get_sorted(arr, values.size());


    RC_ASSERT(arr != result);


    for (size_t i = 0; i < values.size(); i++) {
        RC_ASSERT(&arr[i] != &result[i]);
    }

    delete[] arr;
    delete[] result;

}











