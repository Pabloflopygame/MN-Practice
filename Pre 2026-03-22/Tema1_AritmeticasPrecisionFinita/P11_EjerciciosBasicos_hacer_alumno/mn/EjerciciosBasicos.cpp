/// INCLUSION DE LIBRERIAS NECESARIAS
#include <stdio.h>
#include "EjerciciosBasicos.h"

/// P11.1 FUNCIÓN QUE CALCULA LA MEDIA DE UN VECTOR
real mn_media(Array1D< real > &u){
  /// HACER ALUMNO
    // nos pasan u por dirección usando & por lo que debemos evitar modificar el original.
    // en este apartado no hace falta modificarlo, pero es importante recordarlo para futuros.

    // observamos el tamaño del vector.
    int size = u.dim();

    // si es 0 retornamos 0 para evitar la expección 0/0
    if (size == 0){
        return 0;
    }

    // caso contrario es un vector con datos a hacer media.
    real amount = 0;
    for(int i=0; i<size; i++){
        amount += u[i];
    }
    real average = amount/size;

    return average;

    // la veríficación sería que el valor real es el mismo que el que hemos calculado.
}

/// P11.2 FUNCIÓN QUE CALCULA EL MAXIMO DE UN VECTOR
real mn_max(Array1D< real > &u){
  /// HACER ALUMNO

    // observamos el tamaño del vector.
    int size = u.dim();

    // si es 0 retornamos 0 para evitar llamar a un espacio no inicializado en u[0]
    if (size == 0){
        return 0;
    }

    // escogemos el primero como mayor y buscamos en todo el vector por uno mayor para sustituirlo.
    real biggest = u[0];
    for(int i=1; i<size; i++){
        if (biggest < u[i]){
            biggest = u[i];
        }
    }

    return biggest;

    // la veríficación sería que el valor real es el mismo que el que hemos calculado.
}

/// P11.3 FUNCIÓN QUE CALCULA EL MINIMO DE UN VECTOR
real mn_min(Array1D< real > &u){
  /// HACER ALUMNO

    // observamos el tamaño del vector.
    int size = u.dim();

    // si es 0 retornamos 0 para evitar llamar a un espacio no inicializado en u[0]
    if (size == 0){
        return 0;
    }

    // escogemos el primero como menor y buscamos en todo el vector por uno menor para sustituirlo.
    real smallest = u[0];
    for(int i=1; i<size; i++){
        if (smallest > u[i]){
            smallest = u[i];
        }
    }

    return smallest;

    // la veríficación sería que el valor real es el mismo que el que hemos calculado.
}

/// P11.4 FUNCIÓN QUE ORDENA UN VECTOR DE MENOR A MAYOR
void mn_ordenar(Array1D< real > &u){
  /// HACER ALUMNO

    // observamos el tamaño del vector.
    int size = u.dim();

    // si es 0 o 1 retornamos para evitar llamar a un espacio no inicializado en u[0] o u[1]
    // es el caso base que es una expeción a nuestro algoritmo a tratar antes de empezar.
    if (size < 2){
        return;
    }

    // el algoritmo que nos gustaría usar es:
    // Cogemos el primer elemento como pivote y miramos en todo el array por el más pequeño
    // si existe hacemos un cambio entre los 2 y seguimos al siguiente elemento.
    //
    // aquí el primer bucle mira todos menos el último (porque ese ya esta ordenado
    // y si lo mirara el segundo bucle haría overflow).
    //
    // tenemos que inicializar las variables fuera del bucle, porque si lo hacemos dentro estaríamos
    // creando 2 variables con el mismo nombre y daría error.
    //
    // para el profesor que tiene un ojo importante para IA; comentamos en español porque estamos en
    // una clase española y escribimos código en ingles porque código sin tildes o ñ es incorrecto de cara
    // a buenas prácticas en legibilidad del código.
    real current_value;
    for(int i=0; i<size-1; i++){
        for(int j=i+1; j<size; j++){
            if (u[i] > u[j]){
                current_value = u[i];

                u[i] = u[j];
                u[j] = current_value;
            }
        }
    }

    return;
    // la veríficación sería que esta ordenado en el testcase pasado
}

