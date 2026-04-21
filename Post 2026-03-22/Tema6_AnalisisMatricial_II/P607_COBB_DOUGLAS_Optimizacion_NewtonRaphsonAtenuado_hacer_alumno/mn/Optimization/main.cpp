#include <stdio.h>
#include "../mn_optimizacion.h"
#include "../mn_lapack.h"
#include "../mn_utilidades.h"
#include <stdlib.h>

///    PROGRAMA PRINCIPAL
int main()
{
  real TOL=1e-8;
  int Nmax=1000;
  double h=1e-8;

  /// AJUSTE DE PARÁMETROS DEL MODELO Cobb--Douglas
  Array1D<real> u(4);
  u[0]=0.4;
  u[1]=0.3;
  u[2]=0.4;
  u[3]=5;
  printf("aproximacion inicial u=(%lf,%lf,%lf,%lf) \n",u[0],u[1],u[2],u[3]);
  printf("error ajuste inicial : %e \n",error_ajuste(u));

  printf("\nAPLICACION METODO NEWTON-RAPHSON ATENUADO\n");
  int Niter= mn_newton_raphson_atenuado(error_ajuste,u,h,TOL,Nmax);

  printf("resultadoa final u=(%lf,%lf,%lf,%lf) \n",u[0],u[1],u[2],u[3]);
  printf("error ajuste final : %e N.Iter = %d\n",error_ajuste(u),Niter);


}


