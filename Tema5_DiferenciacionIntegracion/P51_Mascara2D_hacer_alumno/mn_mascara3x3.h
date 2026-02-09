
// SI EL FICHERO HA SIDO INCLUIDO PREVIAMENTE POR OTRO INCLUDE NO SE AÑADE
// PARA EVITAR ERRORES POR TENER REPETIDA UNA FUNCION
#ifndef MN_INTERPOLACION_H
#define MN_INTERPOLACION_H
#include "tnt_array/tnt.h"
using namespace TNT;

// DECLARACION DE TIPOS DE LAS FUNCIONES BASICAS
Array2D< real > mn_mascara3x3(Array2D< real > &F,Array2D< real > &m);
Array2D< real > mn_calculo_bordes(Array2D< real > &I,int NiteracionesFiltroSuavizado,
                                  double percentil_gradiente,Array2D< real > &Ig);

#endif
