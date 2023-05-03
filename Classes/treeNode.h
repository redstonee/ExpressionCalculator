#pragma once
class TreeNode
{
public:
    TreeNode();
    double val;
    char op;
    TreeNode *left, *right;

    double evaluate();
};