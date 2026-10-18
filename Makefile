CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -pedantic
CPPFLAGS ?= -Iinclude

TARGET := produk.exe
SOURCE := src/main.cpp
HEADER := include/produk.h

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCE) $(HEADER)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
