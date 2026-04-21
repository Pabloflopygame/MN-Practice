#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"

/**
 LA INTERPOLACION POR SPLINES DE GRADO 2 SEGÚN SE EXPLICÓ EN CLASE.
 EN ESTE CASO SE SUPONE CONOCIDO EL ÚLTIMO VALOR DEL VECTOR c Y SE CALCULA EL RESTO DE COEFICIENTES
 LA FUNCION DEVUELVE -1 SI ENCUENTRA ALGÚN PROBLEMA Y 0 EN CASO CONTRARIO
*/
int mn_calculo_splines_2(
const Array1D< real > &x, /// vector con los puntos de interpolación
const Array1D< real > &f, /// vector con los valores de la función
const real &cLast,        /// último valor del vector c[] asignado como parámetro
Array1D< real > &a,       /// vector de salida con los coeficientes a[i] del spline de grado 2
Array1D< real > &b,       /// vector de salida con los coeficientes b[i] del spline de grado 2
Array1D< real > &c)       /// vector de salida con los coeficientes c[i] del spline de grado 2
{
  /// HACER ALUMNO
    // En vez de darnos c0 nos dan cN-1 y toca hacerlo a la inversa.
    // nada muy loco, lo mismo pero al revez.
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
    // x esté ordenado, hace falta aquí también que se me olvido.
    // no me preocupa este int porque desaparece una vez termine el loop, debajo
    // si hay que tener más cuidado
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

    // hasta ahora todo igual :D

    // Lo nuevo es calcular los valores [i] en vez de [0].
    int i = x.dim()-2; // cuando el algoritmo habla de i es i de la dim de a,b,c (se ve por ai = f(xi))
    int n = x.dim()-1; // n en cambio es la dimensión de x/f. Tienes que poner -1 porque es un índice x[n] es overflow

    // estado Cn-1;
    c[n-1] = cLast;
    // bn−1 = (f(xn) − f(xn−1) − cn−1(xn − xn−1)^2)/(xn − xn−1)
    // ojo que la formula cambia cuando es a la inversa.
    real difx = x[n] - x[n-1];
    b[n-1] = (f[n] - f[n-1] - c[n-1]*(difx*difx))/(difx);
    // ai = f(xi)
    a[i] = f[i];

    // calculamos para el resto de valores (ahora con las nuevas formulas :D).
    // esta vez ponemos sin el int porque ya lo declaramos fuera y es lo que queremos seguir usando.
    // Aquí paramos en 1, por el -1 para llegar a 0.
    for (i=i; i>0; i--){ // también sirve (; i>0; i--), pero no pongas -1 porque el algoritmo ya viene diseñado para eso
                        // te dice que "para ver el siguiente dado un i... Por lo que dale un i y no se te ocurra hacer i=i-1
                        // el algoritmo ya te calcula el siguiente."
        // a[i-1] = f(xi-1) (se asume del primer caso, nada muy loco, es el valor de f en ese i-1) - para mi
        a[i-1] = f[i-1];
        // bi−1 = ((2*(f(xi) − f(xi−1)))/(xi − xi−1)) − bi
        b[i-1] = ((2*(f[i] - f[i-1]))/(x[i] - x[i-1])) - b[i];
        // ci−1 = (bi*(xi − xi−1) + f(xi−1) − f(xi))/(xi − xi−1)**2
        real difx = (x[i] - x[i-1]); // se me olvido en el 3.2 pero esto ahora calculo
        c[i-1] = (b[i]*difx + f[i-1] - f[i])/(difx*difx);
    }

    // ejecución sin problemas
    return 0;
}

/**
  EVALUACIÓN SPLINE DE GRADO DOS. SE DEVUELVE EL VALOR DE LA
  EVALUACIÓN EN x0
*/
real mn_evaluar_splines_2(
const Array1D< real > &x,
Array1D< real > &a,
Array1D< real > &b,
Array1D< real > &c,
real x0 ){
  /// HACER ALUMNO
    /// Igual que antes, no cambia nada.

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
    // validación? mismo resultado esperado que antes salvo que ahora el vector sale del punto final en vez del inicial XD
}
