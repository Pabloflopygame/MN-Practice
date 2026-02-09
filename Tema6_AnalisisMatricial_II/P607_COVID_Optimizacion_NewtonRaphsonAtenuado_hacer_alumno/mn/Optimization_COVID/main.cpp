#include <stdio.h>
#include "../mn_optimizacion.h"
#include "../mn_lapack.h"
#include "../mn_utilidades.h"
#include <stdlib.h>

/// VARIABLE GLOBAL CON EL VALOR DE LA POTENCIA p DEL FUNCIONAL ERROR A MINIMIZAR
extern real p_;

///    PROGRAMA PRINCIPAL
int main()
{
  /// DECLARAMOS VARIABLES
  real h=1e-4; /// PASO PARA CALCULAR LAS DERIVADAS
  real TOL=1e-8; /// TOLERANCIA PARA PARAR LAS ITERACIONES
  int Nmax=10000; /// NÚMERO MÁXIMO ITERACIONES NEWTON-RAPHSON ATENUADO

  /// LEEMOS LOS DÍAS QUE TARDAN EN PRODUCIRSE SÍNTOMAS ENTRE
  /// UN CASO PRIMARIO Y SECUNDARIO (EL ARRAY VA DESDE -5 HASTA 24)
  Array1D<real> x("dias.csv");

  /// LEEMOS EL HISTOGRAMA DEL NUMERO DE CASOS, y[k], DONDE EL CASO
  /// SECUNDARIO PRESENTA SÍNTOMAS x[k] DÍAS DESPUÉS DEL CASO PRIMARIO
  Array1D<real> y("serial_interval.csv");

  /// DISTRIBUCIÓN INICIAL DE LOS PARAMETROS DE LA LOG-NORMAL QUE SE
  /// OBTIENEN A PARTIR DE LA MEDIA Y VARIANZA MUESTRALES
  Array1D<real> uI=Inicializar_log_normal(x,y);

  /// DISTRIBUCIÓN OBTENIDA POR EL MÉTODO DE NEWTON-RAPHSON ATENUADO CON p=2
  /// INICIALIZAMOS EL VECTOR DE PARÁMETROS AL OBTENIDO INICIALMENTE
  /// OPTIMIZAMOS LOS PARÁMETROS USANDO NEWTON-RAPHSON ATENUADO
  p_=2;
  Array1D<real> up2=uI.copy();
  int Niterp2 = mn_newton_raphson_atenuado(Error_p,up2,h,TOL,Nmax);

  /// DISTRIBUCIÓN OBTENIDA POR EL MÉTODO DE NEWTON-RAPHSON ATENUADO CON p=1
  /// INICIALIZAMOS EL VECTOR DE PARÁMETROS AL OBTENIDO INICIALMENTE
  /// OPTIMIZAMOS LOS PARÁMETROS USANDO NEWTON-RAPHSON ATENUADO
  p_=1.;
  Array1D<real> up1=uI.copy();
  int Niterp1 = mn_newton_raphson_atenuado(Error_p,up1,h,TOL,Nmax);


  /// IMPRIMIMOS RESULTADOS POR PANTALLA
  p_=2;
  printf("p=%1.0lf LOG-NORMAL INICIAL             : a=%1.3lf, b=%1.3lf, c=%1.3lf, d=%1.3lf,  Error=%1.3lf\n",p_,uI[0],uI[1],uI[2],uI[3],Error_p(uI));
  printf("p=%1.0lf LOG-NORMAL OPTIMIZADA (real)   : a=%1.3lf, b=%1.3lf, c=%1.3lf, d=%1.3lf,  Error=%1.3lf, Iter=%d\n",p_,-4.601,2.382,0.242,694.881,565.434,16);
  printf("p=%1.0lf LOG-NORMAL OPTIMIZADA (alumno) : a=%1.3lf, b=%1.3lf, c=%1.3lf, d=%1.3lf,  Error=%1.3lf, Iter=%d\n\n",p_,up2[0],up2[1],up2[2],up2[3],Error_p(up2),Niterp2);
  p_=1;
  printf("p=%1.0lf LOG-NORMAL INICIAL             : a=%1.3lf, b=%1.3lf, c=%1.3lf, d=%1.3lf,  Error=%1.3lf\n",p_,uI[0],uI[1],uI[2],uI[3],Error_p(uI));
  printf("p=%1.0lf LOG-NORMAL OPTIMIZADA (real)   : a=%1.3lf, b=%1.3lf, c=%1.3lf, d=%1.3lf,  Error=%1.3lf, Iter=%d\n",p_,-4.998,2.409,0.192,689.000,96.090,436);
  printf("p=%1.0lf LOG-NORMAL OPTIMIZADA (alumno) : a=%1.3lf, b=%1.3lf, c=%1.3lf, d=%1.3lf,  Error=%1.3lf, Iter=%d\n\n",p_,up1[0],up1[1],up1[2],up1[3],Error_p(up1),Niterp1);

  printf("ALGUNAS CONCLUSIONES UTILIZANDO LA LOG-NORMAL OPTIMIZADA CON p=1:\n");
  printf("(real)  : EL TIEMPO MEDIO QUE TRANSCURRE ENTRE PRESENTACION DE SINTOMAS ES DE %1.2lf DIAS\n",7.242044);
  printf("(alumno): EL TIEMPO MEDIO QUE TRANSCURRE ENTRE PRESENTACION DE SINTOMAS ES DE %1.2lf DIAS\n",media_log_normal(up1));
  printf("(real)  : EN EL 90%% DE LOS CASOS EL TIEMPO ENTRE PRESENTACION DE SINTOMAS ESTA ENtre %1.2lf y %1.2lf DIAS\n",3.103868,10.257990);
  printf("(alumno): EN EL 90%% DE LOS CASOS EL TIEMPO ENTRE PRESENTACION DE SINTOMAS ESTA ENtre %1.2lf y %1.2lf DIAS\n",percentil_log_normal(up1,5),percentil_log_normal(up1,95));

  printf("\nGUARDAMOS EN DISCO LOS RESULTADOS EN resultados.csv\n");
  printf("HAY QUE PONER EN LA MEMORIA UNA GRAFICA EXCEL EXPLICADA CON LOS RESULTADOS\n");
  FILE *f;
  f=fopen("resultados.csv","w");
  fprintf(f,"dias;muestra,log-normal inicial,log-normal optimizada p=2, log-normal optimizada p=1\n");
  for(int k=0;k<x.dim();k++){
    fprintf(f,"%1.0lf,%lf,%lf,%lf,%lf\n",x[k],y[k],log_normal(x[k],uI),log_normal(x[k],up2),log_normal(x[k],up1));
  }

  fclose(f);

  // AYUDA GESTIÓN FICHERO
  //FILE *f;
  //f=fopen("resultados.csv","w");
  //fprintf(f,"dias;muestra;log-normal inicial;log-normal optimizada p=2; log-normal optimizada p=1;log-normal optimizada p=10\n");
  //fprintf(f,"%1.0lf;%lf;%lf;%lf;%lf;%lf\n",1.,2.,3.,4.,5.,6.);
  //fclose(f);

}


