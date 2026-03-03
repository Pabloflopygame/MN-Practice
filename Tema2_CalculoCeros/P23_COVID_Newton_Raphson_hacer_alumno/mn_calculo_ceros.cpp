#include "mn_calculo_de_ceros.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
// using namespace std; portatil update

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

  // portatil update con std::
  std::cout << "\nalfa = " << alfa << " beta = " << beta << " d = " << d << "\n";

}

/// FUNCION QUE IMPLEMENTA EL METODO DE NEWTON-RAPHSON APROXIMANDO LA FUNCION DERIVADA
/// LA FUNCIÓN DEVUELVE EL NÚMERO DE ITERACIONES REALIZADAS SI TERMINA BIEN Y DEVUELVE -1
/// EN CASO CONTRARIO
int mn_newton_raphson (
real (*f)( real), /// funcion sobre la que se calcula el cero
real &x0, /// raíz inicial que actualiza la función
int NiterMax, /// número de iteraciones máximo
real TOL) /// tolerancia para parar el algoritmo
{
  /// HACER ALUMNO
    // Se parte de una función f(x) y de una aproximación inicial x0
    // de la raíz. AKA no tenemos que hacer ningún validity check.

    // Se inicia un procedimiento iterativo para ir actualizando x0
    // utilizando el nuevo valor x1 dado por la ecuación (2.8).

    // Las iteraciones paran si la función vale 0 en x0, si la derivada
    // de la función vale 0 en x0, si la distancia entre x1 y x0 es
    // pequeña módulo una tolerancia T OL o cuando se excede el
    // número de iteraciones máximo.
    real x1;
    real derivada;
    real fx0;
    for (int Niter = 0; Niter <= NiterMax; Niter++){
        // Esto es para ahorrar calculos, dicho por el profesor.
        derivada = mn_derivada1(f, x0);
        fx0 = f(x0);

        if (fx0 == 0) {
            // encontramos la raíz
            return Niter;
        }

        if (derivada == 0) {
            // encontramos un valle y nos atascamos en este algoritmo.
            return -1;
        }

        // la función 2.8 dicha.
        // además si retornamos en el siguiente if
        // ya le pasamos la mejor aproximación (x1).
        x1 = x0 - fx0/derivada;

        // si llegamos a la tolerancia adecuada retornamos.
        if (mn_distancia(x0, x1) < TOL) {
            return Niter;
        }

        // nos quedamos con el nuevo valor
        x0 = x1;
    }

    // nos pasamos de las iteraciones
    return -1;
    // validación es que los gamma de las 2 primeras lineas son 0.01 como el estudio,
    // que los valores son coherentes con la gráfica, el número de iteraciones es
    // normal y Gammap tiende a 0.
}



/// APROXIMACIÓN DERIVADA PRIMERA DE UNA FUNCIÓN
real mn_derivada1(
real (*f)( real), /// función que se deriva
real x) /// punto donde se evalúa la derivada primera
{
   /// CALCULO DE LA RAIZ CUADRADA DE LA UNIDAD DE REDONDEO u
   static real sqrt_u = sqrt( (double) mn_precision_aritmetica());

   /// CALCULO DESPLAZAMIENTO DE x PARA CALCULAR LA DERIVADA
   /// NOS ALEJAMOS DE x CON LA MITAD DE BITS QUE PERMITE LA ARITMÉTICA
   real h=(mn_abs(x)+1.)*sqrt_u;

   return (f(x+h)-f(x-h))/(2.*h);

}
