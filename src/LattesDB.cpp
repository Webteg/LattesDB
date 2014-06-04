#include "LattesDB.h"


namespace std {

LattesDB::LattesDB(string file_name) {

	seqFile = new LDBSeqFile(file_name);

}

bool LattesDB::readXML(string dir_name) {
	
	bool flag;
	LDBRegister *reg;
	pugi::xml_document doc;
	pugi::xml_parse_result result;
	
	DIR *pDIR;
	struct dirent *entry;
	
	pDIR=opendir((std::string("./") + dir_name).c_str());
	if(pDIR) {
		flag = true;
		while(entry = readdir(pDIR)){
			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
				result = doc.load_file((std::string("xmlLattes/") + entry->d_name).c_str());

				if(result) {
					reg = new LDBRegister(doc);
					seqFile->write(*reg);
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

	LDBRegister *reg;
	pugi::xml_document doc;
	pugi::xml_parse_result result;
	bool flag;

	result = doc.load_file(file_name.c_str());
	if(result) {
		flag = true;
		reg = new LDBRegister(doc);
		seqFile->write(*reg);
	} else {
		flag = false;
	}

	return flag;

}

LattesDB::~LattesDB() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
