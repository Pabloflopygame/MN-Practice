#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mn_ceros_pol_grado_2.h"

int sign(real x) {
    // función externa del alumno.
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

/// FUNCION QUE IMPLEMENTA EL CALCULO DE LAS RAICES DE UN POLINOMIO DE GRADO 2
/// P(x)=ax^2 + bx + c EVITANDO ERRORES DE CANCELACIÓN. DEVUELVE EL NÚMERO DE
/// RAÍCES ENCONTRADAS. LAS RAÍCES SE DEVUELVEN EN LAS VARIABLES x1 Y x2 QUE
/// ENTRAN COMO PARÁMETROS. HAY QUE TENER EN CUENTA TODAS LAS OPCIONES QUE SE
/// PUEDEN DAR CON a=0 y/o b=0
int mn_ceros_pol_grado_2(
real &a, real &b, real &c, /// coeficientes polinomio de grado 2
real &x1,real &x2) /// raíces del polinomio
{
  /// HACER ALUMNO
    // al ser real solo podemos retornar numeros reales
    // por lo que el imaginario lo trataremos como un
    // "no hay raíces reales" (devolvemos 0)
    //
    // para resolverlo usaremos:
    //
    // x1 = (-b + sqrt((b**2)-4*a*c))/(2a)
    // x2 = (-b - sqrt((b**2)-4*a*c))/(2a)
    //
    // el error de cancelación ocurre sobre todo al calcular una de las raíces
    // cuando |b| ~ sqrt((b**2)-4*a*c), porque se restan 2 números muy parecidos.
    //
    // Por esta razón usamos esta ecuación estable:
    //
    // inner_sqr = (b*b) - 4*a*c   (esto es el discriminante D)
    // q = -0.5 * (b + sign(b)*sqrt(inner_sqr))
    // x1 = q/a
    // x2 = c/q
    //
    // De esta manera evitamos la cancelación en (-b ± sqrt(D)).
    // Usamos 0.5 porque 1/2 como enteros daría 0 (división entera).

    // ----- CASO: a == 0 -> NO ES CUADRATICA -----
    if (a == 0) {

        // si a == 0 y b == 0 -> ya no hay x, es c = 0 o c != 0
        if (b == 0) {

            if (c == 0) {
                // a == 0, b == 0, c == 0 -> 0 = 0 (infinitas soluciones)
                x1 = c;   // lo dejo como lo tenías (0)
                x2 = -1;
                return -1;
            } else {
                // a == 0, b == 0, c != 0 -> no tiene solución
                x1 = -1;
                x2 = -1;
                return 0;
            }
        }

        // a == 0, b != 0 -> ecuación lineal: bx + c = 0
        x1 = -c / b;
        x2 = -1;
        return 1;
    }

    // ----- CASO: a != 0 -> ES CUADRATICA -----
    real inner_sqr = (b*b) - 4*a*c;  // discriminante D

    if (inner_sqr < 0) {
        // no hay raíces reales (serían complejas)
        x1 = -1;
        x2 = -1;
        return 0;
    }

    if (inner_sqr == 0) {
        // dos raíces reales iguales (raíz doble) -> el profesor cuenta multiplicidad
        x1 = -b / (2*a);
        x2 = x1;
        return 2;   // <-- antes era 1
    }

    // inner_sqr > 0 -> dos raíces reales
    real raiz = sqrt(inner_sqr);

    // Si b == 0, sign(b) sería 0 y q quedaría mal (q = -0.5*b = 0)
    // Por eso forzamos el signo como +1 cuando b == 0.
    int sb = (b >= 0) ? 1 : -1;

    real q = -0.5 * (b + sb * raiz);

    x1 = q / a;
    x2 = c / q;

    return 2;

    // la validación es que para cada test que nos dió el profesor
    // nuestros resultados son identicos.
}

// De cara al futuro, necesite a chaty que me ayudara con la formula para aprender
// a cancelar errores y al final me tuvo que corregir 3 errores que este tenía.
// Para evitar esto en un examen ve caso a caso y comprueba tu mismo, esto te evita
// tener que hacer debugs de algoritmos enteros (aunque este tema es bastante especial
// ya que es el único en el que no nos dan formulas raw para implementar).
// Pero bueno, paso a paso en este tema para evitar errores.
