#include <stddef.h>
#include "assert.h"
#include "mem.h"
#include "binary_tree.h"
#include "list.h"
#include <stdio.h>


BinaryTree BinaryTree_create( size_t data_size,
                                void (*assign)(void*, const void*),
                                int (*compare)(void const *, void const *) ) {
    BinaryTree tree;
    NEW( tree );
    tree->data_size = data_size;
    tree->root = NULL;
    tree->assign_func = assign;
    tree->compare_func = compare;
    tree->print_element_func = NULL;

    return tree;
}

void BinaryTree_dispose( BinaryTree *tree ) {
    BinaryTree_make_empty( &(*tree)->root );
    FREE( *tree );
    *tree = NULL;
}

void BinaryTree_make_empty( BinaryNode *node ) {
    if( (*node) == NULL )
        return;
    
    BinaryTree_make_empty( &(*node)->left );
    BinaryTree_make_empty( &(*node)->right );
    FREE( (*node)->element );
    FREE( *node );
    
    *node = NULL;
}


BinaryNode binary_search_tree_insert( BinaryNode *node, void* element, size_t data_size, 
                            void (*assign)(void*, const void*), 
                            int (*compare)( void const *, void const * ) ) {
    if( (*node) == NULL ) {
        NEW( (*node) );
        void* ptr = ALLOC( data_size );
        if( (*assign) != NULL )
            (*assign)( ptr, element );
        else
            COPY( ptr, element, data_size );
        (*node)->element = ptr;
        (*node)->left = (*node)->right = NULL;
    } else {
        int result = (*compare)( element, (*node)->element );
        if( result > 0 ) {
            (*node)->right = binary_search_tree_insert( &((*node)->right), element, data_size, (*assign), (*compare) );
        } else if( result < 0 ) {
            (*node)->left = binary_search_tree_insert( &((*node)->left), element, data_size, (*assign), (*compare) );
        }
    }

    return *node;
} 

void SearchTree_insert( BinaryTree tree, void* element ) {
    binary_search_tree_insert( &(tree->root), element, tree->data_size, 
                                tree->assign_func, tree->compare_func ) ;
}

int get_node_count( BinaryNode node, int count ) {
    if( node == NULL )
        return count;
    
    count++;
    count = get_node_count( node->left, count );
    count = get_node_count( node->right, count );
    
    return count;
}

int BinaryTree_node_count( BinaryNode node ) {
    return get_node_count( node, 0 );
}

int get_tree_height( BinaryNode node, int height ) {
    if( node == NULL )
        return height;

    height++;
    int leftHeight = get_tree_height( node->left, height );
    int rightHeight = get_tree_height( node->right, height );
    height = rightHeight > leftHeight ? rightHeight : leftHeight;
     
    return height;
}

int BinaryTree_height( BinaryNode node ) { 
    return get_tree_height( node, 0 );
}

void get_same_level_node( BinaryNode node, int height, List* listArray ) {
    if( node == NULL )
        return;    
    
    List list = *(listArray + height);
    List_push_back( list, node->element );
        
    get_same_level_node( node->left, height + 1, listArray );
    get_same_level_node( node->right, height + 1, listArray );
}

void get_node_position( BinaryNode node, BinaryNode* positions, int *index ){
    if( node == NULL )
        return;
    
    get_node_position( node->left, positions, index );
    *(positions + *index) = node;
    (*index)++;
    get_node_position( node->right, positions, index );
    
}

int find_index( void* element, BinaryNode* positions, int count ) {
    for( int i = 0; i < count; i++ ) {
        if( *(int*)(*(positions + i))->element == *(int*)element )
            return i;
    }

    return -1;
}

void BinaryTree_print( BinaryTree tree ) {
    BinaryNode node = tree->root;

    int height = BinaryTree_height( node );
    List listArray[height];
    for( int i = 0; i < height; i++ ) {
        listArray[i] = List_create( tree->data_size, tree->assign_func, tree->compare_func );
    }
    get_same_level_node( node, 0, listArray );
    
    int count = BinaryTree_node_count( node );
    BinaryNode positions[count];
    int index = 0;
    get_node_position( node, positions, &index );

    for( int i = 0; i < height; i++ ) {
        int space = 0;
        List list = listArray[i];
        NodePosition pos = list->header;
        while( ( pos = pos->next ) != NULL ) {
            int index = find_index( pos->element, positions, count );
            for( ; space < index; space++ )
                printf( " " );
            (*tree->print_element_func)( pos->element );
            space++;
        }
        printf( "\n" );
    }
    printf( "\n" );
    
    for( int i = 0; i < height; i++ ) {
        List_dispose(&listArray[i]);
    } 
}

BinaryNode SearchTree_find_min( BinaryNode node ) {
    if( node == NULL )
        return NULL;
    while( node->left != NULL )
        node = node->left;
    return node;
}

BinaryNode SearchTree_find_max( BinaryNode node ) {
    if( node == NULL )
        return NULL;
    while( node->right != NULL )
        node = node->right;
    return node;
}

BinaryNode* search_tree_find( BinaryNode *node, void *element, 
                                int (*compare)( void const *, void const * ) ) {
    assert(compare);

    if( *node == NULL )
        return NULL;

    int result = (*compare)( element, (*node)->element );
    if( result > 0 ) {
        return search_tree_find( &(*node)->right, element, compare );
    } else if( result < 0 ) {
        return search_tree_find( &(*node)->left, element, compare );
    } else {
        return node;
    }
}

BinaryNode SearchTree_find( BinaryTree tree, void *element ) {
    assert( tree->compare_func );

    return *search_tree_find( &tree->root, element, tree->compare_func );
}


BinaryNode* search_tree_delete( BinaryNode *node, void *element, size_t data_size, 
                                int (*compare)( void const *, void const * ), 
                                void (*assign)(void*, const void*) ) {
    assert( compare );

    if( *node == NULL )
        return NULL;

    BinaryNode *find_node = search_tree_find( node, element, compare );
    if( (*find_node)->left != NULL && (*find_node)->right != NULL ) {
        BinaryNode min_node = SearchTree_find_min( (*find_node)->right );
        if( (*assign) != NULL )
            (*assign)( (*find_node)->element, min_node->element );
        else
            COPY( (*find_node)->element, min_node->element, data_size );
        return search_tree_delete( &(*find_node)->right, min_node->element, data_size, compare, assign );
    } else {
        BinaryNode temp_node = *find_node;
        if( (*find_node)->left == NULL )
            *find_node = (*find_node)->right;
        else if( (*find_node)->right == NULL )
            *find_node = (*find_node)->left;
        
        FREE( temp_node->element );
        FREE( temp_node );
    }
    
    return find_node;
}

BinaryNode SearchTree_delete( BinaryTree tree, void *element ) {
    return *search_tree_delete( &tree->root, element, tree->data_size, 
                                tree->compare_func, tree->assign_func );
}
