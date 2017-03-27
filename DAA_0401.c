#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insert_sorts();
void insert_sort_01( int *arr, int size );
void insert_sort_02( int *arr, int size );
int create_random_number();
void TestShellSort();
void shell_sort(int *arr, int size);
int f( int n );
int main()
{
    //insert_sorts();
    printf("%d\n", f(15));
    TestShellSort();
    return 0;
}

int f( int n )
{
    if( n <= 1 )
        return 1;
    if( n == 2 )
        return 2;
    return f(n-1) + f(n-2) + f(n-3);
}

void TestShellSort()
{
    int arr[1000000] = {};
    int size = sizeof(arr)/sizeof(int);
    for( int i = 0; i < size; i++ )
        arr[i] = i;

    srand((unsigned)time(NULL));
    for( int i = 0; i < size; i++ )
        arr[i] = create_random_number() % (size * 10);
        
    //insert_sort_01( arr, size );
    shell_sort(arr, size);

    /*
    for( int i = 0; i < size; i++ )
    {
        if( i % 10 == 0)
            printf("\n");
        printf( "%d\t", arr[i] );
    }
    printf("\n");
    */
}

int create_random_number()
{
    return rand();
}

void shell_sort(int *arr, int size )
{
    int intervals[8] = {701, 301, 132, 57, 23, 10, 4, 1};
    //int intervals[3] = { 10, 4, 1 };
    for( int j = 0; j < sizeof(intervals)/sizeof(int); j++ )
    {
        int interval = intervals[j];
        for( int i = 0; i < interval; i++ )
        {
            int flag_index = i + 0 + interval;
            for( int index = interval + i; index < size; index += interval )
            //for( int index = i + 0; index < size; index += interval )
            {
                int k = index - interval;
                int val = arr[index];
                while( k >= 0 && arr[k] > val )
                {
                    arr[k + interval] = arr[k];
                    k -= interval;
                }
                arr[k + interval] = val;
//                printf( "%d\t", arr[index] );
            }
  //          printf( "\n" );
        }
    }
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