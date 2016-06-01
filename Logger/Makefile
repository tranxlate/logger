#.SUFFIXES	: .c .cpp .o
SRC_DIR=src
INC_DIR=include
OBJ_DIR=obj
LIB_DIR=lib
TEST_DIR=test

#Lib
LOGGER_LIB=Logger

#make
all	: libdir logger testpg

libdir	: 
	mkdir -p $(LIB_DIR)
	mkdir -p $(OBJ_DIR)
	
logger	:
	g++ -c $(SRC_DIR)/Logger.cpp -I$(INC_DIR)
	mv Logger.o $(OBJ_DIR)
	ar rv $(LIB_DIR)/lib$(LOGGER_LIB).a $(OBJ_DIR)/Logger.o

testpg	:
	g++ -o $(TEST_DIR)/LoggerTest $(TEST_DIR)/LoggerTest.cpp -I$(INC_DIR) -L$(LIB_DIR) -l$(LOGGER_LIB)

#.PHONY : clean	
clean	: 
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_DIR)/*