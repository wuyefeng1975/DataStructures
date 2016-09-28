#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

struct TreeNode;
typedef struct BinaryTreeNode *BinaryTreeNode;
typedef struct BinaryTreeNode *SearchTree;
typedef struct BinaryTree *BinaryTree;

struct BinaryTreeNode {
    void* element;
    BinaryTreeNode left;
    BinaryTreeNode right;
    int height;
};

struct BinaryTree {
    BinaryTreeNode root;
    size_t data_size;
    void (*assign_func)(void*, const void*);
    int (*compare_func)(void const *, void const *);
    void (*print_element_func)(void*);
};

extern BinaryTree BinaryTree_create( size_t data_size,
                                        void (*assign)(void*, const void*),
                                        int (*compare)(void const *, void const *) );
extern void BinaryTree_make_empty( BinaryTreeNode *node );
extern void BinaryTree_dispose( BinaryTree *tree );

extern BinaryTreeNode BinaryTree_create_node( BinaryTree tree, void* element );
extern void SearchTree_insert( BinaryTree tree, void* element );
extern BinaryTreeNode SearchTree_delete( BinaryTree tree, void *element );

extern int BinaryTree_height( BinaryTreeNode node );
extern int BinaryTree_node_count( BinaryTreeNode node );

extern void BinaryTree_print( BinaryTree tree );

extern BinaryTreeNode SearchTree_find_min( BinaryTreeNode node );
extern BinaryTreeNode SearchTree_find_max( BinaryTreeNode node );
extern BinaryTreeNode SearchTree_find( BinaryTree tree, void *element );

extern int AvlTree_height( BinaryTreeNode node );
extern BinaryTreeNode AvlTree_insert( BinaryTree tree, void* element );
extern int AvlTree_delete( BinaryTree tree, void* element );

#endif