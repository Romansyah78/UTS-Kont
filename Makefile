# Kompiler dan Flag
CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -Iinclude

# Direktori Proyek
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Mengumpulkan seluruh file .cpp di folder src/
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
TARGET = $(BIN_DIR)/main

# Target Utama
all: $(TARGET)

# Kompilasi Executable dari Object Files
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# Kompilasi File .cpp menjadi File .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Membuat Direktori Output Kompilasi
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Menjalankan Program
run: $(TARGET)
	./$(TARGET)

# Membersihkan Hasil Kompilasi
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all run clean