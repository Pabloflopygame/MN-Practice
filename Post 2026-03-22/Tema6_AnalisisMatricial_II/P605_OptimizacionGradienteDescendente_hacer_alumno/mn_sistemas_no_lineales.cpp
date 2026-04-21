#include "mn_sistemas_no_lineales.h"
#include <stdlib.h>
#include <stdio.h>

/// CALCULO DE LA DISTANCIA MEDIA ENTRE ELEMENTOS DE DOS VECTORES
real mn_average_distance(Array1D< real > &u,Array1D< real > &v){
  real dist=0;
  for(int k=0;k<u.dim();k++){
    dist+=mn_distancia(u[k],v[k]);
  }
  return dist/u.dim();
}

/// CALCULO DEL GRADIENTE. DEVUELVE EL VECTOR GRADIENTE
Array1D< real > mn_gradiente(
real  (*F)(Array1D< real >), /// FUNCIÓN A LA QUE SE LE CALCULA EL GRADIENTE
Array1D< real > &u, /// VECTOR DONDE SE CALCULA EL GRADIENTE
real h) /// PASO FIJO PARA CALCULAR TODAS LAS DERIVADAS PARCIALES
{
  Array1D< real > g(u.dim());   /// declaración vector gradiente
  real F0=F(u);                 /// evaluación de F(u)
  Array1D< real > v=u;          /// vector auxiliar para calcular las derivadas

  /// CALCULO DE LAS DERIVADAS PARCIALES
  for(int k=0;k<u.dim();k++){
    v[k]=u[k]+h;
    g[k]=(F(v)-F0)/h;
    v[k]=u[k];
  }

  return g;
}


/// CALCULO DEL BENEFICIO (CON SIGNO CAMBIADO) USANDO EL MODELO DE Cobb--Douglas
/// DEVUELVE LA FUNCIÓN QUE SE USA PARA OPTIMIZAR EL BENEFICIO
real mn_beneficio(
Array1D< real > u) /// u[0]=K, u[1]=L, u[2]=M
{
  /// PARÁMETROS DEL MODELO DE Cobb--Douglas
  real a=0.35;
  real b=0.4;
  real c=0.25;
  real d=2.2;
  real r=0.1;

  /// COMPROBAMOS EL TAMAÑO DEL VECTOR
  if(u.dim()!=3) return 1e20;

  /// ASIGNACIÓN DE LOS VALORES K,L,M DEL MODELO DE Cobb--Douglas
  real K=u[0];
  real L=u[1];
  real M=u[2];

  /// K,L,M DEBEN SER MAYORES QUE CERO. EN CASO CONTRARIO
  /// SE DEVUELVE UN VALOR MUY ALTO
  if(K<=0 || L<=0 || M<=0 ) return 1e20;

  /// SE DEVUELVE LA EVALUACIÓN DEL MODELO DE Cobb--Douglas
  return -(d*pow(K,a)*pow(L,b)*pow(M,c)-L-M-r*K)+(K+L+M-30)*(K+L+M-30);
}


/// IMPLEMENTACIÓN DEL MÉTODO DE GRADIENTE DESCENDENTE
/// DEVUELVE EL NÚMERO DE ITERACIONES Y UN NÚMERO NEGATIVO SI ALGO VA MAL
int mn_gradiente_descendente(
real  (*F)(Array1D< real >), /// FUNCIÓN A LA QUE SE APLICA EL MÉTODO
Array1D< real > &u, /// APROXIMACIÓN INICIAL QUE SE VA MEJORANDO
real TOL, /// TOLERANCIA PARA PARAR LAS ITERACIONES
real h, /// PASO FIJO PARA CALCULAR EL VALOR GRADIENTE
int Nmax) /// MÁXIMO NÚMERO DE ITERACIONES
{
  /// HACER ALUMNO

}





