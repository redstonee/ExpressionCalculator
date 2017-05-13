/*#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

enum Operation {plus, minus, product, division};
class Operator {
public:
	Operation operation;
	operator Operation() {
		return operation;
	}
	int apply(int a, int b) {
		switch (operation) {
		case Operation::minus: return a - b;
		case Operation::division: return a / b;
		case Operation::product: return a * b;
		case Operation::plus: return a + b;
		}
	}
};
struct State {
	
	vector<Operator> genes;
	State(vector<Operator> Genes) : genes{ Genes }{}
	int evaluate(vector<int> numbers) {
		int s = numbers[0];
		for (int i = 1; i < numbers.size(); i++) {
			s = genes[i].apply(s, numbers[i]);
		}
		return s;
	}
};

int main() {
	ifstream is{ "C:\\Users\\HHAA9\\Desktop\\numbers.txt"};
	vector<int> numbers;
	while (!is.eof()) {
		int nr;
		is >> nr;
		numbers.push_back(nr);
	}
	
	for (int i : numbers) {
		cout << i << " ";
	}

	cin.get();
	cin.get();
}*/