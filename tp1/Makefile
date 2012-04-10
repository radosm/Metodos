export LC_ALL=C

CXXFLAGS=
LDFLAGS=

ALL=newton biseccion

all: $(ALL)

newton: newton.o TFloat.o fisica.o metodos.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

biseccion: biseccion.o TFloat.o fisica.o metodos.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


biseccion.o: biseccion.cpp TFloat.h fisica.h
newton.o: newton.cpp TFloat.h
TFloat.o: TFloat.cpp TFloat.h
fisica.o: fisica.cpp fisica.h TFloat.h

clean:
	rm -f *.o $(ALL)
