/*========================================================================
  FUNCIONES PARA LA INTERPOLACION DE FUNCIONES
  ======================================================================== */

// INCLUSION DE LA LIBRERIA PARA GESTIONAR LA ARITMETICA
#include "mn_aritmeticas.h"
#include "mn_interpolacion.h"


Array1D< real > solucion_sistema(
Array1D< real > &L,
Array1D< real > &M,
Array1D< real > &U,
Array1D< real > &B
)
{
  Array1D< real > c(M.dim());
  c[0]=B[0];
  c[c.dim()-1]=B[B.dim()-1];

  for(int k=0;k<10000;k++){
    real error=0;
    for(int n=1;n<M.dim()-1;n++){
        real temp=c[n];
        c[n]= (-L[n]*c[n-1]-U[n]*c[n+1]+B[n])/M[n];
        error+=mn_distancia(temp,c[n]);
    }
    if(error<1e-8) return c;
  }
  return Array1D< real >();

}

/**
 LA INTERPOLACION POR SPLINES DE GRADO 3 SEGÚN SE EXPLICÓ EN CLASE.
 LA FUNCION DEVUELVE -1 SI ENCUENTRA ALGÚN PROBLEMA Y 0 EN CASO CONTRARIO.
 HAY QUE USAR LA FUNCIÓN solucion_sistema() QUE SE VE ARRIBA
*/
int mn_calculo_splines_3(
const Array1D< real > &x, /// vector con los puntos de interpolación
const Array1D< real > &f, /// vector con los valores de la función
const real c0,            /// primer valor del vector c[] asignado como parámetro
const real cN,            /// último valor del vector c[] asignado como parámetro
Array1D< real > &a,       /// vector de salida con los coeficientes a[i] del spline de grado 2
Array1D< real > &b,       /// vector de salida con los coeficientes b[i] del spline de grado 2
Array1D< real > &c,       /// vector de salida con los coeficientes c[i] del spline de grado 2
Array1D< real > &d)       /// vector de salida con los coeficientes d[i] del spline de grado 2
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

    // caso normal:
    int n = x.dim()-1; // n es la rango de x/f [0, x.dim()-1]; tienes que poner -1 porque es un índice x[n] es overflow.
    int i = n-1; // i es la rango para ITERAR a,b,c,d,... [0, x.dim()-2]; es n-1, porque hay n-1 intervalos.
    // usa i solo para a,b,c,d!

    // declaramos el tamaño de a,b,d
    a = Array1D<real>(n);
    b = Array1D<real>(n);
    d = Array1D<real>(n);
    // no tocamos c porque nos la da la matríz

    // declaramos el tamaño de L, M, U, B.
    // si no te lo dan tienes que hacerlo de esta manera
    // o como hace el main Array1D< real > a,b,c,d; y dsp normal
    Array1D<real> L(n);
    Array1D<real> M(n+1);
    Array1D<real> U(n);
    Array1D<real> B(n+1);
    // en vez de crear un Array2D y calcularlo a mano, simplemente hacemos las filas
    // se la pasamos a solucion_sistema y el ya nos retorna todo c.
    // ¿Porque tienen tamaños diferentes?
    // M0-U0-00-00 | c0   B0
    // L0-M1-U1-00 | c1   B1
    // 00-L1-M2-U2 | c2 = B2
    // 00-00-L2-M3 | c3   B3
    // *Mi mejor interpretación del sistema de ecuaciones matricial en comentarios.
    // M0-M3 / U0-U2 / L0-L2 / B0-B3
    //
    // Si te da error de caracteres no declarados borra porque son caracteres invisibles del
    // pdf que te rompen todo esten donde estén

    // se calcula el vector hi = xi+1 − xi
    // nota: el tamaño de h tiene que ser n porque lo usara M y B y es como el profe lo tiene
    Array1D<real> h (n);
    for(int j=0; j<n; j++){
        h[j] = x[j+1] - x[j];
    }
    // debug para ver que tenemos el vector declarado correctamente.
    // std::cout << "h: \n" << h << "\n";
    // system("pause");
    //
    // Más abajo hay una mejor manera porque h se imprime de forma desordenada.
    // (inclusive puedes hacerlo dentro del bucle si quieres, pero me gusta separarlos,
    // especialmente porque no se va a ejecutar cuando se comente cuando esté bien).
    //
    //for(int j=0; j<n; j++){
    //    std::cout << "h[" << j << "]: " << h[j] << "\n";
    //}
    //system("pause");
    //
    // En un examen deja estos simplemente porque enseña que no es chatgpt y que has hecho tests
    // AHORA, dejalo documentado y bien bonito para que no te digan nada!

    // la diagonal principal del sistema que llamaremos Mi vale M0 = MN = 1 y
    // en el resto de los casos Mi = 2(hi−1 + hi)
    M[0] = 1;
    M[n] = 1;
    for(int j=1; j<n; j++){
        // Apuntes de pablo, cuidado con el copiar y pegar porque te puede dar errores
        // por "−" que no es igual que -. Por lo que solo copia y pega en comentarios.
        M[j] = 2*(h[j-1] + h[j]);
    }
    // debug para ver que tenemos el vector declarado correctamente.
    // Cuidado porque aparece desordenado!!!
    // std::cout << "M: \n" << M << "\n";
    //
    // Debug Arreglado :D.
     //for(int j=0; j<n; j++){
     //    std::cout << "M[" << j << "]: " << M[j] << "\n";
     //}
     //system("pause");

    // la diagonal inferior del sistema que llamaremos Li
    // vale LN−1 = 0 y para i < N − 1 -> Li = hi
    L[n-1] = 0;
    for(int j=n-2; j>=0; j--){
        L[j] = h[j];
    }
    // debug para ver que tenemos el vector declarado correctamente.
     //for(int j=n-1; j>=0; j--){
     //    std::cout << "L[" << j << "]: " << L[j] << "\n";
     //}
     //system("pause");
    // recuerda ir trabajando debug a debug, mirando que el debug y parte del
    // codigo a testear valla funcionando como se debe, inclusive metiendo prints
    // dentro de la iteración y hacerlo a mano.
    // quizas debería hacer un pointer para L y B...
    //
    // recuerda hacer guardar antes de ejecutar para que los cambios pasen.
    // creo que si le daz click a compilar y ejecutar no debería pasar, pero
    // hacer ambas no es mala práctica.

    // la diagonal superior del sistema que llamaremos Ui
    // vale U0 = 0 y para i > 0 -> Ui = hi
    U[0] = 0;
    for(int j=1; j<n; j++){
        U[j] = h[j];
    }
    // debug para ver que tenemos el vector declarado correctamente.
     //for(int j=0; j<n; j++){
     //    std::cout << "U[" << j << "]: " << U[j] << "\n";
     //}
     //system("pause");

    // el término independiente del sistema, que llamaremos Bi
    // vale B0 = c0, BN = cN, y en el resto de los casos:
    // Bi = (3*(fi+1 − fi)/hi) - (3*(fi − fi−1)/hi−1)
    // Comentario de Pablo: esto parece más un leetcode test que un algoritmo a este punto XD.
    B[0] = c0;
    B[n] = cN; // los 2 únicos valores de c que nos dan y necesitamos aquí (comentario de pablo)
    for(int j=1; j<=n-1; j++){
        B[j] = ((3 * (f[j+1] - f[j])) / (h[j])) - ((3 * (f[j] - f[j-1]))/h[j-1]);
    }
    // debug para ver que tenemos el vector declarado correctamente.
    // ojo en este caso, ambos c0 y cN son 0's.
     //for(int j=0; j<=n; j++){
     //   std::cout << "B[" << j << "]: " << B[j] << "\n";
     //}
     //system("pause");

    // ojo en todo esta parte mi problema principal fue aprender las dimensiones y no equivocarme en
    // las codiciones de paradas de los for, los < -1 o -2, <=... Los debugs son esenciales

    // se calcula ci resolviendo el sistema resultante usando una función previamente
    // implementada a la que pasamos como parámetros los vectores M, L, U y B.
    c = solucion_sistema(L, M, U, B);

    // perfe ya lo tenemos todo C, y con ayuda de los mil debugs de cada LMUB y H
    // se pueden depurar errores de dimensión, de cálculo... Hace el proceso de creación super agradable.
    // ahora toca sacar el resto de las letras con las formulas :D (hapyness.exe).

    // una vez obtenido el vector ci se calculan ai, bi y di usando las ecuaciones:
    // ai = f(xi) i = 0, .., N
    // di = (ci+1 − ci)/(3hi) i = 0, .., N − 1
    // bi = (fi+1 − fi)/(hi)−(hi (2ci + ci+1))/(3) i = 0, .., N − 1
    //
    // Creo que una errata es el rango de a porque todos utilizan el N-1
    // y es el lógico para usar (aunque supongo que a fuerza bruta puedes conseguir N
    // aunque como no hay más intervalos no lo usamos).
    // por lo que eso, se puede hasta N pero no se usa porque solo queremos entre intervalos
    // por lo que N-1 para todo es lo lógico.
    for(int k=0;k<n;k++){
        a[k]=f[k];
        d[k]=(c[k+1]-c[k])/(3.*h[k]);
        b[k]=((f[k+1]-f[k])/h[k]) - (h[k]*(2*c[k]+c[k+1])/3.);
        // recuerda poner 3. para que sea división de coma flotante!
        // importante para el examen!!!
    }

    return 0;
}

