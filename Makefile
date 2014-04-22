.PHONY: all

PROJECT=ecppc
TYPE=app

SOURCES+= tokenizer.cpp lexer.cpp
INCLUDES+=
INCLUDE_DIRS+= /Users/avandra/projects/c++/gtest-1.7.0/include


LIBS+= stdc++
LIB_DIRS+= /Users/avandra/projects/c++/gtest-1.7.0/lib

TESTS+= eccpc_test.cpp lexer_test.cpp

SRC_DIR=src
TEST_DIR=test
INC_DIR=include

INSTALL_DIR=install


include common.mk
