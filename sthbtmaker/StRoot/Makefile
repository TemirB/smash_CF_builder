# Название выходного бинарного файла
TARGET = hbt_auau_simu

# Файл исходника
SRC = hbt_auau_simu.cxx

# Компилятор и флаги
CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17 \
  -I. \
  -I./StarClassLibrary

# Путь к ROOT
ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs)

# Локальные библиотеки (путь указывается относительно текущего каталога)
LDFLAGS = -Llibs -lStHbtMaker -lStHbtMakerUser -lMcDst -lStPicoDst -lStFemtoDst

# Компоновка
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(ROOTCFLAGS) $(SRC) -o $(TARGET) $(ROOTLIBS) $(LDFLAGS)

clean:
	rm -f $(TARGET)
