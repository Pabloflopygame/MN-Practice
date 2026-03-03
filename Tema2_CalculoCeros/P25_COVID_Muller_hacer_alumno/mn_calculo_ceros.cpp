#include "mn_calculo_de_ceros.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
// portatil update
//using namespace std;

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

/// FUNCION QUE IMPLEMENTA EL CALCULO DE LAS RAICES DE UN POLINOMIO DE GRADO 2
/// DEVUELVE EL NÚMERO DE RAÍCES OBTENIDAS
/// LAS RAÍCES SALEN ORDENADAS POR VALOR ABSOLUTO. ES DECIR |x1|<=|x2|
int mn_ceros_pol_grado_2(
real a, real b, real c, // coeficientes polinomio de grado 2
real &x1, // primera raíz
real &x2) // segunda raíz
{
  if(a==0.) return(0);
  real dis=b*b-4*a*c;
  if(dis<0.) return(0);
  else if(dis==0.){
    x1=-b/(2*a);
    return(1);
  }
  dis=sqrt(dis);
  if(b>0){
    x1=(-b+dis)/(2*a);
    x2=(-b-dis)/(2*a);
  }
  else{
    x1=(-b-dis)/(2*a);
    x2=(-b+dis)/(2*a);
  }
  return(2);
}

/// FUNCION QUE IMPLEMENTA EL METODO DE MULLER USANDO UNA APROXIMACIÓN DE LAS DERIVADAS
/// LA FUNCIÓN DEVUELVE EL NÚMERO DE ITERACIONES REALIZADAS SI TERMINA BIEN Y DEVUELVE -1
/// EN CASO CONTRARIO
int mn_muller (
real (*f)( real), /// funcion sobre la que se calcula el cero
real &x0, /// raíz inicial que actualiza la función
int NiterMax, /// número de iteraciones máximo
real TOL) /// tolerancia para parar el algoritmo
{
  /// HACER ALUMNO
    // Se parte de una función f(x) y de una aproximación inicial x0
    // de la raíz. AKA ningun initial check fancy.
    //
    // Se inicia un procedimiento iterativo para ir actualizando x0
    // utilizando el nuevo valor x1 la raíz más cercana a x0 del polinomio
    // dado por la ecuación (2.11).
    //
    // Las iteraciones paran si la función vale 0 en x0, si el polinomio
    // de la ecuación (2.11) no tiene raíces realeas, si la distancia
    // entre x1 y x0 es pequeña módulo una tolerancia TOL o cuando
    // se excede el número de iteraciones máximo.
    // AKA 3/4 partes lo mismo de siempre.

    real fx0 = f(x0);
    real f1x0 = mn_derivada1(f, x0);
    real f2x0 = mn_derivada2(f, x0);
    real inside_square_root = sqrt((f1x0*f1x0)-2*fx0*f2x0);
    // resultados imaginarios.
    if (std::isnan(inside_square_root)) {
        return -1;
    }
    real x1;
    real x1pos = x0 + (-f1x0+inside_square_root)/f2x0;
    real x1neg = x0 + (-f1x0-inside_square_root)/f2x0;
    for(int Niter = 0; Niter <= NiterMax; Niter++) {
        // si x0 es raíz terminamos
        if (fx0 == 0) {
            return Niter;
        }

        // nos quedamos con el más cercano de x1.
        if (mn_distancia(x0, x1pos) < mn_distancia(x0, x1neg)){
            x1 = x1pos;
        } else{
            x1 = x1neg;
        }

        // si encontramos la tolerancia
        if (mn_distancia(x0, x1) < TOL) {
            return Niter;
        }

        // updateamos x0
        x0 = x1;

        // para ahorrar calculos
        fx0 = f(x0);
        f1x0 = mn_derivada1(f, x0);
        f2x0 = mn_derivada2(f, x0);
        inside_square_root = sqrt((f1x0*f1x0)-2*fx0*f2x0);
        // resultados imaginarios (si sqrt < 0 y retorna NAN).
        // otra opción es simplemente calcular su interior y verificar
        // que es >= 0 antes de mandarla al sqrt().
        if (std::isnan(inside_square_root)) {
            return -1;
        }
        // calculo de los 2 x1.
        x1pos = x0 + (-f1x0+inside_square_root)/f2x0;
        x1neg = x0 + (-f1x0-inside_square_root)/f2x0;
    }

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

/// APROXIMACIÓN DERIVADA SEGUNDA DE UNA FUNCIÓN
real mn_derivada2(
real (*f)( real), /// función que se deriva
real x) /// punto donde se evalúa la derivada primera
{
   /// CALCULO DE LA RAIZ CUADRADA DE LA UNIDAD DE REDONDEO u
   static real sqrt_u = sqrt( (double) mn_precision_aritmetica());

   /// CALCULO DESPLAZAMIENTO DE x PARA CALCULAR LA DERIVADA
   /// NOS ALEJAMOS DE x CON LA MITAD DE BITS QUE PERMITE LA ARITMÉTICA
   real h=(mn_abs(x)+1.)*sqrt_u;

   return (f(x+h)+f(x-h)-2*f(x))/(h*h);

}
