#include <stdio.h>

int LOG( float N );
void Exercise_02();

int main()
{
    Exercise_02();
}

void Exercise_02()
{
    printf( "log value is: %d\n", LOG(1000000) );
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