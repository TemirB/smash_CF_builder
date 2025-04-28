# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -pthread -m64

# Пути
ROOT_DIR = /home/tahea/root_install
MC_DST = /home/tahea/McDst
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Подключение заголовочных файлов
CXXFLAGS += -I$(ROOT_DIR)/include -I$(MC_DST) -I$(INC_DIR)

# Линкирование
LDFLAGS = -L$(ROOT_DIR)/lib -L$(MC_DST) $(shell root-config --libs) -lMcDst

# Исходники
SRC = main.cpp $(SRC_DIR)/OscarConverter.cpp $(SRC_DIR)/Particle.cpp
OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC))

# Имя выходного файла
TARGET = convert_oscar

# Правила
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

# Компиляция с выводом в build/
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

run-test:
	@if [ -z "$$OSCAR_INPUT_DIR" ]; then \
		echo "Please set OSCAR_INPUT_DIR first!"; exit 1; \
	fi; \
	./$(TARGET) "$$OSCAR_INPUT_DIR/test_input.oscar" test_output.root
