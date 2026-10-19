CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -pedantic
CPPFLAGS ?= -Ihelpers

TARGET := produk.exe
SOURCES := $(wildcard program/*.cpp)
HEADERS := $(wildcard helpers/*.h)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET)
