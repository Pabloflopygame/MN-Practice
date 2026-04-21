#ifndef AN_INTERPOLACION_H
#define AN_INTERPOLACION_H
#include "tnt_array/tnt.h"
using namespace TNT;

/// DECLARACION DE TIPOS DE LAS FUNCIONES BASICAS

Array1D< real > mn_construir_polinomio_interpolador(const Array1D< real > &X, const Array1D< real > &F);
real mn_evaluar_polinomio_interpolador(const Array1D< real > &A, const Array1D< real > &X,const real X0);


#endif
