# Define C++ compiler
CXX = g++

# Define linker
LINKER = g++

# Debug flag: either nothing or -ggdb
DEBUGFLAG =

# Opitmization flag
OPTFLAG = -O2

# ROOT flag: -D__ROOT__
ROOTFLAG =

# Define C++ flags (-D_VANILLA_ROOT_ is needed to avoid StMessMgr confusion)
CXXFLAGS = $(shell root-config --cflags) -I. -I.. $(OPTFLAG) -fPIC -W -Woverloaded-virtual -Wno-deprecated-declarations -Wall
CXXFLAGS += -pipe $(ROOTFLAG) -std=c++17 -D_VANILLA_ROOT_ $(DEBUGFLAG)

# Define libraries to be added
LIBS = $(shell root-config --libs) -lEG -lgfortran
LIBS += -L$(HBTMAKERPATH) -lStHbtMaker -L../McDst -lMcDst -L../StPicoEvent -lStPicoDst
LIBS += -L../StFemtoEvent -lStFemtoDst

# Define path to include directories
INCS = $(shell root-config --incdir)

# Linker flags
LDFLAGS = $(shell root-config --cflags) $(OPTFLAG) $(ROOTFLAG) -fPIC -Wall
LDFLAGS += -pipe -D_VANILLA_ROOT_ -I. -I..

# Define output library
STHBTMAKERUSER = libStHbtMakerUser.so

# Compile all *.cxx classes in the directory
SRC = $(shell find . -name "*.cxx" -printf "%f\n")

all: $(STHBTMAKERUSER)

# Main constructor // was in the next line  StHbtMakerUser_Dict.C
$(STHBTMAKERUSER): $(SRC:.cxx=.o)
	$(LINKER) $(LDFLAGS) -shared $^ -o $(STHBTMAKERUSER) $(LIBS)

# Compile C++ files
%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Dictionary generation
StHbtMakerUser_Dict.C: $(shell find . -name "*.h" ! -name "*LinkDef*")
	rootcint -f $@ -c -D_VANILLA_ROOT_ -DROOT_CINT -D__ROOT__ -I. -I.. -I$(INCS) $^ StHbtMakerUserLinkDef.h

# PHONY options
.PHONY: clean distclean

# Remove object files and dictionary
clean:
	rm -vf *.o StHbtMakerUser_Dict*

# Remove object files, dictionary and library
distclean:
	rm -vf *.o StHbtMakerUser_Dict* $(STHBTMAKERUSER)
