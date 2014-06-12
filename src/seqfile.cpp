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
	events.push_back("SIM 2014 - Polarity-Oriented AIG Rewriting for XOR/XNOR");
	LDBRegister reg("Marcos Henrique Backes", "UFRGS", journals, events);
	unsigned int pos = file.write(reg);
	cout << "Inserted at: " << pos << endl;
	file.close();

	cout << "Trying to read the one just inserted:" << endl;
	LDBSeqFile file2("test.ldb");
	LDBRegister reg2 = file2.read(pos);
	cout << reg2.to_string();

	cout << "Trying to read all entries:" << endl;

	vector<LDBRegister> regs = file2.read_all();

	for (LDBRegister v : regs) {
		cout << v.to_string();
	}

	file2.close();

	return 0;
}

#endif

