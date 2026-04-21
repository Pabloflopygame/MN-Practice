#ifndef MN_INTERPOLACION_H
#define MN_INTERPOLACION_H
#include "tnt_array/tnt.h"
using namespace TNT;

/// DECLARACION DE TIPOS DE LAS FUNCIONES BASICAS

int mn_calculo_splines_2( Array1D< real > &x,  Array1D< real > &f, real &c0,Array1D< real > &a,Array1D< real > &b,Array1D< real > &c);

real mn_evaluar_splines_2( Array1D< real > &x,Array1D< real > &a,Array1D< real > &b,Array1D< real > &c,real x0 );



#endif
