CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g

PROGRAM      := src/program
HEADERS      := src/headers
OFILE    := Ofile
TARGET   := app
CPPFLAGS := -I$(HEADERS)

OBJS := $(OFILE)/main.o \
        $(OFILE)/produk.o \
        $(OFILE)/tampilan.o \
        $(OFILE)/editData.o \
        $(OFILE)/statistikAndMemory.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OFILE)/main.o: $(PROGRAM)/main.cpp $(HEADERS)/produk.h $(HEADERS)/tampilan.h \
                 $(HEADERS)/editData.h $(HEADERS)/statistikAndMemory.h | $(OFILE)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OFILE)/produk.o: $(PROGRAM)/produk.cpp $(HEADERS)/produk.h $(HEADERS)/tampilan.h \
                   $(HEADERS)/editData.h | $(OFILE)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OFILE)/tampilan.o: $(PROGRAM)/tampilan.cpp $(HEADERS)/tampilan.h $(HEADERS)/produk.h | $(OFILE)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OFILE)/editData.o: $(PROGRAM)/editData.cpp $(HEADERS)/editData.h $(HEADERS)/produk.h | $(OFILE)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OFILE)/statistikAndMemory.o: $(PROGRAM)/statistikAndMemory.cpp \
                               $(HEADERS)/statistikAndMemory.h $(HEADERS)/produk.h | $(OFILE)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OFILE) $(TARGET)

.PHONY: all run clean