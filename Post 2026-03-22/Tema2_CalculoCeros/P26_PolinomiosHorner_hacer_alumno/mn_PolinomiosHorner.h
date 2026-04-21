#ifndef AN_RAICES_POLINOMIOS_H
#define AN_RAICES_POLINOMIOS_H
#include "tnt_array/tnt.h"
#include "mn_aritmeticas.h"
using namespace TNT;

/// DECLARACION DE TIPOS DE LAS FUNCIONES BASICAS
real mn_evaluar_polinomio(Array1D< real > &a,real x);
void mn_evaluar_polinomio_horner(Array1D< real > &a, real x, real &Px,real &PPx);
Array1D< real > mn_calcular_derivada_polinomio(Array1D< real > &a);
#endif
