#ifndef HEURISTICAS_H
#define HEURISTICAS_H

#include <vector>
#include <set>
#include "Coef.h"

using namespace std;

typedef set < vector<Coef> > SetPruebas;

void h1(int n,Coef m0, Coef ml, Coef mp, vector<Coef> &k, vector<int> &l, vector<int> &p, vector< vector <tuple <int,int> > > &P);

#endif
