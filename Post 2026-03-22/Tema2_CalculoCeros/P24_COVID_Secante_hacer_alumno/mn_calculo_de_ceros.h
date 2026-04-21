#include <stdlib.h>
#include <math.h>
#include "mn_aritmeticas.h"
#include "tnt_array/tnt.h"
using namespace TNT;

/// DISTRIBUCIÓN GAMMA
real Gamma(real x);

/// DERIVADA DE LA DISTRIBUCIÓN GAMMA
real Gammap(real x);

/// CALCULO DE LOS PARÁMETROS DE LA DISTRIBUCIÓN GAMMA A PARTIR DE LA
/// MEDIA Y VARIANZA MUESTRAL
void calculo_parametros_Gamma(real media, real varianza);

/// MÉTODO DE LA SECANTE
int mn_secante (real (*f)( real),real &x0,real &x1,int NiterMax,real TOL);
