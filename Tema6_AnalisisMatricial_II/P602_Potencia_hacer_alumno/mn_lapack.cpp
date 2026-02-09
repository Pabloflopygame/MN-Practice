/*========================================================================
  FUNCIONES RELACIONADAS CON LA RESOLUCION DE SISTEMAS DE ECUACIONES
  ======================================================================== */

// INCLUSION DE LIBRERIAS NECESARIAS
#include <stdio.h>
#include "mn_lapack.h"

/// FUNCION QUE CALCULA EL PRODUCTO ESCALAR ENTRE 2 VECTORES
real mn_producto_escalar(Array1D< real > &u, Array1D< real > &v)
{
   int i;
   if(u.dim()!=v.dim() || u.dim()==0 ){
     printf("funcion mn_producto_escalar(): los vectores tienen dimension distinta\n");
     return(-1.);
   }
   real Sum=0.;
   for (i=0;i<u.dim();i++){
      Sum+=u[i]*v[i];
   }
   return (Sum);
}

/// FUNCION QUE CALCULA LA NORMA EUCLIDEA DE UN VECTOR
real mn_norma_euclidea(Array1D< real > u)
{
  real norma=0;
  for(int i=0;i<u.dim();i++){
    norma+=u[i]*u[i];
  }
  return(sqrt(norma));
}

/** FUNCION PARA CALCULAR EL AUTOVALOR Y AUTOVECTOR MAXIMO POR EL METODO DE LA
POTENCIA. EL AUTOVALOR Y AUTOVECTOR SE PASAN COMO PARAMETROS.
LA FUNCION RETORNA EL NUMERO DE ITERACIONES REALIZADO SI TERMINA BIEN Y UN
NUMERO NEGATIVO SI TERMINA MAL
*/
int mn_metodo_potencia(
Array2D< real > &A, /// MATRIZ PARA APLICAR EL METODO DE LA POTENCIA
Array1D< real > &u_max, /// AUTOVECTOR MAXIMO CALCULADO (DEBE ESTAR INICIALIZADO AL ENTRAR)
real &l_max,  /// AUTOVALOR MAXIMO
int Nmax, /// NUMERO ITERACIONES MAXIMO
real TOL) /// TOLERANCIA PARA LA CONVERGENCIA DEL ALGORITMO
{
  /// HACER ALUMNO

}






