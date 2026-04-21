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

/// APROXIMACIÓN DERIVADA PRIMERA DE UNA FUNCIÓN
real mn_derivada1(real (*f)( real),real x);

/// APROXIMACIÓN DERIVADA SEGUNDA  DE UNA FUNCIÓN
real mn_derivada2(real (*f)( real),real x);

/// MÉTODO DE NEWTON-RAPHSON
int mn_muller (real (*f)( real),real &root,int Nmax,real TOL);
