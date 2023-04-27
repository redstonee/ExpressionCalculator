#pragma once
#include <cmath>
#include "treeNode.h"

TreeNode::TreeNode()
{
	this->val = 0;
	this->op = 'x';
	this->left = nullptr;
	this->right = nullptr;
}

double TreeNode::eval()
{
	switch (this->op)
	{
	case '+':
		return this->left->eval() + this->right->eval();
	case '-':
		return this->left->eval() - this->right->eval();
	case '/':
		return this->left->eval() / this->right->eval();
	case '*':
		return this->left->eval() * this->right->eval();
	case '^':
		return pow(this->left->eval(), this->right->eval());
	case 'x':
		return this->val;
	}
}