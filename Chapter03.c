#include <stdio.h>
#include <stdbool.h>
#include "List.h"

void PrintList( List L )
{
    Position p = ListHeader( L )->Next;
    while( p != NULL )
    {
        printf( "%d\n", p->Element );
        p = p->Next;
    }
}

void SwapAdjacentElement( ElementType X, List L )
{
    Position current = ListFind( X, L );
    if( current == NULL )
    {
        printf( "Element has not been found!\n" );
        return;
    }
    if( ListIsLastOne( current, L ) )
    {
        printf( "It is the last element. Without element to be swaped\n" );
        return;
    }
    Position previous = ListFindPrevious( X, L );
    Position tempPosition = current;
    Position nextPosition = current->Next;

    previous->Next = current->Next;
    current->Next = nextPosition->Next;
    nextPosition->Next = current;
}

void Exerice_03_01( List L )
{
    printf( "Print List\n" );
    PrintList( L );    
}

void Exerice_03_02()
{
    printf( "<E-03-02>\n" );
    List L = ListInit();
    List P = ListInit();

    Position headerP = ListHeader( P );
    Position headerL = ListHeader( L );
    for( int i = 0; i < 10; i++ )
        ListInsert( i, L, headerL );
    for( int i = 4; i > 0; i-- )
        ListInsert( 2 * i, P, headerP );

    Position l = headerL->Next;
    Position p = headerP->Next;
    int currentIndex = 0;
    while( l != NULL && p != NULL )
    {
        int printIndex = p->Element;
        if( currentIndex == printIndex )
        {
            printf( "%d ", l->Element );
            p = p->Next;
            l = l->Next;
        }
        else if ( currentIndex < printIndex )
        {
            l = l->Next;
        }
        else
        {
            p = p->Next;
        }
        currentIndex++;
    }
    printf( "</E-03-02>\n" );
}

void Exerice_03_03( List L )
{
    printf( "Print List Exerice 3\n" );
    SwapAdjacentElement( 5, L );   
    PrintList( L );
}

void Exerice_03_04()
{
    printf( "<E-03-04>\n" );

    List L1, L2, L3;
    L1 = ListInit();
    L2 = ListInit();
    L3 = ListInit();

    Position header1 = ListHeader( L1 );
    Position header2 = ListHeader( L2 );
    Position header3 = ListHeader( L3 );

    for( int i = 0; i < 10; i++ )
        ListInsert( i, L1, header1 );
    for( int i = 0; i < 10; i++ )
        ListInsert( 2 * i, L2, header2 );

    Position p1 = header1->Next;
    Position p2 = header2->Next;
    while( p1 != NULL && p2 != NULL )
    {
        if( p1->Element > p2->Element )
        {
            p1 = p1->Next;
        }
        else if( p1->Element < p2->Element )
        {
            p2 = p2->Next;
        }
        else
        {
            ListInsert( p1->Element, L3, header3 );
            p1 = p1->Next;
            p2 = p2->Next;
        }
    }
    printf( "^ elements are:\n" );
    PrintList( L3 );

    ListDestory( L1 );
    ListDestory( L2 );
    ListDestory( L3 );

    printf( "</E-03-04>\n" );
}

void Exerice_03_05()
{
    printf( "<E-03-05>\n" );

    List L1, L2, L3;
    L1 = ListInit();
    L2 = ListInit();
    L3 = ListInit();

    Position header1 = ListHeader( L1 );
    Position header2 = ListHeader( L2 );
    Position header3 = ListHeader( L3 );

    for( int i = 0; i < 10; i++ )
        ListInsert( i, L1, header1 );
    for( int i = 0; i < 10; i++ )
        ListInsert( 2 * i, L2, header2 );

    Position p1 = header1->Next;
    Position p2 = header2->Next;
    while( p1 != NULL && p2 != NULL )
    {
        if( p1->Element > p2->Element )
        {
            ListInsert( p1->Element, L3, header3 );
            p1 = p1->Next;
        }
        else if( p1->Element < p2->Element )
        {
            ListInsert( p2->Element, L3, header3 );
            p2 = p2->Next;
        }
        else
        {
            ListInsert( p1->Element, L3, header3 );
            p1 = p1->Next;
            p2 = p2->Next;
        }
    }
    printf( "U elements are:\n" );
    PrintList( L3 );

    ListDestory( L1 );
    ListDestory( L2 );
    ListDestory( L3 );

    printf( "</E-03-05>\n" );
}


int main()
{
    List myList = ListInit();
    for( int i = 0; i < 10; i++ )
        ListInsert( i, myList, myList );
    Exerice_03_01( myList );
    Exerice_03_02();
    Exerice_03_03( myList );
    Exerice_03_04();
    Exerice_03_05();

    ListDestory( myList );

    return 0;
}
