CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g

PROGRAM      := src/program
HEADERS      := src/headers
BUILD    := build
TARGET   := app
CPPFLAGS := -I$(HEADERS)

OBJS := $(BUILD)/main.o \
        $(BUILD)/produk.o \
        $(BUILD)/tampilan.o \
        $(BUILD)/editData.o \
        $(BUILD)/statistikAndMemory.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD)/main.o: $(PROGRAM)/main.cpp $(HEADERS)/produk.h $(HEADERS)/tampilan.h \
                 $(HEADERS)/editData.h $(HEADERS)/statistikAndMemory.h | $(BUILD)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD)/produk.o: $(PROGRAM)/produk.cpp $(HEADERS)/produk.h $(HEADERS)/tampilan.h \
                   $(HEADERS)/editData.h | $(BUILD)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD)/tampilan.o: $(PROGRAM)/tampilan.cpp $(HEADERS)/tampilan.h $(HEADERS)/produk.h | $(BUILD)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD)/editData.o: $(PROGRAM)/editData.cpp $(HEADERS)/editData.h $(HEADERS)/produk.h | $(BUILD)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD)/statistikAndMemory.o: $(PROGRAM)/statistikAndMemory.cpp \
                               $(HEADERS)/statistikAndMemory.h $(HEADERS)/produk.h | $(BUILD)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD) $(TARGET)

.PHONY: all run clean