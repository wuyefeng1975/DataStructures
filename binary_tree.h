#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

struct TreeNode;
typedef struct BinaryTreeNode *BinaryTreeNode;
typedef struct BinaryTreeNode *SearchTree;

struct BinaryTreeNode {
    void* element;
    BinaryTreeNode left;
    BinaryTreeNode right;
};

struct PrintNode { 
    void* element;
    int index;
};
typedef struct PrintNode PrintNode;

void BinaryTree_make_empty( BinaryTreeNode *tree );
BinaryTreeNode SearchTree_insert( BinaryTreeNode tree, void* element
                            , int (*compare)( void const *, void const * ) );

int BinaryTree_node_count( BinaryTreeNode tree );
void BinaryTree_print( BinaryTreeNode tree );
int BinaryTree_height( BinaryTreeNode tree, int height );

#endif