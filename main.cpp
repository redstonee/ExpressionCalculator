#include "calculator.h"
#include "treePrinter.h"
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
		Parser parser{str};
		try
		{
			TreeNode *node = parser.parse();
			cout << str << " = " << node->eval() << endl;
			// print(node);
			TreePrinter x;
			cout << "\n";
			x.printTree(node);
		}
		catch (exception e)
		{
			cout << "ERROR: " << e.what();
		}
		cout << "\nPress Enter to continue...";
		getline(cin, str);
		getline(cin, str);
		system("cls");
	}
}