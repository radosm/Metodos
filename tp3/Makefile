export LC_ALL=C

CXXFLAGS=-O3
LDFLAGS=

ALL=tp3

all: $(ALL)

tp3: matriz.o tp3.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

tp3.o: tp3.cpp
matriz.o: matriz.cpp matriz.h
Matriz_Givens.o: Matriz_Givens.cpp Coef.h matriz.h
Trig_Sup.o: Trig_Sup.cpp  Trig_Sup.h

clean:
	rm -f *.o $(ALL)
