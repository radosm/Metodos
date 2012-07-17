#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  if (argc<4) {
    cerr << "Error, ingrese parametros: archivo_entrada, archivo_salida, nro de heurística (1 o 2)\n";
    exit(1);
  }

  char *archivo_entrada=argv[1];
  char *archivo_salida=argv[2];
  int nh=atoi(argv[3]);

  vector<int> parametros;
  for(int i=4;i<argc;i++){
    parametros.push_back(atoi(argv[i]));
  }

  assert(nh==1 || nh==2);

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
  for(int i=0;i<n;i++){ f>>k[i]; }
  vector<int> l(n);
  for(int i=0;i<n;i++){ f>>l[i]; assert(l[i]>=0); }
  vector<int> p(n);
  for(int i=0;i<n;i++){ f>>p[i]; assert(p[i]>=0); }
  f.close();

  vector<int> l_orig;
  vector<int> p_orig;
  l_orig=l;
  p_orig=p;

  // Calcula matriz K
  Matriz K(n,n);
  for(int i=0;i<n;i++){
 
    if (i>0) {
      K.sub(i,i-1)=k[i];  
    }
    if (i<n-1) {
      K.sub(i,i)=(-k[i]-k[i+1]);
      K.sub(i,i+1)=k[i+1];
    } else {
      K.sub(i,i)=-k[i];
    }
  }

  bool ok;         // Aca la heurística devuelve si encontro solución o no
  bool tmax;       // Aca la heurística devuelve si terminó por tiempo máximo
  int c;           // Aca la heurística devuelve la cantidad de pruebas ejecutadas
  double segundos; // Aca la heurística devuelve la cantidad de segundos transcurridos

  cout << "Ejecutando heurística " << nh << endl;
  ejecuta_heuristica(nh,parametros,n,m0,ml,mp,K,l,p,ok,tmax,c,segundos);
  cout << "Fin heurística " << nh << endl;

  int movs=0;
  // Si encontró solución graba salida
  if (ok) {
    // Cuenta cantidad de movimientos

    for(int i=0;i<n;i++){
      if (p_orig[i]<p[i]) movs+=p[i]-p_orig[i];
      if (l_orig[i]<l[i]) movs+=l[i]-l_orig[i];
    }

    f_salida.open(archivo_salida);
    assert(f_salida);
    cout << endl;
    f_salida << n << " " << m0 << " " << ml << " " << mp <<endl;
    for(int i=0;i<n;i++){ f_salida << setprecision(15) << k[i] << " "; }
    f_salida << endl;
    for(int i=0;i<n;i++){ f_salida << l[i] << " "; }
    f_salida << endl;
    for(int i=0;i<n;i++){ f_salida << p[i] << " "; }
    f_salida << endl;
    f_salida.close();
    cout << "resultado en archivo=" << archivo_salida << " cantidad de movimientos=" << movs << endl;
  } 


  cout << "LOG ";
  for(int i=1;i<argc;i++){
    cout << argv[i] << " ";
  }
  cout << ok << " " << movs << " " << tmax << " " << c << " " << segundos << endl;

  return 0;
}
