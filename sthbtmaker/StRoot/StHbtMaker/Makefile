# Define C++ compiler
CXX = g++

# Define Fortran compiler
FC = gfortran

# Define linker
LINKER = g++

# Debug flag: either nothing or -ggdb
DEBUGFLAG =

# Opitmization flag
OPTFLAG = -O2

# ROOT flag: -D__ROOT__
ROOTFLAG =

# Define C++ flags (-D_VANILLA_ROOT_ is needed to avoid StMessMgr confusion)
CXXFLAGS = $(shell root-config --cflags) $(OPTFLAG) -fPIC -W -Woverloaded-virtual -Wno-deprecated-declarations
CXXFLAGS += -Wall -pipe $(ROOTFLAG) -I. -I.. -std=c++17 -D_VANILLA_ROOT_ $(DEBUGFLAG)
# Define libraries to be added
LIBS = $(shell root-config --libs) -lEG -lgfortran
# Define path to include directories
INCS = $(shell root-config --incdir)
# Linker flags
LDFLAGS = $(shell root-config --cflags) $(OPTFLAG) -fPIC -Wall -pipe -D_VANILLA_ROOT_ $(ROOTFLAG) -I. -I..

# Define fortran compilation flags
FFLAGS = -fPIC -pipe $(OPTFLAG) $(DEBUGFLAG)

# Define output library
STHBTMAKER = libStHbtMaker.so

# Compile all *.cxx classes in the directory
SRCCXX = $(shell find . -name "*.cxx" -printf "%f\n")
# Compile all *.f classes in the directory
SRCF = $(shell find . -name "*.F" -printf "%f\n")

# C++ and Fortran extensions: TODO - make it automatic
SRCEXT = F cxx

all: $(STHBTMAKER)

# Main constructor // was in the next line StHbtMaker_Dict.C
$(STHBTMAKER): $(SRCCXX:.cxx=.o) $(SRCF:.F=.o)
	$(LINKER) $(LDFLAGS) -shared $^ -o $(STHBTMAKER) $(LIBS)

# Compile C++ files
%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile fortran files
%.o: %.F
	$(FC) $(FFLAGS) -c -o $@ $<

# Dictionary generation
StHbtMaker_Dict.C: $(shell find . -name "*.h" ! -name "*LinkDef*")
	rootcint -f $@ -c -D_VANILLA_ROOT_ -DROOT_CINT  -I. -I.. -I$(INCS) -D__ROOT__ $^ StHbtMakerLinkDef.h

# PHONY options
.PHONY: clean distclean

# Remove object files and dictionary
clean:
	rm -vf *.o StHbtMaker_Dict*

# Remove object files, dictionary and library
distclean:
	rm -vf *.o StHbtMaker_Dict* $(STHBTMAKER)
