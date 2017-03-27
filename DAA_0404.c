#include <stdio.h>

void Exercise_02();
int LOG( float N );
void Exercise_12();
int RussianPeasant( int n, int m );

int main()
{
    Exercise_02();
    Exercise_12();
}

void Exercise_02()
{
    printf( "log value is: %d\n", LOG(1000000) );
}

void Exercise_12()
{
    printf( "RussianPeasant: %d\n", RussianPeasant(26, 47) );
}

int RussianPeasant( int n, int m )
{
    if( n == 1 )
        return m;
    if( n % 2 == 0 )
        return RussianPeasant( n/2, 2*m );
    else
        return RussianPeasant( (n - 1)/2, 2*m ) + m;
        //Next line's code is error.
        //return RussianPeasant( (n - 1)/2, 2*m + m );
}

int LOG( float N )
{
    if( N > 2 )
        return LOG( N / 2 ) + 1;
    else if( N == 2 )
        return 1;
    else
        return 0;
}