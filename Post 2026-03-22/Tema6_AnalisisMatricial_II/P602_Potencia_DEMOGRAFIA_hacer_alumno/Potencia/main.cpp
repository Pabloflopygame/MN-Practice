#include "../mn_aritmeticas.h"
#include "../mn_lapack.h"



int main()
{

  int Nmax=10000; // NUMERO MAXIMO DE ITERACIONES
  real TOL=1e-8; // TOLERANCIA PARA LA CONVERGENCIA
  real a_max; // AUTOVALOR MAXIMO

  /// LECTURA MATRIZ EJEMPLO
  Array2D< real >  A("A.txt");
  A.print("A");

  /// CREAMOS AUTOVECTOR Y LO INICIALIZAMOS A 1
  Array1D< real > u_max(A.dim1(),1);

  /// RESULTADOS REALES APLICACIÓN MÉTODO
  std::cout << "Resultados reales: Niter=39, a_max=3, u_max=(0.930949,0.358057,0.0716115)" << "\n";

  /// CALCULAMOS AUVECTOR Y AUTOVALOR MÁXIMO
  int Niter=mn_metodo_potencia(A,u_max,a_max,Nmax,TOL);
  std::cout << "Resultados alumno: Niter=" << Niter << ", a_max=" << a_max << ", u_max=(" << u_max[0]
  << "," << u_max[1] << "," << u_max[2] << ")\n";

  /// CAMBIAMOS SIGNO A LA MATRIZ Y VOLVEMOS A CALCULAR
  A=A*(-1);
  u_max=Array1D< real >(A.dim1(),1);

  std::cout << "\nCAMBIAMOS EL SIGNO DE A Y RECALCULAMOS\n";
  std::cout << "Resultados reales: Niter=39, a_max=-3, u_max=(0.930949,0.358057,0.0716115)" << "\n";
  Niter=mn_metodo_potencia(A,u_max,a_max,Nmax,TOL);
  std::cout << "Resultados alumno: Niter=" << Niter << ", a_max=" << a_max << ", u_max=(" << u_max[0]
  << "," << u_max[1] << "," << u_max[2] << ")\n";


  printf("\nEJEMPLO DEMOGRAFIA (VER LIBRO PARA MAS DETALLES)\n");


  /// LECTURA TASA DE SUPERVIVENCIA MUJERES
  Array1D< real > TS("TASA_SUPERVIVENCIA.txt");
  TS.subarray(95,100).print("  TASA DE SUPERVIVENCIA MUJERES (ULTIMOS VALORES, EDAD ENTRE 95 Y 100)");

  /// LECTURA TASA DE FECUNDIDAD
  Array1D< real > TF("TASA_FECUNDIDAD.txt");
  TF.subarray(25,30).print("  TASA DE FECUNDIDAD MUJERES (EDAD DE LA MADRE ENTRE 25 Y 30)");

  /// CONSTRUIMOS MATRIZ DE Leslie
  Array2D< real >  L(TS.dim(),TS.dim(),0.);
  for(int k=0;k<TS.dim();k++) L[0][k]=TF[k];
  for(int k=0;k<TS.dim()-1;k++) L[k+1][k]=TS[k];

  /// APLICAMOS MÉTODO DE LA POTENCIA A MATRIZ DE Leslie
  u_max=Array1D< real >(L.dim1(),1);
  Niter=mn_metodo_potencia(L,u_max,a_max,Nmax,TOL);
  std::cout << "\nResultados reales matriz Leslie 1: Niter=1053, a_max=0.981631\n";
  std::cout << "Resultados alumno matriz Leslie 1: Niter=" << Niter << ", a_max=" << a_max << "\n" ;
  u_max.write("AUTOVECTOR_LESLIE_1.csv");

  /// DUPLICAMOS LA FECUNDIDAD EN LA MATRIZ DE LESLIE
  for(int k=0;k<TS.dim();k++) L[0][k]=2*TF[k];

  /// APLICAMOS MÉTODO DE LA POTENCIA A LA NUEVA MATRIZ DE Leslie
  u_max=Array1D< real >(L.dim1(),1);
  Niter=mn_metodo_potencia(L,u_max,a_max,Nmax,TOL);
  std::cout << "\nResultados reales matriz Leslie 2: Niter=818, a_max=1.00225\n";
  std::cout << "Resultados alumno matriz Leslie 2: Niter=" << Niter << ", a_max=" << a_max << "\n" ;
  u_max.write("AUTOVECTOR_LESLIE_2.csv");

  std::cout << "\nEL ALUMNO DEBERA HACER UNA GRAFICA SIMILAR A LA DEL LIBRO EN EXCEL\n" <<
    "USANDO LOS FICHEROS CON LOS AUTOVECTORES CALCULADOS\n";


}




