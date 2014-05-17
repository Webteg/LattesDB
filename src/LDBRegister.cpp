/*
 * LDBRegister.cpp
 *
 *  Created on: May 17, 2014
 *      Author: marcos
 */

#include "LDBRegister.h"

namespace std {

LDBRegister::LDBRegister(pugi::xml_parse_result result) {
	// TODO Auto-generated constructor stub
	/*
	name = result.???;
	institution = result.???;
	while(???){
		journals.pushback(???);
	}
	while(???){
		events.pushback(???);
	}
	*/
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
