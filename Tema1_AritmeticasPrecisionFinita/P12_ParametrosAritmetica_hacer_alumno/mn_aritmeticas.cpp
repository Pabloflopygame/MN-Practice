///*========================================================================
///  FUNCIONES PARA EL MANEJO DE ARITMETICAS DE PRECISION FINITA
///  ======================================================================== */

/// INCLUSION DE LA LIBRERIA PARA GESTIONAR LA ARITMETICA
#include "mn_aritmeticas.h"
#include <iostream>
using namespace std;

/// FUNCION PARA CALCULAR LA PRECISION (UNIDAD DE REDONDEO) DE LA ARITMETICA
real mn_precision_aritmetica()
{
  /// HACER ALUMNO

}

/// FUNCION PARA CALCULAR EL MENOR NUMERO POSITIVO
int mn_menor_numero_positivo()
{
    /// HACER ALUMNO

}

/// FUNCION PARA CALCULAR EL MAYOR NUMERO POSITIVO
int mn_mayor_numero_positivo()
{
    /// HACER ALUMNO

}

/// FUNCION PARA CALCULAR LA DISTANCIA RELATIVA ENTRE 2 NUMEROS REALES
real mn_distancia(real A,real B)
{
  /// HACER ALUMNO
  /// PARA CALCULAR LA DISTANCIA SE DEBE UTILIZAR LA FÓRMULA |B-A|/( max(|A|,|B|)+1. )
  /// PARA CALCULAR EL VALOR ABSOLUTO SE PUEDE UTILIZAR LA MACRO mn_abs(x)
  /// PARA CALCULAR EL MÁXIMO DE 2 NÚMEROS SE PUEDE UTILIZAR LA MACRO mn_max(A,B)
  return( mn_abs(B-A) / ( mn_max(mn_abs(A),mn_abs(B)) + 1. ) );
}

