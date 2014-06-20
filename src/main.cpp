/*
 * main.cpp
 *
 *  Created on: Jun 19, 2014
 *      Author: marcos
 */

#include "main.h"

#ifdef MAIN_API

#include "LDBAPI.h"

using namespace std;

int main() {

	LDBAPI api("Lattes");
	api.mainMenu();
	vector<string> events;
	vector<string> journals;
	vector<int> journal_coauthors;
	vector<int> event_coauthors;
	events.push_back("SIM 2014 ashdjfhadskjlfhkjasdhfkjadshfkjhasdkjhkj");
	event_coauthors.push_back(3);
	LDBRegister marcos("Marcos Henrique Backes", "UFRGS", journals, events,
			journal_coauthors, event_coauthors);
	//api.showRegisterData(marcos);
}

#endif
