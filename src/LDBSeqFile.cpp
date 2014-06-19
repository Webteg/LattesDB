/*
 * LDBSeqFile.cpp
 *
 *  Created on: May 19, 2014
 *      Author: marcos
 */

#include "LDBSeqFile.h"

#include <iostream>

namespace std {

LDBSeqFile::LDBSeqFile() {
	size = 0;
}

LDBSeqFile::LDBSeqFile(string file_name) {
	file.open(file_name.c_str(), ios::in | ios::out | ios::binary);
	if (!file.is_open()) {
		file.open(file_name.c_str(),
				ios::in | ios::out | ios::binary | ios::trunc);
		size = 0;
		file.seekp(file.beg);
		file.write((char*) &size, SIZE_UINT); //makes sure position 0 is empty.
	} else {
		file.read((char*) &size, SIZE_UINT);
	}
}

void LDBSeqFile::open(string file_name) {
	file.open(file_name.c_str(), ios::in | ios::out | ios::binary);
	if (!file.is_open()) {
		file.open(file_name.c_str(),
				ios::in | ios::out | ios::binary | ios::trunc);
		unsigned int size = 0;
		file.seekp(file.beg);
		file.write((char*) &size, SIZE_UINT); //makes sure position 0 is empty.
	} else {
		file.read((char*) &size, SIZE_UINT);
	}
}

bool LDBSeqFile::is_open() {
	return file.is_open();
}

unsigned long int LDBSeqFile::write(LDBRegister reg) {
	file.seekp(0, file.end);
	unsigned long int ret = file.tellp();
	unsigned int size;
	string element;
	vector<string> vec;
	vector<int> vec_n;

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
		size = s.size() + 1;
		file.write((char*) &size, SIZE_UINT);
		file.write(s.c_str(), size);
	}

	//write list of journal_coauthors
	vec_n = reg.get_journal_coauthors();
	for (int n : vec_n) {
		char c = n;
		file.write(&c, SIZE_CHAR);
	}

	//write list of events
	vec = reg.get_events();
	size = vec.size();
	file.write((char*) &size, SIZE_UINT);
	for (string s : vec) {
		size = s.size() + 1;
		file.write((char*) &size, SIZE_UINT);
		file.write(s.c_str(), size);
	}

	//write list of event_coauthors
	vec_n = reg.get_event_coauthors();
	for (int n : vec_n) {
		char c = n;
		file.write(&c, SIZE_CHAR);
	}
	file.flush();
	this->size++;
	return ret;
}

LDBRegister LDBSeqFile::read(unsigned long int pos) {
	file.seekg(pos);
	string name;
	string institution;
	string publication;

	unsigned int size;
	unsigned int vec_size;
	char buffer[BUFFER_SIZE]; // TODO não é seguro, tentar mudar.

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
	vector<string> journals(vec_size);
	for (unsigned int i = 0; i < vec_size; i++) {
		file.read((char*) &size, SIZE_UINT);
		file.read(buffer, size);
		publication = buffer;
		journals[i] = publication;
	}
	//read list of journal_coauthors
	vector<int> journal_coauthors(vec_size);
	for (unsigned int i = 0; i < vec_size; i++) {
		char c;
		file.read(&c, SIZE_CHAR);
		journal_coauthors[i] = c;
	}

	//read list of events
	file.read((char*) &vec_size, SIZE_UINT);
	vector<string> events(vec_size);
	for (unsigned int i = 0; i < vec_size; i++) {
		file.read((char*) &size, SIZE_UINT);
		file.read(buffer, size);
		publication = buffer;
		events[i] = publication;
	}

	vector<int> event_coauthors(vec_size);
	for (unsigned int i = 0; i < vec_size; i++) {
		char c;
		file.read(&c, SIZE_CHAR);
		event_coauthors[i] = c;
	}
	LDBRegister rec(name, institution, journals, events, journal_coauthors,
			event_coauthors);

	LDBRegister ret(name, institution, journals, events, journal_coauthors,
			event_coauthors);
	return ret;
}

vector<LDBRegister> LDBSeqFile::read_all() {
	vector<LDBRegister> ret;
	file.seekg(SIZE_UINT, file.beg);
	file.peek();
	while (file.good()) {
		string name;
		string institution;
		string publication;

		unsigned int size;
		unsigned int vec_size;
		char buffer[BUFFER_SIZE]; // TODO não é seguro, tentar mudar.

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
		vector<string> journals(vec_size);
		for (unsigned int i = 0; i < vec_size; i++) {
			file.read((char*) &size, SIZE_UINT);
			file.read(buffer, size);
			publication = buffer;
			journals[i] = publication;
		}
		//read list of journal_coauthors
		vector<int> journal_coauthors(vec_size);
		for (unsigned int i = 0; i < vec_size; i++) {
			char c;
			file.read(&c, SIZE_CHAR);
			journal_coauthors[i] = c;
		}

		//read list of events
		file.read((char*) &vec_size, SIZE_UINT);
		vector<string> events(vec_size);
		for (unsigned int i = 0; i < vec_size; i++) {
			file.read((char*) &size, SIZE_UINT);
			file.read(buffer, size);
			publication = buffer;
			events[i] = publication;
		}

		vector<int> event_coauthors(vec_size);
		for (unsigned int i = 0; i < vec_size; i++) {
			char c;
			file.read(&c, SIZE_CHAR);
			event_coauthors[i] = c;
		}
		LDBRegister rec(name, institution, journals, events, journal_coauthors,
				event_coauthors);
		ret.push_back(rec);

		file.peek();
	}
	return ret;
}

void LDBSeqFile::close() {
	file.seekp(file.beg);
	file.write((char*) &size, SIZE_UINT);
	file.close();
}

unsigned int LDBSeqFile::get_size() {
	return size;
}

LDBSeqFile::~LDBSeqFile() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
