#include "mn_determinante.h"
#include <stdlib.h>
#include <stdio.h>

/// CÁLCULO DEL DETERMINANTE DE UNA MATRIZ USANDO UN ALGORITMO RECURSIVO
/// DESARROLLANDO EL DETERMINANTE POR LA PRIMERA FILA
/// DEVUELVE 0 SI LA MATRIZ ESTÁ VACÍA O NO ES CUADRADA
real mn_determinante_recursivo(Array2D< real > &A)
{
  /// HACER ALUMNO
    // Casos exepcionales
    // si no esta inicializado (dimensión será 0)
    // o sus dimensiones son diferentes
    if((A.dim1()==0) || (A.dim1()!=A.dim2())){
        return 0.; // retornamos 0. que a la función tener la firma de return real
                   // hará (real) 0. De esa forma si real es float o double cambia solito
                   // y 0. será lo que esperamos que retorne.
    }


    // caso general
    // Si N > 1 construimos N matrices A0, ..., Ak, ...AN−1 de dimensión N − 1.
    // Para cada k, Ak se construye quitando la primera fila de A y su columna k-ésima.
    //
    // Se retorna después como:
    // determinante(A, N) = sumatoria(N−1, k=0, (−1)k· a0,k · determinante(Ak, N − 1)).
    //
    // Si N no fuera > 1 retorna A[0][0].

    int N = A.dim1(); // N es la dim de A pasado
    real result = 0.;

    if (A.dim1() > 1){
        // queremos crear N matrices.
        for (int k=0; k<N; k++){
            // nueva matriz pero con una fila y columna menos
            Array2D<real> B(N-1, N-1);

            // recorremos todo elemento de B
            for(int i=0; i<B.dim1(); i++){
                    for(int j=0; j<B.dim1(); j++){
                        // k va a ser las columnas (la selecionada a borrar en el loop)
                        // i es la fila y j la columna
                        //
                        // si estamos en la misma columna que k
                        // simplemente saltamos con un +1 en la fila para evitar la que se quiere borrar
                        // (la fila a borrar se hizo cuando la dimensión de B fué menor)
                        //
                        // ¿Puede haber overflow? No, por dimensiones diferentes, un -1 y +1.
                        // + siempre saltan una columna, por lo que recorremos solo B (seguro)
                        // y A esta segura porque si quieren borrar la primera columna dejando la
                        // última en +1 al estar i en B es B+1, no hace nunca overflow.
                        //
                        // Corto pero te quita de lugar verlo así
                        if (j >= k) {
                            B[i][j] = A[i+1][j+1];
                        } else {
                            B[i][j] = A[i+1][j];
                        }
                    }
            }

            // calculamos el determinante y mandamos al siguiente a
            // ser calculado.
            if(k%2==0){
                result+=A[0][k]*mn_determinante_recursivo(B);
            }else {
                result-=A[0][k]*mn_determinante_recursivo(B);
            }
        }

    // si N == 1 es el caso base y es simplemente el numero.
    } else{
        return A[0][0];
    }

    // terminamos de crear las K matrices y hacer las operaciones
    // y retornamos el resultado
    return result;
}

// validación, los resultados esperados y retornados son iguales y el tiempo de ejecución es
// el esperado para el tamaño de las operaciones.
