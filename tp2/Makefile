export LC_ALL=C

CXXFLAGS=
LDFLAGS=

ALL=tp2 ruido_gauss

all: $(ALL)

tp2: tp2.o pgm.o matriz.o Banda.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ruido_gauss: ruido_gauss.o pgm.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

main: main.o matriz.o Banda.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

pruebapgm: pruebapgm.o pgm.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

tp2.o: tp2.cpp pgm.h matriz.h
pgm.o: pgm.cpp pgm.h
matriz.o: matriz.cpp matriz.h
Banda.o: Banda.cpp Banda.h
ruido_gauss.o: ruido_gauss.cpp pgm.h

clean:
	rm -f *.o $(ALL)
