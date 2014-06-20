/*
 * LDBAPI.h
 *
 *  Created on: Jun 19, 2014
 *      Author: marcos
 */

#ifndef LDBAPI_H_
#define LDBAPI_H_

#include "LattesDB.h"
#include "LDBRegister.h"
#include <vector>

namespace std {

class LDBAPI {
	LattesDB* lattes;
public:
	LDBAPI(string name);
	void mainMenu();
	void addXML();
	void addDir();
	void searchName();
	void searchInstitution();
	void printResults(vector<LDBRegister>);
	virtual ~LDBAPI();
};

} /* namespace std */

#endif /* LDBAPI_H_ */
