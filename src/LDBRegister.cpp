/*
 * LDBRegister.cpp
 *
 *  Created on: May 17, 2014
 *      Author: marcos
 */

#include "LDBRegister.h"
#include "LattesDB.h"
#include <sstream>

namespace std {

LDBRegister::LDBRegister() {

}

LDBRegister::LDBRegister(string name, string institution,
		vector<string> journals, vector<string> events) {
	this->name = name;
	this->key = utfToAscii(name);
	this->institution = institution;
	this->journals = journals;
	this->events = events;
}

bool LDBRegister::readXML(string file_name) {
	pugi::xml_document doc;
	pugi::xml_parse_result result;
	result = doc.load_file(file_name.c_str());

	if (result) {
		pugi::xml_node events_works = doc.child("CURRICULO-VITAE").child(
				"PRODUCAO-BIBLIOGRAFICA").child("TRABALHOS-EM-EVENTOS");

		pugi::xml_node journal_works = doc.child("CURRICULO-VITAE").child(
				"PRODUCAO-BIBLIOGRAFICA").child("ARTIGOS-PUBLICADOS");

		name = doc.child("CURRICULO-VITAE").child("DADOS-GERAIS").attribute(
				"NOME-COMPLETO").value();

		institution = doc.child("CURRICULO-VITAE").child("DADOS-GERAIS").child(
				"ENDERECO").child("ENDERECO-PROFISSIONAL").attribute(
				"NOME-INSTITUICAO-EMPRESA").value();

		for (pugi::xml_node work = journal_works.first_child(); work; work =
				work.next_sibling()) {
			journals.push_back(
					work.child("DADOS-BASICOS-DO-ARTIGO").attribute(
							"TITULO-DO-ARTIGO").value());
		}
		for (pugi::xml_node work = events_works.first_child(); work;
				work = work.next_sibling()) {
			events.push_back(
					work.child("DADOS-BASICOS-DO-TRABALHO").attribute(
							"TITULO-DO-TRABALHO").value());
		}

		return true;
	}
	return false;
}

string LDBRegister::get_name() {
	return name;
}

string LDBRegister::get_key() {
	return key;
}

vector<int> get_coauthors() {
	return coauthors;
}

string LDBRegister::get_institution() {
	return institution;
}

int LDBRegister::get_n_publications() {
	return journals.size() + events.size();
}

int LDBRegister::get_n_journals() {
	return journals.size();
}

vector<string> LDBRegister::get_journals() {
	return journals;
}

int LDBRegister::get_n_events() {
	return events.size();
}

string LDBRegister::to_string() {
	stringstream output;
	output << name << " - " << institution << endl;
	output << "Total Pulications: " << journals.size() + events.size() << endl;
	output << journals.size() << " Journal Publication(s): " << endl;
	for (string s : journals) {
		output << s << endl;
	}
	output << endl;
	output << events.size() << " Event Publication(s): " << endl;
	for (string s : events) {
		output << s << endl;
	}
	output << "////////////////////////////////////////////////////////////"
			<< endl;
	return output.str();
}

vector<string> LDBRegister::get_events() {
	return events;
}

string LDBRegister::utfToAscii(string str) {
	string new_str;
	unsigned int size = str.size();
	for (unsigned int i = 0; i < size; i++) {
		if (str[i] < 0) {
			i++;
			if ((str[i] >= -128 && str[i] <= -123)
					|| (str[i] >= -96 && str[i] <= -91)) {
				new_str.push_back('A');
			} else if ((str[i] >= -120 && str[i] <= -117)
					|| (str[i] >= -88 && str[i] <= -85)) {
				new_str.push_back('E');
			} else if ((str[i] >= -116 && str[i] <= -113)
					|| (str[i] >= -84 && str[i] <= -81)) {
				new_str.push_back('I');
			} else if ((str[i] >= -110 && str[i] <= -106)
					|| (str[i] >= -78 && str[i] <= -74)) {
				new_str.push_back('O');
			} else if ((str[i] >= -103 && str[i] <= -100)
					|| (str[i] >= -71 && str[i] <= -68)) {
				new_str.push_back('U');
			} else if (str[i] == -89 || new_str[i] == -121) {
				new_str.push_back('C');
			}
		} else {
			new_str.push_back(toupper(str[i]));
		}
	}
	return new_str;
}

LDBRegister::~LDBRegister() {
}
;

}
/* namespace std */
