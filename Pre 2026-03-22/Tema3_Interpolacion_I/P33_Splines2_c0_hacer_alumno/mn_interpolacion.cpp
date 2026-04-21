#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/**
 LA INTERPOLACION POR SPLINES DE GRADO 2 SEGÚN SE EXPLICÓ EN CLASE.
 EN ESTE CASO SE SUPONE CONOCIDO c[0] Y SE CALCULA EL RESTO DE COEFICIENTES
 LA FUNCION DEVUELVE -1 SI ENCUENTRA ALGÚN PROBLEMA Y 0 EN CASO CONTRARIO
*/
int mn_calculo_splines_2(
 Array1D< real > &x, /// vector con los puntos de interpolación
 Array1D< real > &f, /// vector con los valores de la función
 real &c0,           /// valor de c[0] asignado como parámetro
Array1D< real > &a,       /// vector de salida con los coeficientes a[i] del spline de grado 2
Array1D< real > &b,       /// vector de salida con los coeficientes b[i] del spline de grado 2
Array1D< real > &c)       /// vector de salida con los coeficientes c[i] del spline de grado 2
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
    // no se puede comprobar si c0 ha sido inicializado en C++
    // (creo que se puede con librerías externas)
    // x esté ordenado
    for (int i = 1; i < sizex; i++) {
        if (x[i] <= x[i-1]) {
            return -1;
        }
    }


    // casos normales
    // inicializamos los vectores con el tamaño correcto
    // hay n puntos pero n-1 intervalos!
    a = Array1D<real>(x.dim()-1);
    b = Array1D<real>(x.dim()-1);
    c = Array1D<real>(x.dim()-1);
    // además trata de calcular más (te quedas sin x y
    // no se puede) - no poner examen solo para mi!

    // estado [0];
    c[0] = c0;
    // b0 = (f(x1) − f(x0) − c0(x1 − x0)**2)/(x1 − x0)
    real difx = x[1] - x[0];
    b[0] = (f[1] - f[0] - c[0]*(difx*difx))/(difx);
    // f(xi) = Pi2(xi) = ai
    a[0] = f[0];

    // calculamos para el resto de valores.
    //recuerda parar 1 antes por el x[i+2]
    for (int i=0; i<sizex-2; i++){
        // f(xi+1) = Pi2(xi+1) = ai+1
        a[i+1] = f[i+1];
        // bi+1 = bi + 2ci(xi+1 − xi)
        b[i+1] = b[i] + 2*c[i]*(x[i+1]-x[i]);
        // ci+1 = (f(xi+2) − f(xi+1) − bi+1(xi+2 − xi+1))/(xi+2 − xi+1)**2
        c[i+1] = (f[i+2] - f[i+1] - b[i+1]*(x[i+2] - x[i+1]))/((x[i+2] - x[i+1])*(x[i+2] - x[i+1]));

        // x[i+2] - x[i+1] podrías haberlo dejado como una variable en memoria para no tener que recalcular 3 veces!
    }

    // ejecución sin problemas
    return 0;
}

/**
  EVALUACIÓN SPLINE DE GRADO DOS. SE DEVUELVE EL VALOR DE LA
  EVALUACIÓN EN x0
*/
real mn_evaluar_splines_2(
Array1D< real > &x,
Array1D< real > &a,
Array1D< real > &b,
Array1D< real > &c,
real x0 ){
  /// HACER ALUMNO

    // Casos expecionales.
    int sizex = x.dim1();
    int sizea = a.dim1();
    int sizeb = b.dim1();
    int sizec = c.dim1();
    // para vacios o negativos
    if ((sizex <= 0) || (sizea <= 0) || (sizeb <= 0) || (sizec <= 0)) {
        return -1;
    }
    // dimensiones diferentes
    if ((sizex-1 != sizea) || (sizea != sizeb) || (sizeb != sizec)) {
        return -1;
    }
    // x esté ordenado <-- TE LO PEDIRÁN EN EL EXAMEN!!!
    // debe revisarse antes para evitar inconsistencia de datos.
    // debemos estar seguros que todos los datos tengan la integridad correcta,
    // independientemente si el intervalo que miramos la tenga
    // (aunque se puede juntar con el otro loop por limpieza mejor tenerlo fuera
    // a ser necesario se puede juntar haciendo una variable resultado y que retorne fuera)
    for (int i = 1; i < sizex; i++) {
        if (x[i] <= x[i-1]) {
            return -1;
        }
    }

    // Casos extremos.
    // extrema izquierda (se toma primer intervalo)
    if (x0 <= x[0]) {
        int i = 0;
        real difx = x0-x[i];
        return a[i] + b[i]*(difx) + c[i]*(difx)*(difx);
    }
    // extrema derecha (se toma último intervalo)
    if (x0 >= x[sizex-1]) {
        int i = sizex-2; // recuerda que el último intervalo no empieza en n,
        // pero en n-1 (no existe un n+1 pasado el n que es el tope)
        real difx = x0-x[i];
        return a[i] + b[i]*(difx) + c[i]*(difx)*(difx);
    }

    // Casos normales.
    // Vamos a recorrer de izquierda a derecha.
    // x[0]-x[1] / x[1]-x[2] / ... / x[n-1] - x[n]
    // y ver cual contiene a x0.
    for(int i=0; i < sizex-1; i++){
        // comprobamos si tenemos el valor exacto antes de interpolar.
        //if (x0 == x[i]){
        //    return f[i];
        //}
        //if (x0 == x[i+1]){
        //    return f[i+1];
        //}
        //
        // En este caso, eso no hace falta porque la parabola ya tiene los 2 puntos.
        // Pero evidentemente es más rápido y limpio hacer eso, pero como no nos
        // pasan f tenemos que hacerlo de la otra manera.

        // si está entre el intervalo calculamos la parabola entre los puntos.
        if ((x0 >= x[i]) && (x0 <= x[i+1])) {
            // Pi2(x) = ai + bi(x − xi) + ci(x − xi)2
            // vamos a guardar en memoria calculos repetidos
            real difx = x0-x[i];
            return a[i] + b[i]*(difx) + c[i]*(difx)*(difx);
        }
    }

    // caso de error no esperado;
    return -1;
    // Hora de la validación :D
    // Primero de todo, aquí ya nos dan el resultado calculado y comparamos y tenemos 2 tests (+1 visual).
    // el primer test es un calculo de coeficientes de a-alumno a-real | b-alumno ... y debajo los valores.
    // vemos que encajan por los que perfecto.
    // El siguiente test es ahora calculando el valor interpolado con dichos a's,b's,c's. QUe de nuevo es comparado con el real
    // y vemos que encajan y son razonables y esperables.
    // Estos valores son curiosos porque realmente son "logaritmo de la probabilidad de defunción en esa edad"
    // esto se hace para poder representar aspectos logaritmicos más facilmente.
    // Algunos salen negativos por estar entre [0, 1), no siempre pasa pero es un caso especial y puede ocurrir, especialmente
    // en la interpolación, quiere decir que la muestra era pequeña.
    // De igual manera, encajan con la tabla, menos fatalidades en jovenes y la grán mayoría en 70+ (descansen en paz).
    //
    // El último apartado es visual donde se aplica estos conocimientos en geometría interpolando un vector
    // el resultado es un vector con los mismos puntos bases pero más redondeado (aunque con giros bruscos
    // intenta emular como serían esos intermediarios basados en el c0 dado y los puntos futuros).
}

