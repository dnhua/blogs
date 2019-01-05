#include<iostream>
#include"HeapAlg.hpp"

using namespace std;

int main() 
{
	cout << "----------- start test -----------" << endl;
	vector<int> vec = { 0,68,31,65,21,24,32,26,19,16,13 };
	
	cout << "----------- test push_heap -----------" << endl;
	push_heap(vec, 50);
	for (int value : vec) {
		cout << value << endl;
	}

	cout << "----------- test pop_heap -----------" << endl;
	int a = pop_heap(vec);
	cout << a << endl;
	for (int value : vec) {
		cout << value << endl;
	}

	cout << "----------- test sort_heap -----------" << endl;
	sort_heap(vec);
	for (int value : vec) {
		cout << value << endl;
	}
	system("pause");
}