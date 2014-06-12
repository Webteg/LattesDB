/**
 * WB-Tree benchmark, test and demonstration program
 * @author: AbiusX (me@abiusx.com)
 * @version 1.0
 *
 * The original WB-Tree was developed by a few of MIT fellows, its an official GNU project now available at :
 * https://savannah.gnu.org/cvs/?group=wb
 * The developer's presonal page is :
 * http://people.csail.mit.edu/jaffer/WB
 *
 *
 * Keep in mind that this sample is based on a very recent version only available through CVS at the time of this writing (8 jun 2011)
 * and the wb-2b1.zip and wb.zip file available at the author's page are not correctly functional.
 *
 *
 * This was intentionally done for the Shahid Beheshti University Data Storage And Retrieval Final Course Project, hope it helps.
 */

#include "main.h"

#ifdef MAIN_WB

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
extern "C"
{
#include "wb/wbsys.h"
}
using namespace std;
typedef unsigned char uchar;

inline void uchar_out(uchar* str, int len, ostream *stream = 0)
{
	if (stream == 0)
		stream = &cout;
	char *t = new char[len + 1];
	int i;
	for (i = 0; i < len; ++i)
		t[i] = str[i];
	t[i] = 0;
	(*stream) << t << endl;
	delete[] t;
}
int main(int argc, char *argv[])
{
	const int benchmark = 1000000;
	diagout = stderr;
	init_wb(75, 150, 4096);
	HAND* handle; //B-Tree handle

	//Verbose mode detection
	bool verbose = false;
	if (argc > 1)
		if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--verbose") == 0)
		{
			clog << "Verbose mode enabled.";
			verbose = true;
		}

	if (!verbose)
		clog
				<< "You could also enable the verbose (detailed) mode by providing the application with -v or --verbose as command line arguments."
				<< endl;

	ifstream f("btree.db");
	//check to see if file exists and is read/writable
	if (!f.good())
	{
		f.close();
		clog << "attempting to create B-Tree database for the first time..."
				<< endl;
		SEGD*db = make_seg((uchar*) "btree.db", 2048);
		if (db == false)
			clog << "Can not create database" << endl;
		else
			clog << "btree.db B-Tree database successfully created." << endl;

		handle = create_db(db, 'T', (unsigned char*) "mytable");
		clog << "creating root B-Tree in database result : " << endl;
		close_seg(db, 0);
	}

	//open existing database
	SEGD *db = open_seg((uchar*) "btree.db", true);
	if (db == false)
	{
		clog << "unable to open database!" << endl;
		exit(1);
	}

	//open first B-Tree in database
	handle = open_db(db, (unsigned char*) "mytable");
	clog << "open root B-Tree succeeded. benchmarking " << benchmark
			<< " nodes ..." << endl;

	//insert some key/value pairs in database if not exists
	clog << "trying to write " << benchmark << " nodes ..." << endl;
	int count = 0;
	for (int i = 0; i < benchmark; ++i)
	{
		stringstream key;
		key << "k" << i;
		stringstream value;
		value << "v" << i;

		int r = bt_write(handle, (uchar*) key.str().c_str(), key.str().size(),
				(uchar*) value.str().c_str(), value.str().size());
		if (r < 0)
		{
			if (verbose)
				clog << "--error writing " << i << " : " << r << endl;
		}
		else
			count++;
	}
	clog << "done writing " << count << " items." << endl;

	//reading inserted/existing key/value pairs
	clog << "attempting to read " << benchmark << " nodes ..." << endl;
	count = 0;
	for (int i = 0; i < benchmark; ++i)
	{
		uchar value[256];
		stringstream key;
		key << "k" << i;

		int r = bt_get(handle, (uchar*) key.str().c_str(), key.str().size(),
				value);
		if (r < 0)
		{
			if (verbose)
				clog << "--get error : " << r << endl;
		}
		else
		{
			count++;
			if (verbose)
				uchar_out(value, r, &clog);
		}
	}
	clog << "done reading " << count << " items." << endl;

	//changing values for those keys
	clog << "attempting to change " << benchmark << " nodes..." << endl;
	count = 0;
	for (int i = 0; i < benchmark; ++i)
	{
		stringstream key;
		key << "k" << i;
		stringstream value;
		value << "v" << i << "changed";
		int r = bt_put(handle, (uchar*) key.str().c_str(), key.str().size(),
				(uchar*) value.str().c_str(), value.str().size());
		if (r < 0)
		{
			//if (verbose)
				clog << "--put error : " << r << endl;
		}
		else
			count++;

	}
	clog << "done putting " << count << " items." << endl;

	//reading values again to see changes
	clog << "attempting to read " << benchmark << " nodes ..." << endl;
	count = 0;
	for (int i = 0; i < benchmark; ++i)
	{
		uchar value[256];
		stringstream key;
		key << "k" << i;

		int r = bt_get(handle, (uchar*) key.str().c_str(), key.str().size(),
				value);
		if (r < 0)
		{
			if (verbose)
				clog << "get error : " << r << endl;
		}
		else
		{
			cout << value << endl;
			if (verbose)
				uchar_out(value, r, &clog);
			count++;
		}
	}
	clog << "done reading " << count << " items." << endl;

	//close B-Tree
	bt_close(handle);

	//close database, mandatory
	if (close_seg(db, 1) < 0)
		clog << "error closing database" << endl;

	final_wb();
	clog << "all done. :)" << endl;
	return 0;
}

#endif
