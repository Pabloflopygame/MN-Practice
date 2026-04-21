#include <stdlib.h>
#include <math.h>
#include "mn_aritmeticas.h"
#include "tnt_array/tnt.h"
using namespace TNT;


int mn_gradiente_descendente(real  (*F)(Array1D< real >), Array1D< real > &u,real TOL,real h,int Nmax);
real mn_beneficio(Array1D< real > u);
