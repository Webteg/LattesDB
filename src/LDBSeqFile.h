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

	const int SIZE_UINT = sizeof(unsigned int);
	/**< Size of unsigned int constant */

public:

	/**
	 * Open a .ldb file, if fails, creates a new one.
	 * @param file_name Name of the file to be opened.
	 */
	LDBSeqFile(string file_name);

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
