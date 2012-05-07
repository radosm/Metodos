#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

main(){
  ifstream f;
  f.open("64x64/blond.pgm",ios::binary);
  f.unsetf(ios_base::skipws);

  int cant_tok=0, width, height, maxval;
  string token;
  char c, I[64][64];

  while ( f >> c, !f.eof()){

    if (c==' ' || c=='\t' || c=='\n' || c=='\r') {  // Blancos

      if (token!="") {
        cant_tok++;
        if (cant_tok==2) width=atoi(token.c_str());
        if (cant_tok==3) height=atoi(token.c_str());
        if (cant_tok==4) maxval=atoi(token.c_str());
        if (cant_tok==4) break;
        token="";
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

  int i=0, j=0;
  for(i=0;i<height;i++){
    for(j=0;j<width;j++){
      f>>I[i][j];
    }
  }

  f.close();

  cout << "P5" << endl;
  cout << "# Manipulado" << endl;
  cout << width << endl;
  cout << height << endl;
  cout << maxval << endl;

  for(i=0;i<height;i++){
    for(j=0;j<width;j++){
      if (j%2) {
        cout << I[i][j];
      } else {
        cout << (char)0;
      }
    }
  }
  
}

