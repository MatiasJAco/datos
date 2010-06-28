######################################################################################
# Makefile TP1 7506 
# Grupo PAITITI
# Autor Alex
# Fecha 1/04/10	
######################################################################################

FILE_DIR = physical/file/
UTILS_DIR = physical/utils/
HASH_DIR = logic/structures/hash/
LOGGER_DIR = logic/logger/
TREE_DIR = logic/structures/tree/
TREE_DATA_DIR = $(TREE_DIR)dataNode/
INPUT_DIR =logic/input/
OBJ_DIR = obj/
BIN_DIR = bin/
TEST_PHYSICAL_DIR = testPhysical/
TREE_MAIN_DIR = treeMain/
HASH_MAIN_DIR = hashMain/
PPMC_HASH_DIR = ppmcHashMain/
PPMC_TREE_DIR = ppmcTreeMain/
GENERAL_STRUCTURE_DIR = logic/structures/
MD5_DIR = logic/utils/md5/
BIGINT_DIR =  logic/utils/bigint/
ARITHMETIC_DIR = application/compresion/arithmetic/
COMPRESION_COMMON_DIR = application/compresion/common/
PPMC_DIR = application/compresion/ppmc/
LOGGER_MAIN_DIR = loggerMain/

##Objetos physical

PHYSICAL_OBJS = BlockFile.o BlockManager.o Block.o File.o FixedRegister.o FreeBlockFile.o Register.o VarRegister.o ByteConverter.o SequentialFile.o BitFile.o

PHYSICAL_OBJS_O = $(OBJ_DIR)BlockFile.o $(OBJ_DIR)BlockManager.o $(OBJ_DIR)Block.o $(OBJ_DIR)File.o $(OBJ_DIR)FixedRegister.o $(OBJ_DIR)FreeBlockFile.o $(OBJ_DIR)Register.o $(OBJ_DIR)VarRegister.o $(OBJ_DIR)ByteConverter.o $(OBJ_DIR)SequentialFile.o $(OBJ_DIR)BitFile.o

PHYSICAL_OBJS_D = $(OBJ_DIR)BlockFile.d $(OBJ_DIR)BlockManager.d $(OBJ_DIR)Block.d $(OBJ_DIR)File.d $(OBJ_DIR)FixedRegister.d $(OBJ_DIR)FreeBlockFile.d $(OBJ_DIR)Register.d $(OBJ_DIR)VarRegister.d $(OBJ_DIR)ByteConverter.d $(OBJ_DIR)SequentialFile.d $(OBJ_DIR)BitFile.d

##Objetos logic
LOGIC_OBJS = Bucket.o Hash.o Table.o InputData.o StringInputData.o archivoTexto.o Logger.o BPlusTree.o InnerNode.o LeafNode.o Node.o INodeData.o MD5.o BigIntegerAlgorithms.o BigUnsigned.o BigInteger.o BigUnsignedInABase.o BigIntegerUtils.o GeneralStructure.o

LOGIC_OBJS_O = $(OBJ_DIR)Bucket.o $(OBJ_DIR)Hash.o $(OBJ_DIR)Table.o $(OBJ_DIR)InputData.o $(OBJ_DIR)StringInputData.o $(OBJ_DIR)archivoTexto.o $(OBJ_DIR)Logger.o $(OBJ_DIR)BPlusTree.o $(OBJ_DIR)InnerNode.o $(OBJ_DIR)LeafNode.o $(OBJ_DIR)Node.o $(OBJ_DIR)INodeData.o $(OBJ_DIR)MD5.o $(OBJ_DIR)BigIntegerAlgorithms.o $(OBJ_DIR)BigUnsigned.o $(OBJ_DIR)BigInteger.o $(OBJ_DIR)BigUnsignedInABase.o $(OBJ_DIR)BigIntegerUtils.o $(OBJ_DIR)GeneralStructure.o

LOGIC_OBJS_D = $(OBJ_DIR)Bucket.d $(OBJ_DIR)Hash.d $(OBJ_DIR)Table.d $(OBJ_DIR)InputData.d $(OBJ_DIR)StringInputData.d $(OBJ_DIR)archivoTexto.d $(OBJ_DIR)Logger.d $(OBJ_DIR)BPlusTree.d $(OBJ_DIR)InnerNode.d $(OBJ_DIR)LeafNode.p      $(OBJ_DIR)Node.d $(OBJ_DIR)INodeData.d $(OBJ_DIR)MD5.d $(OBJ_DIR)BigIntegerAlgorithms.d $(OBJ_DIR)BigUnsigned.d $(OBJ_DIR)BigInteger.d $(OBJ_DIR)BigUnsignedInABase.d $(OBJ_DIR)BigIntegerUtils.d $(OBJ_DIR)GeneralStructure.d


