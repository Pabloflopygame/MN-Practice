/*========================================================================
  FUNCIONES PARA LA INTERPOLACION DE FUNCIONES
  ======================================================================== */

// INCLUSION DE LA LIBRERIA PARA GESTIONAR LA ARITMETICA
#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"


Array1D< real > solucion_sistema(
Array1D< real > &L,
Array1D< real > &M,
Array1D< real > &U,
Array1D< real > &B
)
{
  Array1D< real > c(M.dim());
  c[0]=B[0];
  c[c.dim()-1]=B[B.dim()-1];

  for(int k=0;k<10000;k++){
    real error=0;
    for(int n=1;n<M.dim()-1;n++){
        real temp=c[n];
        c[n]= (-L[n]*c[n-1]-U[n]*c[n+1]+B[n])/M[n];
        error+=mn_distancia(temp,c[n]);
    }
    if(error<1e-8) return c;
  }
  return Array1D< real >();

}

/**
 LA INTERPOLACION POR SPLINES DE GRADO 3 SEGÚN SE EXPLICÓ EN CLASE.
 LA FUNCION DEVUELVE -1 SI ENCUENTRA ALGÚN PROBLEMA Y 0 EN CASO CONTRARIO.
 HAY QUE USAR LA FUNCIÓN solucion_sistema() QUE SE VE ARRIBA
*/
int mn_calculo_splines_3(
const Array1D< real > &x, /// vector con los puntos de interpolación
const Array1D< real > &f, /// vector con los valores de la función
const real c0,            /// primer valor del vector c[] asignado como parámetro
const real cN,            /// último valor del vector c[] asignado como parámetro
Array1D< real > &a,       /// vector de salida con los coeficientes a[i] del spline de grado 2
Array1D< real > &b,       /// vector de salida con los coeficientes b[i] del spline de grado 2
Array1D< real > &c,       /// vector de salida con los coeficientes c[i] del spline de grado 2
Array1D< real > &d)       /// vector de salida con los coeficientes d[i] del spline de grado 2
{
  /// HACER ALUMNO

}

/**
  EVALUACIÓN SPLINE DE GRADO 3. SE DEVUELVE EL VALOR DE LA
  EVALUACIÓN EN x0
*/
real mn_evaluar_splines_3(
const Array1D< real > &x,
Array1D< real > &a,
Array1D< real > &b,
Array1D< real > &c,
Array1D< real > &d,
real x0 ){
  /// HACER ALUMNO


}

