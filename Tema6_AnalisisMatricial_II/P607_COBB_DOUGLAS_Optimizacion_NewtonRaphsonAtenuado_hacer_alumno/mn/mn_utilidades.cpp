#include "mn_utilidades.h"
#include "mn_lapack.h"
#include <stdlib.h>
#include <stdio.h>

/// -------------------------------------------------------------
/// EVALUACIÓN DE LA DISTRIBUCIÓN LOG-NORMAL
real log_normal(
real x,
Array1D< real > &u)
{
  /// OBTENEMOS LOS PARÁMETROS DE LA LOG-NORMAL A PARTIR DEL VECTOR u
  real a=u[0];
  real b=u[1];
  real c=u[2];
  real d=u[3];

  /// CONTROLAMOS QUE EL PARÁMETRO c SEA POSITIVO
  if(c<=0) return d;

  /// EVALUAMOS LA LOG-NORMAL A PARTIR DE SU FÓRMULA
  if(x<=a) return 0.;
  real aux=log(x-a)-b;
  return d*exp(-aux*aux/(2*c))/( (x-a)*sqrt(2*M_PI*c) );
}

/// -------------------------------------------------------------
/// FUNCIÓN PARA INICIALIZAR LOS PARÁMETROS DE LA LOG-NORMAL
/// USANDO LA MEDIA Y LA VARIANZA MUESTRALES
Array1D<real> Inicializar_log_normal(
Array1D<real> &x,
Array1D<real> &y)
{
  /// PARAMETROS DE LA LOG-NORMAL
  Array1D<real> u(4);

  /// CALCULAMOS LA MEDIA Y VARIANZA MUESTRALES SUPONIENDNO x[0]=0;
  real media=0.,varianza=0.,suma=0.;;
  for(int k=0;k<y.dim();k++){
    suma+=y[k];
    media+=k*y[k];
  }
  media/=suma;
  for(int k=0;k<y.dim();k++){
    varianza+=(k-media)*(k-media)*y[k];
  }
  varianza/=suma;

  /// CALCULAMOS LOS PARAMETROS DE LA LOG-NORMAL
  u[2]=log(varianza/(media*media)+1);
  u[1]=log(media)-u[2]/2.;
  u[0]=x[0];
  u[3]=suma;

  /// DEVOLVEMOS LOS PARÁMETROS DE LA LOG-NORMAL
  return u;

}

/// --------------------------------------------------------------------------------
/// FUNCIÓN QUE CALCULA PERCENTILES DE UNA DISTRIBUCIÓN LOG-NORMAL
real percentil_log_normal(
Array1D<real> &u, /// PARÁMETROS DE LA LOG-NORMAL
int percentil) /// PERCENTIL. SU VALOR PUEDE SER 5,25,50,75,95
{
  /// OBTENEMOS LOS PARÁMETROS DE LA LOG-NORMAL A PARTIR DEL VECTOR u
  real a=u[0];
  real b=u[1];
  real c=u[2];

  real aux;
  switch (percentil)
  {
  case 5:
      aux=-1.163087154;
      break;
  case 25:
      aux=-0.4769362762;
      break;
  case 50:
      aux=0;
      break;
  case 75:
      aux=0.4769362762;
      break;
  case 95:
      aux=1.163087154;
      break;
  default:
      printf("Esta funcion solo esta implementada para los percentiles : 5, 25, 50, 75 y 95\n");
      system("pause");
      break;
  }
  return a+exp(b+sqrt(2.)*c*aux);
}

/// --------------------------------------------------------------------------------
/// FUNCIÓN QUE CALCULA LA MEDIA DE UNA DISTRIBUCIÓN LOG-NORMAL
real media_log_normal(
Array1D<real> &u) /// PARÁMETROS DE LA LOG-NORMAL
{
  real a=u[0];
  real b=u[1];
  real c=u[2];
  return a+exp(b+c/2.);
}

/// --------------------------------------------------------------------------------
/// FUNCIÓN QUE CALCULA DONDE ALCANZA EL MÁXIMO UNA DISTRIBUCIÓN LOG-NORMAL
real pico_log_normal(
Array1D<real> &u) /// PARÁMETROS DE LA LOG-NORMAL
{
  real a=u[0];
  real b=u[1];
  real c=u[2];
  return a+exp(b-c);
}

/// --------------------------------------------------------------------------------
/// FUNCIÓN QUE CALCULA EL MÁXIMO DE UNA DISTRIBUCIÓN LOG-NORMAL
real maximo_log_normal(
Array1D<real> &u) /// PARÁMETROS DE LA LOG-NORMAL
{
  real a=u[0];
  real b=u[1];
  real c=u[2];
  real d=u[3];
  real xmax=a+exp(b-c);
  return log_normal(xmax,u)/d;

}

