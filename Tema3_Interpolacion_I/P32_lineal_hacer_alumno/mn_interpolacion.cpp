#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/// INTERPOLACION LINEAL
real mn_interpolacion_lineal(
Array1D<real> &x, /// puntos de interpolación
Array1D<real> &f, /// valores de función en los puntos de interpolación
real x0)  /// punto donde se evalua la función interpolada
{
  /// HACER ALUMNO
    // Casos exepcionales.
    int sizex = x.dim1();
    int sizef = f.dim1();
    // inputs inválidos:
    // vacios (facilmente puede ocurrir)
    // negativos, no tiene sentido en nuestro uso,
    // pero es por si modifican cosas avanzadas de c++.
    //
    // *Los juntamos en 1 para evitar un if de "vacios" y otro de "negativos".
    if ((sizex <= 0) || (sizef <= 0)) {
        return -1;
    }
    // dimensiones diferentes
    if (sizex != sizef) {
        return -1;
    }

    // casos extremos
    // extrema izquierda (se toma primer intervalo)
    if (x0 <= x[0]) {
        return f[0] + ((f[0+1] - f[0])/(x[0+1] - x[0]))*(x0-x[0]);;
    }
    // extrema derecha (se toma último intervalo)
    if (x0 >= x[sizex-1]) {
        return f[sizex-2] + ((f[sizex-1] - f[sizex-2])/(x[sizex-1] - x[sizex-2]))*(x0-x[sizex-2]);;
    }

    // Casos normales.
    // Vamos a recorrer de izquierda a derecha.
    // x[0]-x[1] / x[1]-x[2] / ... / x[n-1] - x[n]
    // y ver cual contiene a x0.
    for(int i=0; i < sizex-1; i++){
        // si está entre el intervalo calculamos la recta
        if ((x0 >= x[i]) && (x0 <= x[i+1])) {
            // comprobamos si tenemos el valor exacto antes de interpolar.
            // lo hacemos dentro del intervalo para evitar operaciones inecesarias del loop.
            if (x0 == x[i]){
                return f[i];
            }
            if (x0 == x[i+1]){
                return f[i+1];
            }

            // aquí para simplificar simplemente vamos a usar la formula
            // que calcula la recta y a su vez calcula el punto para esta.
            // Pi(x) = f(xi) + ((f(xi+1) − f(xi))/(xi+1 − xi)) * (x−xi).

            return f[i] + ((f[i+1] - f[i])/(x[i+1] - x[i]))*(x0-x[i]);
        }
    }

    // caso de error no esperado;
    // Probablemente x no esté ordenado.
    // si f no está ordenado retornaría un valor (aunque incorrecto), no llegaría a -1
    // es x el que causa que el recorrido falle y pueda llegar aquí.
    return -1;
    // En esta verificación aparte de lo de epidemeología que lo hemos mencionado en ejercicios anteriores
    // lo han aplicado en un vector de 4 puntos y han interpolado para añadir más definición.
    // con este método esperamos lo que hacemos, crear montón de puntos intermedios.
    // Muy buena herramienta si lo que queremos hacer es subdividir un segmento y usada en trabajos vectoriales!
    // exactamente lo que esperamos y con una utilidad muy real.
    //
    // Ha mencionar el proceso de creación tiene que retornar 0 para que se haya hecho de forma correcta.
    // a su vez el tiempo debe ser lógico, 0.08 segundos es esperable (algo lento, pero esperable al tener
    // leer y escribir de disco en ficheros).
}



