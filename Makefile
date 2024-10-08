CXX = g++
CXXFLAGS = -Wall -std=c++11

target: etapa1

etapa1: lex.yy.o main.o Symbols.o
	$(CXX) -o etapa1 lex.yy.o main.o Symbols.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c

lex.yy.cpp: scanner.l
	flex -o lex.yy.cpp scanner.l

clean:
	rm etapa1 lex.yy.cpp *.o



