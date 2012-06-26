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
// Arma matriz MK=inv(M)*K, devuelve matrices Qac y Dant con autovectores y autovalores
//
void calculo_av_prueba(int n,Coef m0, Coef ml, Coef mp, Matriz K, vector < Piso > &VP, Matriz& Qac, Matriz& Dant){
  Matriz MK(n,n);
  for(int i=0;i<n;i++){
    float div=m0+VP[i].l*ml+VP[i].p*mp; // div es el coeficiente de M (M es diagonal)
    
    // Dividir cada fila de K por div es equivalente a multiplicarla a izq por inv(M)
    if (i>0) {
        MK.sub(i,i-1)=K.sub(i,i-1)/div;  
    }
    if (i<n-1) {
      MK.sub(i,i)=K.sub(i,i)/div;
      MK.sub(i,i+1)=K.sub(i,i+1)/div;
    } else {
      MK.sub(i,i)=K.sub(i,i)/div;
    }
  }
  // Calculo autovectores y autovalores de inv(M)*K
  MK.autoval_autovect(Qac,Dant);
}

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

  // Calcula matriz K
  Matriz K(n,n);
  for(int i=0;i<n;i++){
 
    // Dividir cada fila de K por div es equivalente a multiplicarla a izq por inv(M)
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

  // En este vector quedará el set de pruebas calculado por la heurística
  vector< vector < Piso > > P;   // P[c][i].l=cantidad de livianos de piso i en la prueba c
                                 // P[c][i].p=cantidad de pesados de piso i en la prueba c

  // Calcula set de pruebas de heurística 1
  h1(n,m0,ml,mp,k,l,p,P);

  int c;
  for(c=0;c<P.size();c++){
    if (!(c%10)) cout << "." << flush; // Para ver que está trabajando

    Matriz Qac;
    Matriz Dant;

    // Calcula autovectores y autovalores para esta prueba
    calculo_av_prueba(n,m0,ml,mp,K,P[c],Qac,Dant); // P[c] es la configuración de los pisos
    
    // Calcula frecuencias a partir de autovalores

    vector<Coef> w(Dant.cantFilas());
    for (int i=0;i<Dant.cantFilas();i++) w[i]=sqrt(-Dant.sub(i,i));

    // Verifica si no están en el rango prohibido (2.7 a 3.3)
    bool ok=true;
    for (int i=0;i<Dant.cantFilas();i++) {
      if (w[i]>=2.7 && w[i] <= 3.3) ok=false;
    }

    // Si las frecuencias no están en el rango prohibido graba el archivo de salida y sale
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
    
    // Si llegó acá todavía no hay solución, pasa a la próxima prueba
  }

  // Imprime el tiempo transcurrido
  fin=clock();
  double segundos=(double)fin/CLOCKS_PER_SEC;

  cout << endl;
  cout << "Cantidad de pruebas: " << c << "." << endl;
  cout << "Tiempo ejecucion: " << segundos << " segundos." << endl;

  return 0;
}
