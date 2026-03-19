#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/// INTERPOLACION VECINO
real mn_interpolacion_vecino(
Array1D<real> &x, /// puntos de interpolación
Array1D<real> &f, /// valores de función en los puntos de interpolación
real x0)  /// punto donde se evalua la función interpolada
{
  /// HACER ALUMNO
    /// Recordemos que programamos usando ingles por las limitaciones de
    /// variables al no poder usar ñ o tildes, pero comentaremos en Español.

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
    // Se podría descartar el de la derecha y ponerlo al final del bucle,
    // pero nos dejaría abiertos a errores de falta de ordenación y no retornar
    // un código de error a su vez que sería lento eficientemente hablando O(n)
    // para un caso extremo sin ninguna necesidad.
    // extrema izquierda
    if (x0 <= x[0]) {
        return f[0];
    }
    // extrema derecha
    if (x0 >= x[sizex-1]) {
        return f[sizef-1];
    }

    // Casos normales.
    // Vamos a recorrer de izquierda a derecha.
    // x[0]-x[1] / x[1]-x[2] / ... / x[n-1] - x[n]
    // y ver cual contiene a x0.
    for(int i=0; i < sizex-1; i++){
        // si está entre el intervalo lo aproximamos al más cercano.
        if ((x0 >= x[i]) && (x0 <= x[i+1])) {
            // no usamos mn_distancia porque tiene problemas cuando el valor es central.
            // al normalizar en esa función se pierde precición y genera ruido decimal.
            real distance_left = fabs(x[i]-x0);
            real distance_right = fabs(x0-x[i+1]);

            // aquí sientanse libres de quitar o dejar el = para la política que deseén.
            // actualmente acotamos a la izquierda en caso de estar en el medio
            // (para que encaje con los resultados calculados en la verificación).
            if (distance_left <= distance_right) {
                return f[i];
            } else{
                return f[i+1];
            }
        }
    }

    // caso de error no esperado;
    // Probablemente x no esté ordenado.
    return -1;
    // en 3.7 explica la verificación con el estudio (contexto) en el que se usa.
    // en este caso se nos simplifica considerablemente ya que el main tiene precalculados
    // las interpolaciones con este métodos guardados y simplemente estamos comparando.
    // Pero el contexto es meramente ver el numero de fallecimientos por grupo de edad, que si
    // miramos en la gráfica real vemos que está en valores razonables dado a como es el algoritmo.
    //
    // *Recuerda que en el examen esto sobra, porque iría en el documento. Esto lo pongo para estudiar.
}



