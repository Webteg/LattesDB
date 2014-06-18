/*
 * sorting.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: marcos
 */
#include "main.h"

#ifdef MAIN_SORTING

#include <vector>
#include <iostream>
#include <iomanip>
#include "LattesDB.h"

using namespace std;

int main() {

	LattesDB lattes("Lattes");
	if (lattes.readXMLDir("xmlLattes")) {
		int i = 0;
		vector<LDBRegister> results;

		cout << "\nTrying to read records by full institution name..." << flush;
		cout << "Sorting: No Sort." << endl << flush;
		results = lattes.get_by_institution_full(
				"Universidade Federal do Rio Grande do Sul");
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_name() << endl;
		}
		cout << "####################################################" << endl;

		cout << "\nTrying to read records by full institution name..." << flush;
		cout << "Sorting: Alphabetical." << endl << flush;
		results = lattes.get_by_institution_full(
				"Universidade Federal do Rio Grande do Sul",
				BY_ALPHABETICAL_ORDER);
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_name() << endl;
		}
		cout << "####################################################" << endl;

		cout << "\nTrying to read records by full institution name..." << flush;
		cout << "Sorting: Alphabetical Reverse." << endl << flush;
		results = lattes.get_by_institution_full(
				"Universidade Federal do Rio Grande do Sul",
				BY_ALPHABETICAL_ORDER_REV);
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_name() << endl;
		}
		cout << "####################################################" << endl;

		cout << "\nTrying to read records by full institution name..." << flush;
		cout << "Sorting: Publications." << endl << flush;
		results = lattes.get_by_institution_full(
				"Universidade Federal do Rio Grande do Sul", BY_N_PUBLICATIONS);
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_n_publications() << " publications - "
					<< r.get_name() << endl;
		}
		cout << "####################################################" << endl;

		cout << "\nTrying to read records by full institution name..." << flush;
		cout << "Sorting: Publications Reverse." << endl << flush;
		results = lattes.get_by_institution_full(
				"Universidade Federal do Rio Grande do Sul",
				BY_N_PUBLICATIONS_REV);
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_n_publications() << " publications - "
					<< r.get_name() << endl;
		}
		cout << "####################################################" << endl;

		cout << "\nTrying to read records by full institution name..." << flush;
		cout << "Sorting: Journals." << endl << flush;
		results = lattes.get_by_institution_full(
				"Universidade Federal do Rio Grande do Sul", BY_N_JOURNALS);
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_n_journals() << " journals - "
					<< r.get_name() << endl;
		}
		cout << "####################################################" << endl;

		cout << "\nTrying to read records by full institution name..." << flush;
		cout << "Sorting: Journals Reverse." << endl << flush;
		results = lattes.get_by_institution_full(
				"Universidade Federal do Rio Grande do Sul", BY_N_JOURNALS_REV);
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_n_journals() << " journals - "
					<< r.get_name() << endl;
		}
		cout << "####################################################" << endl;

		cout << "\nTrying to read records by full institution name..." << flush;
		cout << "Sorting: Events." << endl << flush;
		results = lattes.get_by_institution_full(
				"Universidade Federal do Rio Grande do Sul", BY_N_EVENTS);
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_n_events() << " events - "
					<< r.get_name() << endl;
		}
		cout << "####################################################" << endl;

		cout << "\nTrying to read records by full institution name..." << flush;
		cout << "Sorting: Events Reverse." << endl << flush;
		results = lattes.get_by_institution_full(
				"Universidade Federal do Rio Grande do Sul", BY_N_EVENTS_REV);
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_n_events() << " events - "
					<< r.get_name() << endl;
		}
		cout << "####################################################" << endl;

	} else {
		cout << "Could not read files." << endl << flush;
	}

	return 0;
}

#endif

