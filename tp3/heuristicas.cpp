#include <iomanip>
#include <vector>
#include <set>
#include <stdlib.h>
#include <math.h>
#include "Coef.h"
#include "matriz.h"
#include "heuristicas.h"

using namespace std;

#define CANT_PRUEBAS_H1 5000
#define TMAX 60              // Tiempo máximo en segundos

//
// Arma matriz MK=inv(M)*K, devuelve matrices Qac y Dant con autovectores y autovalores
//
void calculo_av_prueba(int n,Coef m0, Coef ml, Coef mp, Matriz &K, vector < Piso > &VP, Matriz& Qac, Matriz& Dant){
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

void h1(int n,Coef m0, Coef ml, Coef mp, Matriz& K, vector<int> l, vector<int> p, bool& ok, bool& tmax, vector< Piso >& P) {
  vector<Piso> v(n);
  vector< vector <Piso> > VP;
  
  for (int i=0;i<n;i++){ // La primera prueba es como vino originalmente
    v[i].l=l[i];
    v[i].p=p[i];
  }
  VP.push_back(v);

  int ps=0;
  int pp=0;
  for (int i=1;i<CANT_PRUEBAS_H1;i++) { 
    // Elige dos pisos
    ps=rand()%n;
    pp=rand()%n; 
    while (ps==pp) { pp=rand()%n; } 
    int cp=0;
    int cl=0;
    if (l[ps]!=0) cl=rand()%(l[ps]); // Cuantos livianos saco
    if (p[ps]!=0) cp=rand()%(p[ps]); // Cuantos pesados saco

    l[ps]-=cl;
    l[pp]+=cl;
    p[ps]-=cp;
    p[pp]+=cp;
    for (int j=0;j<n;j++){
      v[j].l=l[j];
      v[j].p=p[j];
    }
    VP.push_back(v);
  }

  vector<Coef> w(n); // Acá quedarán las frecuencias
  clock_t inicio,fin;
  double segundos;
  Matriz Qac;
  Matriz Dant;

  inicio=clock();
  int c;
  for(c=0;c<VP.size();c++){
    if (!(c%10)) cout << "." << flush; // Para ver que está trabajando

    P=VP[c]; // Configuración de pisos
    // Calcula autovectores y autovalores para esta prueba
    calculo_av_prueba(n,m0,ml,mp,K,P,Qac,Dant); // P[c] es la configuración de los pisos
                                                   // en Dant quedan los autovalores
    
    // Calcula frecuencias a partir de autovalores
    for (int i=0;i<n;i++) w[i]=sqrt(-Dant.sub(i,i));

    // Verifica si no están en el rango prohibido (2.7 a 3.3)
    ok=true;
    for (int i=0;i<n;i++) {
      if (w[i]>=2.7 && w[i] <= 3.3) ok=false;
    }

    // Calcula el tiempo transcurrido
    fin=clock();
    segundos=(double)(fin - inicio)/CLOCKS_PER_SEC;

    // Si las frecuencias no están en el rango prohibido terminamos=>sale
    if (ok) {
      cout << endl;
      cout << "Solución encontrada:" << endl;
      for (int i=0;i<n;i++) { cout << "  w[" << i << "]=" << w[i] << endl; }
      break;
    }
    
    if (segundos > 60) { // Máximo tiempo permitido para las pruebas
      cout << endl;
      cout << "Tiempo máximo alcanzado!" << endl;
      tmax=true;
      break;
    }
  }
  if (!ok && !tmax) cout << endl;

  cout << "Cantidad de pruebas: " << c << "." << endl;
  cout << "Tiempo ejecucion: " << setprecision(15) << segundos << " segundos." << endl;

}

void h2(int n,Coef m0, Coef ml, Coef mp, Matriz& K, vector<int> l, vector<int> p, bool& ok, bool& tmax, vector< Piso >& P){
  
  P.resize(n);
  for (int i=0;i<n;i++){ // La primera prueba es como vino originalmente
    P[i].l=l[i];
    P[i].p=p[i];
  }

  vector<Coef> w(n); // Acá quedarán las frecuencias
  clock_t inicio,fin;
  double segundos;
  Matriz Qac;
  Matriz Dant;

  inicio=clock();
  int c=0;
  while (true){
    if (!(c%10)) cout << "." << flush; // Para ver que está trabajando

    //
    // Aca va la heuristica
    //

    // Calcula el tiempo transcurrido
    fin=clock();
    segundos=(double)(fin - inicio)/CLOCKS_PER_SEC;

    // Si las frecuencias no están en el rango prohibido terminamos=>sale
    if (ok) {
      cout << endl;
      cout << "Solución encontrada:" << endl;
      for (int i=0;i<n;i++) { cout << "  w[" << i << "]=" << w[i] << endl; }
      break;
    }
    
    if (segundos > 60) { // Máximo tiempo permitido para las pruebas
      cout << endl;
      cout << "Tiempo máximo alcanzado!" << endl;
      tmax=true;
      break;
    }
    c++;
  }
  if (!ok && !tmax) cout << endl;

  cout << "Cantidad de pruebas: " << c << "." << endl;
  cout << "Tiempo ejecucion: " << setprecision(15) << segundos << " segundos." << endl;
}
