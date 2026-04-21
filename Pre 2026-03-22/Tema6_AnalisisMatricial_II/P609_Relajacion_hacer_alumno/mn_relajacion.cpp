#include "mn_aritmeticas.h"
#include "mn_lapack.h"
#include "mn_relajacion.h"
#include <stdio.h.>


/******************************************************************************
  FUNCION QUE CALCULA LA SOLUCION DE UN SISTEMA POR EL METODO DE RELAJACIÓN
  DEVUELVE EL NUMERO DE ITERACIONES REALIZADA.
*******************************************************************************/
int mn_relajacion (
const Array2D< real > &A, /// MATRIZ DEL SISTEMA
const Array1D< real > &b, /// VECTOR DE TÉRMINOS INDEPENDIENTES DEL SISTEMA
Array1D< real > &u,       /// VECTOR SOLUCION (DE ENTRADA ES UNA INICIALIZACIÓN)
const int nMax,           /// NÚMERO DE ITERACIONES MÁXIMO
const real TOL,           /// TOLERANCIA PARA CONTROLAR LA CONVERGENCIA DEL ALGORITMO
const real w)             /// PARÁMETRO DE RELAJACIÓN
{
    /// HACER ALUMNO

}


