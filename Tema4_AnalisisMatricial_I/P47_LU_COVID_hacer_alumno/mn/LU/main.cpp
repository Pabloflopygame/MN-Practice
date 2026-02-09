/// APLICACIÓN DEL MÉTODO DE GAUSS AL ESTUDIO DE LA TRANSMISIÓN DE LA COVID-19 POR TRAMOS DE EDAD

#include <stdio.h>
#include "../mn_lapack.h"
#include <stdlib.h>

///PROGRAMA PRINCIPAL.
int main()
{
  /// NÚMERO REPRODUCTIVO BÁSICO QUE INDICA CUANTAS PERSONAS
  /// (EN MEDIA) CONTAGIA CADA CONTAGIADO
  real R=3;

  /// NÚMERO DE GENERACIONES QUE SE VAN A GENERAR
  int Ngeneraciones=11;

  /// LA GENERACIÓN 0 ES UNA SOLA PERSONA EN EL TRAMO DE EDADES ENTRE 10 Y 15 AÑOS
  /// QUE CORRESPONDE AL INDICE 2 DEL VECTOR DONDE SE ACUMULAN LOS CASOS

  /// LEEMOS LA MATRIZ DE CONTACTOS
  Array2D< real > A;
  int N=mn_leer_matriz("MatrizContactosSociales.txt",A);

   /// DEFINIMOS EL VECTOR CON LA GENERACION CERO
  Array1D< real > u0(A.dim1(),0.);
  u0[2]=1.;

  /// CALCULAMOS LA GENERACIÓN 11 TENIENDO EN CUENTA QUE EN CADA GENERACIÓN EL NÚMERO TOTAL DE CASOS
  /// SE MULTIPLICA POR R Y ES PROPORCIONAL A LOS CONTACTOS GENERADOS POR LA GENERACIÓN ANTERIOR.

  /// HACEMOS UNA COPIA DEL VECTOR ORIGINAL DONDE CALCULAREMOS LA GENERACIÓN 11
  Array1D< real > u11=u0.copy();
  for(int k=0;k<Ngeneraciones;k++){
    Array1D< real > c=A*u11;
    u11=c*(R*u11.suma()/c.suma());
  }

  /// RECUPERAMOS LA GENERACIÓN CERO A PARTIR DE LA GENERACIÓN 11 HACIENDO EL PROCESO INVERSO
  /// HACEMOS UNA COPIA DEL VECTOR DE LA GENERACIÓN 11 PARA RECUPERAR LA GENERACION 0
  Array1D< real > u0_new=u11.copy();

  /// FACTORIZACIÓN LU
  Array2D< real > L,U;
  int error= mn_LU_factorization(A,L,U);
  for(int k=Ngeneraciones-1;k>=0;k--){
    Array1D< real > z=mn_LU(L,U,u0_new);
    u0_new=z*((u0_new.suma()/z.suma())/R);
  }

  /// IMPRIMIMOS LOS RESULTADOS
  printf("generacion 0 :\n");
  for(int k=0;k<u0.dim();k++) printf("%1.0lf, ", (double) u0[k]);
  printf("\n\n");

  printf("generacion %d :\n",Ngeneraciones);
  for(int k=0;k<u0.dim();k++) printf("%1.0lf, ",(double) u11[k]);
  printf("\n\n");

  printf("CONCLUSIONES GENERACION %d\n",Ngeneraciones);
  printf("El mayor numero de casos es 17727, que corresponde a la edad [35-40]\n");
  printf("El menor numero de casos es 5213, que corresponde a la edad [70-75]\n\n");

  printf("Precision de la aritmetica (numero de bits de la mantisa) = %d\n",mn_precision_aritmetica());
  printf("Recuperando generacion 0 con esta precision de la aritmetica:\n");
  for(int k=0;k<u0.dim();k++) printf("%1.1lf, ",(double) u0_new[k]);
  printf("\n\n");



  /// CONCLUSIONES
  /// SE DEBE OBSERVAR QUE LA PRECISIÓN CON LA QUE SE RECUPERA LA GENERACION CERO
  /// DEPENDE MUCHO DE LA PRECISIÓN DE LA ARITMÉTICA. HAY QUE EJECUTAR EL CÓDIGO
  /// USANDO LAS PRECISIONES float, double Y long double Y DISCUTIR LAS DIFERENCIAS
  /// EN LAS CONCLUSIONES. POR TANTO HAY QUE PRESENTAR 3 VENTANAS DE EJECUCIÓN (UNA
  /// PARA float, OTRA PARA double Y OTRA PARA long double.
  /// LOS RESULTADOS PUEDEN SER DISTINTOS SEGÚN EL COMPILADOR DE C++ QUE SE USE

  // AYUDA SINTAXIS C++ IMPRIMIR POR PANTALLA
  //cout << "El numero " << 5 << " es entero, y el numero " << 5.1 << " es real\n";
  //printf("El numero %d es entero, el numero %1.2lf es real que se imprime con 2 decimales y %s es un string\n",5,5.1395,"STRING");
  //printf("el numero %1.0lf es un real que se imprime con 0 decimales y %1.3lf con 3 decimales \n",5.7345,5.7345);
   return 0;
}



