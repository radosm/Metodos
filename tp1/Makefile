export LC_ALL=C

CXXFLAGS=-O3
LDFLAGS=

ALL=newton biseccion extra

all: $(ALL)

extra: extra.o TFloat.o fisica.o metodos.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

newton: newton.o TFloat.o fisica.o metodos.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

biseccion: biseccion.o TFloat.o fisica.o metodos.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


biseccion.o: biseccion.cpp TFloat.h fisica.h
newton.o: newton.cpp TFloat.h
TFloat.o: TFloat.cpp TFloat.h
fisica.o: fisica.cpp fisica.h TFloat.h
extra.o: extra.cpp TFloat.h

clean:
	rm -f *.o $(ALL)
