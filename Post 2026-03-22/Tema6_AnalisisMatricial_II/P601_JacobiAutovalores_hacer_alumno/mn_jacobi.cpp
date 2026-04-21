#include "mn_jacobi.h"

/******************************************************************************
// FUNCION QUE CALCULA LOS AUTOVALORES DE UNA MATRIZ (LOS DEVUELVE EN UN ARRAY)
//*****************************************************************************/
Array1D< real > jacobi (Array2D< real >&A, /// matriz original
Array2D< real >&Autovectores,  /// matriz de salida con los autovectores
const int NMaxIter,  /// número máximo de iteraciones
const real TOL, /// tolerancia para detener el algoritmo
int &Niter) /// variable de salida con el numero  de iteraciones
{
  /** COMPROBAMOS QUE LAS DIMENSIONES SON COHERENTES */
  if(A.dim1()!=A.dim2() || A.dim1()!=Autovectores.dim1()
     || A.dim2()!=Autovectores.dim2() ){
         return(Array1D< real >());
  }

  /** COMPROBAMOS QUE LA MATRIZ A ES SIMÉTRICA */
  int N=A.dim1();
  for(int i=0;i<N;i++){
    for(int j=i+1;j<N;j++){
      if(A[i][j]!=A[j][i]){
        return(Array1D< real >());
      }
    }
  }

  /** HACER ALUMNO */

}

