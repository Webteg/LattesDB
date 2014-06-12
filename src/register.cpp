/*
 * register.cpp
 *
 *  Created on: May 17, 2014
 *      Author: marcos
 */
#include "main.h"

#ifdef MAIN_REGISTER

#include <vector>
#include <iostream>
#include "LDBRegister.h"

using namespace std;

int main() {
	vector<string> journals;
	vector<string> events;
	events.push_back("SIM 2014");
	LDBRegister reg("Marcos Henrique Backes", "UFRGS", journals, events);
	cout << reg.get_name() << " - " << reg.get_institution() << endl;
	cout << "Total Pulications: " << reg.get_n_publications() << endl;
	cout << reg.get_n_journals() << " Journal Publication(s): " << endl;
	for (string s : reg.get_journals()) {
		cout << s << endl;
	}
	cout << endl;
	cout << reg.get_n_events() << " Event Publication(s): " << endl;
	for (string s : reg.get_events()) {
		cout << s << endl;
	}
	return 0;
}

#endif

