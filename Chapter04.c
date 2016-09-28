#include <stdio.h>
#include <stdlib.h>
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

BinaryTree create_binary_tree() {
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
    
    return tree;
}

void Exercise_04_09()
{
    printf( "<E-04-09>\n" );

    BinaryTree tree = create_binary_tree();
    BinaryTree_print( tree );

    int i = 3;
    SearchTree_delete( tree, &i );
    BinaryTree_print( tree );

    BinaryTree_dispose( &tree );
    
    printf( "</E-04-09>\n" );
}

int get_binary_tree_node_count( BinaryTreeNode node ) {
    if( node == NULL )
        return 0;
    
    return 1 + get_binary_tree_node_count( node->left ) + 
            get_binary_tree_node_count( node->right );
}

int get_binary_tree_leave_count( BinaryTreeNode node ) {
    if( node == NULL )
        return 0;
    if( node->left == NULL && node->right == NULL ) 
        return 1;
    return get_binary_tree_leave_count( node->left ) + 
            get_binary_tree_leave_count( node->right );
}

int get_binary_tree_full_node_count( BinaryTreeNode node ) {
    if( node == NULL )
        return 0;

    return (int)(node->left != NULL && node->right != NULL ? 1 : 0) + 
            get_binary_tree_full_node_count( node->right ) +
            get_binary_tree_full_node_count( node->left );
}

void Exercise_04_28()
{
    printf( "<E-04-28>\n" );

    BinaryTree tree = create_binary_tree();
    BinaryTree_print( tree );
    printf( "Node count is: %d\n", get_binary_tree_node_count( tree->root ) );
    printf( "Leaf count is: %d\n", get_binary_tree_leave_count( tree->root ) );
    printf( "Full node count is: %d\n", get_binary_tree_full_node_count( tree->root ) );
    
    BinaryTree_dispose( &tree );
    
    printf( "</E-04-28>\n" );
}

int generate_random(int min, int max)
{
    if (min <= 0 || max <= 0 || (min > max) )
        return rand();
    if( min == max )
        return min;

    return min + rand() % ( max - min + 1);
}

void generate_rand_binary_search_tree( int min, int max, BinaryTree tree, BinaryTreeNode *node ) {
    if( min > max )
        return;
        
    int rand_number = generate_random(min, max);
    *node = BinaryTree_create_node( tree, &rand_number );
    
    generate_rand_binary_search_tree( rand_number + 1, max, tree, &(*node)->right );
    generate_rand_binary_search_tree( min, rand_number - 1, tree, &(*node)->left );
}

void Exercise_04_29()
{
    printf( "<E-04-29>\n" );

    BinaryTree tree = BinaryTree_create( sizeof( int ), NULL, &int_compare );
    tree->print_element_func = &int_element_print;
    
    generate_rand_binary_search_tree( 11, 19, tree, &tree->root );
    BinaryTree_print( tree );
    BinaryTree_dispose( &tree );
    
    printf( "</E-04-29>\n" );
}

int my_power( int x, int n ) {
    if( n == 0 )
        return 1;
    if( n == 1 )
        return x;
    
    if( n % 2 == 1 )
        return my_power( x * x, n / 2 ) * x;
    else
        return my_power( x * x, n / 2 );
}

void Exercise_04_31()
{
    printf( "<E-04-31>\n" );
    
    BinaryTree tree = BinaryTree_create( sizeof( int ), NULL, &int_compare );
    tree->print_element_func = &int_element_print;
    int height = 3;
    int max = my_power( 2, height + 1 ) - 1;
    for( int i = 1; i <= max; i++ ) 
        AvlTree_insert( tree, &i );
    
    BinaryTree_print( tree );
    BinaryTree_dispose( &tree );
    
    printf( "</E-04-31>\n" );
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
    Exercise_04_28();
    Exercise_04_29();
    Exercise_04_31();
    Exercise_04_41();

    return 0;
}
