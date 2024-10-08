CXX = g++
CXXFLAGS = -std = c++11 -Wall

target: etapa1

etapa1: lex.yy.c
		$(CXX) lex.yy.c -o etapa1

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $ < -c

lex.yy.cpp: scanner.l
	flex scanner.l

clean:
	rm etapa1 lex.yy.cpp


