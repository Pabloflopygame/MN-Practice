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
  for(int k=0;k<a.dim();k++){   // nos pasan el polinomio de menor
    Px+=a[k]*xk;                // a mayor (a[0] es x**0 a[n] es x**n).
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
    // P(x)=a0​+a1​x+a2​x2+⋯+an​xn --> P(x)=a0​+x(a1​+x(a2​+⋯+xan​))
    // P(x0​)=b0​ --> P′(x0​)=c1​
    // aka, este algoritmo reorganiza el polinomio y calcula
    // simultaneamente P(x0​) y P′(x0​) (que es util en algunos campos).
    //
    // Del libro:
    // Descripción algoritmo para evaluar un polinomio P(x) de grado n
    // y su derivada P′(x) usando el algoritmo de Horner. La evaluación
    // se guarda en las variables b=P(x) y c=P′(x).
    //
    // (lo de arriba es el enunciado)
    //
    // Se inicializa b = an y c = an. (lás más altas)
    //
    // Hacemos un proceso iterativo desde n-1 hasta 1 y vamos actualizando
    // b y c de acuerdo con las ecuaciones (2.17) y (2.18).
    //
    // bk = ak + bk+1x0 con bn = an, k = n − 1, .., 0, (2.17)
    // ck = bk + ck+1x0 con cn = an, k = n − 1, .., 1 (2.18)
    //
    // Al terminar el bucle actualizamos b usando la ecuación (2.17) con k = 0.
    //
    //
    // Vamos que ahora con el libro puedes hacerlo sin problema ^^.


    int n = a.dim() - 1;   // grado del polinomio
    Px=a[n];
    PPx=a[n];
    for(int k=n-1;k>0;k--){
        Px=Px*x+a[k]; // bk​=ak​+bk+1​x
        PPx=PPx*x+Px; // ck​=bk​+ck+1​x
    }
    Px=Px*x+a[0];
    // la verificación es correcta ya que los resultados del test
    // y el nuestro son iguales. A su vez el tiempo de ejecución
    // es coherente
}

/// ****************************************************
///  CALCULO POLINOMIO DERIVADA
///  DEVUELVE UN VECTOR CON EL POLINOMIO DERIVADA
/// ****************************************************
Array1D< real > mn_calcular_derivada_polinomio(
Array1D< real > &a /** coeficientes del polinomio */){
  /// HACER ALUMNO
    // no se usa en el ejercicio anterior, simplemente es un extra.
    // evitar calculos extras.
    int a_size = a.dim();

    // casos base:
    if (a_size == 0) {
        Array1D<real> result(0);
        return result;
    }
    if (a_size == 1) {
        Array1D<real> result(1);
        a[0] = 0;
        return result;
    }

    // casos generales:
    // esta en el orden correcto al ser de tamaño -1.
    Array1D<real> result(a_size-1);
    // empezamos en 1 porque el primer término de a queda a 0.
    for(int k=1;k<a_size;k++){
        result[k-1] = a[k]*(k);
    }

    return result;
}





