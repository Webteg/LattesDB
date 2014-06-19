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

int main()
{
	LDBAPI api("Lattes");
	api.mainMenu();
	//api.addXMLMenu();
}

#endif
