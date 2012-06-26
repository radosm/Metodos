#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cassert>
#include <vector>
#include <math.h>
#include "matriz.h"
#include "Coef.h"
#include "heuristicas.h"

using namespace std;

//
// MAIN
//
int main(int argc, char* argv[])
{
  if (argc<3) {
    cerr << "Error, ingrese parametros: archivo_entrada, archivo_salida\n";
    exit(1);
  }

  char *archivo_entrada=argv[1];
  char *archivo_salida=argv[2];

  clock_t inicio, fin;
 
  inicio=clock();

  //
  // Lee datos de entrada
  //
  ifstream f;
  ofstream f_salida;
  f.open(archivo_entrada);
  assert(f);

  int n;
  Coef m0,ml,mp;
  f >> n >> m0 >> ml >> mp;
  assert(n>0 && m0>0 && ml>0 && mp>0);

  vector<Coef> k(n);
  for(int i=0;i<n;i++){
    f>>k[i];
  }
  vector<int> l(n);
  for(int i=0;i<n;i++){
    f>>l[i];
    assert(l[i]>=0);
  }
  vector<int> p(n);
  for(int i=0;i<n;i++){
    f>>p[i];
    assert(p[i]>=0);
  }
  f.close();

  //
  // Arma matriz MK=inv(M)*K
  //

  vector< vector < Piso > > P;

  // Calcula set de pruebas de heurística 1
  h1(n,m0,ml,mp,k,l,p,P);

  Matriz MK(n,n);
  
  for(int c=0;c<P.size();c++){
    if (!(c%10)) cout << "." << flush;
    for(int i=0;i<n;i++){
      float div=m0+P[c][i].l*ml+P[c][i].p*mp; // div es el coeficiente de M (M es diagonal)
  
      // Dividir cada fila de K por div es equivalente a multiplicarla a izq por inv(M)
      if (i>0) {
          MK.sub(i,i-1)=k[i]/div;  
      }
      if (i<n-1) {
      MK.sub(i,i)=(-k[i]-k[i+1])/div;
        MK.sub(i,i+1)=k[i+1]/div;
      } else {
        MK.sub(i,i)=-k[i]/div;
      }
    }

    Matriz Qac;
    Matriz Dant;
    MK.autoval_autovect(Qac,Dant);
    
    vector<Coef> w(Dant.cantFilas());
    for (int i=0;i<Dant.cantFilas();i++) w[i]=sqrt(-Dant.sub(i,i));
    bool ok=true;
    for (int i=0;i<Dant.cantFilas();i++) {
      if (w[i]>=2.7 && w[i] <= 3.3) ok=false;
    }
    if (ok) {
      f_salida.open(archivo_salida);
      assert(f_salida);
      cout << endl;
      for (int i=0;i<Dant.cantFilas();i++) {
        cout << "l[" << i << "]=" << Dant.sub(i,i) << " / w[" << i << "]=" << w[i] << endl;
      }

      f_salida << n << " " << m0 << " " << ml << " " << mp <<endl;
      for(int i=0;i<n;i++){
        f_salida << setprecision(15) << k[i] << " ";
      }
      f_salida << endl;
      for(int i=0;i<n;i++){
        f_salida << P[c][i].l << " ";
      }
      f_salida << endl;
      for(int i=0;i<n;i++){
        f_salida << P[c][i].p << " ";
      }
      f_salida << endl;
      f_salida.close();
      break;
    }
  }
  cout << endl;


/*
  cout << endl;

  cout << MK << endl;

  cout << Qac << endl;

  cout << Dant << endl;
*/

  fin=clock();
  double segundos=(double)fin/CLOCKS_PER_SEC;

  cout << endl;
  cout << "Tiempo ejecucion: " << segundos << " segundos." << endl;

  return 0;
}