/// P11.5 FUNCIÓN PARA MULTIPLICAR UNA MATRIZ POR UN VECTOR
Array1D< real > mn_multiplicacion_matriz_vector(Array2D< real > &A,Array1D< real > &u){
  /// HACER ALUMNO
    // btw, tabular a 3 algunas veces y a 4 otras es criminal.
    // 4 es por defecto del programa, que necesidad de tocarlo...

    // casos exepcionales:
    // La matrix y vector tienen dimensiones incompatibles.
    //    - Matrix tiene cualquier dimensión 0.
    //    - El vector tiene dimensión 0.
    //    - fila (dim row matrix) y columna (dim vector) tienen dimensiones diferentes.

    // realmente no es necesario mirar las 2, ya que si 1 es 0 la otra lo es a la fuerza
    // pero por si acaso lo revisamos (no sabemos si alguien ha tocado los datos de manera rara).
    if ((A.dim1() == 0) || (A.dim2() == 0)){
        // retornamos un vector vacio ya que es una operación inválida.
        return Array1D<real> ();
    }

    // miramos el segundo caso
    if (u.dim() == 0){
        return Array1D<real> ();
    }

    // último caso.
    if (u.dim() != A.dim2()){
        return Array1D<real> ();
    }

    // ahora el procedimiento es bastante simple,
    // vamos a hacer matrix * vector (diferente de row * matrix)
    // para este ejercicio A*u esta desabilitado.
    //
    // lo que haremos sera crear un vector del tamaño de la cantidad de columnas de la matrix.
    // para cada fila de la matrix lo multiplicamos como si fuera un vector con el otro vector
    // y lo sumamos todos los elementos de ese resultado y lo guardamos en el vector
    // (lo que es un producto escalar).
    //
    // El resultado será el mismo numero de filas que A.
    // la variable sum es para calcular el resultado del producto escalar de cada fila
    Array1D<real> result(A.dim1());
    real sum = 0;

    // para cada fila
    for(int i=0; i<A.dim1(); i++){
        // para cada elemento en la fila
        for(int j=0; j<A.dim2(); j++){
            // multiplica y suma
            sum += A[i][j] * u[j];
        }
        result[i] = sum;
        sum = 0;
    }

    return result;
    // la veríficación sería que esta ordenado en el testcase pasado.
}

/// P11.6 FUNCIÓN QUE DETERMINA SI UN NÚMERO ENTERO ES PRIMO
bool mn_es_primo(int i){
  /// HACER ALUMNO
    // aquí existe una propiedad muy chula de los numeros primos y es que
    // solo tenemos que probar entre los enteros (2, sqr(i)] y si sale sin
    // resto en algún momento durante el intervalo no es primo.
    // Si el número es <= 2 es primo.

    if (i <= 2){
        return true;
    }

    for (int n = 2; n <= sqrt(i); n++) {
        if (i % n == 0){
            return false;
        }
    }

    return true;
    // la verificación es que dan los mismos resultados que al test
}

/// P11.7 FUNCIÓN QUE CALCULA EL FACTORIAL DE UN NÚMERO NATURAL
real mn_factorial(int n){
  /// HACER ALUMNO
    // no hay mucho que comentar, esto es la forma bruta de toda
    // la vida para calcular esto.
    real result = 1;
    // Paramos en 2 para evitar una iteración extra en comparación con 1,
    // es prácticamente negable el performance, pero así el profe lo quiere,
    // este quita puntos de todos lados, por lo que mejor cortar por lo seguro.
    for (int i=n; i>1; i--){
        result *= i;
    }

    return result;
    // la verificación es que dan los mismos resultados que al test
}


/// P11.8 FUNCIÓN QUE CALCULA UNA POTENCIA CON UN NÚMERO NATURAL
/// NO SE PUEDE USAR LA FUNCIÓN pow()
real mn_potencia(real x,int n){
 /// HACER ALUMNO
    // caso especial
    if (n == 0){
        return (real) 1;
    }

    // forma simple de toda la vida
    real result = 1;
    for(int i=n; i>0; i--){
        result *= x;
    }

    return result;
    // la verificación es que dan los mismos resultados que al test
}

/// P11.9 FUNCIÓN QUE CALCULA EL DESARROLLO DE TAYLOR DE e^x
/// e^x = 1 + x + x^2/2! + ...... +x^n/n!
real mn_exp(real x,int n){
  /// HACER ALUMNO
    real result = 0;

    // + x^n/n!
    // copiar y pegar lo que piden
    for(int i=n; i>=0; i--){
        result += pow(x, i)/mn_factorial(i);
    }

    return result;
    // la verificación es que dan los mismos resultados que al test
}

