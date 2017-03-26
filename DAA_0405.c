#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utility_integer.h"

int quick_select(int *arr, int median, int left, int right);
int lomuto_partition(int *arr, int left , int right);
void test_quick_select();

int main()
{
    test_quick_select();
}

int lomuto_partition(int *arr, int left , int right)
{
    int pivot = left;
    int small_end = left;
    for( int index = left + 1; index <= right; index++ )
        if( arr[index] < arr[pivot] )
            swap_int_value( arr + (++small_end), arr + index );
    swap_int_value( arr + pivot, arr + small_end );
    
    return small_end;
}

void test_quick_select()
{
    int arr[13] = {};
    int size = sizeof(arr)/sizeof(int);

    srand((unsigned)time(NULL));
    for( int i = 0; i < size; i++ )
        arr[i] = random_integer(1, 10 * size);

    print_int_array( arr, size );
    printf( "%d\n", quick_select(arr, size/2, 0, size - 1) );
    print_int_array( arr, size );
}

int quick_select(int *arr, int median_index, int left, int right)
{
    int pivot = lomuto_partition( arr, left, right );
    if( pivot == median_index )
        return arr[pivot];
    if( pivot < median_index )
        return quick_select(arr, median_index, ++pivot, right);
    return quick_select(arr, median_index, left, --pivot);
}
