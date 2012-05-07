#include <cassert>
#include <iostream>
#include <fstream>
#include <stdlib.h>

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

    int rw=(Width*(100-fr))/100;
    int rh=(Height*(100-fr))/100;

    //cout << rw << endl;
    //cout << rh << endl;

    Raster=vector< vector<int> >(Height, vector<int>(Width,0));

    for(int i=0;i<Height;i++){
      for(int j=0;j<Width;j++){
        f>>c;
        Raster[i][j]=c;
        if (Maxval > 255) {
          f>>c;
          Raster[i][j]=Raster[i][j]*256+c;
        }
      }
    }

    f.close();
}

void Pgm::save(const char* archivo){
    ofstream f;
    f.open(archivo);
    assert(f);

    f << "P5" << endl;
    f << "# Grabado por clase Pgm de Elisa y Martin!" << endl;
    f << Width << endl;
    f << Height << endl;
    f << Maxval << endl;

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

