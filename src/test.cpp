/*
 * test.cpp
 *
 *  Created on: May 11, 2014
 *      Author: marcos
 */

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
extern "C" {
#include "wb/wbsys.h"
}
using namespace std;
typedef unsigned char uchar;

int main(int argc, char *argv[]) {
	init_wb(50, 50, 512);
	HAND* handle; //B-Tree handle

	ifstream f("btree.db");
	//check to see if file exists and is read/writable
	if (!f.good()) {
		f.close();
		SEGD*db = make_seg((uchar*) "btree.db", 512);
		if (db == false)
			clog << "Can not create database" << endl;

		handle = create_db(db, 'T', (unsigned char*) "mytable");
		clog << "creating root B-Tree in database result : " << endl;
		close_seg(db, 0);
	}

	//open existing database
	SEGD *db = open_seg((uchar*) "btree.db", true);
	if (db == false) {
		clog << "unable to open database!" << endl;
		exit(1);
	}

	//open first B-Tree in database
	handle = open_db(db, (unsigned char*) "mytable");

	bool exit = false;
	while (exit == false) {
		uchar c;
		cout << "P - put\nG - get\nQ - quit\n";
		cin >> c;
		c = tolower(c);
		int k, r;
		string d;
		stringstream key, value;
		switch (c) {
		case 'p': //put operation
			cout << "Insert key:\n";
			cin >> k;
			cout << "Insert data:\n";
			cin >> d;

			key << k;
			value << d;

			r = bt_put(handle, (uchar*) key.str().c_str(), key.str().size(),
					(uchar*) value.str().c_str(), value.str().size());
			if (r < 0) {
				clog << "--error writing " << endl;
			}
			break;
		case 'g': //get operation
			cout << "Insert key:\n";
			cin >> k;
			key << k;

			uchar ret[256];

			r = bt_get(handle, (uchar*) key.str().c_str(), key.str().size(),
					ret);

			if (r < 0) {
				clog << "--get error : " << r << endl;
			} else {
				cout << ret << endl;
			}
			break;
		case 'q': //quit
			exit = true;
		}
	}

	//close B-Tree
	bt_close(handle);

	//close database, mandatory
	if (close_seg(db, 1) < 0)
		clog << "error closing database" << endl;

	final_wb();
}

