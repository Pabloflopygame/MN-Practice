#include <stdlib.h>
#include <math.h>
#include "mn_aritmeticas.h"
#include "tnt_array/tnt.h"
using namespace TNT;

#ifndef MN_OPTIMIZACION_H
#define MN_OPTIMIZACION_H


/// -------------------------------------------------------------
/// EVALUACIÓN DEL ERROR AL APROXIMAR POR UNA LOG-NORMAL
/// DE PARÁMETROS u[] LA NUBE DE PUNTOS (x[],y[]).
real Error_p(Array1D<real> &u);


/// -------------------------------------------------------------
/// MÉTODO DE NEWTON-RAPHSON ATENUADO PARA MINIMIZAR f()
int mn_newton_raphson_atenuado(
real (*f)(Array1D<real> &u), Array1D<real> &u, real h, real TOL, int Nmax);


#endif
