SOURCES := $(wildcard *.cpp) $(wildcard */*.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
TARGET := $(shell pwd | xargs basename)
CXX = g++
CXXFLAGS = -g -Wall -Werror -std=c++20 -MMD -I ./
DEPENDS = ${OBJECTS:.o=.d} main.d

${TARGET}: ${OBJECTS}
	g++ -g -std=c++20 ${OBJECTS}  -o ${TARGET} -lsfml-graphics -lsfml-window -lsfml-system

-include ${DEPENDS}

clean:
	rm -f *.o
	rm -f */*.o
	rm -f *.d
	rm -f */*.d
