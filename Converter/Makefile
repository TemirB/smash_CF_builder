# Makefile для компиляции программы

# Путь к установке ROOT
ROOT_DIR = /home/tahea/root_install

# Путь к библиотекам McDst
MCDST_DIR = /home/tahea/McDst

# Компилятор
CXX = g++

# Флаги компилятора
CXXFLAGS = $(shell root-config --cflags) -fPIC -Wall -std=c++17
CXXFLAGS += -I$(MCDST_DIR) -I$(ROOT_DIR)/include -Iinclude
LIBS = $(shell root-config --glibs) -L$(ROOT_DIR)/lib -lCore -lRIO -lTree -lHist -lGraf -lGpad -lPhysics -lThread -lm
LIBS += -L$(MCDST_DIR) -lMcDst

# Имя исполняемого файла
TARGET = converter

# Директории
SRC_DIR = src
BUILD_DIR = build

# Источники
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Создать build директорию при необходимости
$(shell mkdir -p $(BUILD_DIR))

# Правила сборки
all: $(TARGET)

# Сборка исполняемого файла в корне
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

# Компиляция объектных файлов в build
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Удаление всех промежуточных файлов
distclean: clean
	rm -f *~