/** ================================================================
  MACROS Y DECLARACION DE TIPOS PARA GESTIONAR OPERACIONES CON
  MATRICES Y VECTORES
  ================================================================= */

#ifndef MN_LAPACK_H
#define MN_LAPACK_H

#include <math.h>
#include "mn_aritmeticas.h"
#include "tnt_array/tnt.h"
using namespace TNT;

/// DECLARACION DE TIPOS PARA LAS FUNCIONES DE MN_LAPACK

/// FACTORIZACIÓN LU
int mn_LU_factorization(Array2D< real > &A,Array2D< real > &L,Array2D< real > &U);

/// RESOLUCIÓN SISTEMA A PARTIR FACTORIZACIÓN LU
Array1D< real > mn_LU(Array2D< real > &L,Array2D< real > &U, Array1D< real > &b);

/// FUNCION PARA RESOLVER UN SISTEMA TRIANGULAR INFERIOR
Array1D< real > mn_descenso (Array2D< real > &B, Array1D< real > &b);

/// FUNCION PARA RESOLVER UN SISTEMA TRIANGULAR SUPERIOR
Array1D< real > mn_remonte (Array2D< real > &B,Array1D< real > &z);

/// FUNCION PARA CALCULAR LA FACTORIZACIÓN LU
Array2D< real > mn_gauss_inversa(const Array2D< real > &A);

/** FUNCION PARA LEER UNA MATRIZ DE DISCO DE DIMENSION dimension Y LO ALMACENA EN LA MATRIZ matriz  */
int mn_leer_matriz( char *nombrefichero,  Array2D< real > &matriz);

/** FUNCION PARA ESCRIBIR UNA MATRIZ DE DISCO DE DIMENSION dimension */
int mn_escribir_matriz( char *nombrefichero,  Array2D< real > &vmatriz);


#endif

