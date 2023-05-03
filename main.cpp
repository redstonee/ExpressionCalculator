#include "Parser.h"
#include "TreePrinter.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	while (true)
	{
		string str;
		cout << "Enter expression>> ";
		cin >> str;
		try
		{
			TreeNode *node = Parser::parse(str);
			cout << str << " = " << node->evaluate() << endl;
			TreePrinter tp;
			cout << "\n";
			tp.printTree(node);
			delete(node);
		}
		catch (exception &e)
		{
			cout << "ERROR: " << e.what();
		}
		cout << "\nPress Enter to continue...";
		getline(cin, str);
		getline(cin, str);
		system("cls");
	}
}