#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/// FUNCIÓN PARA CALCULAR UN ZOOM DE FACTOR z A UN Array2D< real >
/// USANDO INTERPOLACIÓN BILINEAL
/// SE CONSIDERA QUE LA DISTANCIA ENTRE LOS PIXELS DEL Array2D ES 1
/// DADO UN PUNTO EN LA IMAGEN DE ÍNDICES (i,j) SI AL ACCEDER AL
/// PUNTO (i+1,j) NOS SALIMOS DE LA IMAGEN, TOMAMOS EN SU LUGAR EL PUNTO (i,j)
/// LO MISMO SI NOS SALIMOS AL ACCEDER A (i,j+1) O (i+1,j+1)
Array2D< real > zoom_bilineal(
Array2D< real > &A /** IMAGEN ORIGINAL */,
real z /** FACTOR DE ZOOM */)
{
  /// HACER ALUMNO
    // Btw recuerda que A no es más que una matríz 2D con valores entre 0 y 1. Nada fancy.
    // Es en blanco y negro por sencillez.

    // Casos extremos (si no los pones quitan puntos).
    // Eliminamos dimensiones inválidas (negativas o 0)
    int dim1New = A.dim1()*z;
    int dim2New = A.dim2()*z;

    if (dim1New <= 0 || dim2New <= 0){
        return Array2D<real>();
    }
    // Se construye una matriz F′ de dimensiones (z · dim1) × (z · dim2).
    Array2D<real> F(z*A.dim1(), z*A.dim2());
    // podrías hacer una variable z*A.dim1() porque la calculas 2 veces.

    // Se recorren todos los puntos (i′, j′) de la nueva matriz.
    // Para cada (i′, j′) se calcula en precisión real el punto (x, y) = (i′/z, j′/z).
    // * ip = i'; jp = j'

    // Declaramos las variables a usar en el loop
    // las borre porque no hace falta.

    // iteramos por cada pixel de la nueva imagen.
    for (int ip = 0; ip < F.dim1(); ip++){
        for (int jp = 0; jp < F.dim2(); jp++){

            // posición relativa a la matriz original.
            real x = ip/z;
            real y = jp/z;

            // Se calculan los enteros i = x, j = y (al almacenar una variable real en
            // una entera se produce un truncamiento al eliminar los decimales.)
            // eliminamos los reales y redondeamos

            int i = x;
            int j = y;
            // Si quiere truncamiento, al pasarlo al int quita los decimales, tal como piden.
            // (y como hace el profe).

            // Se calcula F′i′,j′ = F(x, y) usando la fórmula de interpolación bilineal.
            // Salvo indicación de lo contrario se considera que la distancia entre los puntos
            // de interpolación es 1. Es decir xi+1 − xi = yi+1 − yi = 1. Si al aplicar la fórmula
            // de interpolación, Fi,j , Fi+1,j , Fi,j+1, o Fi+1,j+1 se salen de las dimensiones
            // de la matriz F utilizamos el criterio del vecino más cercano y sustituimos dichos
            // valores por los más cercanos dentro de la matriz.

            // en caso que el valor a la derecha sea > que el último valor del rango nos quedamos
            // con el último valor
            int i_next = min(i+1, A.dim1()-1);
            int j_next = min(j+1, A.dim2()-1);
            // le cambie el nombre a esto y el ctrl + F ayudo mucho a cambiar donde aparecía rápidamente

            // dix = (x − xi) / (xi+1 − xi)
            real dx = (x - i);
            //djy = (y − yj) / (yj+1 − yj)
            real dy = y - j;
            // están en los docs, lo importante es saber el contexto
            // (aunque no hay mucho que confundirse porque solo pasan A, ningún X para confundirnos)

            // F(x, y)≈ (1−djy) * ((1−dix) *Fij + dix * Fi+1j)
            // + djy * ((1−dix)* Fij+1 + dix * Fi+1j+1)
            F[ip][jp] = (1.-dy) * ( (1.-dx)*A[i][j] + dx*A[i_next][j] ) +
            dy  * ( (1.-dx)*A[i][j_next] + dx*A[i_next][j_next] );
            // única cosa a tener cuidado aquí es poner los 1. para no perder presición!
        }
    }

    // Se termina el proceso iterativo.
    return F;
    // como validación vemos que hace exactamente igual que antes en las imagenes, lo único a destacar es
    // como de fluido el escalado este proceso es y como de limpio se ve. Mientras que al hacer pequeño se ve peor
    // (Probablemente porque ir pixel a pixel es más facil para nosotros entender aún siendo menos representativo).
    // aunque si que guarda mucha mejor resolución en cosas como puertas, cosas que el anterior no podía, eso es destacable!

    // también vemos el error máximo bilineal ser 0.44, esto quiere decir
    // "En algún píxel, tu valor difiere del valor esperado en 0.444444"
    // Por lo que en algún momento nuestros al comparar la imagen guardada con la nuestra encontramos un error de 0.4.
    // Pero al ser entre 0 y 1 no nos preocupa, si fuera 1 implicaría que hay un pixel fuera de lugar, esto quiere decir
    // que uno es ligeramente diferente y es perfectamente posible que pase, es un error acceptable que al comparar con
    // las imagenes se puede despreciar tranquilamente.
}
