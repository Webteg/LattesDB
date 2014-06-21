/*
 * intersection.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: marcos
 */
/*
 * sorting.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: marcos
 */
#include "main.h"

#ifdef MAIN_INTERSECTION

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

		cout << "\nTring to get records by name and institution prefix..."
				<< endl;
		cout << "Sorting: Alphabetical." << endl << flush;
		results = lattes.get_by_name_and_institution_prefix("", "a");
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_name() << " - " << r.get_institution()
					<< endl;
		}
		cout << "####################################################" << endl;

		cout << "\nTring to get records by name and institution prefix..."
				<< endl;
		cout << "Sorting: Alphabetical Reverse." << endl << flush;
		results = lattes.get_by_name_and_institution_prefix("A", "U",
				BY_ALPHABETICAL_ORDER_REV);
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_name() << " - " << r.get_institution()
					<< endl;
		}
		cout << "####################################################" << endl;

		cout << "\nTring to get records by name and institution prefix..."
				<< endl;
		cout << "Sorting: Publications." << endl << flush;
		results = lattes.get_by_name_and_institution_prefix("A", "U",
				BY_N_PUBLICATIONS);
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_n_publications() << " publications - "
					<< r.get_name() << endl;
		}
		cout << "####################################################" << endl;

		cout << "\nTring to get records by name and institution prefix..."
				<< endl;
		cout << "Sorting: Publications Reverse." << endl << flush;
		results = lattes.get_by_name_and_institution_prefix("A", "U",
				BY_N_PUBLICATIONS_REV);
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_n_publications() << " publications - "
					<< r.get_name() << endl;
		}
		cout << "####################################################" << endl;

		cout << "\nTring to get records by name and institution prefix..."
				<< endl;
		cout << "Sorting: Journals." << endl << flush;
		results = lattes.get_by_name_and_institution_prefix("A", "U",
				BY_N_JOURNALS);
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_n_journals() << " journals - "
					<< r.get_name() << endl;
		}
		cout << "####################################################" << endl;

		cout << "\nTring to get records by name and institution prefix..."
				<< endl;
		cout << "Sorting: Journals Reverse." << endl << flush;
		results = lattes.get_by_name_and_institution_prefix("A", "U",
				BY_N_JOURNALS_REV);
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_n_journals() << " journals - "
					<< r.get_name() << endl;
		}
		cout << "####################################################" << endl;

		cout << "\nTring to get records by name and institution prefix..."
				<< endl;
		cout << "Sorting: Events." << endl << flush;
		results = lattes.get_by_name_and_institution_prefix("A", "U",
				BY_N_EVENTS);
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_n_events() << " events - "
					<< r.get_name() << endl;
		}
		cout << "####################################################" << endl;

		cout << "\nTring to get records by name and institution prefix..."
				<< endl;
		cout << "Sorting: Events Reverse." << endl << flush;
		results = lattes.get_by_name_and_institution_prefix("A", "U",
				BY_N_EVENTS_REV);
		i = 0;
		for (LDBRegister r : results) {
			cout << i++ << " - " << r.get_n_events() << " events - "
					<< r.get_name() << endl;
		}
		cout << "####################################################" << endl;

		lattes.close();
	} else {
		cout << "Could not read files." << endl << flush;
	}

	return 0;
}

#endif

