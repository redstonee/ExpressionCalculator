#pragma once
#include"node.hpp"
#include<iostream>
#include<unordered_map>
#include<sstream>
#include<string>
using namespace std;

void floatToString(float f, char* buffer) {
	ostringstream os;
	os << f;
	for (char a : os.str()) {
		*buffer = a;
		buffer++;
	}
}

class TreePrinter {
	static constexpr int border = 3;
	static constexpr int NOTHING = -1;
	static constexpr int LOWEST_PARENT = 0;
	static constexpr int LEFT = 1;
	static constexpr int RIGHT = 2;
	static constexpr int BOTH = 3;
	ostream& outStream;
	vector<vector<char>> output;
	int rightPeak = 0;
	int leftPeak = 0;
	int height = 0;
	int leftPadding = 0;
    unordered_map<Node*, pair<int,int>> hPosFromHead;
	void measureSpace(Node* head, int h = 0);
	void assignRelativePositions(Node* head, int x=0, int y=0);
	pair<Node*, Node*> samePositionNodes();
	pair<Node*, int> lowestParent(Node* left, Node* right, Node* currentNode);
	void normalizeTree(Node* head);
	void printNode(Node* head);
	void drawLineRight(int x, int y, int toX);
	void drawLineLeft(int x, int y, int toX);
public:
	void printTree(Node* head);
	TreePrinter() :outStream{ cout } {}
	TreePrinter(ostream& os) : outStream{ os } {}
};

void TreePrinter::measureSpace(Node* head, int h) {
	if (head->op == 'x') {
		if (hPosFromHead[head].first < leftPeak)
			leftPeak = hPosFromHead[head].first;
		else if (hPosFromHead[head].first > rightPeak)
			rightPeak = hPosFromHead[head].first;
		int h = hPosFromHead[head].second;
		if (h > height) {
			height = h;
			//cout << "newHeight = " << height;
		}
	}
	else {
		measureSpace(head->left);
		measureSpace(head->right);
	}
}


void TreePrinter::assignRelativePositions(Node* head, int x, int y) {
	hPosFromHead[head] = pair<int, int>(x, y);
	//cout << "y=" << y << endl;
	//cout << "confirm y:" << hPosFromHead[head].second<<endl;
	if (head->op != 'x') {
		assignRelativePositions(head->left, x - 3, y + 3);
		assignRelativePositions(head->right, x + 3, y + 3);
	}
}

pair<Node*, Node*> TreePrinter::samePositionNodes() {
	for (auto i = hPosFromHead.begin(); i != hPosFromHead.end(); i++) {
		auto j = i;
		j++;
		for (; j != hPosFromHead.end(); j++)
			if (abs(j->second.first - i->second.first) + abs(j->second.second - i->second.second) < 3)
				return pair<Node*, Node*>(j->first, i->first);
	}
	return pair<Node*, Node*>(nullptr, nullptr);
}


pair<Node*, int> TreePrinter::lowestParent(Node* left, Node* right, Node* currentNode) {
	if (currentNode == left) {
		return pair<Node*, int>(currentNode, LEFT);
	}
	else if (currentNode == right) {
		return pair<Node*, int>(currentNode, RIGHT);
	}

	if (currentNode->op != 'x') {
		pair<Node*, int> l, r;
		l = lowestParent(left, right, currentNode->left);
		r = lowestParent(left, right, currentNode->right);
		if (l.second == LOWEST_PARENT)
			return l;
		else if (r.second == LOWEST_PARENT) {
			return r;
		}
		else if (l.second + r.second == BOTH) {
			return pair<Node*, int>(currentNode, LOWEST_PARENT);
		}
		else if (l.second > 0) {
			return l;
		}
		else if (r.second > 0) {
			return r;
		}
	}
	return pair<Node*, int>(nullptr, NOTHING);
}

void TreePrinter::normalizeTree(Node* head) {
	Node* node = nullptr;
	do {
		auto a = samePositionNodes();
		if (!a.first)
			break;
		auto parentAndVal = lowestParent(a.first, a.second, head);
		node = parentAndVal.first;
		/*
		if (node == nullptr) {
			cout << "node 1: " << a.first->val << " x=" << hPosFromHead[a.first].first << " y=" << hPosFromHead[a.first].second 
				<< " op="<<a.first->op<< endl;
			cout << "node 2: " << a.second->val << " x=" << hPosFromHead[a.second].first << " y=" <<
				hPosFromHead[a.second].second << " op=" << a.second->op << endl;
			cout << "parent is null" << endl;
		}*/
		const auto leftNode = hPosFromHead[node->left];
		const auto rightNode = hPosFromHead[node->right];
		const int rightDiff = 1.5 * (rightNode.second - hPosFromHead[node].second - 1)-1;
		const int leftX = leftNode.first - rightDiff;
		const int leftY = leftNode.second + rightDiff;
		const int rightX = rightNode.first + rightDiff;
		const int rightY = rightNode.second + rightDiff;
		assignRelativePositions(node->right, rightX, rightY);
		//cout << "assignRelativePositions right\n";
		assignRelativePositions(node->left, leftX, leftY);
		//cout << "assignRelativePositions left\n";
	} while (node);
}

void TreePrinter::drawLineRight(int x, int y, int toX) {
	x++; y++;
	for (; x < toX; y++, x++) {
		output[y][x] = '\\';
	}
	
}

void TreePrinter::drawLineLeft(int x, int y, int toX) {
	x--; y++;
	for (; x > toX; y++, x--) {
		output[y][x] = '/';
	}
}

void TreePrinter::printNode(Node* head) {
	auto pos = hPosFromHead[head];
	pos.first += leftPadding;
	if (head->op == 'x')
		floatToString(head->val, &output[pos.second][pos.first]);
	else {
		//cout << "x=" << pos.first << " y=" << pos.second << endl;
		output[pos.second][pos.first] = head->op;
		output[pos.second][pos.first - 1] = '(';
		output[pos.second][pos.first + 1] = ')';
		drawLineLeft(pos.first, pos.second, hPosFromHead[head->left].first + leftPadding);
		drawLineRight(pos.first, pos.second, hPosFromHead[head->right].first + leftPadding);
		printNode(head->left);
		printNode(head->right);
	}
}

void TreePrinter::printTree(Node* head) {
	assignRelativePositions(head);
	//cout << "assignRelativePositions\n";
	normalizeTree(head);
	//cout << "normalizeTree\n";
	measureSpace(head);
	//cout << "measureSpace\n";
	leftPadding = abs(leftPeak);
	height++;
	//cout << "leftPadding = " << leftPadding << endl;
	//cout << "height = " << height << endl;
	output.resize(height);
	int length = leftPadding + rightPeak + border*2;
	for (int i = 0; i < height; i++) {
		output[i].resize(length);
		for (int j = 0; j < length; j++)
			output[i][j] = ' ';
	}

	printNode(head);
	for (auto& v : output) {
		for (auto c : v)
			outStream << c;
		outStream << endl;
	}
}