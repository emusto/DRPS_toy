#Template Makefile for a simple executable created from a single cxx file and linked with the root librariess

MYMAIN	  = DRPS_toy
SOURCEDIR = src
SOURCES = $(wildcard $(SOURCEDIR)/*.cxx)

# the name you want for the .so
LIBNAME	  = DRPS

#The first target defined is the default for the makefile
CXX	= /usr/bin/g++
RM	= /bin/rm -f
SHELL = /bin/sh
MAKE = /usr/bin/make

##### Library path and compiler / linker / rootcint options #####
LPATH		= -L.
CXXFLAGS	= -O2 -Wall
CXX		= g++
SOFLAGS		= -shared -fPIC -O2

##### Libraries to pull in and flags #####
#for the dependency generation, it is often useful to add the last two directories 
#to supress warnings (and get the dependencies correct)
ROOTCFLAGS   	:= $(shell root-config --cflags) 
ROOTLIBS     	:= $(shell root-config --libs)
ROOTGLIBS    	:= $(shell root-config --glibs)

CXXFLAGS	+= $(ROOTCFLAGS) -I./include
SOFLAGS 	+= $(ROOTGLIBS)
SOFLAGS 	+= $(LPATH)

#Add specific options for our EXE to enable it to find shared libraries
EXEFLAGS        = $(CXXFLAGS) $(LPATH)
EXELIBS		= $(ROOTGLIBS) $(ROOTLIBS) -Wl,-rpath . -l$(LIBNAME)

#### All our targets#####
#build a list of cpp files, this is going to be used when we generate our header file dependencies automatically
#CXXFILES := $(shell ls src/*.cxx)

#### The actual compilation commands
#g++ -shared -I./include -fPIC `root-config --libs --glibs --cflags` -o libDRPS.so *.cxx
#g++ -L. -I./include `root-config --libs --glibs --cflags` -Wl,-rpath . -lDRPS -o DRPS_toy DRPS_toy.C

##### Rules #####
.SUFFIXES:   	.C .d .P
.PHONY:  all clean
default:     all

# the rules
lib: $(SOURCEDIR) 
	$(info  Compiling the $(LIBNAME) library)	
	$(CXX) $(SOFLAGS) $(CXXFLAGS) -o lib$(LIBNAME).so $(SOURCES)

exe: $(MYMAIN).C
	$(info  Compiling the main executable)	
	$(CXX) $(EXEFLAGS) $(EXELIBS) -o $(MYMAIN) $^

all:	lib exe

clean: 
	-$(RM)  $(MYMAIN)  *.so



