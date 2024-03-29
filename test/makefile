# -*- mode:C++; c-basic-offset:2; indent-tabs-mode:nil -*-
#
# Copyright2023 Glen S. Dayton
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

.SUFFIXES:
.SUFFICES: .cpp .hpp .h .o

SRCDIR=./
TESTS=CppUnitXLiteTests NoMacroTests

VPATH=$(SRCDIR)

INCLUDEDIR=$(SRCDIR)../..
CPPFLAGS=-I$(INCLUDEDIR)

SRCS:=CppUnitXLiteTests.cpp NoMacroTests.cpp
OBJS:=$(SRCS:%.cpp=%.o)

SRCS:=$(addprefix $(SRCDIR),$(SRCS))
DEPS:=$(OBJS:%.o=%.d)

%.o : %.cpp
	$(COMPILE.cc) -o $@ $<

CPPFLAGS = -I/Users/gdayton19/Projects/CppUnitXLite/test/../..

CXXFLAGS = -g -std=c++2b -fcolor-diagnostics

all: test

CppUnitXLiteTests: CppUnitXLiteTests.o
	$(LINK.cc) -o $@ CppUnitXLite.o


CppUnitXLiteTests.o : $(SRCDIR)CppUnitXLiteTests.cpp  \
$(SRCDIR)CppUnitXLiteTests.hpp \
$(SRCDIR)../CppUnitXLite.cpp \
$(SRCDIR)../CppUnitXLite.hpp


NoMacroTests: NoMacroTests.o
	$(LINK.cc) -o $@ NoMacroTests.o

NoMacroTests.o : $(SRCDIR)NoMacroTests.cpp $(SRCDIR)../CppUnitXLite.hpp


test: $(TESTS)
	./CppUnitXLiteTests
	./NoMacroTests


# Rebuild this project
rebuild: clean all

# Clean this project
clean:
	$(RM) -f $(TESTS)
	$(RM) -f $(OBJS)
	$(RM) -f $(DEPS)


