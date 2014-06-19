/*
 * LDBAPI.h
 *
 *  Created on: Jun 19, 2014
 *      Author: marcos
 */

#ifndef LDBAPI_H_
#define LDBAPI_H_

#include <string>
#include "LattesDB.h"
#include "LDBRegister.h"
#include <vector>

namespace std {

class LDBAPI {
	LattesDB* lattes;
public:
	LDBAPI(string name);
	void mainMenu();

	void showRegisterData(LDBRegister reg);
	void addXMLMenu();
	void addXML();
	void addDir();
	void printResults(vector<LDBRegister>);
	virtual ~LDBAPI();
};

} /* namespace std */

#endif /* LDBAPI_H_ */
