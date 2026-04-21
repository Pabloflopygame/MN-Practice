#include "mn_aritmeticas.h"
#include "mn_lapack.h"
#include <stdio.h.>


/******************************************************************************
  FUNCION QUE CALCULA LA SOLUCION DE UN SISTEMA POR EL METODO DE GAUSS-SEIDEL
  DEVUELVE EL NUMERO DE ITERACIONES REALIZADA. DEVUELVE WL Nº DE ITERACIONES
  SI TERMINA BIEN Y -1 SI TERMINA MAL
  EN LAS ITERACIONES SE ALTERNAN LA DIRECCION DE LOS RECORRIDOS AL ACTUALIZAR
  LAS INCOGNITAS
*******************************************************************************/
int mn_gauss_seidel (
const Array2D< real > &A, /// MATRIZ DEL SISTEMA
const Array1D< real > &b, /// VECTOR DE TÉRMINOS INDEPENDIENTES DEL SISTEMA
Array1D< real > &u,       /// VECTOR SOLUCION (DE ENTRADA ES UNA INICIALIZACIÓN)
const int nMax,           /// NÚMERO DE ITERACIONES MAXIMO
const real TOL)           /// TOLERANCIA PARA CONTROLAR LA CONVERGENCIA DEL ALGORITMO
{
  /// HACER ALUMNO

}
