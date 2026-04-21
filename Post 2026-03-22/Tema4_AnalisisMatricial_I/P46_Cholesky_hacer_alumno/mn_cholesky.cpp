#include "mn_cholesky.h"
#include "mn_lapack.h"
#include <stdlib.h>
#include <stdio.h>

/// Función que calcula las matrices de descomposición de Cholesky. Se implementa
///   en una sola matriz pues se trata de una matriz triangular inferior y su traspuesta
Array2D< real > mn_cholesky_factorization(const Array2D< real > &A)
{
   /// HACER ALUMNO

}


/// FUNCION PARA RESOLVER UN SISTEMA POR EL METODO DE CHOLESKY
Array1D< real > mn_cholesky (const Array2D< real > &A, const Array1D< real > &b)
{
    /// HACER ALUMNO


}

/// FUNCION PARA RESOLVER UN SISTEMA TRIANGULAR INFERIOR
Array1D< real > mn_descenso (const Array2D< real > &B, const Array1D< real > &b)
{
   int i,j;
   if(B.dim1()!=B.dim2() || B.dim1()!=b.dim() ) return(Array1D< real >());
   int N=B.dim1();
   Array1D< real > z(N);

   /// INICIAMOS EL DESCENSO
   for (i=0;i<N;i++){
      if (B[i][i]==0) { /// comprobamos que la diagonal es distinto de cero
         return(Array1D< real >());
      }
      z[i]=b[i]; /// inicializamos la solucion
      for (j=0;j<i;j++){ /// aplicamos la formula para calcular la solucion
         z[i]=z[i] - B[i][j]*z[j];
      }
      z[i]=z[i]/B[i][i];
  }
  return(z);
}

/// FUNCION PARA RESOLVER UN SISTEMA TRIANGULAR SUPERIOR
Array1D< real > mn_remonte (const Array2D< real > &B, const Array1D< real > &z)
{
   int i,j;
   if(B.dim1()!=B.dim2()  || B.dim1()!=z.dim() ) return(Array1D< real >());
   int N=B.dim1();
   Array1D< real > DU(N);

   /// INICIAMOS EL REMONTE
   for (i=N-1;i>=0;i--){
      if (B[i][i]==0){  /// comprobamos que la diagonal es distinto de cero
         return(Array1D< real >());
      }
      DU[i]=z[i]; /// inicializamos la solucion
      for  (j=i+1;j<N;j++){ /// aplicamos la formula para calcular la solución
         DU[i]=DU[i] - B[i][j]*DU[j];
      }
      DU[i]=DU[i]/B[i][i];
  }
  return(DU);
}
