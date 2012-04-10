#include "fisica.h"
#include "TFloat.h"

extern size_t pr;
extern TFloat g;

// version caida libre

TFloat posicionCaidaLibre(const Datos& d, TFloat t){
  return d.h + d.v0*t - (g/2)*t*t;
}

TFloat velocidadCaidaLibre(const Datos& d, TFloat t){
  return d.v0 - g*t;
}

TFloat aceleracionCaidaLibre(const Datos& d, TFloat t){
  TFloat menos_uno_tf=TFloat(-1,pr);
  return  menos_uno_tf*g;
}

// version con rozamiento

TFloat posicionConRozamiento(const Datos& d, TFloat t){
  TFloat a=d.cr/d.m;
  TFloat menos_uno_tf=TFloat(-1,pr);
  return d.h + d.v0/a + g/(a*a) - (g/a)*t - ( d.v0/a + g/(a*a) ) * ((menos_uno_tf*a*t).exponencial());
}

TFloat velocidadConRozamiento(const Datos& d, TFloat t){
  TFloat a=d.cr/d.m;
  TFloat menos_uno_tf=TFloat(-1,pr);
  return menos_uno_tf*g/a + (d.v0+g/a) * ((menos_uno_tf*a*t).exponencial());
}

TFloat aceleracionConRozamiento(const Datos& d, TFloat t){
  TFloat a=d.cr/d.m;
  TFloat menos_uno_tf=TFloat(-1,pr);
  return (d.v0+g/a) * ((menos_uno_tf*a*t).exponencial())*menos_uno_tf*a;
}

// genericos

// velocidad en el instante t
TFloat velocidad(const Datos& d, TFloat t){
    if (d.cr.dbl()>0){
        return velocidadConRozamiento(d, t);
    } else {
        return velocidadCaidaLibre(d, t);
    }
}

// altura en el instante t
TFloat posicion(const Datos& d, TFloat t){
    if (d.cr.dbl()>0){
        return posicionConRozamiento(d, t);
    } else {
        return posicionCaidaLibre(d, t);
    }
}

// aceleracion en el instante t
TFloat aceleracion(const Datos& d, TFloat t){
    if (d.cr.dbl()>0){
        return aceleracionConRozamiento(d, t);
    } else {
        return aceleracionCaidaLibre(d, t);
    }
}

// energia mecanica
TFloat energiaMecanica(const Datos& d, TFloat t){
  TFloat dos_tf=TFloat(2.0,pr);
  return posicion(d, t)*g + velocidad(d,t)*velocidad(d,t) / dos_tf;
}
