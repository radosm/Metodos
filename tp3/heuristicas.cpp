#include <vector>
#include <set>
#include <stdlib.h>
#include "Coef.h"
#include "matriz.h"
#include "heuristicas.h"

using namespace std;

void h1(int n,Coef m0, Coef ml, Coef mp, vector<Coef> &k, vector<int> &l, vector<int> &p, vector< SetPruebas > &P)
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
