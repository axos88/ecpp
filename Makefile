.PHONY: all

PROJECT=ecppc
TYPE=app

SOURCES+= tokenizer.cpp
SOURCES+= lexer.cpp

INCLUDES+=
INCLUDE_DIRS+= /Users/avandra/projects/c++/gtest-1.7.0/include

LIBS+= stdc++
LIB_DIRS+= /Users/avandra/projects/c++/gtest-1.7.0/lib

TESTS+= tokenizer_test.cpp
TESTS+= lexer_test.cpp
TESTS+= render_context_test.cpp

SRC_DIR=src
TEST_DIR=test
INC_DIR=include

INSTALL_DIR=install


include common.mk
