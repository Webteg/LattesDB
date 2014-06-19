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
	LattesDB lattes("Lattes");

	if (lattes.readXMLDir("xmlLattes")) {
		vector<LDBRegister> results = lattes.get_by_institution_prefix("U");
		LDBAPI api("aaaa");
		//api.mainMenu();
		//api.addXMLMenu();
		api.printResults(results);
	}
}

#endif
