#include <stdio.h>
#include "binary_tree.h"


int int_compare( const void* elem1, const void* elem2 ) {
    int int1 = *(int*)elem1;
    int int2 = *(int*)elem2;
    if( int1 < int2 )
        return -1;
    else if( int1 == int2 )
        return 0;
    
    return 1;
}

void int_element_print( void* element ) {
    printf( "%d", *(int*)element );
}

void Exercise_04_09()
{
    printf( "<E-04-09>\n" );

    BinaryTree tree = BinaryTree_create( sizeof( int ), NULL, &int_compare );
    tree->print_element_func = &int_element_print;
    
    int i = 3;
    int j = 1;
    int k = 4;
    int l = 6;
    int m = 9;
    int n = 2;
    int o = 5;
    int p = 7;

    SearchTree_insert( tree, &i );
    SearchTree_insert( tree, &j );
    SearchTree_insert( tree, &k );
    SearchTree_insert( tree, &l );
    SearchTree_insert( tree, &m );
    SearchTree_insert( tree, &n );
    SearchTree_insert( tree, &o );
    SearchTree_insert( tree, &p );
    BinaryTree_print( tree );

    SearchTree_delete( tree, &i );
    BinaryTree_print( tree );

    BinaryTree_dispose( &tree );
    
    printf( "</E-04-09>\n" );
}

int check_tree_samilarity( BinaryTreeNode node1, BinaryTreeNode node2 ) {
    if( node1 == NULL || node2 == NULL ) 
        return node1 == NULL && node2 == NULL;;

    return check_tree_samilarity( node1->left, node2->left ) && 
            check_tree_samilarity( node1->right, node2->right );
}

void Exercise_04_41()
{
    printf( "<E-04-41>\n" );

    BinaryTree tree1 = BinaryTree_create( sizeof( int ), NULL, &int_compare );
    tree1->print_element_func = &int_element_print;
    BinaryTree tree2 = BinaryTree_create( sizeof( int ), NULL, &int_compare );
    tree2->print_element_func = &int_element_print;

    int i = 3;
    int j = 1;
    int k = 4;
    int l = 6;
    
    SearchTree_insert( tree1, &i );
    SearchTree_insert( tree1, &j );
    SearchTree_insert( tree1, &k );
    SearchTree_insert( tree1, &l );
    BinaryTree_print( tree1 );

    int m = 9;
    int n = 8;
    int o = 15;
    int p = 17;
    SearchTree_insert( tree2, &m );
    SearchTree_insert( tree2, &n );
    SearchTree_insert( tree2, &o );
    SearchTree_insert( tree2, &p );
    BinaryTree_print( tree2 );

    printf( "Is Same: %d\n", check_tree_samilarity( tree1->root, tree2->root ) );

    BinaryTree_dispose( &tree1 );
    BinaryTree_dispose( &tree2 );

    printf( "</E-04-41>\n" );
}

int main()
{
    Exercise_04_09();
    Exercise_04_41();

    return 0;
}
