.PHONY: all

PROJECT=ecppc
TYPE=app

SOURCES+= odd.cpp
INCLUDES+=
INCLUDE_DIRS+= /Users/avandra/projects/c++/gtest-1.7.0/include

LIBS+= stdc++
LIB_DIRS+= /Users/avandra/projects/c++/gtest-1.7.0/lib

TESTS+= a.cpp b.cpp

SRC_DIR=src
TEST_DIR=test
INC_DIR=include

INSTALL_DIR=install


include common.mk
