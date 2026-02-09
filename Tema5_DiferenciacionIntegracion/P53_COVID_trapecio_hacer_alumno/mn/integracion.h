#include <stdlib.h>
#include <math.h>
#include "mn_aritmeticas.h"
#include "tnt_array/tnt.h"
using namespace TNT;

/// INTERPOLACION LINEAL (SE SUPONE QUE LOS PUNTOS DE INTERPOLACIÓN SON 0,1,2,3...)
real interpolacion_lineal(Array1D<real> &f,real x);

/// FUNCION PARA CALCULAR UNA INTEGRAL POR EL METODO DE SIMPSON
/// UTILIZANDO N INTERVALOS EN UN INTERVALO [a,b]
real trapecio(real (*f)(real x), real a, real b, int N);
