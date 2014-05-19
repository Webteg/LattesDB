/*
 * LDBRegister.cpp
 *
 *  Created on: May 17, 2014
 *      Author: marcos
 */

#include "LDBRegister.h"

namespace std {

LDBRegister::LDBRegister(pugi::xml_document doc) {

	pugi::xml_node events_works = doc.child("CURRICULO-VITAE").child(
			"PRODUCAO-BIBLIOGRAFICA").child("TRABALHOS-EM-EVENTOS");
	pugi::xml_node journal_works = doc.child("CURRICULO-VITAE").child(
			"PRODUCAO-BIBLIOGRAFICA").child("ARTIGOS-PUBLICADOS");

	name = doc.child("CURRICULO-VITAE").child("DADOS-GERAIS").attribute(
			"NOME-COMPLETO").value();
	institution =
			doc.child("CURRICULO-VITAE").child("DADOS-GERAIS").child(
					"ENDERECO-PROFISSIONAL").attribute(
					"NOME_INSTITUICAO-EMPRESA").value();
	for (pugi::xml_node work = journal_works.first_child(); work;
			work = work.next_sibling()) {
		journals.push_back(
				work.child("DADOS-BASICOS-DO-TRABALHO").attribute(
						"TITULO-DO-TRABALHO").value());
	}
	for (pugi::xml_node work = events_works.first_child(); work;
			work = work.next_sibling()) {
		events.push_back(
				work.child("DADOS-BASICOS-DO-TRABALHO").attribute(
						"TITULO-DO-TRABALHO").value());
	}

}

LDBRegister::LDBRegister(string name, string institution,
		vector<string> journals, vector<string> events) {
	this->name = name;
	this->institution = institution;
	this->journals = journals;
	this->events = events;
}

string LDBRegister::get_name() {
	return name;
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

vector<string> LDBRegister::get_events() {
	return events;
}

LDBRegister::~LDBRegister() {};

}
/* namespace std */
