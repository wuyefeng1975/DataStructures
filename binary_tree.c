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

void BinaryTree_make_empty( BinaryTreeNode *node ) {
    if( (*node) == NULL )
        return;
    
    BinaryTree_make_empty( &(*node)->left );
    BinaryTree_make_empty( &(*node)->right );
    FREE( (*node)->element );
    FREE( *node );
    
    *node = NULL;
}


BinaryTreeNode binary_search_tree_insert( BinaryTreeNode *node, void* element, size_t data_size, 
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

BinaryTreeNode BinaryTree_create_node( BinaryTree tree, void* element ) {
    BinaryTreeNode node;
    NEW(node);
    
    void* ptr = ALLOC( tree->data_size );
    if( *tree->assign_func != NULL )
        (*tree->assign_func)( ptr, element );
    else
        COPY( ptr, element, tree->data_size );
    node->element = ptr;
    node->left = node->right = NULL;

    return node;
}

void BinaryTree_assign_node_value( BinaryTree tree, 
                                    BinaryTreeNode node, 
                                    void* element ) {
    if( *tree->assign_func != NULL )
        (*tree->assign_func)( node->element, element );
    else
        COPY( node->element, element, tree->data_size );
}

int BinaryTree_node_count( BinaryTreeNode node ) {
    if( node == NULL )
        return 0;
    
    return 1 + BinaryTree_node_count( node->left ) + 
            BinaryTree_node_count( node->right );
}

int get_tree_height( BinaryTreeNode node, int height ) {
    if( node == NULL )
        return height;

    height++;
    int leftHeight = get_tree_height( node->left, height );
    int rightHeight = get_tree_height( node->right, height );
    height = rightHeight > leftHeight ? rightHeight : leftHeight;
    
    return height;
}

int BinaryTree_height( BinaryTreeNode node ) { 
    return get_tree_height( node, 0 );
}

void get_same_level_node( BinaryTreeNode node, int height, List* listArray ) {
    if( node == NULL )
        return;    
    
    List list = *(listArray + height);
    List_push_back( list, node->element );
        
    get_same_level_node( node->left, height + 1, listArray );
    get_same_level_node( node->right, height + 1, listArray );
}

void get_node_position( BinaryTreeNode node, BinaryTreeNode* positions, int *index ){
    if( node == NULL )
        return;
    
    get_node_position( node->left, positions, index );
    *(positions + *index) = node;
    (*index)++;
    get_node_position( node->right, positions, index );
    
}

int find_index( void* element, BinaryTreeNode* positions, int count ) {
    for( int i = 0; i < count; i++ ) {
        if( *(int*)(*(positions + i))->element == *(int*)element )
            return i;
    }

    return -1;
}

void BinaryTree_print( BinaryTree tree ) {
    BinaryTreeNode node = tree->root;

    int height = BinaryTree_height( node );
    List listArray[height];
    for( int i = 0; i < height; i++ ) {
        listArray[i] = List_create( tree->data_size, tree->assign_func, tree->compare_func );
    }
    get_same_level_node( node, 0, listArray );
    
    int count = BinaryTree_node_count( node );
    BinaryTreeNode positions[count];
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

BinaryTreeNode SearchTree_find_min( BinaryTreeNode node ) {
    if( node == NULL )
        return NULL;
    while( node->left != NULL )
        node = node->left;
    return node;
}

BinaryTreeNode SearchTree_find_max( BinaryTreeNode node ) {
    if( node == NULL )
        return NULL;
    while( node->right != NULL )
        node = node->right;
    return node;
}

BinaryTreeNode* search_tree_find( BinaryTreeNode *node, void *element, 
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

BinaryTreeNode SearchTree_find( BinaryTree tree, void *element ) {
    assert( tree->compare_func );

    return *search_tree_find( &tree->root, element, tree->compare_func );
}


BinaryTreeNode* search_tree_delete( BinaryTreeNode *node, void *element, size_t data_size, 
                                int (*compare)( void const *, void const * ), 
                                void (*assign)(void*, const void*) ) {
    assert( compare );

    if( *node == NULL )
        return NULL;

    BinaryTreeNode *find_node = search_tree_find( node, element, compare );
    if( (*find_node)->left != NULL && (*find_node)->right != NULL ) {
        BinaryTreeNode min_node = SearchTree_find_min( (*find_node)->right );
        if( (*assign) != NULL )
            (*assign)( (*find_node)->element, min_node->element );
        else
            COPY( (*find_node)->element, min_node->element, data_size );

        return search_tree_delete( &(*find_node)->right, min_node->element, data_size, 
                                    compare, assign );
    } else {
        BinaryTreeNode temp_node = *find_node;
        if( (*find_node)->left == NULL )
            *find_node = (*find_node)->right;
        else if( (*find_node)->right == NULL )
            *find_node = (*find_node)->left;
        
        FREE( temp_node->element );
        FREE( temp_node );
    }
    
    return find_node;
}

BinaryTreeNode SearchTree_delete( BinaryTree tree, void *element ) {
    return *search_tree_delete( &tree->root, element, tree->data_size, 
                                tree->compare_func, tree->assign_func );
}


int AvlTree_height( BinaryTreeNode node ) {
    if( node == NULL )
        return -1;
    return node->height;
}

int Max( int value_1, int value_2 ) {
    return value_1 > value_2 ? value_1 : value_2;  
}

static BinaryTreeNode SingleRotateWithLeft( BinaryTreeNode root ) {
    BinaryTreeNode new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;

    root->height = Max( AvlTree_height( root->left ), AvlTree_height( root->right ) ) + 1;
    new_root->height = Max( AvlTree_height( new_root->left ), AvlTree_height( new_root->right ) ) + 1;
    
    return new_root;
}

static BinaryTreeNode SingleRotateWithRight( BinaryTreeNode root ) {
    BinaryTreeNode new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    
    root->height = Max( AvlTree_height( root->left ), AvlTree_height( root->right ) ) + 1;
    new_root->height = Max( AvlTree_height( new_root->left ), AvlTree_height( new_root->right ) ) + 1;
    
    return new_root;
}

static BinaryTreeNode DoubleRotateWithLeft( BinaryTreeNode root ) {
    root->left = SingleRotateWithRight( root->left );
    return SingleRotateWithLeft( root );
}

static BinaryTreeNode DoubleRotateWithRight( BinaryTreeNode root ) {
    root->right = SingleRotateWithLeft( root->right );
    return SingleRotateWithRight( root );
}

BinaryTreeNode avl_tree_insert( BinaryTreeNode *node, void* element, size_t data_size, 
                                void (*assign)(void*, const void*), 
                                int (*compare)( void const *, void const * ) ) {
    if( *node == NULL ) {
        NEW( *node );
        void* ptr = ALLOC( data_size );
        if( (*assign) != NULL )
            (*assign)( ptr, element );
        else
            COPY( ptr, element, data_size );
        (*node)->element = ptr;
        (*node)->left = (*node)->right = NULL;
        (*node)->height = 0;
    } else {
        int result = (*compare)( element, (*node)->element );
        if( result > 0 ) {
            avl_tree_insert( &(*node)->right, element, data_size, (*assign), (*compare) );
            if( AvlTree_height( (*node)->right ) - AvlTree_height( (*node)->left ) == 2 ) {
                if( (*compare)( element, (*node)->right->element ) > 0 )
                    *node = SingleRotateWithRight( *node );
                else
                    *node = DoubleRotateWithRight( *node );
            }
        } else if( result < 0 ) {
            avl_tree_insert( &(*node)->left, element, data_size, (*assign), (*compare) );
            if( AvlTree_height( (*node)->left ) - AvlTree_height( (*node)->right ) == 2 ) {
                if( (*compare)( element, (*node)->left->element ) < 0 )
                    *node = SingleRotateWithLeft( *node );
                else
                    *node = DoubleRotateWithLeft( *node );
            }
        }
    } 

    (*node)->height = Max( AvlTree_height( (*node)->right ), AvlTree_height( (*node)->left ) ) + 1;

    return *node;
}

BinaryTreeNode AvlTree_insert( BinaryTree tree, void* element ) {
    return avl_tree_insert( &tree->root, element, tree->data_size,
                            tree->assign_func, tree->compare_func );
}

int avl_tree_delete( BinaryTreeNode *node, void* element, size_t data_size, 
                                int (*compare)( void const *, void const * ), 
                                void (*assign)(void*, const void*) ) {
    if( *node == NULL )
        return 0;
    
    int deleted = 0;
    int result = (*compare)( element, (*node)->element );
    if( result > 0 ) {
        deleted = avl_tree_delete( &(*node)->right, element, data_size,
                                    (*compare), (*assign) );
        if( AvlTree_height( (*node)->left ) - AvlTree_height( (*node)->right ) == 2 ) {
            if( AvlTree_height( (*node)->left->left ) >= AvlTree_height( (*node)->left->right ) ) {
                *node = SingleRotateWithLeft( *node );
            } else {
                *node = DoubleRotateWithLeft( *node );
            }
        }
    } else if( result < 0 ){
        deleted = avl_tree_delete( &(*node)->left, element, data_size,
                                    (*compare), (*assign) );
        if( AvlTree_height( (*node)->right ) - AvlTree_height( (*node)->left ) == 2 ) {
            if( AvlTree_height( (*node)->right->left ) <= AvlTree_height( (*node)->right->right ) ) {
                *node = SingleRotateWithRight( *node );
            } else {
                *node = DoubleRotateWithRight( *node );
            }
        }
    } else {
        if( (*node)->left != NULL && (*node)->right != NULL ) {
            BinaryTreeNode min_node = SearchTree_find_min( (*node)->right );
            if( (*assign) != NULL ) {
                (*assign)( (*node)->element, min_node->element );
            } else {
                COPY( (*node)->element, min_node->element, data_size );
            }
            deleted = avl_tree_delete( &(*node)->right, min_node->element, data_size,
                                        (*compare), (*assign) );
            if( AvlTree_height( (*node)->left ) - AvlTree_height( (*node)->right ) == 2 ) {
                if( AvlTree_height( (*node)->left->left ) >= AvlTree_height( (*node)->left->right ) ) {
                    *node = SingleRotateWithLeft( *node );
                } else {
                    *node = DoubleRotateWithLeft( *node );
                }
            }
        } else {
            BinaryTreeNode temp_node = *node;
            if( (*node)->left == NULL ) {
                *node = (*node)->right;
            } else if( (*node)->right == NULL ) {
                *node = (*node)->left;
            }
            FREE(temp_node->element);
            FREE(temp_node);

            deleted = 1;
        }
    }
    if( *node != NULL )
        (*node)->height = Max( AvlTree_height( (*node)->right ), AvlTree_height( (*node)->left ) ) + 1;

    return deleted;   
}

int AvlTree_delete( BinaryTree tree, void* element ) {
    return avl_tree_delete( &tree->root, element, tree->data_size,
                            tree->compare_func, tree->assign_func );
}
