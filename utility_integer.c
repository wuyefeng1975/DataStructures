#include "utility_integer.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

long get_random_integer( long min, long max )
{
	time_t t;
	static int i = 0;
	srand(time(&t) + i++);
	return rand() % ( max - min + 1 ) + min;
}

int random_integer(int min, int max)
{
	return rand() % ( max - min + 1 ) + min;
}

void print_int_array(int *arr, int size)
{
    for( int i = 0; i < size; i++ )
        printf( "%d\t", arr[i] );
    printf( "\n" );    
}

void swap_int_value(int *value1, int *value2)
{
    int temp = *value1;
    *value1 = *value2;
    *value2 = temp;
}