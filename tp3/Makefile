export LC_ALL=C

CXXFLAGS=-O3
LDFLAGS=

ALL=main tp3

all: $(ALL)

tp3: matriz.o tp3.o Matriz_Givens.o heuristicas.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

main: main.o matriz.o Matriz_Givens.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

tp3.o: tp3.cpp heuristicas.h Coef.h
main.o: main.cpp matriz.h Matriz_Givens.h Coef.h
matriz.o: matriz.cpp matriz.h Coef.h Matriz_Givens.h
Matriz_Givens.o: Matriz_Givens.cpp Coef.h matriz.h Coef.h Matriz_Givens.h
heuristicas.o: heuristicas.cpp heuristicas.h Coef.h

clean:
	rm -f *.o $(ALL)
