#include "mn_aritmeticas.h"
#include "mn_lapack.h"
#include "mn_relajacion.h"
#include <stdio.h.>


///******************************************************************************
///  FUNCION QUE CALCULA LA SOLUCION DE UN SISTEMA POR EL METODO DE RELAJACIÓN
///  DEVUELVE EL NUMERO DE ITERACIONES REALIZADA. USA ALMACENAMIENTO ESCASO DE LA MATRIZ
///*******************************************************************************/
int mn_relajacion_escasa (
const Array1D < Array1D< real > > &A, /// MATRIZ ALMACENADA EN FORMA DE MATRIZ ESCASA
const Array1D < Array1D< int > > &J, /// VECTOR DE INDICES MATRIZ ESCASA
const Array1D< real > &b, /// VECTOR DE TÉRMINOS INDEPENDIENTES DEL SISTEMA
Array1D< real > &u,       /// VECTOR SOLUCION (DE ENTRADA ES UNA INICIALIZACIÓN)
const int nMax,           /// NÚMERO DE ITERACIONES MAXIMO
const real TOL,           /// TOLERANCIA PARA CONTROLAR LA CONVERGENCIA DEL ALGORITMO
const real w)             /// PARÁMETRO DE RELAJACIÓN
{
    /// HACER ALUMNO

}


/// FUNCION QUE CALCULA LA DIFERENCIA ENTRE 2 VECTORES
real mn_error_vectores(Array1D< real > &u, Array1D< real > &v)
{
   int i;

   if(u.dim()!=v.dim()){
     printf("mn_error_vectores() : arrays of different dimensions \n");
   }

   int N=u.dim();
   real Sum=0.;
   for (i=0;i<N;i++)
   {
      Sum = Sum + fabs(u[i]-v[i])/(fabs(u[i])+1.);
   }
   return (Sum/N);
}