/// P11.10 FUNCIÓN QUE CALCULA EL DESARROLLO DE TAYLOR DE cos(x)
///  cos(x) = 1 - x^2/2! + x^4/4! - x^6/6!+...... +- x^(2n)/(2n)!
real mn_cos(real x,int n){
  /// HACER ALUMNO
    real result = 0;

    // +-x^(2n)/(2n)!
    // copiar y pegar lo que piden (+ par, - impar)
    for(int i=n; i>=0; i--){
        if (i % 2 == 0) {
            result += pow(x, 2*i)/mn_factorial(2*i);
        }else {
            result -= pow(x, 2*i)/mn_factorial(2*i);
        }
    }

    return result;
    // la verificación es que dan los mismos resultados que al test
}

/// P11.11 FUNCIÓN QUE CALCULA EL DESARROLLO DE TAYLOR DE sin(x)
///  sin(x) = x - x^3/3! + x^5/5! - x^7/7!+...... +- x^(2n+1)/(2n+1)!
real mn_sin(real x,int n){
  /// HACER ALUMNO
    real result = 0;

    //  +- x^(2n+1)/(2n+1)!
    // copiar y pegar lo que piden (+ par, - impar)
    for(int i=n; i>=0; i--){
        if (i % 2 == 0) {
            result += pow(x, (2*i)+1)/mn_factorial((2*i)+1);
        }else {
            result -= pow(x, (2*i)+1)/mn_factorial((2*i)+1);
        }
    }

    return result;
    // la verificación es que dan los mismos resultados que al test
}

/// P11.12 FUNCIÓN QUE CALCULA EL DESARROLLO DE TAYLOR DE ln(x)
/// ln(x) = (x-1) - ((x-1)^2)/2 + ((x-1)^3)/3 - ((x-1)^4)/4+...... +- ((x-1)^n)/n
real mn_ln(real x,int n){
  /// HACER ALUMNO
    real result = 0;

    //  +- ((x-1)^n)/n
    // copiar y pegar lo que piden (- par, + impar)
    // no lo dicen, pero este no toma 0, se para/empieza en 1
    // (eso e invierten lo par e impar y te saca de lo que te esperas).
    for(int i=n; i>=1; i--){
        if (i % 2 == 0) {
            result -= pow(x-1, i)/i;
        }else {
            result += pow(x-1, i)/i;
        }
    }

    return result;
    // la verificación es que dan los mismos resultados que al test
}

/// P11.13 FUNCIÓN QUE CALCULA y^x DONDE y,x SON NÚMERO REALES
/// USAR LAS FUNCIONES IMPLEMENTADAS mn_exp() y mn_ln() TENIENDO EN CUENTA y^x=e^(x*ln(y))
real mn_pow(real y,real x,int n){
  /// HACER ALUMNO
  // retornamos lo que pidan.
    return mn_exp(x*mn_ln(y, n), n);
    // la verificación es que dan los mismos resultados que al test
}

/// P11.13 FUNCIÓN QUE CALCULA EL LIMITE DE LA SECUENCIA  yn=(1.+1./n).^n CUANDO n TIENDE A
/// INFINITO EL ALGORITMO PARA CUANDO LA DIFERENCIA EN VALOR ABSOLUTO DE LA DIFERENCIA
/// ENTRE UN VALOR DE LA SECUENCIA Y EL ANTERIOR ES INFERIOR AL PARAMETRO tolerancia
/// EL LIMITE DE LA SECUENCIA ES EL NUMERO e=2.71828182846
/// IMPORTANTE : PARA QUE LAS CONSTANTES LAS TRATE COMO NÚMEROS REALES HAY QUE AÑADIR UN .,
/// ES DECIR, POR EJEMPLO  1. (EN LUGAR DE 1). SI HACEMOS 1/2 EL RESULTADO ES CERO PORQUE HACE
/// LA DIVISIÓN EN PRECISIÓN ENTERA. SIN EMBARGO  1./2.=1./2=1/2.=0.5
real mn_limite1(real tolerancia){
 /// HACER ALUMNO
    // n=1 es el primer valor y necesitamos n=2 para ver la tolerancia.
    int n = 1;
    real previous_value = pow(1. + 1./n, n);
    n++;
    real current_value;

    while(true){
        // yn=(1.+1./n).^n
        current_value = pow(1.+1./n, n);

        // tolerancia
        if (fabs(current_value - previous_value) <= tolerancia){
            return current_value;
            // la verificación es que dan los mismos resultados que al test
        }

        // siguiente iteración
        n++;
        previous_value = current_value;
    }
}

