export LC_ALL=C

CXXFLAGS=-O3
LDFLAGS=

ALL=tp2 ruido_gauss ruido_sp ruido_speckle

all: $(ALL)

tp2: tp2.o pgm.o matriz.o Banda.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ruido_gauss: ruido_gauss.o pgm.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ruido_sp: ruido_sp.o pgm.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ruido_speckle: ruido_speckle.o pgm.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

tp2.o: tp2.cpp pgm.h matriz.h
pgm.o: pgm.cpp pgm.h
matriz.o: matriz.cpp matriz.h
Banda.o: Banda.cpp Banda.h
ruido_gauss.o: ruido_gauss.cpp pgm.h
ruido_sp.o: ruido_sp.cpp pgm.h
ruido_speckle.o: ruido_speckle.cpp pgm.h

clean:
	rm -f *.o $(ALL)
