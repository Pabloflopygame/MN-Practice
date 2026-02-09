#include <stdio.h>
#include "../mn_sistemas_no_lineales.h"
#include "../mn_lapack.h"
#include <stdlib.h>


int main()
{
  real TOL=1e-8;
  int Nmax=1000;
  double h=1e-8;

  /// OPTIMIZACIÓN BENEFICIO DEL MODELO Cobb--Douglas
  Array1D<real> u(3,10.);

  printf("DISTRIBUCION INICIAL DEL CAPITAL Y BENEFICIO ESPERADO (CON SIGNO CAMBIADO)\n");
  printf("K=%lf, L=%lf, M=%lf Benef=%lf\n",u[0],u[1],u[2],mn_beneficio(u));

  printf("\nOPTIMIZACION DEL BENEFICIO USANDO GRADIENTE DESCENDENTE\n");
  int Niter=mn_gradiente_descendente(mn_beneficio,u,TOL,h,Nmax);
  printf("N. ITERACIONES REALIZADAS POR EL ALGORITMO (alumno) = %d\n",Niter);
  printf("N. ITERACIONES REALIZADAS POR EL ALGORITMO  (real)  = %d\n",315);

  printf("\nDISTRIBUCION FINAL DEL CAPITAL Y BENEFICIO ESPERADO (ALUMNO)\n");
  printf("K=%lf, L=%lf, M=%lf, Benef=%lf\n",u[0],u[1],u[2],mn_beneficio(u));

  printf("\nDISTRIBUCION FINAL DEL CAPITAL Y BENEFICIO ESPERADO (REAL)\n");
  printf("K=%lf, L=%lf, M=%lf, Benef=%lf\n",20.446143,5.945009,3.711925,-6.202029);


}


