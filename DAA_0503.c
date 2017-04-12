#include <stdio.h>
#include <stddef.h>
#include "assert.h"
#include "mem.h"
#include "utility_integer.h"
#include "binary_tree.h"

void Exercise_01();
void Execrise_02();
int leaf_count(BinaryTreeNode node);

BinaryTree create_binary_tree();
int int_compare( const void* elem1, const void* elem2 );
void int_element_print( void* element );

void Execrise_06();
void in_order_travel( BinaryTreeNode node );
void post_order_travel( BinaryTreeNode node );

void Execrise_07();

int main()
{
    //Exercise_01();
    //Execrise_02();
    //Execrise_06();
    Execrise_07();

}

void Execrise_07()
{
    BinaryTree tree = BinaryTree_create( sizeof( int ), NULL, &int_compare );
    tree->print_element_func = &int_element_print;
    int i = 2;
    int j = 3;
    int k = 8;
    int l = 9;
    int m = 0;
    int n = 1;
    int o = 4;
    int p = 7;
    int r = 5;
    int s = 6;
    
    SearchTree_insert( tree, &i );
    SearchTree_insert( tree, &j );
    SearchTree_insert( tree, &k );
    SearchTree_insert( tree, &l );
    SearchTree_insert( tree, &m );
    SearchTree_insert( tree, &n );
    SearchTree_insert( tree, &o );
    SearchTree_insert( tree, &p );
    SearchTree_insert( tree, &r );
    SearchTree_insert( tree, &s );

    BinaryTree_print( tree );
    in_order_travel( tree->root );
    printf( "\n" );
    BinaryTree_dispose( &tree );
}

void Execrise_06()
{
    BinaryTree tree = create_binary_tree();
    BinaryTree_print( tree );
    //in_order_travel( tree->root );
    post_order_travel( tree->root );
    printf( "\n" );
    BinaryTree_dispose( &tree );
}

void in_order_travel( BinaryTreeNode node )
{
    if( node != NULL )
    {
        in_order_travel( node->left );
        int_element_print( node->element );
        printf( " " );
        in_order_travel( node->right );
    }
}

void post_order_travel( BinaryTreeNode node )
{
    if( node != NULL )
    {
        post_order_travel( node->left );   
        post_order_travel( node->right );
        int_element_print( node->element );
        printf( " " );
    }
}

void Execrise_02()
{
    BinaryTree tree = create_binary_tree();
    tree->print_element_func = &int_element_print;
    BinaryTree_print( tree );
    printf( "leaf count is: %d\n", leaf_count(tree->root) );

    BinaryTree_dispose( &tree );
}

int leaf_count(BinaryTreeNode node)
{
    if( node == NULL )
        return 0;
    else
    {
        int count = leaf_count(node->left) + leaf_count(node->right);
        return count ? count : 1;
    }
        
}

void Exercise_01()
{
    /*
    int arr[12] = {};
    int size = sizeof(arr)/sizeof(int);
    fill_random_value_to_array(arr, size);

    print_int_array( arr, size );
    */
}

BinaryTree create_binary_tree() 
{
    BinaryTree tree = BinaryTree_create( sizeof( int ), NULL, &int_compare );
    tree->print_element_func = &int_element_print;
    
    int i = 2;
    int j = 3;
    int k = 8;
    int l = 9;
    int m = 0;
    int n = 1;
    int o = 4;
    int p = 7;
    int r = 5;
    int s = 6;

    tree->root = BinaryTree_create_node( tree, &i );
    tree->root->left = BinaryTree_create_node( tree, &j );
    tree->root->right = BinaryTree_create_node( tree, &k );
    tree->root->left->left = BinaryTree_create_node( tree, &l );
    tree->root->left->right = BinaryTree_create_node( tree, &m );
    tree->root->left->right->left = BinaryTree_create_node( tree, &n );
    tree->root->left->right->right = BinaryTree_create_node( tree, &o );
    tree->root->right->left = BinaryTree_create_node( tree, &p );
    tree->root->right->right = BinaryTree_create_node( tree, &r );
    tree->root->right->left->right = BinaryTree_create_node( tree, &s );

    return tree;
}

int int_compare( const void* elem1, const void* elem2 ) 
{
    int int1 = *(int*)elem1;
    int int2 = *(int*)elem2;
    if( int1 < int2 )
        return -1;
    else if( int1 == int2 )
        return 0;
    
    return 1;
}

void int_element_print( void* element ) 
{
    printf( "%d", *(int*)element );
}
