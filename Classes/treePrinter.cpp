#include "treeNode.h"
#include "treePrinter.h"
#include <sstream>
#include <string>
#include <vector>

using namespace std;

constexpr int TreePrinter::border;
constexpr int TreePrinter::NOTHING;
constexpr int TreePrinter::LOWEST_PARENT;
constexpr int TreePrinter::LEFT;
constexpr int TreePrinter::RIGHT;
constexpr int TreePrinter::BOTH;

void floatToString(float f, char *buffer)
{
	ostringstream os;
	os << f;
	for (char a : os.str())
	{
		*buffer = a;
		buffer++;
	}
}

void TreePrinter::measureSpace(TreeNode *head, int h)
{
	if (head->op == 'x')
	{
		if (hPosFromHead[head].first < leftPeak)
			leftPeak = hPosFromHead[head].first;
		else if (hPosFromHead[head].first > rightPeak)
			rightPeak = hPosFromHead[head].first;
		int h = hPosFromHead[head].second;
		if (h > height)
		{
			height = h;
		}
	}
	else
	{
		measureSpace(head->left);
		measureSpace(head->right);
	}
}

void TreePrinter::assignRelativePositions(TreeNode *head, int x, int y)
{
	hPosFromHead[head] = pair<int, int>(x, y);

	if (head->op != 'x')
	{
		assignRelativePositions(head->left, x - 3, y + 3);
		assignRelativePositions(head->right, x + 3, y + 3);
	}
}

pair<TreeNode *, TreeNode *> TreePrinter::samePositionNodes()
{
	for (auto i = hPosFromHead.begin(); i != hPosFromHead.end(); i++)
	{
		auto j = i;
		j++;
		for (; j != hPosFromHead.end(); j++)
			if (abs(j->second.first - i->second.first) + abs(j->second.second - i->second.second) < 3)
				return pair<TreeNode *, TreeNode *>(j->first, i->first);
	}
	return pair<TreeNode *, TreeNode *>(nullptr, nullptr);
}

pair<TreeNode *, int> TreePrinter::lowestParent(TreeNode *left, TreeNode *right, TreeNode *currentNode)
{
	if (currentNode == left)
	{
		return pair<TreeNode *, int>(currentNode, LEFT);
	}
	else if (currentNode == right)
	{
		return pair<TreeNode *, int>(currentNode, RIGHT);
	}

	if (currentNode->op != 'x')
	{
		pair<TreeNode *, int> l, r;
		l = lowestParent(left, right, currentNode->left);
		r = lowestParent(left, right, currentNode->right);
		if (l.second == LOWEST_PARENT)
			return l;
		else if (r.second == LOWEST_PARENT)
		{
			return r;
		}
		else if (l.second + r.second == BOTH)
		{
			return pair<TreeNode *, int>(currentNode, LOWEST_PARENT);
		}
		else if (l.second > 0)
		{
			return l;
		}
		else if (r.second > 0)
		{
			return r;
		}
	}
	return pair<TreeNode *, int>(nullptr, NOTHING);
}

void TreePrinter::normalizeTree(TreeNode *head)
{
	TreeNode *node = nullptr;
	do
	{
		auto a = samePositionNodes();
		if (!a.first)
			break;
		auto parentAndVal = lowestParent(a.first, a.second, head);
		node = parentAndVal.first;

		const auto leftNode = hPosFromHead[node->left];
		const auto rightNode = hPosFromHead[node->right];
		const int rightDiff = 1.5 * (rightNode.second - hPosFromHead[node].second - 1) - 1;
		const int leftX = leftNode.first - rightDiff;
		const int leftY = leftNode.second + rightDiff;
		const int rightX = rightNode.first + rightDiff;
		const int rightY = rightNode.second + rightDiff;
		assignRelativePositions(node->right, rightX, rightY);
		assignRelativePositions(node->left, leftX, leftY);
	} while (node);
}

void TreePrinter::drawLineRight(int x, int y, int toX)
{
	x++;
	y++;
	for (; x < toX; y++, x++)
	{
		output[y][x] = '\\';
	}
}

void TreePrinter::drawLineLeft(int x, int y, int toX)
{
	x--;
	y++;
	for (; x > toX; y++, x--)
	{
		output[y][x] = '/';
	}
}

void TreePrinter::printNode(TreeNode *head)
{
	auto pos = hPosFromHead[head];
	pos.first += leftPadding;
	if (head->op == 'x')
		floatToString(head->val, &output[pos.second][pos.first]);
	else
	{
		output[pos.second][pos.first] = head->op;
		output[pos.second][pos.first - 1] = '(';
		output[pos.second][pos.first + 1] = ')';
		drawLineLeft(pos.first, pos.second, hPosFromHead[head->left].first + leftPadding);
		drawLineRight(pos.first, pos.second, hPosFromHead[head->right].first + leftPadding);
		printNode(head->left);
		printNode(head->right);
	}
}

void TreePrinter::printTree(TreeNode *head)
{
	assignRelativePositions(head);
	normalizeTree(head);
	measureSpace(head);
	leftPadding = abs(leftPeak);
	height++;
	output.resize(height);
	int length = leftPadding + rightPeak + border * 2;
	for (int i = 0; i < height; i++)
	{
		output[i].resize(length);
		for (int j = 0; j < length; j++)
			output[i][j] = ' ';
	}

	printNode(head);
	for (auto &v : output)
	{
		for (auto c : v)
			outStream << c;
		outStream << endl;
	}
}