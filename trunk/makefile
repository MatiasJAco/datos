######################################################################################
# Makefile TP1 7506 
# Grupo PAITITI
# Autor Alex
# Fecha 1/04/10	
######################################################################################

FILE_DIR = physical/file/
UTILS_DIR = physical/utils/
HASH_DIR = logic/hash/
LOGGER_DIR = logic/logger/
TREE_DIR = logic/tree/
TREE_DATA_DIR = $(TREE_DIR)dataNode/
INPUT_DIR =logic/input/
OBJ_DIR = obj/
BIN_DIR = bin/
TEST_PHYSICAL_DIR = testPhysical/
TREE_MAIN_DIR = treeMain/
HASH_MAIN_DIR = hashMain/
LOGGER_MAIN_DIR = loggerMain/

##Objetos physical

PHYSICAL_OBJS = BlockFile.o BlockManager.o Block.o File.o FixedRegister.o FreeBlockFile.o Register.o VarRegister.o ByteConverter.o

PHYSICAL_OBJS_O = $(OBJ_DIR)BlockFile.o $(OBJ_DIR)BlockManager.o $(OBJ_DIR)Block.o $(OBJ_DIR)File.o $(OBJ_DIR)FixedRegister.o $(OBJ_DIR)FreeBlockFile.o $(OBJ_DIR)Register.o $(OBJ_DIR)VarRegister.o $(OBJ_DIR)ByteConverter.o

PHYSICAL_OBJS_D = $(OBJ_DIR)BlockFile.d $(OBJ_DIR)BlockManager.d $(OBJ_DIR)Block.d $(OBJ_DIR)File.d $(OBJ_DIR)FixedRegister.d $(OBJ_DIR)FreeBlockFile.d $(OBJ_DIR)Register.d $(OBJ_DIR)VarRegister.d $(OBJ_DIR)ByteConverter.d

##Objetos logic
LOGIC_OBJS = Bucket.o Hash.o Table.o InputData.o StringInputData.o archivoTexto.o Logger.o BPlusTree.o InnerNode.o LeafNode.o Node.o INodeData.o

LOGIC_OBJS_O = $(OBJ_DIR)Bucket.o $(OBJ_DIR)Hash.o $(OBJ_DIR)Table.o $(OBJ_DIR)InputData.o $(OBJ_DIR)StringInputData.o $(OBJ_DIR)archivoTexto.o $(OBJ_DIR)Logger.o $(OBJ_DIR)BPlusTree.o $(OBJ_DIR)InnerNode.o $(OBJ_DIR)LeafNode.o $(OBJ_DIR)Node.o $(OBJ_DIR)INodeData.o

LOGIC_OBJS_D = $(OBJ_DIR)Bucket.d $(OBJ_DIR)Hash.d $(OBJ_DIR)Table.d $(OBJ_DIR)InputData.d $(OBJ_DIR)StringInputData.d $(OBJ_DIR)archivoTexto.d $(OBJ_DIR)Logger.d $(OBJ_DIR)BPlusTree.d $(OBJ_DIR)InnerNode.d $(OBJ_DIR)LeafNode.p      $(OBJ_DIR)Node.d $(OBJ_DIR)INodeData.d

##Objetos application
#APPLICATION_OBJS 

#APPLICATION_OBJS_O 

#APPLICATION_OBJS_PATH_D


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

all: createDir libphysical.a liblogic.a loggerMain hashMain treeMain
	

#Directorios
createDir: 
	$(MKDIR) $(MKDIRFLAGS) $(OBJ_DIR) $(BIN_DIR)
#Clean
clean:  
	$(RM) $(RMFLAGS) $(PHYSICAL_OBJS_O) $(PHYSICAL_OBJS_D) $(LOGIC_OBJS_O) $(LOGIC_OBJS_D) $(APPLICATION_OBJS_D) $(APPLICATION_OBJS_O)


######################################################################################
#				EJECUTABLES
######################################################################################
testPhysical: testPhysical.o libphysical.a
	$(CC) -L"$(OBJ_DIR)" -o "$(BIN_DIR)testPhysical" "$(OBJ_DIR)testPhysical.o" -lphysical 

loggerMain:loggerMain.o
	$(CC) -L"$(OBJ_DIR)" -o "$(BIN_DIR)loggerMain" "$(OBJ_DIR)loggerMain.o" -lphysical -llogic
 
hashMain:hashMain.o
	$(CC) -L"$(OBJ_DIR)" -o "$(BIN_DIR)hashMain" "$(OBJ_DIR)hashMain.o" -lphysical -llogic
 
treeMain:treeMain.o
	$(CC) -L"$(OBJ_DIR)" -o "$(BIN_DIR)treeMain" "$(OBJ_DIR)treeMain.o" -lphysical -llogic

#######################################################################################
#				LIBRARIES
#######################################################################################
libphysical.a: $(PHYSICAL_OBJS) 
	$(ARCHIVER) $(AFLAGS) "$(OBJ_DIR)libphysical.a" $(PHYSICAL_OBJS_O)

liblogic.a: $(LOGIC_OBJS) 
	$(ARCHIVER) $(AFLAGS) "$(OBJ_DIR)liblogic.a" $(LOGIC_OBJS_O)

#libapplication.a:$(LOGIC_OBJS) 
#	$(ARCHIVER) $(AFLAGS) "$(OBJ_DIR)libphysical.a" $(LOGIC_OBJS_O)

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

#######################################################################################
#			OBJETOS UT
#######################################################################################
testPhysical.o: $(TEST_PHYSICAL_DIR)testPhysical.cpp
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)testPhysical.d" -MT"$(OBJ_DIR)testPhysical.d" -o"$(OBJ_DIR)testPhysical.o" "$(TEST_PHYSICAL_DIR)testPhysical.cpp"

treeMain.o: $(TREE_MAIN_DIR)TreeMain.cpp
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)treeMain.d" -MT"$(OBJ_DIR)treeMain.d" -o"$(OBJ_DIR)treeMain.o" "$(TREE_MAIN_DIR)TreeMain.cpp"

loggerMain.o:$(LOGGER_MAIN_DIR)LoggerMain.cpp
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)loggerMain.d" -MT"$(OBJ_DIR)loggerMain.d" -o"$(OBJ_DIR)loggerMain.o" "$(LOGGER_MAIN_DIR)LoggerMain.cpp"

hashMain.o:$(HASH_MAIN_DIR)HashMain.cpp
	$(CC) $(CFLAGS) -MF"$(OBJ_DIR)hashMain.d" -MT"$(OBJ_DIR)hashMain.d" -o"$(OBJ_DIR)hashMain.o" "$(HASH_MAIN_DIR)HashMain.cpp"


