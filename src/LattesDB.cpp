#include "LattesDB.h"


namespace std {

LattesDB::LattesDB(string file_name) {

	seqFile = new LDBSeqFile(file_name);

}

bool LattesDB::readXML(string dir_name) {
	
	LDBRegister *reg;
	pugi::xml_document doc;
	pugi::xml_parse_result result;
	
	DIR *pDIR;
	struct dirent *entry;
	
	pDIR=opendir((std::string("./") + dir_name).c_str());
	if(pDIR) {
		while(entry = readdir(pDIR)){
			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){
				result = doc.load_file((std::string("xmlLattes/") + entry->d_name).c_str());
				reg = new LDBRegister(doc);
				seqFile->write(*reg);
			}
		}
		closedir(pDIR);
	}
}

LattesDB::~LattesDB() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
