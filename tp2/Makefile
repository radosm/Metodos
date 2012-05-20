xport LC_ALL=C

CXXFLAGS=-O3
LDFLAGS=

ALL=filtrar_img ruido_gauss ruido_sp ruido_speckle psnr

all: $(ALL)

filtrar_img: filtrar_img.o pgm.o matriz.o Banda.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ruido_gauss: ruido_gauss.o pgm.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ruido_sp: ruido_sp.o pgm.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

ruido_speckle: ruido_speckle.o pgm.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

psnr: psnr.o pgm.o matriz.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

filtrar_img.o: filtrar_img.cpp pgm.h matriz.h Banda.h
pgm.o: pgm.cpp pgm.h
matriz.o: matriz.cpp matriz.h
Banda.o: Banda.cpp Banda.h Banda.h
ruido_gauss.o: ruido_gauss.cpp pgm.h
ruido_sp.o: ruido_sp.cpp pgm.h
ruido_speckle.o: ruido_speckle.cpp pgm.h
psnr.o: psnr.cpp pgm.h matriz.h

clean:
	rm -f *.o $(ALL)
