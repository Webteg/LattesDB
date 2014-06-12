/*
 * LDBLinkedList.cpp
 *
 *  Created on: May 21, 2014
 *      Author: marcos
 */

#include "LDBLinkedList.h"
#include <iostream>

namespace std {

LDBLinkedList::LDBLinkedList(string file_name) {
	file.open(file_name.c_str(), ios::in | ios::out | ios::binary);
	if(!file.is_open()){
		file.open(file_name.c_str(), ios::in | ios::out | ios::trunc | ios::binary);
	}
	file.write("\0", 1);
}

unsigned int LDBLinkedList::newList(unsigned int val, unsigned int next) {
	file.seekp(0, file.end);
	unsigned int ret = file.tellp();
	file.write((char*) &next, SIZE_UINT);
	int pos = file.tellp();
	file.write((char*) &val, SIZE_UINT);
	pos = file.tellp();
	if (next == 0)
		file.flush();
	return ret;
}

void LDBLinkedList::addToList(unsigned int val, unsigned int list) {
	file.seekg(list, file.beg);
	int pos = file.tellg();
	unsigned int next;
	file.read((char*) &next, SIZE_UINT);
	pos = file.tellg();
	next = newList(val, next);
	file.seekp(list, file.beg);
	pos = file.tellp();
	file.write((char*) &next, SIZE_UINT);
	pos = file.tellp();
	file.flush();
}

vector<unsigned int> LDBLinkedList::getList(unsigned int list) {
	vector<unsigned int> vec;
	int val;
	while (list != 0) {
		file.seekg(list, file.beg);
		file.read((char*) &list, SIZE_UINT);
		file.read((char*) &val, SIZE_UINT);
		vec.push_back(val);
	}
	return vec;
}

void LDBLinkedList::close() {
	file.close();
}

LDBLinkedList::~LDBLinkedList() {
}

} /* namespace std */
