.SUFFIXES: .cpp .hpp

# Programs
SHELL 	= bash
CC     	= g++
LD	= ld
RM 	= rm
ECHO	= /bin/echo
CAT	= cat
PRINTF	= printf
SED	= sed
DOXYGEN = doxygen
######################################
# Project Name (generate executable with this name)
TARGET = cs251_base

# Project Paths
PROJECT_ROOT=./
EXTERNAL_ROOT=$(PROJECT_ROOT)/external
EXTERNAL_SRC=$(PROJECT_ROOT)/external/src
SRCDIR = $(PROJECT_ROOT)/src
OBJDIR = $(PROJECT_ROOT)/obj
BINDIR = $(PROJECT_ROOT)/bin
DOCDIR = $(PROJECT_ROOT)/doc
MODDIR = $(PROJECT_ROOT)/modsrc
DIR_ECOM = $(EXTERNAL_SRC)/Box2D/Box2D/Common
DIR_EDYN = $(EXTERNAL_SRC)/Box2D/Box2D/Dynamics
BB=$(PROJECT_ROOT)/external/src/Box2D
BC=$(PROJECT_ROOT)/external/lib/
BD=$(PROJECT_ROOT)/external/include/

# Library Paths
BOX2D_ROOT=$(EXTERNAL_ROOT)
GLUI_ROOT=/usr
GL_ROOT=/usr/include/

#Libraries
LIBS = -lBox2D -lglui -lglut -lGLU -lGL

# Compiler and Linker flags
CPPFLAGS =-g -O3 -Wall -fno-strict-aliasing
CPPFLAGS+=-I $(BOX2D_ROOT)/include -I $(GLUI_ROOT)/include
LDFLAGS+=-L $(BOX2D_ROOT)/lib -L $(GLUI_ROOT)/lib

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SRCDIR)/*.cpp)
INCS := $(wildcard $(SRCDIR)/*.hpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


.PHONY: all setup doc clean distclean

all:setup $(BINDIR)/$(TARGET)

r: distclean b2dsetup setup $(BINDIR)/$(TARGET)

b2dsetup: b2dsetupstr modf b2dsetupcont

b2dsetupstr:
	@if [ ! -d external/src/Box2D/build251 ]; \
	then \
	tar -xvzf $(EXTERNAL_SRC)/Box2D.tgz; \
	mv Box2D $(EXTERNAL_SRC)/Box2D; \
	cd $(EXTERNAL_SRC)/Box2D; \
	mkdir build251; \
	cd build251; \
	fi

modf:
	@$(RM) -rf $(SRCDIR)/render.cpp $(SRCDIR)/cs251_base.cpp $(SRCDIR)/cs251_base.hpp 
	@$(RM) -rf $(SRCDIR)/dominos.cpp $(SRCDIR)/dominos.hpp $(SRCDIR)/main.cpp $(SRCDIR)/callbacks.cpp
	@cp $(MODDIR)/render.cpp $(SRCDIR)/
	@cp $(MODDIR)/cs251_base.cpp $(SRCDIR)/
	@cp $(MODDIR)/cs251_base.hpp $(SRCDIR)/
	@cp $(MODDIR)/dominos.hpp $(SRCDIR)/
	@cp $(MODDIR)/dominos_1.cpp $(SRCDIR)/
	@cp $(MODDIR)/dominos_2.cpp $(SRCDIR)/
	@cp $(MODDIR)/main.cpp $(SRCDIR)/
	@cp $(MODDIR)/callbacks.cpp $(SRCDIR)/
	@cp $(MODDIR)/init_sims.cpp $(SRCDIR)/
	@$(RM) $(DIR_ECOM)/b2Draw.h $(DIR_EDYN)/b2World.cpp $(DIR_EDYN)/b2Fixture.h $(DIR_EDYN)/b2Fixture.cpp #For Color
	@$(RM) $(DIR_EDYN)/b2Body.cpp $(DIR_EDYN)/b2Body.h                                                    #For MouseJoint
	@cp $(MODDIR)/b2Draw.h $(DIR_ECOM)/
	@cp $(MODDIR)/b2World.cpp $(DIR_EDYN)/
	@cp $(MODDIR)/b2Fixture.h $(DIR_EDYN)/
	@cp $(MODDIR)/b2Fixture.cpp $(DIR_EDYN)/
	@cp $(MODDIR)/b2Body.cpp $(DIR_EDYN)/
	@cp $(MODDIR)/b2Body.h $(DIR_EDYN)/

b2dsetupcont:	
	@cd $(EXTERNAL_SRC)/Box2D/build251; \
	cmake ../; \
	make; \
	make install; 	

setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p obj
	@mkdir -p bin

$(BINDIR)/$(TARGET): $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

-include -include $(OBJS:.o=.d)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

doc:
	@$(ECHO) -n "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(ECHO) "Done"

clean:
	@$(RM) -rf $(OBJDIR) *~ $(DEPS) $(SRCDIR)/*~ $(BINDIR) 

distclean: clean
	@$(RM) -rf $(BB) $(BC) $(BD) $(PROJECT_ROOT)/doc
