#include "LattesDB.h"


namespace std {

LattesDB::LattesDB(string file_name) {

	seqFile.open(file_name + ".sf");

	//btree.open(file_name + ".bt");

	//linkedlist.open(file_name + ".ll"); ...

}

bool LattesDB::readXMLDir(string dir_name) {
	
	bool flag;
	pugi::xml_document doc;
	pugi::xml_parse_result result;
	
	DIR *pDIR;
	struct dirent *entry;
	
	pDIR=opendir((string("./") + dir_name).c_str());
	if(pDIR) {
		flag = true;
		while((entry = readdir(pDIR))){
			if( strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 ){

				LDBRegister reg;
				if(reg.readXML((string("xmlLattes/") + entry->d_name))) {
					seqFile.write(reg);
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
	LDBRegister *reg = new LDBRegister;

	if(reg->readXML(file_name)) {
		flag = true;
		seqFile.write(*reg);

	} else {
		//flag = false;
	}

	return flag;

}

vector<LDBRegister> LattesDB::get_all(){
	return seqFile.read_all();
}

LattesDB::~LattesDB() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
