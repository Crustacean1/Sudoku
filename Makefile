sources := $(wildcard *.cpp) $(wildcard */*.cpp)
headers := ${wildcard *.h} ${wildcard */*.h}
objects := $(sources:%.cpp=%.o)
target := $(shell pwd | xargs basename)

${target}: ${objects}
	g++ -g -std=c++20 ${objects}  -o ${target}

%.o: %.cpp ${headers}
	g++ -g  -Wall -Werror -std=c++20 -c $< -o $(<:%.cpp=%.o)

clean:
	rm -f *.o
	rm -f */*.o
