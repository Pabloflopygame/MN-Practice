#include "mn_calculo_de_ceros.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
// using namespace std; <-- comentamos porque causa fallas de compilación

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

  // añadimos std:: para que mantenga el código como era.
  std::cout << "\nalfa = " << alfa << " beta = " << beta << " d = " << d << "\n";

}


/// FUNCION QUE IMPLEMENTA EL METODO DE LA BISECCION
real mn_biseccion (
real (*f)(const real), /// función a la cual se calcula un cero
real &a, real &b, /// intervalo inicial para buscar la raíz
const real TOL,  /// tolerancia para parar las iteraciones del algoritmo
int &Niter) /// número de iteraciones realizadas por el método
            ///       Si Niter=-1 la función ha terminado mal
{
  /// HACER ALUMNO
    // como este es el primer ejercicio de este tema primero vamos al libro
    // donde están todos los algoritmos, guardamos el que nos piden hacer y
    // buscamos el método de verificación para poder ser capaz de leerlo correctamente.
    // Para este caso el metodo de verificación es una aplicación en un estudio de
    // transmición vírica explicado en el apartado 2.8
    //
    // En la gráfica podemos ver claramente una distribución de casos por el tiempo.
    // se nos va a evaluar en una formula que después van a igualar a 0.
    // Cambiando esa función ( (ax**(b))*(e**c)-0.01 = 0 ) pueden calcular diversas cosas.
    // Mirando el main, calculan primero cuando b es la media, cuando b es 20 y el máximo.
    //
    // Con todo esto ellos pueden respectivamente calcular:
    // La mayor parte de infectados que presenta sintomas, lo hace entre los dias ...
    // La media de dias que se tarda en presentar sintomas es ...
    // El dia que es mas probable presentar sintomas es...
    //
    // Todo esto con percentil de 0.01 = 1%. Por lo que mirando a la tabla visualmente es
    // - El profesor calculo que entre el día 0 y 16.902 es donde la gran mayoría de infecciones ocurren.
    // - La media que se tarda es alrededor de 4-7.
    // - El día mas probable de presentar síntomas
    //      (¡Mirando las curva no las lineas!) es el 5.
    //
    // Respaldalo con las solucciones correctas del profesor!!!


    // Ahora con todo esto hecho el método es bastante sencillo:
    // Se parte de una función f(x) y de un intervalo [a, b] donde la función cambia de signo.
    //
    // Se inicia un procedimiento iterativo donde se va actualizando el intervalo [a, b] partiendo
    // el intervalo en dos mitades y quedándonos con la mitad que mantiene el cambio de signo.
    //
    // Las iteraciones paran cuando la función vale cero en el punto medio del intervalo o
    // cuando el tamaño del intervalo es muy pequeño módulo una tolerancia TOL.

    // f(A) y f(B) deben tener signos opuestos si no es el caso no podemos usarlos.
    if (f(a) * f(b) > 0) {
        Niter = -1;
        return -1;
    }

    // caso que f(a) o f(b) sean raiz_
    Niter = 0;
    if (f(a) == 0) {
        return f(a);
    }
    if (f(b) == 0) {
        return f(b);
    }

    // aquí iteramos hasta que el intervalo [a,b] tenga
    // la tolerancia deseada (cuando sea <= termina).
    real middle_point;
    // ojo tolerancia del intervalo, no de f(a) y f(b).
    // también a mencionar la simplicidad de usar distancia.
    while(mn_distancia(fabs(a),fabs(b)) > TOL) {
        // dividimos el intervalo con la mitad.
        // (nos aseguramos que la divsión sea con float;
        // usando el .0 en 2.0).
        middle_point = (a+b)/2.0;

        // si encontramos la raiz retornamos.
        if (f(middle_point) == 0) {
            return middle_point;
        }

        // miramos si a y el nuevo punto mantienen != signo.
        // caso que no, será b el que lo mantenga.
        if (f(middle_point) * f(a) < 0){
            b = middle_point;
        } else{
            a = middle_point;
        }

        Niter++;
    }

    // cuando hemos alcanzado nuestra presición retornamos el
    // último punto medio calculado.
    return middle_point;
    // Biseccion: x0 = 0.662633 , N. iteraciones = 29 , Gamma(x0) = 0.01
    // Biseccion: x1 = 16.9024 , N. iteraciones = 27 , Gamma(x1) = 0.01
    // Biseccion: xmax = 5.01384 , N. iteraciones = 29 , Gamma(xmax) = 0.110158,
                                                        // Gammap(xmax) = 2.45607e-10
    //
    // En la primera linea calculamos x0, que es el intervalo
    // inferior donde el 99% de la gente presenta sintomas.
    // Durante esta primera linea vemos que está en 0.66 (coherente ya que el día 0 en
    // la gráfica apenas hay nadie con sintomas). Lo hace en un número normal de
    // iteraciones y el gamma retornado es de 0.01, es decir que calculamos al 99% de
    // presición como quería el profesor en el estudio, el calculo gamma a 0.01.
    //
    // En la segunda linea hacemos lo mismo que la primera pero ahora en el intervalo superior.
    // Igual que antes todo dentro de los resultados esperables.
    // Ahora con las 2 si podemos mirar a la gráfica y corroborar que entre ~[0, 17] se
    // encuentran 99% de los infectados.
    //
    // En la tercera queremos calcular el día más probable de tener síntomas, que en la tabla
    // es ~5. Aquí vemos que lo clava perfectamente y Gammap que representa al error es
    // prácticamente 0. Ahora, gamma del máximo aquí representa la altura del máximo,
    // dicho de manera simple, la probabilidad que te puedas poner malo ese día.
    // 11% tiene sentido comparando con otros días, es un valor coherente.
    //
    //
    // Biseccion: x0 = 0.662633 , N. iteraciones = 29 , Gamma(x0) = 0.01
    // Biseccion: x1 = 16.9024 , N. iteraciones = 27 , Gamma(x1) = 0.01
    // Biseccion: xmax = 5.01384 , N. iteraciones = 29 , Gamma(xmax) = 0.110158,
                                                        // Gammap(xmax) = -5.15451e-11
    // Estos son los resultados del profe, casi igual que el tuyo, vas perfe.
    // el resultado de gammap es más por redondeo que por presición real.
    // De nuevo, vas perfe, te da igual y si no prácticamente igual.
}



