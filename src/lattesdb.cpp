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
		cout << "Size: " << lattes.get_size() << endl;
		cout << "Files read.\n\nTrying to read records by full name...\n\n"
				<< flush;
		LDBRegister result = lattes.get_by_name_full(string("Rodrigo Machado"));
		cout << result.get_name() << endl;
		int i = 0;
		cout << "Trying to read records by name prefix...\n\n" << flush;
		vector<LDBRegister> results = lattes.get_by_name_prefix(string(""));
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_name() << " - " << r.get_institution()
					<< endl;
		}
		cout << "Trying to read records by full institution name...\n\n"
				<< flush;
		results = lattes.get_by_institution_full(
				"Universidade Federal do Rio Grande do Sul");
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_name() << " - " << r.get_institution()
					<< endl;
		}

		cout << "Trying to read records by institution name prefix...\n\n"
				<< flush;
		results = lattes.get_by_institution_prefix("U");
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_name() << " - " << r.get_institution()
					<< endl;
		}
		lattes.close();
	} else {
		cout << "Could not read files." << endl << flush;
	}

	return 0;
}

#endif
