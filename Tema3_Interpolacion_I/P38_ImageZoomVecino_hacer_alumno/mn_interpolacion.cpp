#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"
// #include <math.h> no hace falta y lo añadí

/// FUNCIÓN PARA CALCULAR UN ZOOM DE FACTOR z A UN Array2D< real >
/// USANDO INTERPOLACIÓN POR EL VECINO MÁS CERCANO
/// SE CONSIDERA QUE LA DISTANCIA ENTRE LOS PIXELS DEL Array2D ES 1
/// DADO UN PUNTO EN LA IMAGEN DE ÍNDICES (i,j) SI AL ACCEDER AL
/// PUNTO (i+1,j) NOS SALIMOS DE LA IMAGEN, TOMAMOS EN SU LUGAR EL PUNTO (i,j)
/// LO MISMO SI NOS SALIMOS AL ACCEDER A (i,j+1) O (i+1,j+1)
Array2D< real > zoom_vecino(
Array2D< real > &A /** IMAGEN ORIGINAL */,
real z /** FACTOR DE ZOOM */)
{
  /// HACER ALUMNO
    // Btw recuerda que A no es más que una matríz 2D con valores entre 0 y 1. Nada fancy.
    // Es en blanco y negro por sencillez.

    // Casos extremos (si no los pones quitan puntos).
    // Eliminamos dimensiones inválidas (negativas o 0)
    if (z*A.dim1()*z*A.dim2() <= 0) {
        return Array2D<real>();
    }

    // Se construye una matriz F′ de dimensiones (z · dim1) × (z · dim2).
    Array2D<real> F(z*A.dim1(), z*A.dim2());

    // Se recorren todos los puntos (i′, j′) de la nueva matriz.
    // Para cada (i′, j′) se calcula en precisión real el punto (x, y) = (i′/z, j′/z).
    // * ip = i'; jp = j'

    // Declaramos las variables a usar en el loop
    real x;
    real y;
    int i;
    int j;

    // iteramos por cada pixel de la nueva imagen.
    for (int ip = 0; ip < F.dim1(); ip++){
        for (int jp = 0; jp < F.dim2(); jp++){

            // posición relativa a la matriz original.
            x = ip/z;
            y = jp/z;

            // Se calculan los enteros i = x, j = y (al almacenar una variable real en
            // una entera se produce un truncamiento al eliminar los decimales.)
            // eliminamos los reales y redondeamos
            // Se calcula que punto está más cerca de (x, y) en la cuadrícula (i, j),
            // (i + 1, j), (i, j + 1) y (i + 1, j + 1) y se asigna a la nueva imagen el
            // valor de F en dicho punto.

            // en una cuadrícula regular de paso 1, el vecino más cercano
            // se obtiene redondeando las coordenadas (x,y)!!!
            int i = round(x);
            int j = round(y);
            // PREGUNTA A CHATY SI EL TRUCO DE ROUND ESTA EN EL MANUAL!!!!

            // comprobamos que no nos salgamos de la matriz original
            // (puede ocurrir en los bordes al hacer el redondeo)
            if(i >= A.dim1()) i = A.dim1() - 1;
            if(j >= A.dim2()) j = A.dim2() - 1;

            // asignamos el valor del vecino más cercano
            // en la nueva imagen
            F[ip][jp] = A[i][j];

            // Primera forma que resolví que era ineficiente y te quitaría puntos.
            // La forma correcta era ver que el round te dice el más cercano
            // pero te puede sacar de la matríz (solucionar con un -1 si pasa)
            // y ya con todo checkeado y regulado si hace falta se asigna y listo.
            // Te ahorras tener que hacer calculos de distancias.
            /*
            // default case that never fails
            int best_i = i;
            int best_j = j;

            // distancia entre 2 puntos (comentarios que debes añadir como los otros).
            real score = sqrt((x-i)*(x-i) + (y-j)*(y-j));

            // Si el punto más cercano cae fuera de la matriz se toma el punto dentro
            // de la matriz más cercano.

            // caso (i+1, j)
            if (i+1 < A.dim1()) {
                real new_score = sqrt((x-(i+1))*(x-(i+1)) + (y-j)*(y-j));
                if (new_score < score) {
                    score = new_score;
                    best_i = i+1;
                    best_j = j;
                }
            }

            // caso (i, j+1)
            if (j+1 < A.dim2()) {
                real new_score = sqrt((x-i)*(x-i) + (y-(j+1))*(y-(j+1)));
                if (new_score < score) {
                    score = new_score;
                    best_i = i;
                    best_j = j+1;
                }
            }

            // caso (i+1, j+1)
            if ((i+1 < A.dim1()) && (j+1 < A.dim2())) {
                real new_score = sqrt((x-(i+1))*(x-(i+1)) + (y-(j+1))*(y-(j+1)));
                if (new_score < score) {
                    score = new_score;
                    best_i = i+1;
                    best_j = j+1;
                }
            }

            // asignamos el valor del punto más cercano a la nueva imagen
            F[ip][jp] = A[best_i][best_j];
            */
        }
    }

    // Se termina el proceso iterativo.
    return F;

    // En el main estamos quitando a 1/16 y después a x16, por lo que mantiene la
    // dimensión original pero con mucha menos resolución.
    // También hay un test donde simplemente le hacen un x3 y se puede ver que
    // la resolución es mayor y se sigue preservando buena calidad en rasgos generales
    // (si se hace zoom en la versión maximizada se vé que no tiene mucho detalle).

    // Esto es lo que deberíamos esperar ver (tienes que abrirlo en paint, otros programas fallan).
    // Comparando de lado a lado ayuda a ver.
    //
    // Recuerda sacar captura a tu código para que no lo puedan tocar y la validación va en el
    // word, no es explicar el método, es explicar el resultado que vemos, aka una imagen pixelada
    // y porque tiene sentido que eliminar datos hace eso (cambia de main a main y apartado a apartado).
    // Se entrega en word o pdf (depende lo que el ordenador permita).
    //
    // En este programa si se ejecuta bien sale error 0 (en la pantalla no en el log).
}
