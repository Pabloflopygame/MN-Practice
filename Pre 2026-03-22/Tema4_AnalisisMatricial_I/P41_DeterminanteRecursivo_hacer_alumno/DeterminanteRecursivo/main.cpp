#include <stdio.h>
#include "../mn_determinante.h"
#include "../mn_lapack.h"
#include <stdlib.h>

int main()
{
  Array2D< real > A;

  /// LEEMOS MATRIZ DESDE DISCO
  int N=mn_leer_matriz("../datos/A_3.txt",A);
  A.print("EJEMPLO 1.");
  printf("El determinante que debe salir es : %lf\n",36.);
  printf("El determinante recursivo : %f\n\n",mn_determinante_recursivo(A));

  N=mn_leer_matriz("../datos/A_10.txt",A);
  A.print("EJEMPLO 2.");
  printf("El determinante que debe salir es : %e\n",2.2e+8);
  printf("El determinante recursivo : %e\n\n",mn_determinante_recursivo(A));


}


