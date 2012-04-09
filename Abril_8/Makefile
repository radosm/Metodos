export LC_ALL=C
##CXXFLAGS= -Wall -pedantic -g -ggdb
##LDFLAGS= -lpthread

CXXFLAGS=
LDFLAGS=

all: newton biseccion

newton: newton.o TFloat.o fisica.o metodos.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

biseccion: biseccion.o TFloat.o fisica.o metodos.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


biseccion.o: biseccion.cpp TFloat.h fisica.h
newton.o: newton.cpp TFloat.h
TFloat.o: TFloat.cpp TFloat.h
fisica.o: fisica.cpp fisica.h TFloat.h

clean:
	rm -f *.o newton biseccion
