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
	static const int SIZE_UINT = sizeof(unsigned int);
public:
	LDBLinkedList(string file_name);
	unsigned int newList(unsigned int val, unsigned int next = 0);
	void addToList (unsigned int val, unsigned int list);
	vector<unsigned int> getList (unsigned int list);
	void close();
	virtual ~LDBLinkedList();
};

} /* namespace std */
#endif /* LDBLINKEDLIST_H_ */
