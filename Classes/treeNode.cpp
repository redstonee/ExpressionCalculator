#include <cmath>
#include "TreeNode.h"

TreeNode::TreeNode()
{
	this->val = 0;
	this->op = 'x';
	this->left = nullptr;
	this->right = nullptr;
}

double TreeNode::evaluate()
{
	switch (this->op)
	{
	case '+':
		return this->left->evaluate() + this->right->evaluate();
	case '-':
		return this->left->evaluate() - this->right->evaluate();
	case '/':
		return this->left->evaluate() / this->right->evaluate();
	case '*':
		return this->left->evaluate() * this->right->evaluate();
	case '^':
		return pow(this->left->evaluate(), this->right->evaluate());
	default:
		return this->val;
	}
}