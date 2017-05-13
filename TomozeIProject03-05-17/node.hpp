#pragma once
#include<iostream>
#include<cmath>
using namespace std;
struct Node {
	double val;
	char op = 'x';
	Node *left = nullptr, *right = nullptr;
	Node() {}


	double eval() {
		switch (this->op) {
		case '+': return this->left->eval() + this->right->eval();
		case '-': return this->left->eval() - this->right->eval();
		case '/': return this->left->eval() / this->right->eval();
		case '*': return this->left->eval() * this->right->eval();
		case '^': return pow(this->left->eval(), this->right->eval());
		case 'x': return this->val;
		}
	}

};

