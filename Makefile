CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -pedantic
CPPFLAGS ?= -Ihelpers

TARGET := produk
SOURCE := program/produk.cpp
HEADER := helpers/produk.h

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCE) $(HEADER)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe
