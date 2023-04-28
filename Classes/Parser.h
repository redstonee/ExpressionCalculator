#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include "TreeNode.h"

using namespace std;

namespace Parser
{
    extern istringstream stream;
    extern TreeNode *head;

    bool isSign(char ch);
    TreeNode *parse(string s);
    TreeNode *paranthesis(TreeNode *localHead);
    TreeNode *expression(TreeNode *leftNode);
    TreeNode *term(TreeNode *leftNode);
    TreeNode *newNumberNode();
    TreeNode *power(TreeNode *leftNode);
};

struct FuckException : public exception
{
    const char *msg;
    FuckException(string s) : msg(s.c_str()){};
    FuckException(const char *s) : msg(s){};
    const char *what() const throw() { return msg; }
};