LIBS = libapplication.a liblogic.a libphysical.a

EXEC_OBJS_O = ppmcHashMain.o ppmcTreeMain.o

EXEC_OBJS_D = ppmcHashMain.d ppmcTreeMain.d

##Objetos application
APPLICATION_OBJS = Ppmc.o PpmcHash.o PpmcTree.o ArithmeticCompressor.o FrequencyTable.o CharFrequency.o 

APPLICATION_OBJS_O = $(OBJ_DIR)Ppmc.o $(OBJ_DIR)PpmcHash.o $(OBJ_DIR)PpmcTree.o $(OBJ_DIR)ArithmeticCompressor.o $(OBJ_DIR)FrequencyTable.o $(OBJ_DIR)CharFrequency.o 

APPLICATION_OBJS_PATH_D = $(OBJ_DIR)Ppmc.d $(OBJ_DIR)PpmcHash.d $(OBJ_DIR)PpmcTree.d $(OBJ_DIR)ArithmeticCompressor.d $(OBJ_DIR)FrequencyTable.d $(OBJ_DIR)CharFrequency.d



######################################################################################
#		  PLANTILLA PARA AGREGAR UN EJECUTABLE
######################################################################################
#Foo.cpp es el archivo que contiene el main

#Foo.o: $(FOO_DIR)Foo.cpp
#	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)Foo.d" -MT"$(OBJ_DIR)Foo.d" -o"$(OBJ_DIR)Foo.o" "$(Foo_DIR)Foo.cpp"
#
#...


#Foo: createDir Foo.o libphysical.a liblogic.a
#	$(CC) -L"$(OBJ_DIR)" -o "$(BIN_DIR)Foo" "$(OBJ_DIR)Foo.o" -lphysical -llogic

#Meter en all el nombre del nuevo ejecutable

######################################################################################


MODEL = s
CC = g++
ARCHIVER = ar
AFLAGS = -r
CFLAGS = -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP
RM = rm
RMFLAGS = -f
MKDIR = mkdir
MKDIRFLAGS = -p

.PHONY: clean createDir all

all: createDir libapplication.a liblogic.a libphysical.a ppmcHashMain ppmcTreeMain
	

#Directorios
createDir: 
	$(MKDIR) $(MKDIRFLAGS) $(OBJ_DIR) $(BIN_DIR)
#Clean
clean:  
	$(RM) $(RMFLAGS) $(PHYSICAL_OBJS_O) $(PHYSICAL_OBJS_D) $(LOGIC_OBJS_O) $(LOGIC_OBJS_D) $(APPLICATION_OBJS_D) $(APPLICATION_OBJS_O) $(EXEC_OBJS_O) $(EXEC_OBJS_D) $(LIBS)


######################################################################################
#				EJECUTABLES
######################################################################################
##testPhysical: testPhysical.o libphysical.a
##	$(CC) -L"$(OBJ_DIR)" -o "$(BIN_DIR)testPhysical" "$(OBJ_DIR)testPhysical.o" -lphysical 

##loggerMain:loggerMain.o liblogic.a libphysical.a 
##	$(CC) -L"$(OBJ_DIR)" -o "$(BIN_DIR)loggerMain" "$(OBJ_DIR)loggerMain.o" -llogic -lphysical
 
##hashMain:hashMain.o liblogic.a libphysical.a 
##	$(CC) -L"$(OBJ_DIR)" -o "$(BIN_DIR)hashMain" "$(OBJ_DIR)hashMain.o" -llogic -lphysical
 
##treeMain:treeMain.o liblogic.a libphysical.a 
##	$(CC) -L"$(OBJ_DIR)" -o "$(BIN_DIR)treeMain" "$(OBJ_DIR)treeMain.o" -llogic -lphysical 

ppmcHashMain: ppmcHashMain.o libapplication.a liblogic.a libphysical.a
	$(CC) -L"$(OBJ_DIR)" -o "$(BIN_DIR)ppmcHashMain" "$(OBJ_DIR)ppmcHashMain.o" -lapplication -llogic -lphysical 

