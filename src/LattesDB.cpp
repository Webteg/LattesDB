#include "LattesDB.h"

namespace std {

LattesDB::LattesDB(string file_name) {
	db_name = file_name;

	seqFile.open(db_name + ".sf");

	linkFile.open(db_name + ".ll");

	namePrefix.read(db_name + ".npt");

	institutionPrefix.read(db_name + ".ipt");
}

// reg1.get_name() > reg2.get_name()
bool LattesDB::cmp_reg_name_reverse(LDBRegister reg1, LDBRegister reg2) {
	return reg1.get_key() > reg2.get_key();
}

// reg1.get_name() < reg2.get_name()
bool LattesDB::cmp_reg_name(LDBRegister reg1, LDBRegister reg2) {
	return reg1.get_key() < reg2.get_key();
}

bool LattesDB::cmp_reg_publications_reverse(LDBRegister reg1,
		LDBRegister reg2) {
	return (reg1.get_n_publications() > reg2.get_n_publications());
}

bool LattesDB::cmp_reg_publications(LDBRegister reg1, LDBRegister reg2) {
	return (reg1.get_n_publications() < reg2.get_n_publications());
}

bool LattesDB::cmp_reg_journals_reverse(LDBRegister reg1, LDBRegister reg2) {
	return (reg1.get_n_journals() > reg2.get_n_journals());
}

bool LattesDB::cmp_reg_journals(LDBRegister reg1, LDBRegister reg2) {
	return (reg1.get_n_journals() < reg2.get_n_journals());
}

bool LattesDB::cmp_reg_events_reverse(LDBRegister reg1, LDBRegister reg2) {
	return (reg1.get_n_events() > reg2.get_n_events());
}

bool LattesDB::cmp_reg_events(LDBRegister reg1, LDBRegister reg2) {
	return (reg1.get_n_events() < reg2.get_n_events());
}

bool LattesDB::readXMLDir(string dir_name) {

	bool flag;
	pugi::xml_document doc;
	pugi::xml_parse_result result;

	DIR *pDIR;
	struct dirent *entry;

	pDIR = opendir((string("./") + dir_name).c_str());
	if (pDIR) {
		flag = true;
		while ((entry = readdir(pDIR)) && flag == true) {
			if (strcmp(entry->d_name, ".") != 0
					&& strcmp(entry->d_name, "..") != 0) {

				LDBRegister reg;
				if (reg.readXML((string("xmlLattes/") + entry->d_name))) {
					string name = reg.get_key();
					unsigned long int find = namePrefix.get(name);
					if (find == 0) {
						unsigned long int pos = seqFile.write(reg);
						namePrefix.insert(name, pos);
						string institution = LDBRegister::utfToAscii(
								reg.get_institution());
						unsigned long int list = institutionPrefix.get(
								institution);
						if (list == 0) {
							list = linkFile.newList(pos);
							institutionPrefix.insert(institution, list);
						} else {
							linkFile.addToList(pos, list);
						}
					}
				} else {
					flag = false;
				}
			}
		}
		closedir(pDIR);
	} else {
		flag = false;
	}

	return flag;

}

bool LattesDB::readXMLFile(string file_name) {

	bool flag;
	LDBRegister reg;

	if (reg.readXML(file_name)) {
		flag = true;
		string name = reg.get_name();
		unsigned long int find = namePrefix.get(name);
		if (find == 0) {
			unsigned long int pos = seqFile.write(reg);
			namePrefix.insert(name, pos);
			string institution = reg.get_institution();
			unsigned long int list = institutionPrefix.get(institution);
			if (list == 0) {
				list = linkFile.newList(pos);
				institutionPrefix.insert(institution, list);
			} else {
				linkFile.addToList(pos, list);
			}
		}

	} else {
		flag = false;
	}
	return flag;
}

vector<LDBRegister> LattesDB::get_by_institution_full(string institution,
		SORTING_ORDER sorting) {
	institution = LDBRegister::utfToAscii(institution);
	vector<LDBRegister> ret;
	unsigned long int pos = institutionPrefix.get(institution);
	if (pos != 0) {
		vector<unsigned long int> addressList = linkFile.getList(pos);
		for (unsigned long int address : addressList) {
			ret.push_back(seqFile.read(address));
		}
	}
	sortLDBRegister(ret.begin(), ret.end(), sorting);
	return ret;
}

vector<LDBRegister> LattesDB::get_by_institution_prefix(string institution,
		SORTING_ORDER sorting) {
	institution = LDBRegister::utfToAscii(institution);
	vector<LDBRegister> ret;
	vector<unsigned long int> posList = institutionPrefix.getPrefix(
			institution);
	for (unsigned long int pos : posList) {
		if (pos != 0) {
			vector<unsigned long int> addressList = linkFile.getList(pos);
			for (unsigned long int address : addressList) {
				ret.push_back(seqFile.read(address));
			}
		}
	}
	sortLDBRegister(ret.begin(), ret.end(), sorting);
	return ret;
}

LDBRegister LattesDB::get_by_name_full(string name) {
	name = LDBRegister::utfToAscii(name);
	unsigned long int address = namePrefix.get(name);
	if (address != 0)
		return seqFile.read(address);
	LDBRegister reg;
	return reg;
}

vector<LDBRegister> LattesDB::get_by_name_prefix(string name,
		SORTING_ORDER sorting) {
	name = LDBRegister::utfToAscii(name);
	vector<LDBRegister> ret;
	vector<unsigned long int> addressList = namePrefix.getPrefix(name);
	for (unsigned long int address : addressList) {
		ret.push_back(seqFile.read(address));
	}
	sortLDBRegister(ret.begin(), ret.end(), sorting);
	return ret;
}

vector<LDBRegister> LattesDB::get_by_name_and_institution_prefix(string name,
		string institution, SORTING_ORDER sorting) {
	vector<LDBRegister> result_1 = get_by_name_prefix(name, sorting);
	vector<LDBRegister> result_2 = get_by_institution_prefix(institution, sorting);
	int s1 = result_1.size();
	int s2 = result_2.size();
	int s =min(s1, s2);
	vector<LDBRegister> result(max(result_1.size(), result_2.size()));
	vector<LDBRegister>::iterator it;
	switch (sorting) {
	case BY_ALPHABETICAL_ORDER:
		it = set_intersection(result_1.begin(), result_1.end(),
				result_2.begin(), result_2.end(), result.begin(), cmp_reg_name);
		break;
	case BY_ALPHABETICAL_ORDER_REV:
		it = set_intersection(result_1.begin(), result_1.end(),
				result_2.begin(), result_2.end(), result.begin(),
				cmp_reg_name_reverse);
		break;
	case BY_N_PUBLICATIONS:
		it = set_intersection(result_1.begin(), result_1.end(),
				result_2.begin(), result_2.end(), result.begin(),
				cmp_reg_publications);
		break;
	case BY_N_PUBLICATIONS_REV:
		it = set_intersection(result_1.begin(), result_1.end(),
				result_2.begin(), result_2.end(), result.begin(),
				cmp_reg_publications_reverse);
		break;
	case BY_N_JOURNALS:
		it = set_intersection(result_1.begin(), result_1.end(),
				result_2.begin(), result_2.end(), result.begin(),
				cmp_reg_journals);
		break;
	case BY_N_JOURNALS_REV:
		it = set_intersection(result_1.begin(), result_1.end(),
				result_2.begin(), result_2.end(), result.begin(),
				cmp_reg_journals_reverse);
		break;
	case BY_N_EVENTS:
		it = set_intersection(result_1.begin(), result_1.end(),
				result_2.begin(), result_2.end(), result.begin(),
				cmp_reg_events);
		break;
	case BY_N_EVENTS_REV:
		it = set_intersection(result_1.begin(), result_1.end(),
				result_2.begin(), result_2.end(), result.begin(),
				cmp_reg_events_reverse);
	}
	result.resize(it - result.begin());
	return result;
}

vector<LDBRegister> LattesDB::get_all(SORTING_ORDER sorting) {
	vector<LDBRegister> ret;
	ret = seqFile.read_all();
	sortLDBRegister(ret.begin(), ret.end(), sorting);
	return ret;
}

void LattesDB::sortLDBRegister(vector<LDBRegister>::iterator begin,
		vector<LDBRegister>::iterator end, SORTING_ORDER sorting) {
	switch (sorting) {
	case BY_ALPHABETICAL_ORDER:
		stable_sort(begin, end, cmp_reg_name);
		break;
	case BY_ALPHABETICAL_ORDER_REV:
		stable_sort(begin, end, cmp_reg_name_reverse);
		break;
	case BY_N_PUBLICATIONS:
		stable_sort(begin, end, cmp_reg_publications);
		break;
	case BY_N_PUBLICATIONS_REV:
		stable_sort(begin, end, cmp_reg_publications_reverse);
		break;
	case BY_N_JOURNALS:
		stable_sort(begin, end, cmp_reg_journals);
		break;
	case BY_N_JOURNALS_REV:
		stable_sort(begin, end, cmp_reg_journals_reverse);
		break;
	case BY_N_EVENTS:
		stable_sort(begin, end, cmp_reg_events);
		break;
	case BY_N_EVENTS_REV:
		stable_sort(begin, end, cmp_reg_events_reverse);
	}
}

void LattesDB::close() {
	seqFile.close();
	linkFile.close();
	namePrefix.write(db_name + ".npt");
	institutionPrefix.write(db_name + ".ipt");
}

LattesDB::~LattesDB() {
// TODO Auto-generated destructor stub
}

} /* namespace std */

unsigned int LattesDB::get_size() {
	return seqFile.get_size();
}
