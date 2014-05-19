/*
 * LDBRegister.cpp
 *
 *  Created on: May 17, 2014
 *      Author: marcos
 */

#include "LDBRegister.h"

namespace std {

LDBRegister::LDBRegister(pugi::xml_document doc) {
	// TODO Auto-generated constructor stub
	
	pugi::xml_node events_works = doc.child("CURRICULO-VITAE").child("PRODUCAO-BIBLIOGRAFICA").child("TRABALHOS-EM-EVENTOS");
	
	name = doc.child("CURRICULO-VITAE").child("DADOS-GERAIS").attribute("NOME-COMPLETO").value();
	institution = doc.child("CURRICULO-VITAE").child("DADOS-GERAIS").child("ENDERECO-PROFISSIONAL").attribute("NOME_INSTITUICAO-EMPRESA").value();
	while(???){
		journals.pushback(???);
	}
	while(pugi::xml_node work = events_works.first_child(); work; work = work.next_sibling()){
		events.pushback(work.child("DADOS-BASICOS-DO-TRABALHO").attribute("TITULO-DO-TRABALHO").value());
	}
	
}

LDBRegister::LDBRegister(string name, string institution, vector<string> journals,
			vector<string> events){
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

} /* namespace std */
