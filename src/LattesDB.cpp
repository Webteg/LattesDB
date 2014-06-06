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
		while((entry = readdir(pDIR))){
			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){

				reg = new LDBRegister();
				if(reg->readXML((std::string("xmlLattes/") + entry->d_name))) {
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

	bool flag;
	LDBRegister *reg;
	reg = new LDBRegister();
	if(reg->readXML(file_name)) {
		flag = true;
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
