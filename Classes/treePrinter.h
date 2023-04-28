#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include "TreeNode.h"

using namespace std;

class TreePrinter
{
	static constexpr int border = 3;
	static constexpr int NOTHING = -1;
	static constexpr int LOWEST_PARENT = 0;
	static constexpr int LEFT = 1;
	static constexpr int RIGHT = 2;
	static constexpr int BOTH = 3;

	int rightPeak = 0;
	int leftPeak = 0;
	int height = 0;
	int leftPadding = 0;

	ostream &outStream;
	vector<vector<char>> output;
	unordered_map<TreeNode *, pair<int, int>> hPosFromHead;
	void measureSpace(TreeNode *head, int h = 0);
	void assignRelativePositions(TreeNode *head, int x = 0, int y = 0);
	pair<TreeNode *, TreeNode *> samePositionNodes();
	pair<TreeNode *, int> lowestParent(TreeNode *left, TreeNode *right, TreeNode *currentNode);
	void normalizeTree(TreeNode *head);
	void printNode(TreeNode *head);
	void drawLineRight(int x, int y, int toX);
	void drawLineLeft(int x, int y, int toX);

public:
	void printTree(TreeNode *head);
	TreePrinter() : outStream{cout} {}
	TreePrinter(ostream &os) : outStream{os} {}
};
