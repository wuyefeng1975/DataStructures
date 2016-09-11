#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

struct TreeNode;
typedef struct BinaryTreeNode *BinaryTreeNode;
typedef struct BinaryTreeNode *SearchTree;
typedef struct BinaryTreeNode *BinaryNode;
typedef struct BinaryTree *BinaryTree;

struct BinaryTreeNode {
    void* element;
    BinaryTreeNode left;
    BinaryTreeNode right;
};

struct BinaryTree {
    BinaryNode root;
    size_t data_size;
    void (*assign_func)(void*, const void*);
    int (*compare_func)(void const *, void const *);
    void (*print_element_func)(void*);
};

extern BinaryTree BinaryTree_create( size_t data_size,
                                    void (*assign)(void*, const void*),
                                    int (*compare)(void const *, void const *) );
extern void BinaryTree_make_empty( BinaryTreeNode *tree );
extern void BinaryTree_dispose( BinaryTree *tree );

extern void SearchTree_insert( BinaryTree tree, void* element );

extern int BinaryTree_height( BinaryNode node );
extern int BinaryTree_node_count( BinaryNode node );

extern void BinaryTree_print( BinaryTree tree );

extern BinaryNode SearchTree_find_min( BinaryNode node );
extern BinaryNode SearchTree_find_max( BinaryNode node );
extern BinaryNode SearchTree_find( BinaryTree tree, void *element );

extern BinaryNode SearchTree_delete( BinaryTree tree, void *element );

#endif