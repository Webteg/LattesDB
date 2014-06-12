/*
 * lattesdb.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: marcos
 */
#include "main.h"

#ifdef MAIN_LATTESDB

#include <vector>
#include <iostream>
#include "LattesDB.h"

using namespace std;

int main() {
	LattesDB lattes("Lattes");
	if (lattes.readXMLDir("xmlLattes")) {
		cout << "Files read.\n\nTring to read files...\n\n" << flush;
		vector<LDBRegister> result = lattes.get_all();
		for (LDBRegister r : result) {
			cout << r.to_string() << flush;
		}
	}
	else{
		cout << "Could not read files." << endl << flush;
	}
	return 0;
}

#endif
