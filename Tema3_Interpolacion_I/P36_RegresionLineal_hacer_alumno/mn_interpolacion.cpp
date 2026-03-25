#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

///* FUNCION QUE CALCULA LA RECTA DE REGRESION LINEAL y=ax+b PARA APROXIMAR UNA
/// NUBE DE PUNTOS (x[k],y[k]). LA FUNCION DEVUELVE 0 SI TERMINA BIEN Y -1 SI
/// TERMINA MAL
/// */
int mn_regresion_lineal(
Array1D< real > &x, /// VECTOR DE COORDENADAS x DE LA NUBE DE PUNTOS
Array1D< real > &y, /// VECTOR DE COORDENADAS y DE LA NUBE DE PUNTOS
real &a, /// COMPONENTE a DE LA RECTA DE REGRESIÓN. (PARÁMETRO DE SALIDA)
real &b) /// COMPONENTE b DE LA RECTA DE REGRESIÓN. (PARÁMETRO DE SALIDA)
{
  ///HACER ALUMNO
    /// Para encontrar esto simplete hacer ctrl + f en el pdf con regresión lineal
    /// y encontrar el super mini apartado con "3.4 Aproximación por mínimos cuadrados (regresión lineal)."
    /// y si aparece (esta perdido en los docs). Pero ahí te dice la formula y todo, lo que no en un cuadradito.

    // Te dicen que para todo  {(xi, yi)}i=1,..,N queremos buscar la recta y = ax + b,
    // tal que la función de error cuadrático sea mínima.
    // La función del error cuadrático a minimizar es:
    // E(a, b) = sumatorio(i=1, N, (axi + b − yi)**2)
    // *recuerda que empezamos i terminamos en N en la definición "i=1,..,N"
    //
    // Pero evidentemente para cada valor hayar a y b que lo minimize es la ostia, por lo que
    // debajo hay una demostración con las formulas que explican como resolverlo:

    // a = (N * sum(i=1, N, xi*yi) - sum(i=1, N, xi) * sum(i=1, N, yi)) / (N * sum(i=1, N, xi**2) - sum(i=1, N, xi)**2)
    // b = (sum(i=1, N, xi**2) * sum(i=1, N, yi) - sum(i=1, N, xi*yi) * sum(i=1, N, xi)) / (N * sum(i=1, N, xi**2) - sum(i=1, N, xi)**2)

    // para simplificar podemos quitar componentes que se repiten
    // c1 = (N*sum(i=1, N, xi**2) - sum(i=1, N, xi)**2); denominador (igual en a y b)
    // c2 = sum(i=1, N, xi*yi); usado en el nominador
    // c3 = sum(i=1, N, xi); usado en el nominador
    // c4 = sum(i=1, N, yi); usado en el nominador
    // c1 = (N*sum(i=1, N, xi**2) - c3*c3; simplificado
    // c1_2 = sum(i=1, N, xi**2)
    // c1 = N*c1_2 - c3*c3; simplificado para correr en 1 loop.
    // dejando: (esto es muy bueno que hagas en el examen, enseñas que entiendes).
    // a = (N*c2 - (c3*c4)) / c1
    // b = (c1_2*c4 - c2*c3) / c1;
    //
    // *Podemos retornar -1 si c1 da 0.
    // **Ten mucho cuidado que **2 fuera del sum es muy diferente que dentro!!!
    // Nota extra, si tienes que multiplicar por una costante, que aquí no, aun siendo mainly para dividir
    // siempre añade el ., no suele hacer falta, porque es mainly división, pero hazlo.


    // Por lo que primero miremos los casos exepciones
    // dimensión 0.
    if (x.dim1() <= 0) {
        return -1;
    }
    // dimensiones diferentes
    if (x.dim1() != y.dim1()) {
        return -1;
    }

    // Caso normal
    // Primero calculamos los parametros.
    int N = x.dim1();
    real c1;
    // inicializamos con el i=0
    real c1_2 = x[0]*x[0];
    real c2 = x[0]*y[0];
    real c3 = x[0];
    real c4 = y[0];
    // continuamos para el resto
    for (int i=1; i<x.dim1(); i++){
        c1_2 += x[i]*x[i];
        c2 += x[i] * y[i];
        c3 += x[i];
        c4 += y[i];
    }
    c1 = N*c1_2 - c3*c3;

    // caso expecional que tratamos como error para evitar dividir entre 0
    if (c1 == 0) {
        return -1;
    }

    // ahora simplemente resolvemos y terminamos.
    a = (N*c2 - (c3*c4)) / c1;
    b = (c1_2*c4 - c2*c3) / c1;

    // la verdad que con todo calculado podríamos calcular el error usando la formula main:
    // E(a, b) = sumatorio(i=1, N, (axi + b − yi)**2)
    // pero no lo piden :3.
    //
    // Pero si, esto literalmente fué coger una ecuación compleja
    // ver dependencias e intentar calcularlas en un solo bucle
    // y lo que no se pueda en una operación después.

    // todo termino correctamente
    return 0;
    // verificación:
    // los valores del alumno y del profesor encajan sin diferencia.
    // A su vez podemos ver que los valores inferidos del experimento estadístico
    // sigue una tendencia constante, lo esperable a una recta.PERO, A su vez vemos
    // como los valores grandes del extremo derecho causaron que los izquierdos (casi nulos en comparación)
    // fueran "irrelevantes" undiendolos, llegando a dar valores negativos que no tienen sentido con los datos.
    // Probablemente esta función no debería ser representada con una pendiente estática, pero de forma exponencial.
    // si se calculara la "R" (un valor estadístico) podríamos ver si esta función se encaja a los datos o no.
}