ppmcTreeMain: ppmcTreeMain.o libapplication.a liblogic.a libphysical.a
	$(CC) -L"$(OBJ_DIR)" -o "$(BIN_DIR)ppmcTreeMain" "$(OBJ_DIR)ppmcTreeMain.o" -lapplication -llogic -lphysical 


#######################################################################################
#				LIBRARIES
#######################################################################################
libphysical.a: $(PHYSICAL_OBJS) 
	$(ARCHIVER) $(AFLAGS) "$(OBJ_DIR)libphysical.a" $(PHYSICAL_OBJS_O)

liblogic.a: $(LOGIC_OBJS) 
	$(ARCHIVER) $(AFLAGS) "$(OBJ_DIR)liblogic.a" $(LOGIC_OBJS_O)

libapplication.a:$(APPLICATION_OBJS) 
	$(ARCHIVER) $(AFLAGS) "$(OBJ_DIR)libapplication.a" $(APPLICATION_OBJS_O)

#######################################################################################
#				OBJETOS PHYSICAL
#######################################################################################

ByteConverter.o:$(UTILS_DIR)ByteConverter.cpp
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)ByteConverter.d" -MT"$(OBJ_DIR)ByteConverter.d" -o"$(OBJ_DIR)ByteConverter.o" "$(UTILS_DIR)ByteConverter.cpp"

Register.o: $(FILE_DIR)Register.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)Register.d" -MT"$(OBJ_DIR)Register.d" -o"$(OBJ_DIR)Register.o" "$(FILE_DIR)Register.cpp"

VarRegister.o: $(FILE_DIR)FixedRegister.cpp
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)VarRegister.d" -MT"$(OBJ_DIR)VarRegister.d" -o"$(OBJ_DIR)VarRegister.o" "$(FILE_DIR)VarRegister.cpp"

FixedRegister.o: $(FILE_DIR)FixedRegister.cpp
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)FixedRegister.d" -MT"$(OBJ_DIR)FixedRegister.d" -o"$(OBJ_DIR)FixedRegister.o" "$(FILE_DIR)FixedRegister.cpp"

BlockFile.o: $(FILE_DIR)BlockFile.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)BlockFile.d" -MT"$(OBJ_DIR)BlockFile.d" -o"$(OBJ_DIR)BlockFile.o" "$(FILE_DIR)BlockFile.cpp"

BlockManager.o: $(FILE_DIR)BlockManager.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)BlockManager.d" -MT"$(OBJ_DIR)BlockManager.d" -o"$(OBJ_DIR)BlockManager.o" "$(FILE_DIR)BlockManager.cpp"

Block.o: $(FILE_DIR)Block.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)Block.d" -MT"$(OBJ_DIR)Block.d" -o"$(OBJ_DIR)Block.o" "$(FILE_DIR)Block.cpp"

File.o:	$(FILE_DIR)File.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)File.d" -MT"$(OBJ_DIR)File.d" -o"$(OBJ_DIR)File.o" "$(FILE_DIR)File.cpp"

FreeBlockFile.o: $(FILE_DIR)FreeBlockFile.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)FreeBlockFile.d" -MT"$(OBJ_DIR)FreeBlockFile.d" -o"$(OBJ_DIR)FreeBlockFile.o" "$(FILE_DIR)FreeBlockFile.cpp"

SequentialFile.o: $(FILE_DIR)SequentialFile.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)SequentialFile.d" -MT"$(OBJ_DIR)SequentialFile.d" -o"$(OBJ_DIR)SequentialFile.o" "$(FILE_DIR)SequentialFile.cpp"

BitFile.o: $(FILE_DIR)BitFile.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)BitFile.d" -MT"$(OBJ_DIR)BitFile.d" -o"$(OBJ_DIR)BitFile.o" "$(FILE_DIR)BitFile.cpp"


#######################################################################################
#				OBJETOS LOGIC
#######################################################################################

##HASH
Bucket.o:$(HASH_DIR)Bucket.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)Bucket.d" -MT"$(OBJ_DIR)Bucket.d" -o"$(OBJ_DIR)Bucket.o" "$(HASH_DIR)Bucket.cpp"

