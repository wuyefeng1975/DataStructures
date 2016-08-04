#include <stdio.h>
#include "ListEx.h"
#include "stack.h"

typedef double III;
typedef double *PtrToDouble;
typedef PtrToDouble MyDouble;

#include "except.h"
#include "assert.h"
#include <setjmp.h>

void Test_TRY_CATCH() {
    struct Except_T zeroExcept = { "Can not be zero" };
    TRY
        int i = 0;
        int j = 0;
        if( j == 0 )
            RAISE( zeroExcept );
        printf( "Hello World\n" );
    EXCEPT(zeroExcept)
        printf( "Shit\n");
        Except_flag = Except_entered; 
    END_TRY
    printf( "Out Try catch\n");
    
}

int sqrt( int val ) {
    int i = 1;
    int pow;
    do {
        pow = i * i;
    } while( i <= val || pow < val );

}

int main()
{
    Test_TRY_CATCH();
    /*
    void *vp;
    int j = 11;
    vp = &j;
    int *i = vp;
    (*i)++;
    printf( "%d\n", j );
    
    Stack stack = StackNew();
    double d1 = 11.0;
    MyDouble myD = &d1;
    StackPush( stack, myD );
    
    MyDouble myD2 = (MyDouble)StackPop( stack );
    printf( "%lf\n", *myD2 );
    
    StackFree( stack );
    */
    /*
    III a = 10.0;
    StackPush( stack, &a );
    III *b = (III *)StackPop( stack );
    printf( "%lf\n", *b );
    */
        
    //vp = a;
    return 0;
}
