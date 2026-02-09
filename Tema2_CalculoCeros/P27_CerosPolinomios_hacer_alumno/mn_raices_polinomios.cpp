#include "mn_aritmeticas.h"
#include "mn_raices_polinomios.h"

/// *************************************************************************************
///         EVALUACIÓN DE UN POLINOMIO a EN UN PUNTO x
/// *************************************************************************************
real evaluar_polinomio(
Array1D< real > &a /** coeficientes polinomio */,
real x /** valor donde se evalua el polinomio */){
  real Px=0;
  real xk=1;
  for(int k=0;k<a.dim();k++){
    Px+=a[k]*xk;
    xk*=x;
  }
  return Px;
}



/// *************************************************************************************
/// CALCULO DE UNA RAIZ DE UN POLINOMIO EN UN INTERVALO USANDO EL MÉTODO DE LA BISECCIÓN
/// ANTES DE LLAMAR A LA FUNCIÓN SE HA VERIFICADO QUE HAY CAMBIO DE SIGNO
/// SE UTILIZA UN MÉTODO NO-ESTANDAR DISTINTO A LOS EXPLICADOS EN CLASE.
/// *************************************************************************************
real calculo_cero_en_intervalo(
Array1D< real > &a /** coeficientes polinomio */,
real A,real B /** intervalo donde buscar la raíz */,
real TOL /** Tolerancia para el criterio de parada */){
  real step=(B-A)/10;
  while(step>TOL && A<B){
    for(int k=0;k<10 && A<=B;k++){
      real Anew=A+step;
      if(evaluar_polinomio(a,A)*evaluar_polinomio(a,Anew)<=0){
          B=Anew;
          step/=10;
          break;
      }
      A=Anew;
    }
  }
  return (A+B)/2.;
}

/// ****************************************************
///  CALCULO POLINOMIO DERIVADA
///  DEVUELVE UN VECTOR CON EL POLINOMIO DERIVADA
/// ****************************************************
Array1D< real > calcular_derivada_polinomio(
Array1D< real > &a /** coeficientes del polinomio */){

  /// HACER ALUMNO
}


/// *************************************************************************************
///  CALCULO CEROS DE UN POLINOMIO A PARTIR DE LOS CEROS DE SU DERIVADA
///  DEVUELVE UN VECTOR CON LOS CEROS DEL POLINOMIO.
///  UTILIZA LA FUNCIÓN calculo_ceros_en_intervalo() PARA CALCULAR EL CERO EN CADA INTERVALO
///  PARA CONSTRUIR LOS INTERVALOS HAY QUE AÑADIR A LA IZQUIERDA Y LA DERECHA DE LOS CEROS
///  DE LA DERIVADA LOS LÍMITES DONDE ESTÁN TODAS LAS RAÍCES DEL POLINOMIO
/// *************************************************************************************
Array1D< real > ceros_polinomio_desde_ceros_derivada(
Array1D< real > &a /** coeficientes polinomio */,
Array1D< real > &d /** ceros polinomio derivada */,
real TOL){

  /// HACER ALUMNO

}


/// ****************************************************
///  CALCULO RAÍCES REALES DE UN POLINOMIO
///  DEVUELVE UN VECTOR CON LAS RAÍCES ENCONTRADAS
/// ****************************************************
Array1D< real > ceros_polinomio(
Array1D< real > &a /** coeficientes polinomio */,
real TOL /** Tolerancia para el método de cálculo de ceros en un intervalo */){

  /// HACER ALUMNO


}


