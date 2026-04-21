#include "mn_calculo_de_ceros.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
// using namespace std; poratil compatibility

/// PARAMETROS DE LA DISTRIBUCION GAMMA
real alfa,beta,d;

/// DISTRIBUCIÓN GAMMA
real Gamma(real x){
  if(x<0) return 0;
  return d*pow(x,alfa-1.)*exp(-beta*x);
}

/// DERIVADA DE LA DISTRIBUCIÓN GAMMA
real Gammap(real x){
  if(x<0) return 0;
  return d*(alfa-1)*pow(x,alfa-2.)*exp(-beta*x)-d*beta*pow(x,alfa-1.)*exp(-beta*x);
}

/// CALCULO DE LOS PARÁMETROS DE LA DISTRIBUCIÓN GAMMA A PARTIR DE LA
/// MEDIA Y VARIANZA MUESTRAL
void calculo_parametros_Gamma(real media, real varianza){
  /// calculo de alfa y beta
  beta=media/varianza;
  alfa=media*beta;

  /// calculo de d a través de la integral (se verá en el tema 5)
  real h=0.001;
  real suma=0;
  for(real x=0;x<100;x+=h) suma+=h*pow(x,alfa-1.)*exp(-beta*x);
  d=1./suma;

  // portatil compatibility
  std::cout << "\nalfa = " << alfa << " beta = " << beta << " d = " << d << "\n";

}


/// FUNCION QUE IMPLEMENTA EL METODO DE LA REGULA FALSI  Y DEVUELVE EL NÚMERO DE ITERACIONES
/// SI ALGO VA MAL DEVUELVE -1.  LA RAÍZ SE DEVUELVE COMO PARÁMETRO
int mn_regula_falsi (
real (*f)( real), /// función a la cual se calcula un cero
real &a, real &b, /// intervalo inicial para buscar la raíz
real &x, /// valor de salida de la raíz
real TOL,  /// tolerancia para parar las iteraciones del algoritmo
int NiterMax) /// número máximo de iteraciones permitidas
{
  /// HACER ALUMNO
    // Igual que la bissección lo que ahora usamos una recta para calcular el punto medio.

    // f(A) y f(B) deben tener signos opuestos si no es el caso no podemos usarlos.
    if (f(a) * f(b) > 0) {
        return -1;
    }

    // caso que f(a) o f(b) sean raiz:
    int Niter = 0;
    if (f(a) == 0) {
        x = a;
        return Niter;
    }
    if (f(b) == 0) {
        x = b;
        return Niter;
    }

    // aquí iteramos hasta que el intervalo [a,b] tenga
    // la tolerancia deseada (cuando sea <= termina).
    real middle_point;
    while(mn_distancia(fabs(a),fabs(b)) > TOL) {
        // realmente esto es una recta que parte de a hasta b
        // intersecta con el eje x y ese punto es el nuevo divisor.
        // lo que lo resumimos en una única fórmula.
        middle_point = a - ((b-a)/(f(b)-f(a)))*f(a);
        // quiren retornar el valor por aquí
        x = middle_point;

        // si encontramos la raiz retornamos.
        if (f(middle_point) == 0) {
            return Niter;
        }

        // miramos si a y el nuevo punto mantienen != signo.
        // caso que no, será b el que lo mantenga.
        if (f(middle_point) * f(a) < 0){
            b = middle_point;
        } else{
            a = middle_point;
        }

        if(Niter == NiterMax){
            // si nos quedamos sin iteraciones este es el punto
            // mas cercano al que llegamos.
            return Niter;
        }

        Niter++;
    }

    // cuando hemos alcanzado nuestra presición retornamos el
    // último punto medio calculado.
    return Niter;
    // la verificación es que los valores son coherentes con la tabla:
    // Los gamma están en 0.01 como hace en el trabajo estadístico,
    // los resultados son lógicos con la tabla (máximo en 5 con densidad 11%,
    // 99% de los infectados caen en ~[0, 17] y Gammap que es como un "error"
    // es prácticamente 0).
}



