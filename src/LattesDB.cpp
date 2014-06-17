#include "LattesDB.h"

namespace std {

LattesDB::LattesDB(string file_name) {
	name = file_name;

	seqFile.open(name + ".sf");

	linkFile.open(name + ".ll");

	namePrefix.read(name + ".npt");

	institutionPrefix.read(name + ".ipt");
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
					string name = reg.get_name();
					unsigned long int find = namePrefix.get(name);
					if (find == 0) {
						unsigned long int pos = seqFile.write(reg);
						namePrefix.insert(name, pos);
						string institution = reg.get_institution();
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
	vector<LDBRegister> ret;
	vector<unsigned long int> posList = institutionPrefix.getPrefix(institution);
	for(unsigned long int pos : posList){
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
	unsigned long int address = namePrefix.get(name);
	if (address != 0)
		return seqFile.read(address);
	LDBRegister reg;
	return reg;
}

vector<LDBRegister> LattesDB::get_by_name_prefix(string name) {
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

void LattesDB::close() {
	seqFile.close();
	linkFile.close();
	namePrefix.write(name + ".npt");
	institutionPrefix.write(name + ".ipt");
}

LattesDB::~LattesDB() {
// TODO Auto-generated destructor stub
}

} /* namespace std */
