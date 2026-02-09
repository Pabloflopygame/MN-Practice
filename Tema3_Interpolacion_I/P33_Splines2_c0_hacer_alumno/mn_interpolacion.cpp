#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/**
 LA INTERPOLACION POR SPLINES DE GRADO 2 SEGÚN SE EXPLICÓ EN CLASE.
 EN ESTE CASO SE SUPONE CONOCIDO c[0] Y SE CALCULA EL RESTO DE COEFICIENTES
 LA FUNCION DEVUELVE -1 SI ENCUENTRA ALGÚN PROBLEMA Y 0 EN CASO CONTRARIO
*/
int mn_calculo_splines_2(
 Array1D< real > &x, /// vector con los puntos de interpolación
 Array1D< real > &f, /// vector con los valores de la función
 real &c0,           /// valor de c[0] asignado como parámetro
Array1D< real > &a,       /// vector de salida con los coeficientes a[i] del spline de grado 2
Array1D< real > &b,       /// vector de salida con los coeficientes b[i] del spline de grado 2
Array1D< real > &c)       /// vector de salida con los coeficientes c[i] del spline de grado 2
{
  /// HACER ALUMNO

}

/**
  EVALUACIÓN SPLINE DE GRADO DOS. SE DEVUELVE EL VALOR DE LA
  EVALUACIÓN EN x0
*/
real mn_evaluar_splines_2(
Array1D< real > &x,
Array1D< real > &a,
Array1D< real > &b,
Array1D< real > &c,
real x0 ){
  /// HACER ALUMNO

}

