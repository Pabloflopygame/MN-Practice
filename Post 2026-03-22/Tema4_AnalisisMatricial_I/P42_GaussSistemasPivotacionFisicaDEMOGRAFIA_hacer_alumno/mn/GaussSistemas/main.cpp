/// APLICACIÓN DEL MÉTODO DE GAUSS AL ESTUDIO DE LA TRANSMISIÓN DE LA COVID-19 POR TRAMOS DE EDAD

#include <stdio.h>
#include "../mn_lapack.h"
#include <stdlib.h>

///PROGRAMA PRINCIPAL.
int main()
{
  /// EJEMPLO BÁSICO 3x3 DEL LIBRO DE LA ASIGNATURA
  Array2D<real> A("EjemploLibro_A.txt");
  A.print("Matriz ejemplo libro");

  Array1D<real> b("EjemploLibro_b.txt");
  b.print("  terminos independientes");

  Array1D<real> u("EjemploLibro_u.txt");
  u.print("  solucion real");

  mn_gauss(A,b).print("  solucion obtenida alumno");


  printf("\nEJEMPLO DEMOGRAFIA (VER LIBRO PARA MAS DETALLES)\n");

  /// LCTURA POBLACIÓN DE MUJERES RESIDENTES EN ESPAÑA EN 2024 POR EDADES
  Array1D<real> P("POBLACION_MUJERES_2024.csv");
  P.subarray(95,100).print("  POBLACION MUJERES RESIDENTES EN 2024 (ULTIMOS VALORES)");

  /// LECTURA TASA DE SUPERVIVENCIA MUJERES
  Array1D< real > TS("TASA_SUPERVIVENCIA.txt");
  TS.subarray(95,100).print("  TASA DE SUPERVIVENCIA MUJERES (ULTIMOS VALORES, EDAD ENTRE 95 Y 100)");

  /// LECTURA TASA DE FECUNDIDAD
  Array1D< real > TF("TASA_FECUNDIDAD.txt");
  TF.subarray(25,30).print("  TASA DE FECUNDIDAD MUJERES (EDAD DE LA MADRE ENTRE 25 Y 30)");

  /// LECTURA SALDO MIGRATORIO MUJERES
  Array1D< real > SM("SALDO_MIGRATORIO.txt");
  SM.subarray(25,30).print("  SALDO MIGRATORIO MUJERES (EDAD DEL MIGRANTE ENTRE 25 Y 30)");

  /// CONSTRUIMOS MATRIZ DE Leslie
  Array2D< real >  L(TS.dim(),TS.dim(),0.);
  for(int k=0;k<TS.dim();k++) L[0][k]=TF[k];
  for(int k=0;k<TS.dim()-1;k++) L[k+1][k]=TS[k];

  /// CALCULO POBLACIÓN A 100 AÑOS VISTA CON SALDO MIGRATORIO
  Array1D<real> P100=P.copy();
  for(int k=0;k<100;k++) P100=L*P100+SM;
  P100.write("POBLACION_EN_100_AÑOS_CON_SALDO_MIGRATORIO.csv");

  /// CALCULO POBLACIÓN A 100 AÑOS VISTA SIN SALDO MIGRATORIO
  P100=P.copy();
  for(int k=0;k<100;k++) P100=L*P100;
  P100.write("POBLACION_EN_100_AÑOS_SIN_SALDO_MIGRATORIO.csv");

  /// CALCULO ESTADO ASINTÓTICO CON DADO POR LA SOLUCIÓN w DEL SISTEMA
  /// (Id-L)w = SM

  /// CONSTRUCCIÓN MATRIZ A=(Id-L)
  A=L*(-1.);
  for(int k=0;k<P.dim();k++) A[k][k]+=1;

  /// RESOLVEMOS EL SISTEMA Aw = SM Y GUARDAMOS EN DISCO LA SOLUCIÓN
  Array1D< real > w(P.dim(),0.);
  w = mn_gauss(A,SM);
  w.write("ESTADO_ASINTOTICO_CON_SALDO_MIGRATORIO.csv");

  printf("\nA CONTINUACION EL ALUMNO DEBE, A PARTIR DE LOS FICHEROS GENERADOS,\n");
  printf("REPRODUCIR CON EXCEL UN GRAFICO SIMILAR AL DEL LIBRO PARA LAS PROYECCIONES\n");
  printf("DE LA POBLACION A 100 AGNOS VISTA CON Y SIN SALDO MIGRATORIO\n");
  printf("Y EL ESTADO ASINTOTICO CON SALDO MIGRATORIO\n");


}



