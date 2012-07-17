#include <iomanip>
#include <vector>
#include <cassert>
#include <stdlib.h>
#include <math.h>
#include "Coef.h"
#include "matriz.h"
#include "heuristicas.h"

using namespace std;

#define CANT_PRUEBAS 5000    // Cantidad de pruebas por heurística
#define TMAX 900             // Tiempo máximo en segundos

//
// Arma matriz MK=inv(M)*K, devuelve matrices Qac y Dant con autovectores y autovalores
//
void calculo_av_prueba(int n,Coef m0, Coef ml, Coef mp, Matriz &K, vector<int>& l, vector<int>& p, Matriz& Qac, Matriz& Dant){
  Matriz MK(n,n);
  for(int i=0;i<n;i++){
    float div=m0+l[i]*ml+p[i]*mp; // div es el coeficiente de M (M es diagonal)

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


void prueba_h1(vector<int>& parametros,int n,vector<int>& l, vector<int>& p){
  // Elige dos pisos
  int ps=rand()%n;
  int pp=rand()%n; 
  while (ps==pp) { pp=rand()%n; } 
  int cp=0;
  int cl=0;

  int maxl=RAND_MAX;
  int maxp=RAND_MAX;

  assert(parametros.size()==2);
  
  if (parametros[0]>=0) maxl=parametros[0];
  if (parametros[1]>=0) maxp=parametros[1];

  if (l[ps]!=0 && maxl!=0) cl=rand()%(min(maxl,l[ps])); // Cuantos livianos saco
  if (p[ps]!=0 && maxp!=0) cp=rand()%(min(maxp,p[ps])); // Cuantos pesados saco

  l[ps]-=cl;
  l[pp]+=cl;
  p[ps]-=cp;
  p[pp]+=cp;
}

void prueba_h2(vector<int>& parametros,int n,vector<int>& l, vector<int>& p){
  int m,v;

  assert(parametros.size()==2);

  int c=parametros[0];
  int d=parametros[1];

  for(int i=1;c!=0 && i<n;i++){
    v=l[i];
    if (v!=0) {
      m=v/c;
      if (m==0) m=1;
      l[i]-=m;
      l[i-1]+=m;
    }
  }
  for(int i=n-2;d!=0 && i>=0;i--){
    v=p[i];
    if (v!=0) {
      m=v/d;
      if (m==0) m=1;
      p[i]-=m;
      p[i+1]+=m;
    }
  }
}


void ejecuta_heuristica(int nh,vector<int>& parametros, int n,Coef m0, Coef ml, Coef mp, Matriz& K, vector<int>& l, vector<int>& p, bool& ok, bool& tmax){
  vector<Coef> w(n); // Acá quedarán las frecuencias
  clock_t inicio,fin;
  double segundos;
  Matriz Qac;
  Matriz Dant;

  inicio=clock();
  int cantl=0;
  int cantp=0;
  int v,m;
  int c=1;

  if (nh==1){
    assert(parametros.size()==2);
  }
  if (nh==2){
    assert(parametros.size()==2);
    for (int i=0;i<n;i++) { cantl+=l[i]; l[i]=0; cantp+=p[i]; p[i]=0; }
    p[0]=cantp;
    l[n-1]=cantl;
  }

  while (1){
    if (!(c%10)) cout << "." << flush; // Para ver que está trabajando

    // Calcula autovectores y autovalores para esta prueba
    calculo_av_prueba(n,m0,ml,mp,K,l,p,Qac,Dant); // en Dant quedan los autovalores
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
    
    if (segundos > TMAX) { // Máximo tiempo permitido para las pruebas
      cout << endl;
      cout << "Tiempo máximo alcanzado!" << endl;
      tmax=true;
      break;
    }
    if (nh==1){
      prueba_h1(parametros,n,l,p);
    } else {
      if ((l[0]==cantl || parametros[0]==0) && (p[n-1]==cantp || parametros[1]==0)) break;
      prueba_h2(parametros,n,l,p);
    }
    c++;
  }
  if (!ok && !tmax) cout << endl;

  cout << "Cantidad de pruebas: " << c << "." << endl;
  cout << "Tiempo ejecucion: " << setprecision(15) << segundos << " segundos." << endl;
}
