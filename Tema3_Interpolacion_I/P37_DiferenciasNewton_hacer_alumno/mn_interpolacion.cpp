#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"


/// FUNCION QUE CALCULA EL POLINOMIO INTERPOLADOR POR LAS DIFERENCIAS DE NEWTON
/// DEVUELVE UN VECTOR CON LOS COEFICIENTES DEL POLINOMIO O UN VECTOR VACÍO SI ALGO VA MAL
Array1D< real > mn_construir_polinomio_interpolador(
const Array1D< real > &X, /// VECTOR CON LOS VALORES DE LOS PUNTOS DE INTERPOLACION
const Array1D< real > &F) /// VECTOR DE VALORES DE LA FUNCION EN LOS PUNTOS DE INTERPOLACION
{
  /// HACER ALUMNO
    // ¿Que es newton? En vez de splines donde haces diferentes secciones de x's y por lo tanto
    // varios polinomios de grado 2 o 3 (si es splin 2 o 3). Simplemente te hace un polinomio de
    // grado n (x.dim()) que pasa por todos los puntos.
    // No garantiza suavidad ni estabilidad, ni si quiera es amable con la memoria (por un grado
    // tan grande que puede llegar a tener).
    //
    // ¿Esto no es peor en todos los sentidos? Si, pero a contraste de splines te da un polinomio
    // entero, por lo que es super útil para analisis matemáticos en algunos ámbitos. Pero solo eso
    // es un algoritmo para un uso super concreto.
    //
    // Si subes un poco en el 3.3.2 intentan explicarlo.

    // Casos exepcionales.
    int sizex = X.dim1();
    int sizef = F.dim1();
    // inputs inválidos:
    // vacios (facilmente puede ocurrir)
    // negativos, no tiene sentido en nuestro uso,
    // pero es por si modifican cosas avanzadas de c++.
    //
    // *Los juntamos en 1 para evitar un if de "vacios" y otro de "negativos".
    if ((sizex <= 0) || (sizef <= 0)) {
        return Array1D<real>(); // retornamos un vector sin inicializar como error
    }
    // dimensiones diferentes
    if (sizex != sizef) {
        return Array1D<real>();
    }
    // no se puede comprobar si c0 ha sido inicializado en C++
    // (creo que se puede con librerías externas)
    // x esté ordenado
    for (int i = 1; i < sizex; i++) {
        if (X[i] <= X[i-1]) {
            return Array1D<real>();
        }
    }

    // Caso general:
    // Creamos un vector Ak del tamaño de Xk donde almacenaremos ak.
    Array1D<real> A(sizex);

    // Construimos un valor auxiliar Bk del tamaño de Fk y lo inicializamos a Fk.
    Array1D<real> B(sizex);
    for(int i=0; i<sizex; i++){
        B[i] = F[i];
    }

    // Hacemos a0 = B0.
    A[0] = B[0];

    // Hacemos un proceso iterativo a partir de k = 1. En cada iteración actualizamos
    // todos los valores Bl usando la fórmula de las diferencias divididas.
    // Bl = (Bl+1 − Bl) / (Xk+l − Xl)
    // después de actualizar los valores Bl hacemos Ak = B0
    for (int k=1; k<sizex; k++){
        // aunque el algoritmo es algo ambiguo, usamos -k porque ya hemos calculado
        // AK, por lo que BK no tiene sentido, se le quita para mantener coherencia.
        // esto se sigue quitando hasta que llegemos a B0 (donde terminamos y de ahí
        // el porque de la condición inicial).
        //
        // Algo raro, pero tu simplemente sigue el flow.
        // En el examen pon algo por el estilo de eso y vas bien...
        for (int l=0; l<(sizex-k); l++){
            // El criterio de parada del algoritmo se produce si en alguna iteración
            // encontramos que Xk+l es igual a Xl. Aka, se produce un error.
            // Esto dice que hay 2 puntos iguales en x y se debe parar (aunque como esto
            // lo comprobamos al principio aquí es irrelevante).
            // if (X[k+l] == X[l]){
            //    return Array1D<real>();
            // }

            // calculamos recursivamente al siguente valor de l hasta llegar al indice de k actual
            // porque empezamos de 0 hasta la k actual. Por lo que al llegar al B[l] max cogemos el primero
            // independientientemente (será porque lo prepara para la siguiente iteración).
            B[l] = (B[l+1]-B[l])/(X[k+l]-X[l]);
        }
        A[k] = B[0];
    }

    /*
    Visualmente puedes imaginarte cada iteración como algo como eso:

    col 0          col 1              col 2                  col 3
    -------------------------------------------------------------------
    f[x0]          f[x0,x1]           f[x0,x1,x2]           f[x0,x1,x2,x3]
    f[x1]          f[x1,x2]           f[x1,x2,x3]
    f[x2]          f[x2,x3]
    f[x3]

    A = [ f[x0], f[x0,x1], f[x0,x1,x2], f[x0,x1,x2,x3] ]

    Iteración a iteración sería:
    X: x0   x1   x2   x3
    F: f0   f1   f2   f3

    A = [NA, NA, NA, NA]
    B = [f0, f1, f2, f3]
    A[0] = B[0]
    A = [f0, NA, NA, NA]

    en K=1 hacemos:
    B[0] = (f1 - f0)/(x1 - x0)
    B[1] = (f2 - f1)/(x2 - x1)
    B[2] = (f3 - f2)/(x3 - x2)
    A[1] = B[0]
    A = [f0, f[x0,x1], NA, NA]

    ...
    Necesitas calcular el resto de B's porque dependenden de ellos en el código.
    Seguimos sin entenderlo ni de broma, pero bueno.

    https://youtu.be/S7QIU0i1qLE?si=MbfKCGMemLm5WGD7
    TLDR, básicamente queremos forzar un polinomio de grado n que pase por todos esos
    puntos y para eso necesitamos mates y la forma general de hacerla es esa, que no es
    intuitiva. Es facil, pero cuando te abstraes montón ya es más complejo.
    */

    // terminamos
    return A;
}