Hash.o:$(HASH_DIR)Hash.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)Hash.d" -MT"$(OBJ_DIR)Hash.d" -o"$(OBJ_DIR)Hash.o" "$(HASH_DIR)Hash.cpp"

Table.o:$(HASH_DIR)Table.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)Table.d" -MT"$(OBJ_DIR)Table.d" -o"$(OBJ_DIR)Table.o" "$(HASH_DIR)Table.cpp"

##INPUT

InputData.o:$(INPUT_DIR)InputData.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)InputData.d" -MT"$(OBJ_DIR)InputData.d" -o"$(OBJ_DIR)InputData.o" "$(INPUT_DIR)InputData.cpp"

StringInputData.o:$(INPUT_DIR)StringInputData.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)StringInputData.d" -MT"$(OBJ_DIR)StringInputData.d" -o"$(OBJ_DIR)StringInputData.o" "$(INPUT_DIR)StringInputData.cpp"

##LOGGER
archivoTexto.o:$(LOGGER_DIR)archivoTexto.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)archivoTexto.d" -MT"$(OBJ_DIR)archivoTexto.d" -o"$(OBJ_DIR)archivoTexto.o" "$(LOGGER_DIR)archivoTexto.cpp"

Logger.o:$(LOGGER_DIR)Logger.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)Logger.d" -MT"$(OBJ_DIR)Logger.d" -o"$(OBJ_DIR)Logger.o" "$(LOGGER_DIR)Logger.cpp"

##TREE

BPlusTree.o: $(TREE_DIR)BPlusTree.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)BPlusTree.d" -MT"$(OBJ_DIR)BPlusTree.d" -o"$(OBJ_DIR)BPlusTree.o" "$(TREE_DIR)BPlusTree.cpp"

InnerNode.o: $(TREE_DIR)InnerNode.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)InnerNode.d" -MT"$(OBJ_DIR)InnerNode.d" -o"$(OBJ_DIR)InnerNode.o" "$(TREE_DIR)InnerNode.cpp"

LeafNode.o: $(TREE_DIR)LeafNode.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)LeafNode.d" -MT"$(OBJ_DIR)LeafNode.d" -o"$(OBJ_DIR)LeafNode.o" "$(TREE_DIR)LeafNode.cpp"

Node.o: $(TREE_DIR)Node.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)Node.d" -MT"$(OBJ_DIR)Node.d" -o"$(OBJ_DIR)Node.o" "$(TREE_DIR)Node.cpp"

INodeData.o:$(TREE_DATA_DIR)INodeData.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)INodeData.d" -MT"$(OBJ_DIR)INodeData.d" -o"$(OBJ_DIR)INodeData.o" "$(TREE_DATA_DIR)INodeData.cpp"



#GENERAL STRUCTURE
GeneralStructure.o: $(GENERAL_STRUCTURE_DIR)GeneralStructure.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)Node.d" -MT"$(OBJ_DIR)GeneralStructure.d" -o"$(OBJ_DIR)GeneralStructure.o" "$(GENERAL_STRUCTURE_DIR)GeneralStructure.cpp"

##LOGIC UTILS

MD5.o:$(MD5_DIR)MD5.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)MD5.d" -MT"$(OBJ_DIR)MD5.d" -o"$(OBJ_DIR)MD5.o" "$(MD5_DIR)MD5.cpp"

BigIntegerAlgorithms.o:$(BIGINT_DIR)BigIntegerAlgorithms.cc
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)BigIntegerAlgorithms.d" -MT"$(OBJ_DIR)BigIntegerAlgorithms.d" -o"$(OBJ_DIR)BigIntegerAlgorithms.o" "$(BIGINT_DIR)BigIntegerAlgorithms.cc"

BigUnsigned.o:$(BIGINT_DIR)BigUnsigned.cc 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)BigUnsigned.d" -MT"$(OBJ_DIR)BigUnsigned.d" -o"$(OBJ_DIR)BigUnsigned.o" "$(BIGINT_DIR)BigUnsigned.cc"

BigInteger.o:$(BIGINT_DIR)BigInteger.cc 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)BigInteger.d" -MT"$(OBJ_DIR)BigInteger.d" -o"$(OBJ_DIR)BigInteger.o" "$(BIGINT_DIR)BigInteger.cc"

