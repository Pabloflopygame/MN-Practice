/* ================================================================
  MACROS Y DECLARACION DE TIPOS PARA GESTIONAR OPERACIONES CON
  MATRICES Y VECTORES
  ================================================================= */

#ifndef MN_preliminares_H
#define MN_preliminares_H

#include <math.h>
#include "mn_aritmeticas.h"
#include "tnt_array/tnt.h"
using namespace TNT;

/// FUNCIÓN QUE CALCULA LA MEDIA DE UN VECTOR
real mn_media(Array1D< real > &u);

/// FUNCIÓN QUE CALCULA EL MAXIMO DE UN VECTOR
real mn_max(Array1D< real > &u);

/// FUNCIÓN QUE CALCULA EL MINIMO DE UN VECTOR
real mn_min(Array1D< real > &u);

/// FUNCIÓN QUE ORDENA UN VECTOR DE MENOR A MAYOR
void mn_ordenar(Array1D< real > &u);

/// FUNCIÓN PARA MULTIPLICAR UNA MATRIZ POR UN VECTOR
Array1D< real > mn_multiplicacion_matriz_vector(Array2D< real > &A,Array1D< real > &u);

/// FUNCIÓN QUE DETERMINA SI UN NÚMERO ENTERO ES PRIMO
bool mn_es_primo(int i);

/// FUNCIÓN QUE CALCULA EL FACTORIAL DE UN NÚMERO NATURAL
real mn_factorial(int n);

/// FUNCIÓN QUE CALCULA UNA POTENCIA CON UN NÚMERO NATURAL
real mn_potencia(real x,int n);

/// FUNCIÓN QUE CALCULA EL DESARROLLO DE TAYLOR DE e^x
/// e^x = 1 + x + x^2/2! + ...... +x^n/n!
real mn_exp(real x,int n);

/// FUNCIÓN QUE CALCULA EL DESARROLLO DE TAYLOR DE cos(x)
///  cos(x) = 1 - x^2/2! + x^4/4! - x^6/6!+...... +- x^(2n)/(2n)!
real mn_cos(real x,int n);

/// FUNCIÓN QUE CALCULA EL DESARROLLO DE TAYLOR DE cos(x)
/// sin(x) = x - x^3/3! + x^5/5! - x^7/7!+...... +- x^(2n+1)/(2n+1)!
real mn_sin(real x,int n);

/// FUNCIÓN QUE CALCULA EL DESARROLLO DE TAYLOR DE ln(x)
/// ln(x) = (x-1) - ((x-1)^2)/2 + ((x-1)^3)/3 - ((x-1)^4)/4+...... +- ((x-1)^n)/n
real mn_ln(real x,int n);

/// FUNCIÓN QUE CALCULA y^x DONDE y,x SON NÚMERO REALES
real mn_pow(real y,real x,int n);

/// FUNCIÓN QUE CALCULA EL LIMITE DE LA SECUENCIA  yn=(1+1/n)^n CUANDO n TIENDE A INFINITO
/// EL ALGORITMO PARA CUANDO LA DIFERENCIA EN VALOR ABSOLUTO DE LA DIFERENCIA
/// ENTRE UN EL ELEMENTO Y EL ANTERIOR ES INFERIOR AL PARAMETRO tolerancia
real mn_limite1(real tolerancia);

/// FUNCIÓN QUE CALCULA EL LIMITE DE LA SECUENCIA  yn=sin(1/n)/(1/n) CUANDO n TIENDE A INFINITO
/// EL ALGORITMO PARA CUANDO LA DIFERENCIA EN VALOR ABSOLUTO DE LA DIFERENCIA
/// ENTRE UN EL ELEMENTO Y EL ANTERIOR ES INFERIOR AL PARAMETRO tolerancia
real mn_limite2(real tolerancia);

/// FUNCIÓN QUE CALCULA EL LIMITE DE LA SECUENCIA  yn=X(n+1)/X(n) DONDE X(n) ES LA
/// SUCESIÓN DE FIBONACCI DEFINIDA COMO X(n+1)=X(n)+X(n-1) EMPEZANDO POR X(1)=X(2)=1
/// EL ALGORITMO PARA CUANDO LA DIFERENCIA EN VALOR ABSOLUTO DE LA DIFERENCIA
/// ENTRE UN VALOR DE LA SECUENCIA yn Y EL ANTERIOR ES INFERIOR AL PARAMETRO tolerancia
/// EL LIMITE DE LA SECUENCIA yn ES EL NÚMERO AÚREO IGUAL A (1+SQRT(5))/2 = 1.618033988....
real mn_limite3(real tolerancia);

/// CÁLCULO DEL NÚMERO PI POR EL MÉTODO DE MONTECARLO. EL ÁREA DEL CÍRCULO DE RADIO 1
/// ES PI. Y EL AREA DEL CUADRADO DE LADO 2 DONDE SE INSCRIBE EL CÍRCULO ES 4. POR TANTO
/// SI SE ELIGE UN PUNTO AL AZAR EN EL CUADRADO, LA PROBABILIDAD DE QUE CAIGA EN
/// EL CÍRCULO ES PI/4. EL MÉTODO DE MONTECARLO APROXIMA PI COGIENDO PUNTOS AL AZAR EN
/// EL CUADRADO [-1,1]x[-1,1] Y VIENDO QUE PROPORCIÓN CAE EN EL CÍRCULO.
/// NOTA : LA FUNCIÓN rand() DEVUELVE UN VALOR ENTERO ALEATORIO ENTRE 0 Y RAND_MAX
real calculo_pi_montecarlo(int Nintentos);


#endif
