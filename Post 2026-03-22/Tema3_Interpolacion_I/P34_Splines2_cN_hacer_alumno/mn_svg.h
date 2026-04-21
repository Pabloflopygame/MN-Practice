#ifndef MN_SVG_H
#define MN_SVG_H

#include <iostream>
#include "tnt_array/tnt.h"
#include "mn_aritmeticas.h"
using namespace TNT;

/// FUNCIÓN PARA ESCRIBIR UNA CURVA 2D EN FORMATO SVG AÑADIENDO
/// EL VECTOR DE LA DERIVADA EN EL PUNTO INICIAL Y FINAL
void write_svg(Array1D< real > &x, Array1D< real > &y, char name[300],
               real dx,real dy,real dxn,real dyn,int linewidth,int circlewidth);



#endif
