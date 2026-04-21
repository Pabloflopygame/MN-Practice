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
    real number = 1;

    // mientras el ordenador pueda diferenciarlo de 1 dividelo entre 2.
    // existen otras formulas pero estas es de las más fáciles.
    while ((1 + number) > 1){
        number = number / 2.0;
    }

    // retorna al numero anterior al que dejo de ser diferenciable
    return number * 2;

    // validación, nos retorna el mismo valor que el double, por lo que
    // podemos asumir que el real usa double (y se puede verificar que es el caso
    // en la declaración de real) al tener la misma definición.
}

/// FUNCION PARA CALCULAR EL MENOR NUMERO POSITIVO
int mn_menor_numero_positivo()
{
    /// HACER ALUMNO
    // aquí estamos calculando el 2**M que siga siendo > 0.
    // como es float el más pequeño debe ser potencia de 2.
    // Empezamos en 1 y bajamos hasta llegar a underoflow.

    real x = 1.0;
    int M = 0;

    // Queremos el menor 2^M tal que todavía sea > 0
    while ((x / 2.0) > 0.0)
    {
        x /= 2.0; // no es más que hacer 2**-1
        ++M; // guardamos -1 (lo que en positivo porque al hacer el print lo quiere así)
    }

    return M;
    // la verificación es que el exponente sea el mismo
}

/// FUNCION PARA CALCULAR EL MAYOR NUMERO POSITIVO
int mn_mayor_numero_positivo()
{
    real A = 1.0;
    int M = 0;

    while (true)
    {
        real siguiente = A * 2.0;

        // Si al "deshacer" no vuelves a A, es que hubo overflow (o algo raro).
        // truco barato pero funciona
        if ((siguiente / 2.0) != A)
            break;

        A = siguiente;
        ++M;
    }

    return M;
    // la verificación es que el exponente sea el mismo
}

/// FUNCION PARA CALCULAR LA DISTANCIA RELATIVA ENTRE 2 NUMEROS REALES
real mn_distancia(real A,real B)
{
  /// HACER ALUMNO
  /// PARA CALCULAR LA DISTANCIA SE DEBE UTILIZAR LA FÓRMULA |B-A|/( max(|A|,|B|)+1. )
  /// PARA CALCULAR EL VALOR ABSOLUTO SE PUEDE UTILIZAR LA MACRO mn_abs(x)
  /// PARA CALCULAR EL MÁXIMO DE 2 NÚMEROS SE PUEDE UTILIZAR LA MACRO mn_max(A,B)
  return( mn_abs(B-A) / ( mn_max(mn_abs(A),mn_abs(B)) + 1. ) );

  // la llegó hecha y su verificación encaja con el valor calculado por el profesor.
}

