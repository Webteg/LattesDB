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

	LDBAPI api("Lattes");
	api.mainMenu();
	//LDBRegister reg;
	//if(reg.readXML("xmlLattes/0455487141833418.xml"))
		//api.showRegisterData(reg);
}

#endif
