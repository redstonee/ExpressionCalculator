#include<iostream>
#include<string>
#include<sstream>
#include<string.h>
#include"node.hpp"
#include"tree_printer.hpp"
using namespace std;

bool isSign(char ch) {
	return ch == '-' || ch == '+' || ch == '*' || ch == '/';
}


class Parser {
	istringstream stream;
	Node* head=nullptr;
public:
	Parser(string line) : stream{ line } {

	}
	Node* parse() {
		while (!stream.eof() && stream.peek() != -1) {
			//cout << "Parse\n";
			head = term(head);
		}
		return head;
	}

	Node* paranthesis(Node* localHead=nullptr) {
		char ch = 'n';
		//cout << "paranthesis" << endl;
		do  {
			localHead = term(localHead);
			if (stream.eof())
				throw exception("You didn't close the paranthesis");
			ch = stream.peek();
			//cout << "paranthesis " << ch << endl;
		} while (ch != ')');
		stream >> ch;
		//cout << "END PARANTHESIS\n";
		return localHead;
	}


	Node* expression(Node* leftNode = nullptr) {
		
		if (stream.eof() || stream.peek()==-1)
			return leftNode;
		char ch; 
		do {
			stream >> ch;
		} while (ch == ' ');
		Node* node = nullptr;
		//cout << "expression ch="  << ch << endl;
		//Node* rightNode;
		if (ch >= '0' && ch <= '9') {
			stream.putback(ch);
			node = number();
			return expression(node);
		}
		else {
			switch (ch) {
			case ')': stream.putback(ch);  return leftNode;
			case '(':  return paranthesis();
			case '+':
			case '-': {
				stream.putback(ch);
				return leftNode;
			}
			case '^':return power(leftNode);
			case '*':
			case '/': {
				if (!leftNode) {
					throw exception("Left node is null in division or multiplication");
				}
				//cout << "Expression " << ch << endl;
				node = new Node;
				node->op = ch;
				node->left = leftNode;
				node->right = expression();
				return node;
			}
			default: {
				char a[] = "Unknown character:  ";
				a[sizeof(a) - 2] = ch;
				throw exception(a);
			}
		}
		}
	}

	Node* power(Node* leftNode) {
		Node* node = new Node;
		node->op ='^';
		node->left = leftNode;
		if (stream.peek() == '(') {
			stream.ignore(1);
			node->right = paranthesis();
		}
		else if (isdigit(stream.peek()))
			node->right = number();
		else
			throw exception("'(' or number expected after '^'");
		return node;
	}

	Node* term(Node* leftNode = nullptr) {
		char ch;
		stream >> ch;
		//cout << "Term " << ch << endl;
		if (ch == '+' || ch == '-') {
			char sign = ch;
			if (!leftNode) {
				//cout << "leftNode=null" << endl;
				ch = stream.peek();
				if ((isdigit(ch) || ch == '(') && sign == '-') {
					Node* head = new Node;
					head->op = '*';
					head->left = new Node;
					head->left->val = -1;
					head->right = expression();
					return head;
				}
				else
					return expression();
				}
			Node* node = new Node;
			node->op=ch;
			node->left = leftNode;

			node->right = expression();
			return node;
		}
		else {
			stream.putback(ch);
			return expression(leftNode);
		}
	}
	Node* number() {
		Node* node = new Node;
		stream >> node->val;
		//cout << "Number" << node->val << endl;
		return node;
	}
};

void print(Node* head) {
	if (head == nullptr)
		return;
	if(head->op!='x')
	cout << "(";
	print(head->left);
	if (head->op == 'x')
		cout << head->val;
	else
		cout << head->op;
	print(head->right);
	if(head->op!='x')
	cout << ')';
}

class CalculatorManager {
	Parser parser;
};

int main() {
	string str;
	getline(cin, str);
	Parser parser{ str };
	try {
		Node* node = parser.parse();
		cout << " = " << node->eval() << endl;
		print(node);
		TreePrinter x;
		cout << "\n";
		x.printTree(node);
	}
	catch (exception e) {
		cout << "ERROR: " << e.what();
	}
	cin.get();
	cin.get();
}