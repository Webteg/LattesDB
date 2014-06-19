/*
 * seqfile.cpp
 *
 *  Created on: May 19, 2014
 *      Author: marcos
 */
#include "main.h"

#ifdef MAIN_SEQFILE

#include <vector>
#include <iostream>
#include "LDBRegister.h"
#include "LDBSeqFile.h"

using namespace std;

int main() {
	LDBSeqFile file("test.ldb");

	vector<string> journals;
	vector<string> events;
	vector<int> journal_coauthors;
	vector<int> event_coauthors;
	journals.push_back("asdfasd");
	journal_coauthors.push_back(0);
	events.push_back("SIM 2014 - Polarity-Oriented AIG Rewriting for XOR/XNOR");
	event_coauthors.push_back(3);
	LDBRegister reg("Marcos Henrique Backes", "UFRGS", journals, events, journal_coauthors, event_coauthors);
	unsigned int pos = file.write(reg);
	cout << "Inserted at: " << pos << endl;
	cout << "File size: " << file.get_size() << endl;
	file.close();

	cout << "Trying to read the one just inserted:" << endl;
	file.open("test.ldb");
	LDBRegister reg2 = file.read(pos);
	cout << reg2.to_string();

	cout << "Trying to read all entries:" << endl;

	vector<LDBRegister> regs = file.read_all();

	for (LDBRegister v : regs) {
		cout << v.to_string();
	}

	file.close();

	return 0;
}

#endif

