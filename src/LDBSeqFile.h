/*
 * LDBSeqFile.h
 *
 *  Created on: May 19, 2014
 *      Author: marcos
 */

#ifndef LDBSEQFILE_H_
#define LDBSEQFILE_H_

#include "LDBRegister.h"
#include <fstream>

namespace std {

/**
 * LDBSeqFile is a class for manipulating a sequential file.
 */
class LDBSeqFile {

	fstream file; /**< File handler */

	static const int SIZE_UINT = sizeof(unsigned int);
	/**< Size of unsigned int constant */

	static const int BUFFER_SIZE = 512;

public:

	LDBSeqFile();

	/**
	 * Open a .ldb file, if fails, creates a new one.
	 * @param file_name Name of the file to be opened.
	 */
	LDBSeqFile(string file_name);

	void open(string file_name);

	bool is_open();

	/**
	 * Writes a register into the sequential file.
	 * @param reg A register to be written on disk.
	 * @return The position of the register written on the file.
	 */
	unsigned int write(LDBRegister reg);

	/**
	 * Given the position of the register in file, reads and returns the register.
	 * @param pos The position of the register in the file.
	 * @return The register read from the file.
	 */
	LDBRegister read(unsigned int pos);

	vector<LDBRegister> read_all();

	/**
	 * Saves changes and closes the file.
	 */
	void close();

	/**
	 * Default class destructor.
	 */
	virtual ~LDBSeqFile();
};

} /* namespace std */
#endif /* LDBSEQFILE_H_ */