BigUnsignedInABase.o:$(BIGINT_DIR)BigUnsignedInABase.cc 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)BigUnsignedInABase.d" -MT"$(OBJ_DIR)BigUnsignedInABase.d" -o"$(OBJ_DIR)BigUnsignedInABase.o" "$(BIGINT_DIR)BigUnsignedInABase.cc"

BigIntegerUtils.o:$(BIGINT_DIR)BigIntegerUtils.cc 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)BigIntegerUtils.d" -MT"$(OBJ_DIR)BigIntegerUtils.d" -o"$(OBJ_DIR)BigIntegerUtils.o" "$(BIGINT_DIR)BigIntegerUtils.cc"

##APPLICATION 

Ppmc.o:$(PPMC_DIR)Ppmc.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)Ppmc.d" -MT"$(OBJ_DIR)Ppmc.d" -o"$(OBJ_DIR)Ppmc.o" "$(PPMC_DIR)Ppmc.cpp"

PpmcHash.o:$(PPMC_DIR)PpmcHash.cpp
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)PpmcHash.d" -MT"$(OBJ_DIR)PpmcHash.d" -o"$(OBJ_DIR)PpmcHash.o" "$(PPMC_DIR)PpmcHash.cpp"

PpmcTree.o:$(PPMC_DIR)PpmcTree.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)PpmcTree.d" -MT"$(OBJ_DIR)PpmcTree.d" -o"$(OBJ_DIR)PpmcTree.o" "$(PPMC_DIR)PpmcTree.cpp"

ArithmeticCompressor.o:$(ARITHMETIC_DIR)ArithmeticCompressor.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)ArithmeticCompressor.d" -MT"$(OBJ_DIR)ArithmeticCompressor.d" -o"$(OBJ_DIR)ArithmeticCompressor.o" "$(ARITHMETIC_DIR)ArithmeticCompressor.cpp"

CharFrequency.o:$(COMPRESION_COMMON_DIR)CharFrequency.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)CharFrequency.d" -MT"$(OBJ_DIR)CharFrequency.d" -o"$(OBJ_DIR)CharFrequency.o" "$(COMPRESION_COMMON_DIR)CharFrequency.cpp"

FrequencyTable.o:$(COMPRESION_COMMON_DIR)FrequencyTable.cpp 
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)FrequencyTable.d" -MT"$(OBJ_DIR)FrequencyTable.d" -o"$(OBJ_DIR)FrequencyTable.o" "$(COMPRESION_COMMON_DIR)FrequencyTable.cpp"


#######################################################################################
#			OBJETOS UT
#######################################################################################
##testPhysical.o: $(TEST_PHYSICAL_DIR)testPhysical.cpp
##	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)testPhysical.d" -MT"$(OBJ_DIR)testPhysical.d" -o"$(OBJ_DIR)testPhysical.o" "$(TEST_PHYSICAL_DIR)testPhysical.cpp"

##treeMain.o: $(TREE_MAIN_DIR)TreeMain.cpp
##	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)treeMain.d" -MT"$(OBJ_DIR)treeMain.d" -o"$(OBJ_DIR)treeMain.o" "$(TREE_MAIN_DIR)TreeMain.cpp"

##loggerMain.o:$(LOGGER_MAIN_DIR)LoggerMain.cpp
##	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)loggerMain.d" -MT"$(OBJ_DIR)loggerMain.d" -o"$(OBJ_DIR)loggerMain.o" "$(LOGGER_MAIN_DIR)LoggerMain.cpp"

##hashMain.o:$(HASH_MAIN_DIR)HashMain.cpp
##	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)hashMain.d" -MT"$(OBJ_DIR)hashMain.d" -o"$(OBJ_DIR)hashMain.o" "$(HASH_MAIN_DIR)HashMain.cpp"

ppmcTreeMain.o:$(PPMC_TREE_DIR)ppmcTreeMain.cpp
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)ppmcTreeMain.d" -MT"$(OBJ_DIR)ppmcTreeMain.d" -o"$(OBJ_DIR)ppmcTreeMain.o" "$(PPMC_TREE_DIR)ppmcTreeMain.cpp"

ppmcHashMain.o:$(PPMC_HASH_DIR)ppmcHashMain.cpp
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)ppmcHashMain.d" -MT"$(OBJ_DIR)ppmcHashMain.d" -o"$(OBJ_DIR)ppmcHashMain.o" "$(PPMC_HASH_DIR)ppmcHashMain.cpp"


