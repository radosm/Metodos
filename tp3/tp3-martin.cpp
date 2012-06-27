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

  assert(nh==1 || nh==2);

  clock_t fin;
  double segundos;
 
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

  bool ok;   // Aca la heurística devuelve si encontro solució o no
  bool tmax; // Aca la heurística devuelve si terminó por tiempo máximo

                      // En este vector quedará la configuración del piso calculado por la heurística
  vector< Piso > P;   // P[i].l=cantidad de livianos de piso i
                      // P[i].p=cantidad de pesados de piso i

  if (nh==1) {
    // Ejecuta heurística 1
    cout << "Ejecutando heurística 1" << endl;
    h1(n,m0,ml,mp,K,l,p,ok,tmax,P);
    cout << "Fin heurística 1" << endl;
  } else {
    // Ejecuta heurística 2
    cout << "Ejecutando heurística 2" << endl;
    h2(n,m0,ml,mp,K,l,p,ok,tmax,P);
    cout << "Fin heurística 2" << endl;
  }

  // Si encontró solución graba salida
  if (ok) {
    f_salida.open(archivo_salida);
    assert(f_salida);
    cout << endl;
    f_salida << n << " " << m0 << " " << ml << " " << mp <<endl;
    for(int i=0;i<n;i++){ f_salida << setprecision(15) << k[i] << " "; }
    f_salida << endl;
    for(int i=0;i<n;i++){ f_salida << P[i].l << " "; }
    f_salida << endl;
    for(int i=0;i<n;i++){ f_salida << P[i].p << " "; }
    f_salida << endl;
    f_salida.close();
  } 

  return 0;
}
