#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utility_integer.h"

void test_merge_sort();
void merge_sort(int *arr, int *temp_arr, int left, int right );
void merge_array( int *arr, int *temp_arr, int left1, int left2, int right );

int main()
{
    test_merge_sort();
}


void test_merge_sort()
{
    int arr[11] = {};
    int temp_arr[11] = {};
    int size = sizeof(arr)/sizeof(int);

    srand((unsigned)time(NULL));
    for( int i = 0; i < size; i++ )
        arr[i] = random_integer(1, 10 * size);

    print_int_array( arr, size );
    merge_sort( arr, temp_arr, 0, size - 1 );
    print_int_array( arr, size );
}


void merge_sort(int *arr, int *temp_arr, int left, int right )
{
    int size = right - left + 1;
    if( size > 1 )
    {
        int center = ( right + left ) / 2 + 1;
        merge_sort( arr, temp_arr, left, center - 1 );
        merge_sort( arr, temp_arr, center, right );
        merge_array( arr, temp_arr, left, center, right );
    }
}

void merge_array( int *arr, int *temp_arr, int left, int center, int right )
{
    int l_index = left;
    int r_index = center;
    int temp_index = left;
    
    //printf( "%d\t%d\t%d\n", left, center, right );
    
    while( l_index < center && r_index < right + 1)
    {
        if( arr[l_index] > arr[r_index] )
            temp_arr[temp_index++] = arr[r_index++];
        else
            temp_arr[temp_index++] = arr[l_index++];
    }
    while( temp_index <= right )
    {
        if( l_index == center )
            temp_arr[temp_index++] = arr[r_index++];
        else 
            temp_arr[temp_index++] = arr[l_index++];
    }

    temp_index = left;
    while( temp_index <= right)
    {
        arr[temp_index] = temp_arr[temp_index];
        temp_index++;
    }
    //print_int_array( arr, right - left + 1 );
    //printf( "\n" );
}