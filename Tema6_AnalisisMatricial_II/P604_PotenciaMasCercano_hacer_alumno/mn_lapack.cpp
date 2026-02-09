#include <stdio.h>
#include "mn_lapack.h"


/** FUNCION PARA CALCULAR EL AUTOVALOR Y AUTOVECTOR MAS CERCANO A UN VALOR DADO
(QUE ES LA APROXIMACIÓN INICIAL DEL AUTOVALOR)
USANDO UNA VARIANTE DEL MÉTODO DE LA POTENCIA INVERSA VISTO EN CLASE
EL AUTOVALOR INICIAL Y EL AUTOVECTOR SE PASAN COMO PARAMETROS.
LA FUNCION RETORNA EL NUMERO DE ITERACIONES REALIZADO SI TERMINA BIEN Y UN
NUMERO NEGATIVO SI TERMINA MAL.
NOTA: EN ESTA FUNCION SE DEBE USAR LA FUNCION mn_gauss() PARA RESOLVER SISTEMAS
DECLARADA ARRIBA, EL MÉTODO DE LA CLASE Array1D norma() PARA CALCULAR LA NORMA Y
EL OPERADOR * PARA EL CALCULO DEL PRODUCTO ESCALAR ENTRE VECTORES
*/
int mn_metodo_potencia(
Array2D< real > &A, /// MATRIZ PARA APLICAR EL METODO DE LA POTENCIA
Array1D< real > &u_min, /// AUTOVECTOR CALCULADO (DEBE ESTAR INICIALIZADO AL ENTRAR)
real &l_min,  /// AUTOVALOR MAS CERCANO AL l_min INICIAL. ESTO ES UN PARAMETRO DE ENTRADA SALIDA. EN LA ENTRADA
              /// ES LA APROXIMACIÓN DEL AUTOVALOR, Y EN LA SALIDA ES EL RESULTADO ACTUALIZADO POR EL METODO
int Nmax, /// NUMERO ITERACIONES MAXIMO
real TOL) /// TOLERANCIA PARA LA CONVERGENCIA DEL ALGORITMO
{
  /// HACER ALUMNO

}


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



