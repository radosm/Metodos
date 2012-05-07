export LC_ALL=C

CXXFLAGS=
LDFLAGS=

ALL=pruebapgm main

all: $(ALL)

main: main.o matriz.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

pruebapgm: pruebapgm.o pgm.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

pgm.o: pgm.cpp pgm.h
matriz.o: matriz.cpp matriz.h

clean:
	rm -f *.o $(ALL)
