/*
 * LDBRegister.cpp
 *
 *  Created on: May 17, 2014
 *      Author: marcos
 */

#include "LDBRegister.h"
#include <sstream>

namespace std {

LDBRegister::LDBRegister() {

}

LDBRegister::LDBRegister(string name, string institution,
		vector<string> journals, vector<string> events) {
	this->name = name;
	this->institution = institution;
	this->journals = journals;
	this->events = events;
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

		institution =
				doc.child("CURRICULO-VITAE").child("DADOS-GERAIS").child("ENDERECO").child(
						"ENDERECO-PROFISSIONAL").attribute(
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

string LDBRegister::get_institution() {
	return institution;
}

int LDBRegister::get_n_publications()  {
	return journals.size() + events.size();
}

int LDBRegister::get_n_journals()  {
	return journals.size();
}

vector<string> LDBRegister::get_journals()  {
	return journals;
}

int LDBRegister::get_n_events()  {
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
	output << "////////////////////////////////////////////////////////////" << endl;
	return output.str();
}

vector<string> LDBRegister::get_events()  {
	return events;
}

LDBRegister::~LDBRegister() {
}
;

}
/* namespace std */
