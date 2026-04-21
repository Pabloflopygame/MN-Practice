#include <stdio.h>
#include "../mn_sistemas_no_lineales.h"
#include "../mn_lapack.h"
#include <stdlib.h>


int main()
{
  real TOL=1e-8;
  int Nmax=1000;
  double h=1e-8;

  /// AJUSTE DE PARÁMETROS DEL MODELO Cobb--Douglas
  Array1D<real> u(4);
  u[0]=0.33;
  u[1]=0.33;
  u[2]=0.3;
  u[3]=4.2;
  printf("aproximacion inicial u=(%lf,%lf,%lf,%lf) \n",u[0],u[1],u[2],u[3]);
  printf("error ajuste inicial alumno = %e \n",error_ajuste(u));
  printf("error ajuste inicial real   = %e \n",4.142191e+002);


  /// APLICAMOS NEWTON RAPHSON
  int iter = mn_newton_raphson_sistemas(f, u,TOL,Nmax);
  printf("\nN. iteraciones Newton-Raphson =%d\n",iter);
  printf("\nsolucion alumno u=(%lf,%lf,%lf,%lf) \n",u[0],u[1],u[2],u[3]);
  printf("solucion real   u=(%lf,%lf,%lf,%lf) \n",0.3,0.4,0.2,4.);
  printf("\nerror ajuste final alumno = %e \n",error_ajuste(u));
  printf("error ajuste final real   = %e \n",8.114332e-014);

}