/// FUNCION QUE EVALUA EL POLINOMIO INTERPOLADOR DE NEWTON EN UN PUNTO
real mn_evaluar_polinomio_interpolador(
const Array1D< real > &A, /// VECTOR CON LOS COEFICIENTES DEL POLINOMIO
const Array1D< real > &X, /// VECTOR CON LOS VALORES DE LOS PUNTOS DE INTERPOLACION
const real x0) /// VALOR DONDE SE INTERPOLA EL POLINOMIO
{
  /// HACER ALUMNO
    // Casos exepcionales.
    int sizex = X.dim1();
    int sizea = A.dim1();
    // inputs inválidos:
    // vacios (facilmente puede ocurrir)
    // negativos, no tiene sentido en nuestro uso,
    // pero es por si modifican cosas avanzadas de c++.
    //
    // *Los juntamos en 1 para evitar un if de "vacios" y otro de "negativos".
    if ((sizex <= 0) || (sizea <= 0)) {
        return -1; // no es un caso de error perfecto pero es lo mejor que tenemos
    }
    // dimensiones diferentes
    if (sizex != sizea) {
        return -1;
    }
    // no se puede comprobar si c0 ha sido inicializado en C++
    // (creo que se puede con librerías externas)
    // x esté ordenado
    for (int i = 1; i < sizex; i++) {
        if (X[i] <= X[i-1]) {
            return -1;
        }
    }

    // caso generico:
    // bk = Ak + bk+1(x0 − X[k])
    // recuerda tienes:
    // PN (x) = PN−1(x) + aN (x − x0)(x − x1)...(x − xN−1).
    // eso es básicamente lo que estas haciendo (E es el valor anterior,
    // es propiedad distributiva que empieza por A[N]).
    int N = sizex-1;
    real E = A[N];
    for(int k = N-1; k>=0; k--){
        E = E*(x0-X[k])+A[k];
    }

    /*
    El polinómio que usamos se ve algo así.
    P(x) = A0
         + A1(x-x0)
         + A2(x-x0)(x-x1)
         + A3(x-x0)(x-x1)(x-x2)
    y lo pasamos a:
    E = A0 + (x0-X0)[A1 + (x0-X1)(A2 + A3(x0-X2))]
    Por lo que cogemos AN y Calculamos AN*(x0-X1)+AN-1
    y en la siguiente iteración todo eso lo multiplicas por A1 + (x0-X1).
    De ahí que funcione la multiplicación.
    */

    return E;
    // Validación, solo con los resultados de la consola no puedo decir mucho más que son
    // iguales a los calculados y los resultados son lógicos, razonables y esperables.
}


