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

    vector< vector<int> > RasterTemp2=vector< vector<int> >(HeightOrig, vector<int>(Width,0));

    int co=WidthOrig/Width;
    int rei=WidthOrig%Width/2;
    int ref=WidthOrig%Width/2+(WidthOrig%Width)%2;
    int s;
    int jr=0;
    int cnt=0;
    int color=0;

    for(int i=0;i<HeightOrig;i++){
      for(int j=0;j<WidthOrig;j++){
        if (jr>=rei && jr<=Width-ref-1) s=co; else s=co+1;
        color+=RasterTemp[i][j];
        cnt++;
        if (cnt==s) {
          RasterTemp2[i][jr]=(int)floor((color+0.0)/cnt+0.5);
          color=0;
          cnt=0;
          jr++;
        }
      }
      jr=0;
    }

    Raster=vector< vector<int> >(Height, vector<int>(Width,0));

    co=HeightOrig/Height;
    rei=HeightOrig%Height/2;
    ref=HeightOrig%Height/2+(HeightOrig%Height)%2;
    int ir=0;
    cnt=0;
    color=0;

    for(int j=0;j<Width;j++){
      for(int i=0;i<HeightOrig;i++){
        if (ir>=rei && ir<=Height-ref-1) s=co; else s=co+1;
        color+=RasterTemp2[i][j];
        cnt++;
        if (cnt==s) {
          Raster[ir][j]=(int)floor((color+0.0)/cnt+0.5);
          color=0;
          cnt=0;
          ir++;
        }
      }
      ir=0;
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

