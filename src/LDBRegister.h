/*
 * LDBRegister.h
 *
 *  Created on: May 17, 2014
 *      Author: marcos
 */

#ifndef LDBREGISTER_H_
#define LDBREGISTER_H_

#include <string>
#include <vector>
#include "includes/pugixml.hpp"

namespace std {

class LDBRegister {
	// full name of the researcher.
	string name;

	// institution which the researcher is associated.
	string institution;

	// list of publications in journals of the researcher.
	vector<string> journals;

	// list of publications in events of the researcher.
	vector<string> events;
public:
	/**
	 * Creates a new register from a pugi::xml_parse_result.
	 * @param result - the result of xml parsing.
	 */
	LDBRegister(pugi::xml_parse_result result);

	/**
	 * Creates a new register from parameters
	 * @param name - full name of the researcher.
	 * @param institution - institution which the researcher is associated.
	 * @param journals - list of publications in journals of the researcher.
	 * @param events - list of publications in events of the researcher.
	 */
	LDBRegister(string name, string institution, vector<string> journals,
			vector<string> events);

	/**
	 * Returns the full name of the researcher.
	 * @return the full name of the researcher.
	 */
	string get_name();

	/**
	 * Returns the institution which the researcher is associated.
	 * @return the institution which the researcher is associated.
	 */
	string get_institution();

	/**
	 * Returns the number of publications of the researcher.
	 * @return the number of publications of the researcher.
	 */
	int get_n_publications();

	/*
	 * Returns the number of publications in journals of the researcher.
	 * @return the number of publications in journals of the researcher.
	 */
	int get_n_journals();

	/**
	 * Returns a list of publications in journals of the researcher.
	 * @return a vector with the publications in journals of the researcher.
	 */
	vector<string> get_journals();

	/**
	 * Returns the number of publications in events of the researcher.
	 * @return the number of publications in events of the researcher.
	 */
	int get_n_events();

	/**
	 * Returns a list of publications in events of the researcher.
	 * @return a vector with the publications in events of the researcher.
	 */
	vector<string> get_events();

	virtual ~LDBRegister() {
	}
	;
};

} /* namespace std */
#endif /* LDBREGISTER_H_ */
