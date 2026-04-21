#include <stdio.h>
#include "../mn_calculo_de_ceros.h"
#include <stdlib.h>
using namespace std;

/// PRACTICA PROGRAMACIÓN TEMA 2
/// ESTUDIO DEL TIEMPO QUE TARDAN EN PRESENTAR SÍNTOMAS LAS PERSONAS INFECTADAS POR LA COVID-19
/// ESTUDIAREMOS EL INTERVALO DE TIEMPO EN QUE LA MAYOR PARTE DE LOS INFECTADOS PRESENTAN SÍNTOMAS
/// Y EL DÍA TRAS LA INFECCIÓN DONDE ES MÁS PROBABLE PRESENTAR SÍNTOMAS
/// PARA ESTIMAR EL INTERVALO DE TIEMPO DONDE LA MAYOR PARTE DE INFECTADO PRESENTA SÍNTOMAS
/// ESTUDIAREMOS EN QUE DÍA EL 1% DE LOS INFECTADOS EMPIEZA A PRESENTAR SINTOMAS. EXISTEN DOS RESPUESTAS POSIBLES:
///    (1) EN LOS PRIMEROS DÍAS QUE CORRESPONDE AL PRINCIPIO DEL PERIODO EN QUE LOS INFECTADOS EMPIEZAN A PRESENTAR SÍNTOMAS (ESTE GRUPO DE PERSONAS PRESENTA SÍNTOMAS MUY PRONTO)
///    (2) EN LOS ÚLTIMOS DÍAS QUE CORRESPONDE AL FINAL DEL PERIODO EN QUE LOS INFECTADOS PUEDEN PRESENTAR SÍNTOMAS (ESTE GRUPO DE PERSONAS PRESENTA SÍNTOMAS MUY TARDE)
/// PARA RESPONDER A ESTAS PREGUNTAS SE UTILIZA UNA MUESTRA DEL NÚMERO DE CASOS QUE PRESENTAN SINTOMAS EN FUNCIÓN DE LOS DÍAS PASADOS DESDE LA INFECCIÓN
/// LOS DATOS DE ESTA MUESTRA SE ENCUENTRAN EN EL FICHERO muestra.csv
/// LA MUESTRA SE APROXIMA POR UNA DISTRIBUCIÓN GAMMA Y SE CALCULARÁ A PARTIR DE ELLA LAS SOLUCIONES AL PROBLEMA


/// PARAMETROS DE LA DISTRIBUCIÓN Gamma
extern real d,alfa,beta;

/// DEFINIMOS UNA FUNCIÓN AUXILIAR PARA EXPRESAR LA ECUACIÓN Gamma(x)=0.01 COMO f(x)=0
real f(real x){ return Gamma(x)-0.01;}

///    PROGRAMA PRINCIPAL
int main()
{
  /// LEEMOS LA MUESTRA DEL NÚMERO DE CASOS QUE PRESENTAN SINTOMAS
  /// EN FUNCIÓN DE LOS DÍAS PASADOS DESDE LA INFECCIÓN
  Array1D<real> data("muestra.csv");

  /// CALCULAMOS LA MEDIA Y VARIANZA MUESTRALES DEL NÚMERO DE DÍAS
  ///QUE PASAN DESDE LA INFECCIÓN A PRESENTAR SÍNTOMAS
  real media=0,varianza=0,NumeroCasos=0;
  for(int k=0;k<data.dim();k++){
    media+=k*data[k];
    NumeroCasos+=data[k];
  }
  media/=NumeroCasos;

  for(int k=0;k<data.dim();k++){
    varianza+=data[k]*(media-k)*(media-k);
  }
  varianza/=NumeroCasos;

  cout << "media = " << media  << " varianza = " << varianza << "\n";

  /// CALCULAMOS LOS PARÁMETROS DE LA DISTRIBUCIÓN GAMMA A PARTIR
  /// DE LA MEDIA Y VARIANZA MUESTRALES
  calculo_parametros_Gamma(media,varianza);

  /// CALCULAMOS CUANDO Gamma(x)=0.01 USANDO EL MÉTODO DE LA BISECCIÓN
  /// CALCULO EN LOS PRIMEROS DÍAS TRAS LA INFECCIÓN
  real a=0.1, b=media;
  real TOL=1e-8;
  int NumeroIteraciones;
  real x0=mn_biseccion (f, a, b, TOL,NumeroIteraciones);
  cout << "\nBiseccion     : x0 = " << x0 << " , N. iteraciones = " <<
  NumeroIteraciones << " , Gamma(x0) = " << Gamma(x0) << "\n";

  /// CALCULO EN LOS ÚLTIMOS DÍAS TRAS LA INFECCIÓN
  a=media, b=20;
  real x1=mn_biseccion (f, a, b, TOL,NumeroIteraciones);
  cout << "\nBiseccion     : x1 = " << x1 << " , N. iteraciones = " <<
  NumeroIteraciones << " , Gamma(x1) = " << Gamma(x1) << "\n";

  /// CALCULO DE DONDE ALCANZA EL MÁXIMO LA DISTRIBUCIÓN GAMMA
  ///USANDO EL MÉTODO DE LA BISECCIÓN
  a=x0, b=x1;
  real xmax=mn_biseccion (Gammap, a, b, TOL,NumeroIteraciones);
  cout << "\nBiseccion     : xmax = " << xmax << " , N. iteraciones = " <<
  NumeroIteraciones << " , Gamma(xmax) = " << Gamma(xmax) <<", Gammap(xmax) = " << Gammap(xmax) <<"\n";

  /// POR TANTO, LAS CONCLUSIONES DEL ESTUDIO BASADOS EN ESTA MUESTRA Y SU APROXIMACIÓN POR UNA DISTRIBUCIÓN GAMMA SON LAS SIGUIENTES:
  cout << "\nCONCLUSIONES DEL ESTUDIO\n";
  cout << "La mayor parte de infectados que presenta sintomas, lo hace entre los dias "  << x0 << " y " << x1 << " despues de la infeccion\n";
  cout << "La media de dias que se tarda en presentar sintomas es : "  << media << "\n";
  cout << "El dia que es mas probable presentar sintomas es : "  << xmax << " dias despues de la infeccion\n";


}


