// Headers para funciones de metodos numericos

#ifndef __METODOS_H__
#define __METODOS_H__

#include "TFloat.h"
#include "fisica.h"

// Calcula el error relativo entre dos TFloat
TFloat errorRelativo(TFloat a, TFloat b);

// Biseccion hasta max_iter o hasta que la tolerancia sea menor a la especificada
TFloat biseccion(TFloat (*f)(const Datos&,TFloat),const Datos& d, int& iter);

// Hace solo n iteraciones de biseccion y no sale por la tolerancia, se usa para iniciar newton
TFloat biseccion_n(TFloat (*f)(const Datos&,TFloat),const Datos& d, int iter);

// Newton hasta max_iter o hasta que la tolerancia sea menor a la especificada
TFloat newton(TFloat (*f)(const Datos&,TFloat),TFloat (*f1)(const Datos&,TFloat),const Datos& d, TFloat t, int& iter);

#endif //__METODOS_H__
