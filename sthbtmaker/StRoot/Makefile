# Compiler and flags
CXX := g++
CXXFLAGS := -O2 -std=c++17 -Wall -fPIC \
    `root-config --cflags` \
    -I. -IStHbtMaker -IMcDst -IStHbtMakerUser

LDFLAGS := `root-config --libs` -Llibs \
  -lStHbtMaker -lMcDst -lStHbtMakerUser \
  -lStPicoDst -lStFemtoDst


CXXFLAGS += `root-config --cflags`
LDFLAGS  += `root-config --libs` -lMcDst


# Target macro
TARGET := hbt_auau_simu
SRC := $(TARGET).cxx

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET)
