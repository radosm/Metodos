#include <cassert>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

#include "pgm.h"

using namespace std;

string Pgm::lee_token_s(istream& f) {
  string token;
  unsigned char c;

  while ( f >> c, !f.eof()){

    if (c==' ' || c=='\t' || c=='\n' || c=='\r') {  // Blancos
      if (token!="") {
        return token;
      }
      continue;
    }

    if (c=='#') { // Comentario

      while ( f>>c, !f.eof() ){
        if (c!= '\n' && c!= '\r') continue;
        break;
      }
      if (f.eof()) break;
      continue;
    }
    // Ni blanco ni comentario
    token=token+=c;
  }
  assert(token!="");
  return token;
}

int Pgm::lee_token_n(istream& f) {
   string token;
   token=lee_token_s(f);
   for (int i=0;i<token.size();i++) {
     assert(isdigit(token[i]));
   }
   return atoi(token.c_str());
}

Pgm::Pgm(){
    Width=0;
    Height=0;
    WidthOrig=0;
    HeightOrig=0;
    Maxval=0;
}

Pgm::Pgm(const char* archivo){
    Pgm(archivo,0);
}

Pgm::Pgm(const char* archivo, int fr){
    load(archivo,fr);
}

void Pgm::load(const char* archivo){
    load(archivo,0);
}

void Pgm::load(const char* archivo, int fr){
    ifstream f;
    string magic;
    unsigned char c;

    f.open(archivo);
    f.unsetf(ios_base::skipws);
    assert(f);
    
    magic=lee_token_s(f);
    assert(magic=="P5");
    Width=lee_token_n(f);
    WidthOrig=Width;
    Height=lee_token_n(f);
    HeightOrig=Height;
    Maxval=lee_token_n(f);
    assert(Maxval>=0 && Maxval<=65535);

    vector< vector<int> > RasterTemp=vector< vector<int> >(Height, vector<int>(Width,0));

    for(int i=0;i<Height;i++){
      for(int j=0;j<Width;j++){
        f>>c;
        RasterTemp[i][j]=c;
        if (Maxval > 255) {
          f>>c;
          RasterTemp[i][j]=RasterTemp[i][j]*256+c;
        }
      }
    }

    f.close();

    Width=(int)floor(WidthOrig*((100-fr)/100.0)+0.5);
    Height=(int)floor(HeightOrig*((100-fr)/100.0)+0.5);

    Raster=vector< vector<int> >(Height, vector<int>(Width,0));

    double x_ratio = HeightOrig/(double)Height ;
    double y_ratio = WidthOrig/(double)Width ;
    double px, py ; 

    for (int i=0;i<Height;i++) {
        for (int j=0;j<Width;j++) {
            px = floor(j*x_ratio) ;
            py = floor(i*y_ratio) ;
            Raster[i][j] = RasterTemp[(int)py][(int)px];
        }
    }

}

void Pgm::save(const char* archivo){

    ofstream f;
    f.open(archivo);
    assert(f);

    f << "P5" << endl;
    f << "# Grabado por clase Pgm de Elisa y Martin!" << endl;
    f << Width << endl;
    f << Height << endl;
    f << Maxval << '\n';

    for(int i=0;i<Height;i++){
      for(int j=0;j<Width;j++){
        if (Maxval > 255) {
          f<<(unsigned char)Raster[i][j]/256;
          f<<(unsigned char)(Raster[i][j]-(Raster[i][j]/256)*256);
        } else {
          f<<(unsigned char)Raster[i][j];
        }
      }
    }

    f.close();
}

void Pgm::saveOrig(const char* archivo){

    vector< vector<int> > RasterTemp=vector< vector<int> >(HeightOrig, vector<int>(WidthOrig,0));

    double x_ratio = Height/(double)HeightOrig ;
    double y_ratio = Width/(double)WidthOrig ;
    double px, py ; 

    for (int i=0;i<HeightOrig;i++) {
        for (int j=0;j<WidthOrig;j++) {
            px = floor(j*x_ratio) ;
            py = floor(i*y_ratio) ;
            RasterTemp[i][j] = Raster[(int)py][(int)px];
        }
    }
    ofstream f;
    f.open(archivo);
    assert(f);

    f << "P5" << endl;
    f << "# Grabado por clase Pgm de Elisa y Martin!" << endl;
    f << WidthOrig << endl;
    f << HeightOrig << endl;
    f << Maxval << '\n'; // acá no va endl por el p... windows

    for(int i=0;i<HeightOrig;i++){
      for(int j=0;j<WidthOrig;j++){
        if (Maxval > 255) {
          f<<(unsigned char)RasterTemp[i][j]/256;
          f<<(unsigned char)(RasterTemp[i][j]-(RasterTemp[i][j]/256)*256);
        } else {
          f<<(unsigned char)RasterTemp[i][j];
        }
      }
    }

    f.close();
}

void Pgm::resizeOrig(Pgm& I) {
    int ho, wo;
    ho=I.HeightOrig;
    wo=I.WidthOrig;
    vector< vector<int> > RasterTemp=vector< vector<int> >(ho, vector<int>(wo,0));

    double x_ratio = I.Height/(double)I.HeightOrig ;
    double y_ratio = I.Width/(double)I.WidthOrig ;
    double px, py ; 

    for (int i=0;i<I.HeightOrig;i++) {
        for (int j=0;j<I.WidthOrig;j++) {
            px = floor(j*x_ratio) ;
            py = floor(i*y_ratio) ;
            RasterTemp[i][j] = I.sub((int)py,(int)px);
        }
    }

    Width=I.WidthOrig;
    Height=I.HeightOrig;
    WidthOrig=I.WidthOrig;
    HeightOrig=I.HeightOrig;
    Maxval=I.Maxval;
    Raster=RasterTemp;

}

int Pgm::width(){ return Width; }
int Pgm::width_orig(){ return WidthOrig; }
int Pgm::height(){ return Height; }
int Pgm::height_orig(){ return HeightOrig; }
int Pgm::maxval(){ return Maxval; }
int Pgm::sub(int i,int j) const{
    assert (i>=0 && i<Height);
    assert (j>=0 && j<Width);
    return Raster[i][j];
}

int& Pgm::sub(int i,int j){
    assert (i>=0 && i<Height);
    assert (j>=0 && j<Width);
    return Raster[i][j];
}

void Pgm::operator=(const Pgm& I){
    Width=I.Width;
    Height=I.Height;
    WidthOrig=I.WidthOrig;
    HeightOrig=I.HeightOrig;
    Maxval=I.Maxval;
    Raster=I.Raster;
}

