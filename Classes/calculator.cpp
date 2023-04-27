#include "calculator.h"
#include "treePrinter.h"

using namespace std;

Parser::Parser(string line)
{
	stream = new istringstream(line);
}

bool Parser::isSign(char ch)
{
	return ch == '-' || ch == '+' || ch == '*' || ch == '/';
}

TreeNode *Parser::parse()
{
	while (!stream->eof() && stream->peek() != -1)
	{
		head = term(head);
	}
	return head;
}

TreeNode *Parser::paranthesis(TreeNode *localHead = nullptr)
{
	char ch = 'n';
	do
	{
		localHead = term(localHead);
		if (stream->eof())
			throw "You didn't close the paranthesis";
		ch = stream->peek();
	} while (ch != ')');
	*stream >> ch;
	return localHead;
}

TreeNode *Parser::expression(TreeNode *leftNode = nullptr)
{

	if (stream->eof() || stream->peek() == -1)
		return leftNode;
		
	char ch;
	do
	{
		*stream >> ch;
	} while (ch == ' ');
	TreeNode *node = nullptr;
	if (ch >= '0' && ch <= '9')
	{
		stream->putback(ch);
		node = number();
		return expression(node);
	}
	else
	{
		switch (ch)
		{
		case ')':
			stream->putback(ch);
			return leftNode;
		case '(':
			return paranthesis();
		case '+':
		case '-':
		{
			stream->putback(ch);
			return leftNode;
		}
		case '^':
			return power(leftNode);
		case '*':
		case '/':
		{
			if (!leftNode)
			{
				throw "Left node is null in division or multiplication";
			}
			node = new TreeNode;
			node->op = ch;
			node->left = leftNode;
			node->right = expression();
			return node;
		}
		default:
		{
			char a[] = "Unknown character:  ";
			a[sizeof(a) - 2] = ch;
			throw a;
		}
		}
	}
}

TreeNode *Parser::power(TreeNode *leftNode)
{
	TreeNode *node = new TreeNode;
	node->op = '^';
	node->left = leftNode;
	if (stream->peek() == '(')
	{
		stream->ignore(1);
		node->right = paranthesis();
	}
	else if (isdigit(stream->peek()))
		node->right = number();
	else
		throw "'(' or number expected after '^'";
	return node;
}

TreeNode *Parser::term(TreeNode *leftNode = nullptr)
{
	char ch;
	*stream >> ch;
	if (ch == '+' || ch == '-')
	{
		char sign = ch;
		if (!leftNode)
		{
			ch = stream->peek();
			if ((isdigit(ch) || ch == '(') && sign == '-')
			{
				TreeNode *head = new TreeNode;
				head->op = '*';
				head->left = new TreeNode;
				head->left->val = -1;
				head->right = expression();
				return head;
			}
			else
				return expression();
		}
		TreeNode *node = new TreeNode;
		node->op = ch;
		node->left = leftNode;

		node->right = expression();
		return node;
	}
	else
	{
		stream->putback(ch);
		return expression(leftNode);
	}
}
TreeNode *Parser::number()
{
	TreeNode *node = new TreeNode;
	*stream >> node->val;
	return node;
}

void print(TreeNode *head)
{
	if (head == nullptr)
		return;
	if (head->op != 'x')
		cout << "(";
	print(head->left);
	if (head->op == 'x')
		cout << head->val;
	else
		cout << head->op;
	print(head->right);
	if (head->op != 'x')
		cout << ')';
}
