#include <vector>
#include <set>
#include <stdlib.h>
#include "Coef.h"
#include "matriz.h"
#include "heuristicas.h"

using namespace std;

#define CANT_PRUEBAS_H1 1000

void h1(int n,Coef m0, Coef ml, Coef mp, vector<Coef> &k, vector<int> &l, vector<int> &p, vector< vector <Coef > > &P)
{
  SetPruebas m;
  vector<Coef> v(n);
  int ps=0;
  int pp=0;
  for (int i=0;i<CANT_PRUEBAS_H1;i++) { 
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
      v[j]=(m0+ml*l[j]+mp*p[j]);
    }
    P.push_back(v);
  }
  
}

void h1_fail(int n,Coef m0, Coef ml, Coef mp, vector<Coef> &k, vector<int> &l, vector<int> &p, vector< SetPruebas > &P)
{
  SetPruebas m;
  vector<Coef> v(n);
  for(int c=1;c < 51;c++){
    int cl=0;
    int cp=c;
    while (m.size()<=c*n){
      for (int i=0;i<=cl;i++){
        for (int j=cp;j>=0;j--){
          for (int x=0;x<=i;x++){
            int ps=0;
	    int pp=0;
            while (ps==pp || l[ps]==0) { ps=rand()%n; pp=rand()%n; }
            l[ps]--;
            l[pp]++;
	  }
          for (int x=0;x<=j;x++){
            int ps=0;
	    int pp=0;
            while (ps==pp || p[ps]==0) { ps=rand()%n; pp=rand()%n; }
            //cout << " x=" << x
                 //<< " ps=" << ps
                 //<< " pp=" << pp
                 //<< endl;
            p[ps]--;
            p[pp]++;
	  }
        }
      }
      for (int i=0;i<n;i++){
        v[i]=(m0+ml*l[i]+mp*p[i]);
      }
      m.insert(v);
      //cout <<  "cl=" << cl
           //<< " cp=" << cp
           //<< " m.size()=" << m.size()
           //<< endl;
    }
    P.push_back(m);
  }
}
