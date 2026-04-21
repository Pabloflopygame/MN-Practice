#include "mn_calculo_de_ceros.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
// portatil update
// using namespace std;

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

  // portatil update
  std::cout << "\nalfa = " << alfa << " beta = " << beta << " d = " << d << "\n";

}


/// FUNCION QUE IMPLEMENTA EL METODO DE LA SECANTE
/// LA FUNCIÓN DEVUELVE EL NÚMERO DE ITERACIONES REALIZADAS SI TERMINA BIEN Y DEVUELVE -1
/// EN CASO CONTRARIO
int mn_secante (
real (*f)( real), /// funcion sobre la que se calcula el cero
real &x0, /// primera aproximación raíz que actualiza la función
real &x1, /// segunda aproximación raíz que actualiza la función
int NiterMax, /// número de iteraciones máximo
real TOL) /// tolerancia para para el algoritmo
{
  /// HACER ALUMNO
    // Se parte de una función f(x) y de dos aproximaciones iniciales
    // x0 y x1 de la raíz. AKA no necesitan ningun check al empezar.

    // Se inicia un procedimiento iterativo para ir actualizando x0 y
    // x1 utilizando el nuevo valor x2 dado por la ecuación...

    // las iteraciones paran si la función vale 0 en x1, si la función
    // vale lo mismo en x0 y en x1, si la distancia entre x2 y x1 es
    // pequeña módulo una tolerancia TOL o cuando se excede el
    // número de iteraciones máximo. aka, 3/4 partes lo mismo de siempre.

    real x2;
    real fx0 = f(x0);
    real fx1 = f(x1);
    for (int Niter = 0; Niter <= NiterMax; Niter++){
        // calculamos x2
        x2 = x1 - fx1 * ((x1-x0)/(fx1-fx0));

        // encontramos la raíz
        if (fx1 == 0){
            return Niter;
        }

        // nos quedamos atascados (?)
        if (fx0 == fx1) {
            return -1;
        }

        // ¿Es correcto poner <=?
        // el profe siempre pone <
        // es la forma matemática preferida hacer <
        // formalmente se debe cumplir "Error < TOL".
        if (mn_distancia(x0, x1) < TOL) {
            return Niter;
        }

        // cambio de variables
        x0 = x1;
        x1 = x2;
        // para ahorrar calculos
        fx0 = fx1;
        // esta si se tiene que actualizar.
        fx1 = f(x1);
    }

    return -1;
    // validación es que los gamma de las 2 primeras lineas son 0.01 como el estudio,
    // que los valores son coherentes con la gráfica, el número de iteraciones es
    // normal y Gammap tiende a 0.
}
