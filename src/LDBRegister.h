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
#include "pugi/pugixml.hpp"

namespace std {

/**
 * Class for manipulatin a LattesDB register in main memory.
 */
class LDBRegister {

	string name; /**< Full name of the researcher. */

	string institution; /**< Institution which the researcher is associated. */

	vector<string> journals; /**< List of publications in journals of the researcher. */

	vector<string> events; /**< List of publications in events of the researcher. */

public:

	/**
	 * Creates a new empty record.
	 */
	LDBRegister();

	/**
	 * Creates a new register from parameters
	 * @param name Full name of the researcher.
	 * @param institution Institution which the researcher is associated.
	 * @param journals List of publications in journals of the researcher.
	 * @param events List of publications in events of the researcher.
	 */
	LDBRegister(string name, string institution, vector<string> journals,
			vector<string> events);

	/**
	* Loads attributes froma a xml-lattes file.
	* @param file_name Name of the xml file to be opened.
	* @return if success true, else false.
	*/
	bool readXML(string file_name);

	/**
	 * Returns the full name of the researcher.
	 * @return The full name of the researcher.
	 */
	string get_name();

	/**
	 * Returns the institution which the researcher is associated.
	 * @return The institution which the researcher is associated.
	 */
	string get_institution();

	/**
	 * Returns the number of publications of the researcher.
	 * @return The number of publications of the researcher.
	 */
	int get_n_publications();

	/**
	 * Returns the number of publications in journals of the researcher.
	 * @return The number of publications in journals of the researcher.
	 */
	int get_n_journals();

	/**
	 * Returns a list of publications in journals of the researcher.
	 * @return A vector with the publications in journals of the researcher.
	 */
	vector<string> get_journals();

	/**
	 * Returns the number of publications in events of the researcher.
	 * @return The number of publications in events of the researcher.
	 */
	int get_n_events();

	/**
	 * Returns a list of publications in events of the researcher.
	 * @return A vector with the publications in events of the researcher.
	 */
	vector<string> get_events();

	/**
	 * Default class destructor.
	 */
	virtual ~LDBRegister();

};

} /* namespace std */

#endif /* LDBREGISTER_H_ */
