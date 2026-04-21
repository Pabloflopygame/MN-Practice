#include <stdlib.h>
#include <math.h>
#include "mn_aritmeticas.h"
#include "tnt_array/tnt.h"
using namespace TNT;

#ifndef MN_UTILIDADES_H
#define MN_UTILIDADES_H

/// EVALUACIÓN DE LA DISTRIBUCIÓN LOG-NORMAL
real log_normal(real x,Array1D< real > &u);

/// -------------------------------------------------------------
/// FUNCIÓN PARA INICIALIZAR LOS PARÁMETROS DE LA LOG-NORMAL
/// USANDO LA MEDIA Y LA VARIANZA MUESTRALES
Array1D<real> Inicializar_log_normal(Array1D<real> &x,Array1D<real> &y);

/// --------------------------------------------------------------------------------
/// FUNCIÓN QUE CALCULA PERCENTILES DE UNA DISTRIBUCIÓN LOG-NORMAL
real percentil_log_normal(Array1D<real> &u,int percentil);

/// --------------------------------------------------------------------------------
/// FUNCIÓN QUE CALCULA LA MEDIA DE UNA DISTRIBUCIÓN LOG-NORMAL
real media_log_normal(Array1D<real> &u);

/// --------------------------------------------------------------------------------
/// FUNCIÓN QUE CALCULA DONDE ALCANZA EL MÁXIMO UNA DISTRIBUCIÓN LOG-NORMAL
real pico_log_normal(Array1D<real> &u);

/// --------------------------------------------------------------------------------
/// FUNCIÓN QUE CALCULA EL MÁXIMO DE UNA DISTRIBUCIÓN LOG-NORMAL
real maximo_log_normal(Array1D<real> &u);

#endif
