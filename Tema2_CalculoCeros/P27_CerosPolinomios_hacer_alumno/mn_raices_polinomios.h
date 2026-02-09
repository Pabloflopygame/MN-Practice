#ifndef AN_RAICES_POLINOMIOS_H
#define AN_RAICES_POLINOMIOS_H
#include "tnt_array/tnt.h"
#include "mn_aritmeticas.h"
using namespace TNT;

/// DECLARACION DE TIPOS DE LAS FUNCIONES BASICAS
real evaluar_polinomio(Array1D< real > &a,real x);
Array1D< real > ceros_polinomio(Array1D< real > &a,real TOL);


#endif
