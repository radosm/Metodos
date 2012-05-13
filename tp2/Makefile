export LC_ALL=C

CXXFLAGS=
LDFLAGS=

ALL=tp2 pruebapgm main

all: $(ALL)

tp2: tp2.o pgm.o matriz.o Banda.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

main: main.o matriz.o Banda.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

pruebapgm: pruebapgm.o pgm.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

tp2.o: tp2.cpp pgm.h matriz.h
pgm.o: pgm.cpp pgm.h
matriz.o: matriz.cpp matriz.h
Banda.o: Banda.cpp Banda.h

clean:
	rm -f *.o $(ALL)
