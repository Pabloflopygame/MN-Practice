#include <stdio.h>
#include "mn_lapack.h"

/// FUNCIÓN QUE DEVUELVE LA NORMA 1 DE LA MATRIZ A. SE DEVUELVE -1 SI TERMINA MAL
double norma_1(Array2D< real > &A){
  /// HACER ALUMNO

}

/// FUNCIÓN QUE DEVUELVE LA NORMA INFINITO DE LA MATRIZ A.SE DEVUELVE -1 SI TERMINA MAL
double norma_infinito(Array2D< real > &A){
  /// HACER ALUMNO

}

/// FUNCIÓN QUE DEVUELVE LA NORMA 2 DE LA MATRIZ A
/// SE UTILIZA LA FUNCIÓN mn_autovalor_maximo() QUE FIGURA DEBAJO PARA CALCULAR EL AUTOVALOR MÁXIMO
/// TAMBIEN SE USA EL MÉTODO transpose() DE LA CLASE Array2D PARA CALCULAR LA MATRIZ TRASPUESTA
double norma_2(Array2D< real > &A,real TOL,int Nmax){
  /// HACER ALUMNO

}

/** CALCULO AUTOVALOR MÁXIMO */
real mn_autovalor_maximo( Array2D< real > &A)
{
  Array1D< real > u(A.dim1(),1.);
  real a=u.max();
  u=u/a;
  for(int i=0;i<10000;i++){
    Array1D< real > v=A*u;
    real b=v.max();
    if( b==0) return(a);
    if(u*v<0.) a=-b;
    else a=b;
    v=v/b;
    if( (u-v).max()<1e-8 ){
      return(a);
    }
    u=v;
  }
  return(a);
}






