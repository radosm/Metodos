export LC_ALL=C
##CXXFLAGS= -Wall -pedantic -g -ggdb
##LDFLAGS= -lpthread

CXXFLAGS=
LDFLAGS=

all: newton biseccion

newton: newton.o TFloat.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

biseccion: biseccion.o TFloat.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


biseccion.o: biseccion.cpp TFloat.cpp TFloat.h
newton.o: newton.cpp TFloat.cpp TFloat.h
TFloat.o: TFloat.cpp TFloat.h

clean:
	rm -f $(OBJS) $(MAIN)