/**
  EVALUACIÓN SPLINE DE GRADO 3. SE DEVUELVE EL VALOR DE LA
  EVALUACIÓN EN x0 <--- MENTIRAS! es por return y hasta ellos en el main lo saben!!!
*/
real mn_evaluar_splines_3(
const Array1D< real > &x,
Array1D< real > &a,
Array1D< real > &b,
Array1D< real > &c,
Array1D< real > &d,
real x0 ){
  /// HACER ALUMNO

      // Casos expecionales.
    int sizex = x.dim1();
    int sizea = a.dim1();
    int sizeb = b.dim1();
    int sizec = c.dim1();
    int sized = d.dim1();
    // para vacios o negativos
    if ((sizex <= 0) || (sizea <= 0) || (sizeb <= 0) || (sizec <= 0) || (sized <= 0)) {
        return -1;
    }


    // dimensiones diferentes (c biene con 1 de más con el a,b,d)
    if ((sizex-1 != sizea) || (sizea != sizeb) || (sizeb != sizec-1) || (sizec-1 != sized)) {
        return -1;
    }
    // y si c y x deben tener la misma dimensión,
    // c representa los coeficientes asociados a cada nodo del sistema
    // mientras que el resto trata sobre intervalos o "los tramos", lo mismo.
    // pero bueno, que lo sepas y que lo puedas esperar.
    //
    // random fact con cada std::cout pon un system pause, porque el main corre en loop por alguna razón.
    // por lo que muestra montón de datos. Simplemente para que lo recuerdes.

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
        real difx2 = difx*difx;
        return a[i] + b[i]*(difx) + c[i]*difx2 + d[i]*(difx2*difx);
    }
    // extrema derecha (se toma último intervalo)
    if (x0 >= x[sizex-1]) {
        int i = sizex-2; // recuerda que el último intervalo no empieza en n,
        // pero en n-1 (no existe un n+1 pasado el n que es el tope)
        real difx = x0-x[i];
        real difx2 = difx*difx;
        return a[i] + b[i]*(difx) + c[i]*difx2 + d[i]*(difx2*difx);
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
            // Pi2(x) = ai + bi(x − xi) + ci(x − xi)**2 + di(x − xi)**3
            // vamos a guardar en memoria calculos repetidos
            real difx = x0-x[i];
            real difx2 = difx*difx;
            return a[i] + b[i]*(difx) + c[i]*difx2 + d[i]*(difx2*difx);
        }
    }

    // caso de error no esperado;
    return -1;
    // validación, lo mismo de antes hasta ahora pero ahora el vector tiene 2 vectores guías y es mas suave
    // controlando esos 2 vectores iniciales podemos ajustar como de brusco es. Todo dentro de lo esperado.
    // No se te olvide mencionar que el proceso de creación del vector retorno 0 (que todo salió bien).
}

