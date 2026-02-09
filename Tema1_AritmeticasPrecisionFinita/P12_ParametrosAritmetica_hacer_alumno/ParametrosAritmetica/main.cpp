/// INCLUSION DE LA LIBRERIA STANDARD PARA GESTIONAR ENTRADA-SALIDA
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

/// INCLUSION DE LA LIBRERIA PARA GESTIONAR LA ARITMETICA
#include "../mn_aritmeticas.h"

main(){


  /// CALCULAMOS LA PRECISION (UNIDAD DE REDONDEO) DE LA ARITMETICA
  real p=mn_precision_aritmetica();
  cout << "Calculo precision aritmetica \n";
  cout << "  Resultado con precision float : u = 1.19209e-007\n";
  cout << "  Resultado con precision double : u = 2.22045e-016\n";
  cout << "  Resultado con precision long double : u = 1.0842e-019\n";
  cout << "  Resultado obtenido por el alumno : u = " << p <<"\n\n";



  /// CALCULAMOS EL NUMERO MAS PEQUEÑO
  int menor=mn_menor_numero_positivo();
  cout << "Calculo numero positivo mas pequeno de la aritmetica \n";
  cout << "  Resultado con precision float : 2^M con M = -149\n";
  cout << "  Resultado con precision double : 2^M con M = -1074\n";
  cout << "  Resultado con precision long double : 2^M con M = -16445\n";
  cout << "  Resultado obtenido por el alumno : 2^M con M  = -" << menor <<"\n\n";

  /// CALCULAMOS EL NUMERO MAS GRANDE
  int mayor=mn_mayor_numero_positivo();
  cout << "Calculo numero positivo mas pequeno de la aritmetica \n";
  cout << "  Resultado con precision float : 2^M con M = 127\n";
  cout << "  Resultado con precision double : 2^M con M = 1023\n";
  cout << "  Resultado con precision long double : 2^M con M = 16383\n";
  cout << "  Resultado obtenido por el alumno : 2^M con M  = " << mayor <<"\n\n";

  /// CALCULAMOS DIFERENCIA RELATIVA ENTRE 2 NUMEROS
  real A=1000.;
  real B=1001.;
  cout << "\nCalculo distancia relativa entre los numeros 1000 y 1001\n";
  cout << " Resultado que se debe obtener :  mn_distancia(1000.,1001.) = " << "0.000998004" << "\n";
  cout << " Resultado obtenido por el alumno :  mn_distancia(1000.,1001.) = " << mn_distancia(A,B) << "\n\n";


  cout << "HACEMOS ALGUNAS OPERACIONES PARA MANEJAR EXCEPCIONES\n\n";
  real Inf=1./0.;
  cout << "INFINITO = 1./0. = " << Inf <<"\n";


  real C=Inf*0.;
  cout << "INFINITO * 0. = (1./0.)*0. = " << C <<"\n";

  real D=1./Inf;
  cout << "UNO / INFINITO = 1./(1./0.) = " << D <<"\n";

  real E=sqrt((double) -1.);
  cout << "RAIZ CUADRADA DE -1 = sqrt(-1.) = " << E << "\n";

  real F;
  cout << "IMPRIMIMOS VARIABLE SIN INICIALIZAR : " << F << "\n\n";

  /// HACEMOS UNA PAUSA EN EL PROGRAMA PARA PODER EXAMINAR EL RESULTADO POR CONSOLA
  system("pause");

}


