#ifndef HEURISTICAS_H
#define HEURISTICAS_H

#include <vector>
#include <set>
#include "Coef.h"

using namespace std;

void ejecuta_heuristica(int nh,vector<int>& parametros,int n,Coef m0, Coef ml, Coef mp, Matriz& K, vector<int>& l, vector<int>& p, bool& ok, bool& tmax);

#endif
