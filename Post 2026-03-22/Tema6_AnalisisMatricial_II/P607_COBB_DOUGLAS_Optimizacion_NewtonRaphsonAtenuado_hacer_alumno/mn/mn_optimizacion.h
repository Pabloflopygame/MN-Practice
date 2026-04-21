#include <stdlib.h>
#include <math.h>
#include "mn_aritmeticas.h"
#include "tnt_array/tnt.h"
using namespace TNT;

#ifndef MN_OPTIMIZACION_H
#define MN_OPTIMIZACION_H


/// -------------------------------------------------------------
/// ERROR DE AJUSTE DE COBB-DOUGLAS
real error_ajuste(Array1D< real > &u);


/// -------------------------------------------------------------
/// MÉTODO DE NEWTON-RAPHSON ATENUADO PARA MINIMIZAR f()
int mn_newton_raphson_atenuado(
real (*f)(Array1D<real> &u), Array1D<real> &u, real h, real TOL, int Nmax);


#endif
