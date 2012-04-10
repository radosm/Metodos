// Headers para funciones de caida libre y con rozamiento

#include "TFloat.h"

#ifndef __FISICA_H__
#define __FISICA_H__

struct Datos{

    Datos(){}

    TFloat v0; //velocidad inicial
    TFloat h; //altura
    TFloat m; //masa
    TFloat cr; // coeficiente de rozamiento
    TFloat fr; // factor de restitucion
};

// velocidad en el instante t
TFloat velocidad(const Datos& d, TFloat t);

// altura en el instante t
TFloat posicion(const Datos& d, TFloat t);

// aceleracion en el instante t
TFloat aceleracion(const Datos& d, TFloat t);

// energia mecanica
TFloat energiaMecanica(const Datos& d, TFloat t);

#endif //__FISICA_H__
