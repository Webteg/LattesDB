#include "main.h"

#ifdef MAIN_LINKEDLIST

#include <vector>
#include <iostream>
#include "LDBLinkedList.h"

using namespace std;

int main() {
	LDBLinkedList file("test.ll");
	unsigned int list1 = file.newList(1);
	unsigned int list2 = file.newList(4);
	file.addToList(3, list1);
	file.close();

	LDBLinkedList file2("test.ll");
	file2.addToList(2, list1);
	file2.addToList(6, list2);
	file2.addToList(5, list2);
	file2.close();

	LDBLinkedList file3("test.ll");
	vector<unsigned int> vec1 = file3.getList(list1);
	cout << "List 1: ";
	for (unsigned int i : vec1) {
		cout << i << " ";
	}
	cout << endl << endl;
	vector<unsigned int> vec2 = file3.getList(list2);
	cout << "List 2: ";
	for (unsigned int i : vec2) {
		cout << i << " ";
	}
	cout << endl << endl;
	file2.close();

	return 0;
}

#endif