/// P11.14 FUNCIÓN QUE CALCULA EL LIMITE DE LA FUNCIÓN f(x)=sin(x)/x CUANDO x TIENDE HACIA 0.
/// EL PARAMETRO tolerancia SE UTILIZA PARA PARAR EL ALGORITMO CUANDO ESTAMOS CERCA DEL LÍMITE
/// EL VALOR DEL LÍMITE ES 1.
real mn_limite2(real tolerancia){
  /// HACER ALUMNO
    int n = 1;

    real previous_value = sin(1.0/n) / (1.0/n);
    real current_value;

    while (true) {
        n++;

        current_value = sin(1.0/n) / (1.0/n);

        if (fabs(current_value - previous_value) <= tolerancia) {
            return current_value;
        }

        previous_value = current_value;
    }
}

/// P11.15 FUNCIÓN QUE CALCULA EL LIMITE DE LA SECUENCIA  yn=X(n+1)/X(n) DONDE X(n) ES LA
/// SUCESIÓN DE FIBONACCI DEFINIDA COMO X(n+1)=X(n)+X(n-1) EMPEZANDO POR X(1)=X(2)=1
/// EL ALGORITMO PARA CUANDO LA DIFERENCIA EN VALOR ABSOLUTO
/// ENTRE UN VALOR DE LA SECUENCIA yn Y EL ANTERIOR ES INFERIOR AL PARAMETRO tolerancia
/// EL LIMITE DE LA SECUENCIA yn ES EL NÚMERO AÚREO IGUAL A (1+SQRT(5))/2 = 1.618033988....
real X(int n){
    if (n == 1 || n == 2){
        return 1;
    }
    return X(n-1) + X(n-2);
}

real mn_limite3(real tolerancia){
  /// HACER ALUMNO
    // tienes que salir a definir X porque no puedes hacerlo dentro de la función.
    int n = 1;
    real previous_value = X(n+1)/X(n);
    n++;
    real current_value;

    while(true){
        // yn=X(n+1)/X(n)
        current_value = X(n+1)/X(n);

        // tolerancia
        if (fabs(current_value - previous_value) <= tolerancia){
            return current_value;
            // la verificación es que dan los mismos resultados que al test
        }

        // siguiente iteración
        n++;
        previous_value = current_value;
    }
}

/// P11.16 CÁLCULO DEL NÚMERO PI POR EL MÉTODO DE MONTECARLO. EL ÁREA DEL CÍRCULO DE RADIO
/// 1 ES PI. Y EL AREA DEL CUADRADO DE LADO 2 DONDE SE INSCRIBE EL CÍRCULO ES 4. POR TANTO
/// SI SE ELIGE UN PUNTO AL AZAR EN EL CUADRADO, LA PROBABILIDAD DE QUE CAIGA EN
/// EL CÍRCULO ES PI/4. EL MÉTODO DE MONTECARLO APROXIMA PI COGIENDO PUNTOS AL AZAR EN
/// EL CUADRADO [-1,1]x[-1,1] Y VIENDO QUE PROPORCIÓN CAE EN EL CÍRCULO.
/// NOTA : LA FUNCIÓN rand() DEVUELVE UN VALOR ENTERO ALEATORIO ENTRE 0 Y RAND_MAX
real calculo_pi_montecarlo(int Nintentos){
  /// HACER ALUMNO

    int dentro = 0;

    for (int i = 0; i < Nintentos; i++){

        // Aleatorio en [0,1]
        real rx = (real) rand() / RAND_MAX;
        real ry = (real) rand() / RAND_MAX;

        // Pasar a [-1,1]
        real x = 2.0 * rx - 1.0;
        real y = 2.0 * ry - 1.0;

        // Dentro del círculo?
        if (x*x + y*y <= 1.0){
            dentro++;
        }
    }

    // π ≈ 4 * (dentro / total)
    return 4.0 * dentro / Nintentos;
    // la verificación es que se acerca a pi.
}
