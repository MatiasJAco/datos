/*
 * testPhysical.h
 *
 *  Created on: Jun 27, 2010
 *      Author: adrian
 */

#ifndef TESTPHYSICAL_H_
#define TESTPHYSICAL_H_

#include "../physical/file/VarRegister.h"
#include "../physical/file/FixedRegister.h"
#include "../physical/file/BlockFile.h"
#include "../physical/file/FreeBlockFile.h"
#include "../physical/utils/ByteConverter.h"
#include "../physical/file/BlockManager.h"
#include "../physical/file/SequentialFile.h"
#include "../physical/Exception/PhysicalException.h"
#include <sstream>
#include <fstream>
#include <vector>

class TestPhysical {

public:

	void testVarRegister();
	void testFixedRegister();
	void testFreeBlockFile();
	void testFile();
	void testBlock();
	void testSecuentialFile();
};

#endif /* TESTPHYSICAL_H_ */
