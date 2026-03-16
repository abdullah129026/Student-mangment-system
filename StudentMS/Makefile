# Student Management System Makefile

CXX = g++
CXXFLAGS = -I./include
SRCDIR = src
OBJDIR = obj
TARGET = sms.exe

SOURCES = $(wildcard $(SRCDIR)/*.cpp) main.cpp
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(filter-out $(SRCDIR)/main.cpp,$(SOURCES))) $(OBJDIR)/main.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/main.o: main.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c main.cpp -o $(OBJDIR)/main.o

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	del /Q $(OBJDIR)\*.o $(TARGET) 2>nul || true

run: $(TARGET)
	.\$(TARGET)

.PHONY: all clean run
