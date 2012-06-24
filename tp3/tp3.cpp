#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cassert>
#include <math.h>
#include "matriz.h"
#include "Coef.h"

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

/*
  // Muestra datos de entrada
  cout << "n: "<<n<<" m0: "<<m0<<" ml: "<<ml<<" mp: "<<mp<<endl;
  for(int i=0;i<n;i++){
    cout << k[i] << " ";
  }
  cout << endl;
  for(int i=0;i<n;i++){
    cout << l[i] << " ";
  }
  cout << endl;
  for(int i=0;i<n;i++){
    cout << p[i] << " ";
  }
  cout << endl;
*/

  //
  // Arma matriz MK=inv(M)*K
  //
  Matriz MK(n,n);
  
  for(int i=0;i<n;i++){
    float div=(m0+l[i]*ml+p[i]*mp); // div es el coeficiente de M (M es diagonal)

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

/*
  cout << endl;

  cout << MK << endl;

  cout << Qac << endl;

*/
  cout << Dant << endl;

  vector<Coef> w(Dant.cantFilas());
  for (int i=0;i<Dant.cantFilas();i++) w[i]=sqrt(-Dant.sub(i,i));
  for (int i=0;i<Dant.cantFilas();i++) cout << "w[" << i << "]=" << w[i] << endl;

  fin=clock();
  double segundos=(double)fin/CLOCKS_PER_SEC;

  cout << "Tiempo ejecucion: " << segundos << " segundos." << endl;

  return 0;
}
