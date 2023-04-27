#pragma once
class TreeNode
{
public:
    TreeNode();
    long double val;
    char op;
    TreeNode *left, *right;

    double eval();
};