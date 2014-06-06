
#ifndef LATTESDB_H_
#define LATTESDB_H_

#include "LDBSeqFile.h"
#include "LDBRegister.h"
#include "pugi/pugixml.hpp"
#include <fstream>
#include <dirent.h>
#include <iostream>
#include <string.h>

namespace std {

/**
 * LDBSeqFile is a class for manipulating a sequential file.
 */
class LattesDB {

	LDBSeqFile* seqFile; /* sequential file */


public:
	
	LattesDB(string file_name);
	
	bool readXML(string dir_name);
	
	bool readXMLFile(string file_name);

	virtual ~LattesDB();
};

} /* namespace std */
#endif /* LATTESDB_H_ */
