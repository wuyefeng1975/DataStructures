#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>

#include "time_elapsed.h"
#include "utility_integer.h"

void exe02_13( long N )
{
    bool is_prime = true;
    for( long i = 2; i * i <= N; i++ )
    {
        if( N % i == 0 ) 
        {
            is_prime = false;
            break;
        }
    }
    if( is_prime )
        printf( "Number %ld is a prime.\n", N );
    else
        printf( "Number %ld is not a prime.\n", N );
}

void exe02_07_1( long N )
{
	long array[N];

	for( long i = 0; i < N; i++ )
	{
		int random;
		bool exist;
		do
		{
			exist = false;
			random = get_random_integer( 1, N );

			for( long j = 0; j < i; j++ )
			{
				if( array[j] == random )
				{
					exist = true;
					break;
				}
			}	 
		} while( exist == true );
		array[i] = random;
	}
}

void exe02_07_2( long N )
{
	int generated[N];
	long array[N];
	for( long i = 0; i < N; i++ )
		generated[i] = 0;
		
	for( long i = 0; i < N; i++ )
	{
		long random;
		do{ 
			random = get_random_integer( 1, N );
		} while( generated[random - 1] == 1 );

		generated[random - 1] = 1;
		
		array[i] = random;
	}
}

void exe02_07_3( long N )
{
	long array[N];
	for( long i = 0; i < N; i++ )
		array[i] = i + 1;
		
	for( long i = 0; i < N; i++ )
	{
		long random = get_random_integer( 1, N );

		long temp = array[i];
		array[i] = array[random - 1];
		array[random - 1] = temp;
	}
}

long Horner( int x, int a[], int size )
{
    long result = 0;
    for( int i = size; i >= 0; i-- )
    {
        result = x * result + a[i];
    }
    
    return result;
}


void Exe02_10()
{
    int x = 3;
    int a[] = { 2, 1, 0, 8, 4 };
    printf( "Horner function calculate: %ld \n", Horner( x, a, 5 ) );    
}

void exe02_06_1( long N )
{
    long sum = 0;
    for( long i = 0; i < N; i++ )
            sum++;
}

void exe02_06_2( long N )
{
    long sum = 0;
    for( long i = 0; i < N; i++ )
        for( long j = 0; j < N; j++ )
            sum++;
}

void exe02_06_3( long N )
{
    long sum = 0;
    long count = N * N;
    for( long i = 0; i < N; i++ )
        for( long j = 0; j < count; j++ )
            sum++;
}

void exe02_06_4( long N )
{
    long sum = 0;
    for( long i = 0; i < N; i++ )
        for( long j = 0; j < i; j++ )
            sum++;
}

void exe02_06_5( long N )
{
    long sum = 0;
    for( long i = 0; i < N; i++ )
    {
        long count = i * i;
        for( long j = 0; j < count; j++ )
            for( long k = 0; k < j; k++ )
                sum++;
    }    
}

void exe02_06()
{
    long N = 100;
    float time_elapsed[6];
    
    start_tick();
    exe02_06_1( N );
    time_elapsed[0] = stop_tick();
    
    start_tick();
    exe02_06_2( N );
    time_elapsed[1] = stop_tick();
    
    start_tick();
    exe02_06_3( N );
    time_elapsed[2] = stop_tick();
    
    start_tick();
    exe02_06_4( N );
    time_elapsed[3] = stop_tick();
     
    start_tick();
    exe02_06_5( N );
    time_elapsed[4] = stop_tick();
    
    for( int i = 0; i < 6; i++ )
        printf( "Time eclapsed:%f\n", time_elapsed[i] );
}

void exe02_07()
{
	float time_elapsed[4];
	long N = 640000;

	start_tick();
//    	exe02_07_1( N );
    	time_elapsed[1] = stop_tick();

	start_tick();
    	exe02_07_2( N );
    	time_elapsed[2] = stop_tick();

	start_tick();
    	exe02_07_3( N );
    	time_elapsed[3] = stop_tick();

	for( int i = 1; i < 4; i++ )
        	printf( "Time eclapsed:%f\n", time_elapsed[i] );
}
int main()
{
//    exe02_07();
    
    exe02_13( 993 );

    return 0;
}
