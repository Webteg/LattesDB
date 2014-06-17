/*
 * LDBLinkedList.h
 *
 *  Created on: May 21, 2014
 *      Author: marcos
 */

#ifndef LDBLINKEDLIST_H_
#define LDBLINKEDLIST_H_

#include <fstream>
#include <vector>

namespace std {

class LDBLinkedList {
	fstream file;
	static const int SIZE_ULINT = sizeof(unsigned long int);
public:
	LDBLinkedList();
	LDBLinkedList(string file_name);
	void open(string file_name);
	bool is_open();
	unsigned long int newList(unsigned long int val, unsigned long int next = 0);
	void addToList (unsigned long int val, unsigned long int list);
	vector<unsigned long int> getList (unsigned long int list);
	void close();
	virtual ~LDBLinkedList();
};

} /* namespace std */
#endif /* LDBLINKEDLIST_H_ */
