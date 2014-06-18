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
bool LattesDB::cmp_reg_name(LDBRegister reg1, LDBRegister reg2) {
	if(reg1.get_name().compare(reg2.get_name()) > 0) {
		return true;
	} else {
		return false;
	}
}

// reg1.get_name() < reg2.get_name()
bool LattesDB::cmp_reg_name_reverse(LDBRegister reg1, LDBRegister reg2) {
	if(reg1.get_name().compare(reg2.get_name()) < 0) {
		return true;
	} else {
		return false;
	}
}

bool LattesDB::cmp_reg_publications(LDBRegister reg1, LDBRegister reg2) {
	return (reg1.get_n_publications() > reg2.get_n_publications());
}

bool LattesDB::cmp_reg_publications_reverse(LDBRegister reg1, LDBRegister reg2) {
	return (reg1.get_n_publications() < reg2.get_n_publications());
}

bool LattesDB::cmp_reg_journals(LDBRegister reg1, LDBRegister reg2) {
	return (reg1.get_n_journals() > reg2.get_n_journals());
}

bool LattesDB::cmp_reg_journals_reverse(LDBRegister reg1, LDBRegister reg2) {
	return (reg1.get_n_journals() < reg2.get_n_journals());
}

bool LattesDB::cmp_reg_events(LDBRegister reg1, LDBRegister reg2) {
	return (reg1.get_n_events() > reg2.get_n_events());
}

bool LattesDB::cmp_reg_events_reverse(LDBRegister reg1, LDBRegister reg2) {
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
					string name = utfToAscii(reg.get_name());
					unsigned long int find = namePrefix.get(name);
					if (find == 0) {
						unsigned long int pos = seqFile.write(reg);
						namePrefix.insert(name, pos);
						string institution = utfToAscii(reg.get_institution());
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

vector<LDBRegister> LattesDB::get_by_institution_full(string institution) {
	institution = utfToAscii(institution);
	vector<LDBRegister> ret;
	unsigned long int pos = institutionPrefix.get(institution);
	if (pos != 0) {
		vector<unsigned long int> addressList = linkFile.getList(pos);
		for (unsigned long int address : addressList) {
			ret.push_back(seqFile.read(address));
		}
	}
	return ret;
}

vector<LDBRegister> LattesDB::get_by_institution_prefix(string institution) {
	institution = utfToAscii(institution);
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
	return ret;
}

LDBRegister LattesDB::get_by_name_full(string name) {
	name = utfToAscii(name);
	unsigned long int address = namePrefix.get(name);
	if (address != 0)
		return seqFile.read(address);
	LDBRegister reg;
	return reg;
}

vector<LDBRegister> LattesDB::get_by_name_prefix(string name) {
	name = utfToAscii(name);
	vector<LDBRegister> ret;
	vector<unsigned long int> addressList = namePrefix.getPrefix(name);
	for (unsigned long int address : addressList) {
		ret.push_back(seqFile.read(address));
	}
	return ret;
}

vector<LDBRegister> LattesDB::get_all() {
	return seqFile.read_all();
}

string LattesDB::utfToAscii(string str) {
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
