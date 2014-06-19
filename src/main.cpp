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

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

string choices[] = {
	"Adicionar XML",
	"Adicionar Diretorio",
	"Buscar pelo nome do pesquisador",
	"Buscar pelo instituto do pesquisador",
	"Exit",
	"\0",
};

int main()
{
	LDBAPI api("Lattes");
	api.mainMenu();
}

#endif
