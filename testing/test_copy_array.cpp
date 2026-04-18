#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(CopyArrayTests, SimpleValuesAreSame) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {9,10,12,11,5,17,14,18};
    int leng = 8;

     int* copy = copy_array(arr, leng);
    for (int i = 0 ; i < leng ; i++) {
        EXPECT_EQ(copy[i], arr[i]);
    }

    delete [] copy;

}

TEST(CopyArrayTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {9,10,12,11,5,17,14,18};
    int leng = 8;

    int original[] = {9,10,12,11,5,17,14,18};
    int* copy = copy_array(arr, leng);

    for (int i = 0 ; i < leng ; i++) {
        EXPECT_EQ(arr[i], original[i]);
    }

    delete [] copy;

}

TEST(CopyArrayTests, SimpleCopyWasMade) {
    /*
     * Check that a copy was actually made
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int arr[] = {9,10,12,11,5,17,14,18};
    int leng = 8;


    int* copy = copy_array(arr, leng);

    EXPECT_NE(arr, copy);

    for (int i = 0 ; i < leng ; i++) {
        EXPECT_NE( &copy[i], &arr[i]);
    }

    delete [] copy;


}


RC_GTEST_PROP(CopyArrayTests,
              PropertyValuesAreSame,
              (const std::vector<int>& values)
) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int* arr  = new int[values.size()];
    for (size_t i = 0; i < values.size(); i++) arr[i] = values[i];

    int* copy = copy_array(arr, values.size());

    for (size_t i = 0; i < values.size(); i++) {
        RC_ASSERT(copy[i] == arr[i]);
    }

    delete[] arr;
    delete[] copy;
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int* arr      = new int[values.size()];
    int* original = new int[values.size()];
    for (size_t i = 0; i < values.size(); i++) {
        arr[i]      = values[i];
        original[i] = values[i];
    }

    int* copy = copy_array(arr, values.size());

    for (size_t i = 0; i < values.size(); i++) {
        RC_ASSERT(arr[i] == original[i]);
    }

    delete[] arr;
    delete[] original;
    delete[] copy;
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
  * Check that a copy was actually made
  * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
  * Don't forget to free any memory that was dynamically allocated as part of your test.
  */
    int* arr  = new int[values.size()];
    for (size_t i = 0; i < values.size(); i++) arr[i] = values[i];

    int* copy = copy_array(arr, values.size());


    RC_ASSERT(arr != copy);


    for (size_t i = 0; i < values.size(); i++) {
        RC_ASSERT(&copy[i] != &arr[i]);
    }

    delete[] arr;
    delete[] copy;
}



