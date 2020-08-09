CC=/usr/local/bin/gcc
CXX=/usr/local/bin/g++
OBJS=main.o Lexer.o GraphParser.o GraphLexer.o GraphClass.o CalcParser.o CalcLexer.o Exception.o
SOBJS=graph.o GraphClass.o Exception.o GraphLexer.o GraphParser.o
EXEC=gcalc
COMP_FLAGS=-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG
SWIG_FLAGS=-std=c++11 -Wall -Werror -fPIC -g -pedantic-errors -DNDEBUG


$(EXEC): $(OBJS)
	$(CXX) -std=c++11 $(COMP_FLAGS) $(OBJS) -o $@

libgraph.a: $(SOBJS)
	ar -rs $@ $^
 
CalcLexer.o: CalcLexer.cpp CalcLexer.h Lexer.h Exception.h
	$(CXX) -c $(COMP_FLAGS) $*.cpp

CalcParser.o: CalcParser.cpp CalcParser.h CalcLexer.h Lexer.h Exception.h GraphClass.h GraphParser.h GraphLexer.h
	$(CXX) -c $(COMP_FLAGS) $*.cpp

Exception.o: Exception.cpp Exception.h
	$(CXX) -c $(COMP_FLAGS) -fPIC $*.cpp

GraphLexer.o: GraphLexer.cpp GraphLexer.h Lexer.h Exception.h GraphClass.h
	$(CXX) -c $(COMP_FLAGS) -fPIC $*.cpp

GraphParser.o: GraphParser.cpp GraphParser.h GraphLexer.h Lexer.h Exception.h GraphClass.h
	$(CXX) -c $(COMP_FLAGS) -fPIC $*.cpp

Lexer.o: Lexer.cpp Lexer.h Exception.h
	$(CXX) -c $(COMP_FLAGS) $*.cpp

GraphClass.o: GraphClass.cpp GraphClass.h Exception.h GraphParser.h GraphLexer.h Lexer.h
	$(CXX) -c $(COMP_FLAGS) -fPIC $*.cpp

graph.o: graph.cpp graph.h GraphClass.h Exception.h GraphParser.h GraphLexer.h Lexer.h
	$(CXX) -c $(COMP_FLAGS) -fPIC $*.cpp

main.o: main.cpp CalcParser.h CalcLexer.h Lexer.h Exception.h GraphClass.h GraphParser.h GraphLexer.h
	$(CXX) -c $(COMP_FLAGS) $*.cpp

clean :
	rm -f $(OBJS) $(EXEC) libgraph.a graph.o

tar :
	zip -r gcalc.zip ./