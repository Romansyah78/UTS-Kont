CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -pedantic
CPPFLAGS ?= -Ihelpers

TARGET := produk
SOURCES := program/main.cpp program/produk.cpp program/tampilan.cpp
HEADERS := helpers/produk.h helpers/tampilan.h

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe
