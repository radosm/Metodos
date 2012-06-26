#include <vector>
#include <set>
#include <stdlib.h>
#include "Coef.h"
#include "matriz.h"
#include "heuristicas.h"

using namespace std;

#define CANT_PRUEBAS_H1 5000

void h1(int n,Coef m0, Coef ml, Coef mp, vector<Coef> &k, vector<int> l, vector<int> p, vector< vector < Piso > > &P)
{
  vector<Piso> v(n);
  
  for (int i=0;i<n;i++){ // La primera prueba es como vino originalmente
    v[i].l=l[i];
    v[i].p=p[i];
  }
  P.push_back(v);

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

//cout << i << " " 
//<< ps << " " 
//<< pp << " " 
//<< cl << " " 
//<< cp << " " 
//<< endl;

    l[ps]-=cl;
    l[pp]+=cl;
    p[ps]-=cp;
    p[pp]+=cp;
    for (int j=0;j<n;j++){
      v[j].l=l[j];
      v[j].p=p[j];
    }
    P.push_back(v);
  }
  
}
