/*
 * lattesdb.cpp
 *
 *  Created on: Jun 11, 2014
 *      Author: marcos
 */
#include "main.h"

#ifdef MAIN_AUTOCOMPLETE

#include <vector>
#include <iostream>
#include <curses.h>
#include "LattesDB.h"

using namespace std;

int main() {
	LattesDB lattes("Lattes");
	if (lattes.readXMLDir("xmlLattes")) {
		cout << lattes.get_by_name_autocomplete().get_name() << endl;
		lattes.close();
	} else {
		cout << "Could not read files." << endl << flush;
	}
	return 0;
}

#endif
