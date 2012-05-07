#ifndef __PGM_H__
#define __PGM_H__

//
// Manipulación de imagenes en formato PGM (P5)
//

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Pgm {
public:
    Pgm();
    Pgm(const char* archivo);
    Pgm(const char* archivo, int fr);
    void load(const char* archivo);
    void load(const char* archivo, int fr);
    void save(const char* archivo);
    void operator=(const Pgm& I);

    int width();
    int width_orig();
    int height();
    int height_orig();
    int maxval();
    int sub(int i,int j) const;
    int& sub(int i,int j);

private:
    int Width;
    int Height;
    int WidthOrig;
    int HeightOrig;
    int Maxval;
    vector< vector<int> > Raster;
    string lee_token_s(istream& f);
    int lee_token_n(istream& f);
};

#endif // __PGM_H__
