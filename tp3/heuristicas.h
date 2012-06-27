#ifndef HEURISTICAS_H
#define HEURISTICAS_H

#include <vector>
#include <set>
#include "Coef.h"

using namespace std;

struct Piso {
  int l;
  int p;
};

void h1(int n,Coef m0, Coef ml, Coef mp, Matriz& K, vector<int> l, vector<int> p, bool& ok, bool& tmax, vector< Piso >& P);
void h2(int n,Coef m0, Coef ml, Coef mp, Matriz& K, vector<int> l, vector<int> p, bool& ok, bool& tmax, vector< Piso >& P);

#endif
