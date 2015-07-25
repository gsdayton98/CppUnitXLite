
MAKE=/usr/bin/make
RM=/bin/rm
MKDIR=/bin/mkdir

.SUFFIXES:
.SUFFICES: .cpp .hpp ..h .o

BUILDDIR=./
SRCDIR=
TESTS=$(BUILDDIR)CppUnitXLiteTests

VPATH=$(SRCDIR)

INCLUDEDIR=$(SRCDIR)/../..
CPPFLAGS=-I$(INCLUDEDIR)

MAKEDEPEND=$(CXX)  -MDD -MP $(CPPFLAGS) -o $*.d $<

SRCS:= CppUnitXLiteTests.cpp NoMacroTests.cpp
OBJS:=$(SRCS:%.cpp=%.o)


SRCS:=$(addprefix $(SRCDIR),$(SRCS))
OBJS:=$(addprefix $(BUILDDIR),$(OBJS))
DEPS:=$(OBJS:%.o=%.d)


%.o : %.cpp
	$(COMPILE.cc) -o $(BUILDDIR)/$@ $<

#  Automatic dependency generation
#  Has disadvantage of processing twice but is widely applicable
%.d : %.cpp
	@set -e; rm -f $@; \
	$(CXX) -MMD -MP $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

-include $(DEPS)

all: $(TESTS)

$(BUILDDIR)CppUnitXLiteTests: $(BUILDDIR) $(OBJS)
	$(LINK.cc) -o $@ $(OBJS)

$(BUILDDIR):
	$(MKDIR) -p "$(BUILDDIR)"

$(BUILDDIR)/CppUnitXLiteTests.o : $(SRCDIR)/CppUnitXLiteTests.cpp

$(BUILDDIR)/NoMacroTests.o : $(SRCDIR)/NoMacroTests.cpp

test: $(TESTS)
	$(BUILDDIR)CppUnitXLiteTests


# Rebuild this project
rebuild: clean all

# Clean this project
clean:
	$(RM) -f $(TESTS)
	$(RM) -f $(OBJS)
	$(RM) -f $(DEPS)


