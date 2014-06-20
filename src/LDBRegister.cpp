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
		vector<string> journals, vector<string> events, vector<int> journal_coauthors, vector<int> event_coauthors
) {
	this->name = name;
	this->key = utfToAsciiUpper(name);
	this->institution = institution;
	this->journals = journals;
	this->events = events;
	this->event_coauthors = event_coauthors;
	this->journal_coauthors = journal_coauthors;
}

bool LDBRegister::readXML(string file_name) {
	pugi::xml_document doc;
	pugi::xml_parse_result result;
	result = doc.load_file(file_name.c_str());
	string coauthor_name;
	int coauthors = 0;

	if (result) {
		pugi::xml_node events_works = doc.child("CURRICULO-VITAE").child(
				"PRODUCAO-BIBLIOGRAFICA").child("TRABALHOS-EM-EVENTOS");

		pugi::xml_node journal_works = doc.child("CURRICULO-VITAE").child(
				"PRODUCAO-BIBLIOGRAFICA").child("ARTIGOS-PUBLICADOS");

		name = doc.child("CURRICULO-VITAE").child("DADOS-GERAIS").attribute(
				"NOME-COMPLETO").value();

		key = utfToAsciiUpper(name);

		institution = doc.child("CURRICULO-VITAE").child("DADOS-GERAIS").child(
				"ENDERECO").child("ENDERECO-PROFISSIONAL").attribute(
				"NOME-INSTITUICAO-EMPRESA").value();

		for (pugi::xml_node work = journal_works.first_child(); work; work =
				work.next_sibling()) {
			journals.push_back(
					work.child("DADOS-BASICOS-DO-ARTIGO").attribute(
							"TITULO-DO-ARTIGO").value());

			coauthors = 0;
			for(pugi::xml_node authors = work.child("AUTORES"); strcmp(authors.name(), "AUTORES") == 0; authors = authors.next_sibling()){
				coauthor_name = authors.attribute("NOME-COMPLETO-DO-AUTOR").value();
				if (name != coauthor_name) {
					coauthors++;
				}
			}
			journal_coauthors.push_back(coauthors);
		}


		for (pugi::xml_node work = events_works.first_child(); work;
				work = work.next_sibling()) {
			events.push_back(
					work.child("DADOS-BASICOS-DO-TRABALHO").attribute(
							"TITULO-DO-TRABALHO").value());

			coauthors = 0;
			for(pugi::xml_node authors = work.child("AUTORES"); strcmp(authors.name(), "AUTORES") == 0; authors = authors.next_sibling()){
				coauthor_name = authors.attribute("NOME-COMPLETO-DO-AUTOR").value();
				if (name != coauthor_name) {
					coauthors++;
				}
			}
			event_coauthors.push_back(coauthors);
		}

		return true;
	}
	return false;
}

string LDBRegister::get_name() {
	return name;
}

vector<int> LDBRegister::get_journal_coauthors() {
	return journal_coauthors;
}

vector<int> LDBRegister::get_event_coauthors() {
	return event_coauthors;
}

string LDBRegister::get_key() {
	return key;
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
	for (int i = 0; i < journals.size(); i++) {
		output << journals[i] << " - " << journal_coauthors[i] << " coauthors." << endl;
	}
	output << endl;
	output << events.size() << " Event Publication(s): " << endl;
	for (int i = 0; i < events.size(); i++) {
		output << events[i] << " - " << event_coauthors[i] << " coauthors." << endl;
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
			if (str[i] >= -128 && str[i] <= -123){
				new_str.push_back('A');
			} else if(str[i] >= -96 && str[i] <= -91) {
				new_str.push_back('a');
			} else if (str[i] >= -120 && str[i] <= -117) {
				new_str.push_back('E');
			} else if (str[i] >= -88 && str[i] <= -85) {
				new_str.push_back('e');
			} else if (str[i] >= -116 && str[i] <= -113) {
				new_str.push_back('I');
			} else if (str[i] >= -84 && str[i] <= -81) {
				new_str.push_back('i');
			} else if (str[i] >= -110 && str[i] <= -106) {
				new_str.push_back('O');
			} else if (str[i] >= -78 && str[i] <= -74) {
				new_str.push_back('o');
			} else if (str[i] >= -103 && str[i] <= -100) {
				new_str.push_back('U');
			} else if (str[i] >= -71 && str[i] <= -68) {
				new_str.push_back('u');
			} else if (str[i] == -89) {
				new_str.push_back('c');
			} else if (new_str[i] == -121) {
				new_str.push_back('C');
			}
		} else {
			new_str.push_back(str[i]);
		}
	}
	return new_str;
}

string LDBRegister::utfToAsciiUpper(string str) {
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
