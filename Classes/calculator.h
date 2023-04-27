#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "treeNode.h"
using namespace std;
class Parser
{
private:
    istringstream *stream;
    TreeNode *head;

public:
    Parser(string line);
    
    bool isSign(char ch);
    TreeNode *parse();
    TreeNode *paranthesis(TreeNode *localHead);
    TreeNode *expression(TreeNode *leftNode);
    TreeNode *term(TreeNode *leftNode);
    TreeNode *number();
    TreeNode *power(TreeNode *leftNode);
};
