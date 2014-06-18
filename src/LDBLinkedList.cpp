/*
 * LDBLinkedList.cpp
 *
 *  Created on: May 21, 2014
 *      Author: marcos
 */

#include "LDBLinkedList.h"
#include <iostream>

namespace std {

LDBLinkedList::LDBLinkedList() {

}

LDBLinkedList::LDBLinkedList(string file_name) {
	file.open(file_name.c_str(), ios::in | ios::out | ios::binary);
	if (!file.is_open()) {
		file.open(file_name.c_str(),
				ios::in | ios::out | ios::trunc | ios::binary);
	}
	file.write("\0", 1);
}

unsigned long int LDBLinkedList::newList(unsigned long int val, unsigned long int next) {
	file.seekp(0, file.end);
	unsigned long int ret = file.tellp();
	file.write((char*) &next, SIZE_ULINT);
	int pos = file.tellp();
	file.write((char*) &val, SIZE_ULINT);
	pos = file.tellp();
	if (next == 0)
		file.flush();
	return ret;
}

void LDBLinkedList::open(string file_name) {
	file.open(file_name.c_str(), ios::in | ios::out | ios::binary);
	if (!file.is_open()) {
		file.open(file_name.c_str(),
				ios::in | ios::out | ios::trunc | ios::binary);
	}
	file.write("\0", 1);
}

bool LDBLinkedList::is_open(){
	return file.is_open();
}

void LDBLinkedList::addToList(unsigned long int val, unsigned long int list) {
	file.seekg(list, file.beg);
	unsigned long int next;
	file.read((char*) &next, SIZE_ULINT);
	next = newList(val, next);
	file.seekp(list, file.beg);
	file.write((char*) &next, SIZE_ULINT);
	file.flush();
}

vector<unsigned long int> LDBLinkedList::getList(unsigned long int list) {
	vector<unsigned long int> vec;
	unsigned long int val;
	while (list != 0) {
		file.seekg(list, file.beg);
		file.read((char*) &list, SIZE_ULINT);
		file.read((char*) &val, SIZE_ULINT);
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
