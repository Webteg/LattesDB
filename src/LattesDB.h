#ifndef LATTESDB_H_
#define LATTESDB_H_

#include "LDBSeqFile.h"
#include "LDBRegister.h"
#include "LDBLinkedList.h"
#include "pugi/pugixml.hpp"
#include "trie.h"
#include <fstream>
#include <dirent.h>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <string>
#include <sstream>
#include <locale>
extern "C" {
#include "wb/wbsys.h"
}
typedef unsigned char uchar;

namespace std {

enum SortOrder {
	NO_ORDER,
	BY_ALPHABETICAL_ORDER,
	BY_ALPHABETICAL_ORDER_REV,
	BY_N_PUBLICATIONS,
	BY_N_PUBLICATIONS_REV,
	BY_N_JOURNALS,
	BY_N_JOURNALS_REV,
	BY_N_EVENTS,
	BY_N_EVENTS_REV
};

/**
 * LDBSeqFile is a class for manipulating a sequential file.
 */
class LattesDB {

	string db_name;

	LDBSeqFile seqFile; /* sequential file */

	LDBLinkedList linkFile;

	Trie namePrefix;

	Trie institutionPrefix;

public:

	LattesDB(string file_name);

	bool readXMLDir(string dir_name);

	bool readXMLFile(string file_name);

	LDBRegister get_by_name_full(string name);

	vector<LDBRegister> get_by_name_prefix(string name, SortOrder sorting =
			NO_ORDER);

	vector<LDBRegister> get_by_institution_full(string institution,
			SortOrder sorting = NO_ORDER);

	vector<LDBRegister> get_by_institution_prefix(string institution,
			SortOrder sorting = NO_ORDER);

	vector<LDBRegister> get_all(SortOrder sorting = NO_ORDER);

	static string utfToAscii(string str);

	// reg1 > reg2
	static bool cmp_reg_name( LDBRegister reg1,  LDBRegister reg2);

	// reg1 < reg2
	static bool cmp_reg_name_reverse( LDBRegister reg1,  LDBRegister reg2);

	// reg1 > reg2
	static bool cmp_reg_publications( LDBRegister reg1,  LDBRegister reg2);

	// reg1 < reg2
	static bool cmp_reg_publications_reverse( LDBRegister reg1,  LDBRegister reg2);

	static bool cmp_reg_journals( LDBRegister reg1,  LDBRegister reg2);

	static bool cmp_reg_journals_reverse( LDBRegister reg1,  LDBRegister reg2);

	static bool cmp_reg_events( LDBRegister reg1,  LDBRegister reg2);

	static bool cmp_reg_events_reverse( LDBRegister reg1,  LDBRegister reg2);

	void sort(vector<LDBRegister>::iterator begin,
			vector<LDBRegister>::iterator end, SortOrder sort);

	void close();

	virtual ~LattesDB();
};

} /* namespace std */
#endif /* LATTESDB_H_ */
