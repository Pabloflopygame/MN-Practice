#ifndef MN_INTERPOLACION_H
#define MN_INTERPOLACION_H
#include "tnt_array/tnt.h"
using namespace TNT;

/// DECLARACION DE TIPOS DE LAS FUNCIONES BASICAS

int mn_calculo_splines_3(const Array1D< real > &x, const Array1D< real > &f,const real c0,const real cN,Array1D< real > &a,
                         Array1D< real > &b,Array1D< real > &c,Array1D< real > &d);

real mn_evaluar_splines_3(const Array1D< real > &x,Array1D< real > &a,Array1D< real > &b,Array1D< real > &c,Array1D< real > &d, real x0 );



#endif
