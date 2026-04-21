#include "mn_aritmeticas.h"
#include "mn_PolinomiosHorner.h"

/// *************************************************************************************
///         EVALUACIÓN DE UN POLINOMIO a EN UN PUNTO x
/// *************************************************************************************
real mn_evaluar_polinomio(
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
///  EVALUACIÓN DE UN POLINOMIO Y SU DERIVADA POR EL MÉTODO DE HORNER
/// *************************************************************************************
void mn_evaluar_polinomio_horner(
Array1D< real > &a /** coeficientes polinomio */,
real x /** valor donde se evalua el polinomio */,
real &Px /** evaluación del polinomio en x*/,
real &PPx /** evaluación de la derivada del polinomio en x*/){
  /// HACER ALUMNO

}

/// ****************************************************
///  CALCULO POLINOMIO DERIVADA
///  DEVUELVE UN VECTOR CON EL POLINOMIO DERIVADA
/// ****************************************************
Array1D< real > mn_calcular_derivada_polinomio(
Array1D< real > &a /** coeficientes del polinomio */){
  /// HACER ALUMNO

}





