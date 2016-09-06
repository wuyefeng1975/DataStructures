#include <stddef.h>
#include "assert.h"
#include "mem.h"
#include "binary_tree.h"
#include "list.h"
#include <stdio.h>


void BinaryTree_make_empty( BinaryTreeNode *tree ) {
    if( *tree != NULL ) {
        BinaryTree_make_empty( &(*tree)->left );
        BinaryTree_make_empty( &(*tree)->right );
        FREE( *tree );
    }
    *tree = NULL;
}

SearchTree SearchTree_insert( BinaryTreeNode tree, void* element
                            , int (*compare)( void const *, void const * ) ) {
    if( tree == NULL ) {
        NEW( tree );
        tree->element = element;
        tree->left = tree->right = NULL;
    } else {
        int result = (*compare)( element, tree->element );
        if( result > 0 ) {
            tree->right = SearchTree_insert( tree->right, element, (*compare) );
        } else if( result < 0 ) {
            tree->left = SearchTree_insert( tree->left, element, (*compare) );
        }
    }

    return tree;
}

int get_node_count( SearchTree tree, int count ) {
    if( tree != NULL ) {
        count++;
        count = get_node_count( tree->left, count );
        count = get_node_count( tree->right, count );
    }
    return count;
}

int BinaryTree_node_count( BinaryTreeNode tree ) {
    return get_node_count( tree, 0 );
}

int BinaryTree_height( BinaryTreeNode tree, int height ) {
    if( tree != NULL ) {
        height++;
        int leftHeight = BinaryTree_height( tree->left, height );
        int rightHeight = BinaryTree_height( tree->right, height );
        height = rightHeight > leftHeight ? rightHeight : leftHeight;
    } 
    return height;
}

void get_same_level_node( BinaryTreeNode tree, int height, List* listArray ) {    
    if( tree != NULL ) {
        List list = *(listArray + height);
        List_push_back( list, tree->element, NULL );
        
        get_same_level_node( tree->left, height + 1, listArray );
        get_same_level_node( tree->right, height + 1, listArray );
    }
}

void get_node_position( BinaryTreeNode tree, BinaryTreeNode* positions, int *index ){
    if( tree != NULL ) {
        get_node_position( tree->left, positions, index );
        *(positions + *index) = tree;
        (*index)++;
        get_node_position( tree->right, positions, index );
    }
}

int find_index( void* element, BinaryTreeNode* positions, int count ) {
    for( int i = 0; i < count; i++ ) {
        if( *(int*)(*(positions + i))->element == *(int*)element )
            return i;
    }

    return -1;
}

void print_tree( BinaryTreeNode tree, int height ) {
    height = BinaryTree_height( tree, 0 );
    List listArray[height];
    for( int i = 0; i < height; i++ ) {
        listArray[i] = List_create( sizeof(int) );
    }
    get_same_level_node( tree, 0, listArray );
    
    int count = BinaryTree_node_count( tree );
    BinaryTreeNode positions[count];
    int index = 0;
    get_node_position( tree, positions, &index );

    for( int i = 0; i < height; i++ ) {
        List list = listArray[i];
        NodePosition pos = list->header;
        int space = 0;
        while( ( pos = pos->next ) != NULL ) {
            int index = find_index( pos->element, positions, count );
            for( ; space < index; space++ )
                printf( " " );
            printf( "%d", *(int*)pos->element );
            
        }
        printf( "\n" );
    }

    for( int i = 0; i < height; i++ ) {
        List_dispose(&listArray[i]);
    }
}

void BinaryTree_print( BinaryTreeNode tree ) {
    print_tree( tree, 0 );    
}