SOURCES := $(wildcard *.cpp) $(wildcard */*.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
TARGET := $(shell pwd | xargs basename)
CXX = g++
CXXFLAGS = -O3 -g -Wall -Werror -std=c++20 -MMD -I ./  /home/kamil2/Libraries/boost_1_72_0/
DEPENDS = ${OBJECTS:.o=.d} main.d

${TARGET}: ${OBJECTS}
	g++ -g -std=c++20 ${OBJECTS}  -o ${TARGET} -lsfml-graphics -lsfml-window -lsfml-system -lpthread -lboost_thread

-include ${DEPENDS}

clean:
	rm -f *.o
	rm -f */*.o
	rm -f *.d
	rm -f */*.d
