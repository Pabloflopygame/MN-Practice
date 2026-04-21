/*==========================================================================
       PRACTICA 3 METODOS NUMERICOS. INTERPOLACION
  ==========================================================================*/

// INCLUSION DE LA LIBRERIA STANDARD PARA GESTIONAR ENTRADA-SALIDA
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../mn_aritmeticas.h"
#include "../mn_interpolacion.h"
#include "../mn_svg.h"


main()
{

   /// PRÁCTICA DE INTERPOLACIÓN POR EL MÉTODO DE SPLINES DE GRADO 3 CON LA CONDICIÓN cN=0
   /// SE ESTUDIA EL NÚMERO DE FALLECIMIENTOS POR EDAD DE LA PRIMERA OLA DE
   /// LA COVID EN ESPAÑA. COMO LOS DATOS PÚBLICOS SON POR GRUPOS DE EDAD,
   /// PARA ESTIMAR LOS FALLECIDOS POR CADA EDAD HACE FALTA UN PROCESO DE
   /// INTERPOLACIÓN. TOMAMOS COMO PUNTOS DE INTERPOLACIÓN LA MEDIA DE EDAD
   /// DE CADA GRUPO QUE SON 10, 22.5, 35, 45, 55, 65, 75 Y 85 AÑOS, Y
   /// TOMAMOS COMO VALORES DE LA FUNCIÓN A INTERPOLAR EL NÚMERO DE FALLECIDOS
   /// OBSERVADOS PARA ESE TRAMO DE EDAD DIVIDIDO POR EL NÚMERO DE EDADES DEL GRUPO
   /// TODA LA INFORMACIÓN LA LEEMOS DE FICHEROS

   /// EN LA SEGUNDA PARTE DE LA PRÁCTICA PRESENTAREMOS UNA APLICACIÓN A LA INTERPOLACIÓN
   /// DE CURVAS 2D.

  /// LEEMOS LOS DATOS
  Array1D< real > edad("COVID_edad.txt");
  Array1D< real > fallecimientos("COVID_fallecimientos.txt");

  /// CÁLCULO POLINOMIOS SPLINES DE GRADO 3
  Array1D< real > a,b,c,d;
  real c0=0.;
  real cN=0;
  int error = mn_calculo_splines_3(edad,fallecimientos,c0,cN,a,b,c,d);

  /// COEFICIENTES SPLINES PRECALCULADOS
  Array1D< real > coef_a("coeficientes_splines_a.txt");
  Array1D< real > coef_b("coeficientes_splines_b.txt");
  Array1D< real > coef_c("coeficientes_splines_c.txt");
  Array1D< real > coef_d("coeficientes_splines_d.txt");

  printf("COEFICIENTES SPLINES GRADO 3:\n");
  printf("a alumno - a real | b alumno - b real | c alumno - c real  | d alumno - d real\n");
  for(int k=0;k<a.dim();k++){
    printf("%1.2lf  -   %1.2lf    %1.2lf   -   %1.2lf     %1.2lf    -   %1.2lf     %1.2lf    -   %1.2lf\n",
           a[k],coef_a[k],b[k],coef_b[k],c[k],coef_c[k],d[k],coef_d[k]);

  }

  /// COMPARAMOS LOS RESULTADOS OBTENIDOS CON LOS QUE DEBERÍAN SALIR Y
  /// QUE PREVIAMENTE HEMOS ALMACENADO EN interpolacion.csv
  Array1D< real > res("interpolacion.csv");

  printf("\n      edad     alumno   -    real\n");
  for(int k=0;k<res.dim();k++){
    printf("edad = %d ->  %lf - %lf\n",5+5*k,mn_evaluar_splines_3(edad,a,b,c,d,5.+5.*k),res[k]);
  }

  /// APLICACIÓN A LA INTERPOLACIÓN DE CURVAS 2D. LOS DATOS INICIALES SON DOS VECTORES
  /// DE PUNTOS (x[k],y[k]) QUE REPRESENTAN PUNTOS DE UNA CURVA 2D Y QUEREMOS INTERPOLAR
  /// PUNTOS INTERMEDIOS. PARA ELLO APLICAREMOS LA INTERPOLACIÓN POR SEPARADO A LOS VECTORES
  /// x E y. AÑADIREMOS COMO CONDICIÓN INICIAL LOS VALORES DE c0 y cN EN EL PUNTO INICIAL Y
  /// FINAL DE LA CURVA

  /// DEFINICIÓN DE LOS PUNTOS DE LA CURVA
  Array1D< real > x(4);
  Array1D< real > y(4);
  Array1D< real > t(4);
  x[0]=100; y[0]=100;
  x[1]=300; y[1]=300+200;
  x[2]=700; y[2]=700-100;
  x[3]=924; y[3]=924;

  /// DEFINICIÓN DE LOS PUNTOS DE INTERPOLACIÓN DE LA CURVA DADO POR EL VECTOR t. EMPEZAMOS EN 0
  /// Y VAMOS AÑADIENDO LA LONGITUD DE LOS SEGMENTOS DE LA CURVA
  t[0]=0;
  for(int k=1;k<4;k++){
    t[k]=t[k-1]+sqrt((x[k]-x[k-1])*(x[k]-x[k-1])+(y[k]-y[k-1])*(y[k]-y[k-1]));
  }

  /// DEFINIMOS LOS PARÁMETROS INICIAL Y FINAL DE LA CURVA
  real c0x=0.;
  real cNx=0.;
  real c0y=0.;
  real cNy=0.;

  /// CALCULAMOS LOS SPLINES PARA x E y
  Array1D< real > ax,bx,cx,dx,ay,by,cy,dy,xn,yn;
  error = mn_calculo_splines_3(t,x,c0x,cNx,ax,bx,cx,dx);
  error = mn_calculo_splines_3(t,y,c0y,cNy,ay,by,cy,dy);

  /// CREAMOS UN NUEVO VECTOR DE PUNTOS DE LA CURVA INTERPOLADOS
  /// MATENIENDO UNA DISTANCIA ENTRE ELLOS DE 25
  xn.push_back(x[0]);
  yn.push_back(y[0]);
  real longitud=0;
  for(real k=0;k<t[3];k+=0.1){
    real x2=mn_evaluar_splines_3(t,ax,bx,cx,dx, k);
    real y2=mn_evaluar_splines_3(t,ay,by,cy,dy, k);
    real x3=mn_evaluar_splines_3(t,ax,bx,cx,dx, k+0.1);
    real y3=mn_evaluar_splines_3(t,ay,by,cy,dy, k+0.1);
    real dist=sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
    longitud+=dist;
    if(longitud>25){
      longitud=0;
      xn.push_back(x3);
      yn.push_back(y3);
    }
  }

  /// CALCULO DE LAS DERIVADAS EN EL PUNTO INICIAL Y FINAL
  real dx0=bx[0];
  real dy0=by[0];
  real dxN=bx[2]+2*cx[2]*(t[3]-t[2])+3*dx[2]*(t[3]-t[2])*(t[3]-t[2]);
  real dyN=by[2]+2*cy[2]*(t[3]-t[2])+3*dy[2]*(t[3]-t[2])*(t[3]-t[2]);

  printf("\nAPLICACION A LA INTERPOLACION DE CURVAS 2D\n");
  printf("GUARDAMOS EN DISCO EN FORMATO SVG LA CURVA ORIGINAL Y LA GENERADA\n");
  printf("EN LA MEMORIA DE ENTREGA DEL EJERCICIO HAY QUE INCLUIR IMAGENES CON EL RESULTADO\n");
  write_svg(x,y,"curva_original.svg",0.,0.,0.,0.,3.,7.);
  write_svg(xn,yn,"curva.svg",dx0,dy0,-dxN,-dyN,3.,7.);

}
