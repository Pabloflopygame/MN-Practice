#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../mn_aritmeticas.h"
#include "../mn_interpolacion.h"
#include "../mn_svg.h"

main()
{
   /// PRÁCTICA DE INTERPOLACIÓN POR EL MÉTODO DE INTERPOLACIÓN LINEAL
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

  /// COMPARAMOS LOS RESULTADOS OBTENIDOS CON LOS QUE DEBERÍAN SALIR Y
  /// QUE PREVIAMENTE HEMOS ALMACENADO EN interpolacion.csv
  Array1D< real > res("interpolacion.csv");

  printf("      edad     alumno   -    real\n");
  for(int k=0;k<res.dim();k++){
    printf("edad = %d ->  %lf - %lf\n",5+5*k,mn_interpolacion_lineal(edad,fallecimientos,5.+5.*k),res[k]);
  }

  /// APLICACIÓN A LA INTERPOLACIÓN DE CURVAS 2D. LOS DATOS INICIALES SON DOS VECTORES
  /// DE PUNTOS (x[k],y[k]) QUE REPRESENTAN PUNTOS DE UNA CURVA 2D Y QUEREMOS INTERPOLAR
  /// PUNTOS INTERMEDIOS. PARA ELLO APLICAREMOS LA INTERPOLACIÓN LINEAL A LOS VECTORES

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

  /// CREAMOS UN NUEVO VECTOR DE PUNTOS DE LA CURVA INTERPOLADOS
  /// MANTENIENDO UNA DISTANCIA ENTRE ELLOS DE 25
  Array1D< real > xn,yn;
  xn.push_back(x[0]);
  yn.push_back(y[0]);
  real longitud=0;
  for(real k=0;k<t[3];k+=0.1){
    real x2=mn_interpolacion_lineal(t,x,k);
    real y2=mn_interpolacion_lineal(t,y,k);
    real x3=mn_interpolacion_lineal(t,x,k+0.1);
    real y3=mn_interpolacion_lineal(t,y,k+0.1);
    real dist=sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
    longitud+=dist;
    if(longitud>25){
      longitud=0;
      xn.push_back(x3);
      yn.push_back(y3);
    }
  }

  printf("\nAPLICACION A LA INTERPOLACION DE CURVAS 2D\n");
  printf("GUARDAMOS EN DISCO EN FORMATO SVG LA CURVA ORIGINAL Y LA GENERADA\n");
  printf("EN LA MEMORIA DE ENTREGA DEL EJERCICIO HAY QUE INCLUIR IMAGENES CON EL RESULTADO\n");
  write_svg(x,y,"curva_original.svg",0.,0.,0.,0.,3.,7.);
  write_svg(xn,yn,"curva.svg",0.,0.,0.,0.,3.,7.);



}
