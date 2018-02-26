#ifndef L4_TREE_H
#define L4_TREE_H

#include "TreeNode.h"

template<class T>
class Tree {
    TreeNode<T>* root;
    int treeSize;
    int numberOfOperationsInFind;

    void addRec(T value, TreeNode<T>* parent);

    void showInOrderRec(TreeNode<T>* treeNode);

    bool findRec(T value, TreeNode<T>* treeNode);

    void deleteRec(T value, TreeNode<T>* treeNode);

    void deleteOperation(TreeNode<T>* treeNode);

    TreeNode<T>* findMinimum(TreeNode<T>* treeRoot);

    void changeParentsChildren(TreeNode<T>* treeNode, TreeNode<T>* newChildren);

public:
    Tree();

    void insert(T value);

    void inorder();

    bool find(T value);

    void remove(T value);

    int min();

    int max();

    int size();

    int getNumberOfOperationsInFind();

    void resetNumberOfOperationsInFind();
};


#endif //L4_TREE_H
