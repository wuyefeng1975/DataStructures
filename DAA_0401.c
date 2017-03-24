#include <stddef.h>
#include <stdio.h>


void insert_sorts();
void insert_sort_01( int *arr, int size );
void insert_sort_02( int *arr, int size );

int main()
{
    insert_sorts();
    return 0;
}

void insert_sorts()
{
    int arr[10] = { 11, 33, 2, 77, 18, 99, 1, 22, 36, 5 };
    insert_sort_01( arr, 10 );
    for( int i = 0; i < 10; i++ )
        printf( "%d\t", arr[i] );
    printf( "\n" );
    int arr2[10] = { 11, 33, 2, 77, 18, 99, 1, 22, 36, 5 };
    insert_sort_02( arr2, 10 );
    for( int i = 0; i < 10; i++ )
        printf( "%d\t", arr2[i] );
    printf( "\n" );
}

void insert_sort_02( int *arr, int size )
{
    for( int i = 1; i < size; i++ )
    {
        int j = i - 1;
        while( j >= 0 && arr[j + 1] < arr[j] )
        {
            int temp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = temp;
            j--;
        }
    }
}

void insert_sort_01( int *arr, int size )
{
    for( int i = 1; i < size; i++ )
    {
        int j = i - 1;
        int val = arr[i];
        while( j >= 0 && arr[j] > val )
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = val;
    }
}