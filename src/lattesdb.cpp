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
#include "pugi/pugixml.hpp"
#include "LattesDB.h"

using namespace std;

char utfToAscii(const char utf) {
	char ascii = utf;

	if( (utf >= -128 && utf <= -123) || (utf >= -96 && utf <= -91) ) {
		ascii = 'A';
	} else if( (utf >= -120 && utf <= -117) || (utf >= -88 && utf <= -85) ) {
		ascii = 'E';
	} else if( (utf >= -116 && utf <= -113) || (utf >= -84 && utf <= -81) ) {
		ascii = 'I';
	} else if( (utf >= -110 && utf <= -106) || (utf >= -78 && utf <= -74) ) {
		ascii = 'O';
	} else if( (utf >= -103 && utf <= -100) || (utf >= -71 && utf <= -68) ) {
		ascii = 'U';
	} else if(utf == -89 || utf == -121) {
		ascii = 'C';
	}

	return ascii;
}

char* utfToAsciiString(const char* str, int size){
	char* new_str;
	new_str = (char*) malloc(size*sizeof(char));

	int i, j;

	j = 0;
	for (i=0; i< size; i++) {
		if(str[i] == -61) {
			new_str[j] = utfToAscii(str[i+1]);
			j++;
		} else if(str[i] >= 0 && str[i] <= 127) {
			new_str[j] = toupper(str[i]);
			j++;
		}

	}
	new_str[j] = '\0';
	return new_str;
}

int main() {

	/*
	LattesDB lattes("Lattes");
	if (lattes.readXMLDir("xmlLattes")) {

		cout << "Files read.\n\nTring to read files...\n\n" << flush;
		vector<LDBRegister> result = lattes.get_all();
		for (LDBRegister r : result) {
			cout << r.to_string() << flush;
		}

	}
	else{
		cout << "Could not read files." << endl << flush;
	}
	*/

	pugi::xml_document doc;
	pugi::xml_parse_result result;
	result = doc.load_file("xmlLattes/0455487141833418.xml");
	string name;
	if (result) {
		name = doc.child("CURRICULO-VITAE").child("DADOS-GERAIS").attribute(
			"NOME-COMPLETO").value();
	} else {

		puts("asdasd");

	}

	const char* str = name.c_str();

	char* str_asc = utfToAsciiString(str, 36);
	cout << str_asc << endl;

	/*//char *p = str;
	int i;
	for (i=0; i<32; i=i+2) {

		int k = str[i];
		int j = str[i+1];
		cout << k << endl;
		cout << j << endl;
		//cout << str;
		cout << str[i];
		cout << str[i+1] << endl;
		cout << endl;
	}
	*/
	return 0;
}

#endif
