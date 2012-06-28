#include <iomanip>
#include <vector>
#include <set>
#include <stdlib.h>
#include <math.h>
#include "Coef.h"
#include "matriz.h"
#include "heuristicas.h"

using namespace std;

#define CANT_PRUEBAS 5000    // Cantidad de pruebas por heurística
#define TMAX 180             // Tiempo máximo en segundos

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

void h2_estabilizar(int i, bool& sacar, vector<int>& l,vector<int>& p,vector<Coef>& w){
  int n=w.size();
  // cand_s = candidato para sacar autos, cand_p = candidato para poner autos
  int cand_s,cand_p;
  Coef min_mayor_3,max_menor_3,min_con_autos,max_con_autos;

  cand_s=cand_p=-1;
  min_mayor_3=min_con_autos=999999999;
  max_menor_3=max_con_autos=-1;

  for (int j=i+1;j<n;j++){
    if (w[j]<3 && (p[j]+l[j])!=0 && w[j]>max_menor_3) {max_menor_3=w[j]; cand_s=j;}
    if (w[j]>3 && (p[j]+l[j])!=0 && w[j]<min_mayor_3) {min_mayor_3=w[j]; cand_p=j;}
    if (w[j]>max_con_autos && (p[j]+l[j])!=0 && cand_s==-1) {max_con_autos=w[j];cand_s=j;}
    if (w[j]<min_con_autos && (p[j]+l[j])!=0 && cand_p==-1) {min_con_autos=w[j];cand_p=j;}
  }

  if (cand_s ==-1 || cand_p == -1) {
    for (int j=0;j<i;j++){
      if (w[j]>max_con_autos && p[j]!=0 && cand_s==-1) {max_con_autos=w[j];cand_s=j;}
      if (w[j]>max_con_autos && p[j]==0 && l[j]!=0 && cand_s==-1) {max_con_autos=w[j];cand_s=j;}
      if (w[j]<min_con_autos && cand_p==-1) {min_con_autos=w[j];cand_p=j;}
    }
  }

  for (int j=0;j<n;j++){
    cout 
      <<        "i="<< i
      << "   sacar="<< sacar
      <<     "   w["<<j<<"]="<< w[j]
      <<     "   l["<<j<<"]="<< l[j]
      <<     "   p["<<j<<"]="<< p[j]
      << endl;
  }

  cout 
    <<    "min_mayor_3=" << min_mayor_3
    << "   max_menor_3=" << max_menor_3
    << "   min_con_autos=" << min_con_autos
    << "   max_con_autos=" << max_con_autos
    << "   cand_s=" << cand_s
    << "   cand_p=" << cand_p
    << endl;

  if (cand_s ==-1 && !sacar)  {sacar=true; return;}; // no hay opciones
  if (cand_p ==-1 && sacar) {sacar=false; return;};  // no hay opciones

  if (sacar)  { if (p[i]!=0)      { p[cand_p]+=p[i];p[i]=0;} else { l[cand_p]+=l[i];l[i]=0;} }
  if (!sacar) { if (p[cand_s]!=0) { p[i]+=p[cand_s];p[cand_s]=0;} else { l[i]+=l[cand_s];l[cand_s]=0;} }
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
  for (int i=1;i<CANT_PRUEBAS;i++) { 
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
    calculo_av_prueba(n,m0,ml,mp,K,P,Qac,Dant); // P es la configuración de los pisos
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
    
    if (segundos > TMAX) { // Máximo tiempo permitido para las pruebas
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

  // Calcula autovectores y autovalores para la primera prueba
  calculo_av_prueba(n,m0,ml,mp,K,P,Qac,Dant); // P es la configuración de los pisos
                                              // en Dant quedan los autovalores
  // Calcula frecuencias a partir de autovalores
  for (int i=0;i<n;i++) w[i]=sqrt(-Dant.sub(i,i));

  int iant=-1;
  bool sacar;
  for(int i=0;i<n;i++){
    while (w[i]>=2.7 && w[i]<=3.3 && segundos <= TMAX) {
      if (i!=iant){
        if (w[i]<3) {sacar=true;} else {sacar=false;};  // Decide si achicar o agrandar el av
        iant=i;
      }
      h2_estabilizar(i,sacar,l,p,w);
      for (int i=0;i<n;i++){
        P[i].l=l[i];
        P[i].p=p[i];
      }
      // Calcula autovectores y autovalores para la primera prueba
      calculo_av_prueba(n,m0,ml,mp,K,P,Qac,Dant); // P es la configuración de los pisos
                                                  // en Dant quedan los autovalores
      // Calcula frecuencias a partir de autovalores
      for (int i=0;i<n;i++) w[i]=sqrt(-Dant.sub(i,i));

      // Calcula el tiempo transcurrido
      fin=clock();
      segundos=(double)(fin - inicio)/CLOCKS_PER_SEC;
    }
  }

  // Verifica si no están en el rango prohibido (2.7 a 3.3)
  ok=true;
  for (int i=0;i<n;i++) {
    if (w[i]>=2.7 && w[i] <= 3.3) ok=false;
  }

  // Si las frecuencias no están en el rango prohibido terminamos=>sale
  if (ok) {
    cout << endl;
    cout << "Solución encontrada:" << endl;
    for (int i=0;i<n;i++) { cout << "  w[" << i << "]=" << w[i] << endl; }
  }
    
  if (segundos > TMAX) { // Máximo tiempo permitido para las pruebas
    cout << endl;
    cout << "Tiempo máximo alcanzado!" << endl;
    tmax=true;
  }
  c++;
    
  if (!ok && !tmax) cout << endl;

  cout << "Cantidad de pruebas: " << c << "." << endl;
  cout << "Tiempo ejecucion: " << setprecision(15) << segundos << " segundos." << endl;
}
