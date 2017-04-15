#ifndef L4_TREE_H
#define L4_TREE_H

#include "TreeNode.h"

template<class T>
class Tree {
    TreeNode<T>* root;

    void addRec(T value, TreeNode<T>* parent);

    void showInOrderRec(TreeNode<T>* TreeNode);

    bool findRec(T value, TreeNode<T>* TreeNode);

public:
    Tree();

    void insert(T value);

    void inorder();

    bool find(T value);

    int min();

    int max();
};


#endif //L4_TREE_H
