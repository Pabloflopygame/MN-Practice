/*========================================================================
  FUNCIONES RELACIONADAS CON LA RESOLUCION DE SISTEMAS DE ECUACIONES
  ======================================================================== */

// INCLUSION DE LIBRERIAS NECESARIAS
#include <stdio.h>
#include "mn_lapack.h"

/// FUNCION PARA RESOLVER SISTEMAS POR UNA VARIANTE DEL METODO DE GAUSS
Array1D< real > mn_gauss(
  const Array2D< real > &A  /** MATRIZ DEL SISTEMA */,
  const Array1D< real > &b) /** VECTOR DE TERMINOS INDEPENDIENTES */
{

  real max,paso,mul;
  int i,j,i_max,k;

  int N=A.dim1();
  Array2D< real > PASO(N,N+1);
  Array1D< real > u=b.copy();

  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      PASO[i][j]=A[i][j];
    }
    PASO[i][N]=b[i];
  }

  for(i=N-1;i>=0;i--){
    max=mn_abs(PASO[i][i]);
    i_max=i;
    for(j=0;j<i;j++){
       if(mn_abs(PASO[j][i])>max){
         i_max=j; max=mn_abs(PASO[j][i]);
       }
    }
    if(max<10e-120){
      return(Array1D< real >());
    }
    if(i_max!=i){
      for(k=0;k<=N;k++){
        paso=PASO[i][k];
        PASO[i][k]=PASO[i_max][k];
        PASO[i_max][k]=paso;
      }
    }
    for(j=0;j<i;j++){
      mul=-PASO[j][i]/PASO[i][i];
      for(k=0;k<=N;k++) PASO[j][k]+=mul*PASO[i][k];
    }
  }

  for (i=0;i<N;i++){
      u[i]=PASO[i][N];
      for (j=0;j<i;j++){
         u[i]=u[i] - PASO[i][j]*u[j];
      }
      u[i]=u[i]/PASO[i][i];
  }

  return(u);
}


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

/** FUNCION PARA CALCULAR EL AUTOVALOR Y AUTOVECTOR MINIMO POR EL METODO DE LA
POTENCIA. EL AUTOVALOR Y AUTOVECTOR SE PASAN COMO PARAMETROS.
LA FUNCION RETORNA EL NUMERO DE ITERACIONES REALIZADO SI TERMINA BIEN Y UN
NUMERO NEGATIVO SI TERMINA MAL.
NOTA: EN ESTA FUNCION SE DEBE USAR LA FUNCION mn_gauss() PARA RESOLVER SISTEMAS
DECLARADA ARRIBA.
*/
int mn_metodo_potencia(
Array2D< real > &A, /// MATRIZ PARA APLICAR EL METODO DE LA POTENCIA
Array1D< real > &u_min, /// AUTOVECTOR MAXIMO CALCULADO (DEBE ESTAR INICIALIZADO AL ENTRAR)
real &l_min,  /// AUTOVALOR MINIMO
int Nmax, /// NUMERO ITERACIONES MAXIMO
real TOL) /// TOLERANCIA PARA LA CONVERGENCIA DEL ALGORITMO
{
  /// HACER ALUMNO

}






