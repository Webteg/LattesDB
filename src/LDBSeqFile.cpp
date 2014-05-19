/*
 * LDBSeqFile.cpp
 *
 *  Created on: May 19, 2014
 *      Author: marcos
 */

#include "LDBSeqFile.h"

#include <iostream>

namespace std {

LDBSeqFile::LDBSeqFile(string file_name) {
	file.open(file_name.c_str(), ios::in | ios::out | ios::app | ios::binary);
}

unsigned int LDBSeqFile::write(LDBRegister reg) {
	file.seekp(0, file.end);
	unsigned int ret = file.tellp();
	unsigned int size;
	string element;
	vector<string> vec;

	//write name
	element = reg.get_name();
	size = element.size() + 1;
	file.write((char*) &size, SIZE_UINT);
	file.write(element.c_str(), size);

	//write institution
	element = reg.get_institution();
	size = element.size() + 1;
	file.write((char*) &size, SIZE_UINT);
	file.write(element.c_str(), size);

	//write list of journals
	vec = reg.get_journals();
	size = vec.size();
	file.write((char*) &size, SIZE_UINT);
	for (string s : vec) {
		size = s.size()+1;
		file.write((char*) &size, SIZE_UINT);
		file.write(s.c_str(), size);
	}

	//write list of events
	vec = reg.get_events();
	size = vec.size();
	file.write((char*) &size, SIZE_UINT);
	for (string s : vec) {
		size = s.size()+1;
		file.write((char*) &size, SIZE_UINT);
		file.write(s.c_str(), size);
	}

	return ret;
}

LDBRegister LDBSeqFile::read(unsigned int pos) {
	file.seekg(pos);
	string name;
	string institution;
	string publication;
	vector<string> journals;
	vector<string> events;
	unsigned int size;
	unsigned int vec_size;
	char buffer[512]; // TODO não é seguro, tentar mudar.

	//read name
	file.read((char*) &size, SIZE_UINT);
	file.read(buffer, size);
	name = buffer;

	//read institution
	file.read((char*) &size, SIZE_UINT);
	file.read(buffer, size);
	institution = buffer;

	//read list of journals
	file.read((char*) &vec_size, SIZE_UINT);
	for (unsigned int i = 0; i < vec_size; i++) {
		file.read((char*) &size, SIZE_UINT);
		file.read(buffer, size);
		publication = buffer;
		journals.push_back(publication);
	}

	//read list of events
	file.read((char*) &vec_size, SIZE_UINT);
	for (unsigned int i = 0; i < vec_size; i++) {
		file.read((char*) &size, SIZE_UINT);
		file.read(buffer, size);
		publication = buffer;
		events.push_back(publication);
	}

	LDBRegister ret(name, institution, journals, events);
	return ret;
}

void LDBSeqFile::close() {
	file.close();
}

LDBSeqFile::~LDBSeqFile() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
