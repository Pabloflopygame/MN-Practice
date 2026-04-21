#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "../mn_aritmeticas.h"
#include "../mn_mascara3x3.h"

/// EL OBJETIVO DE ESTA PRÁCTICA ES IMPLEMENTAR LA CONVOLUCIÓN CON UNA MÁSCARA 3X3
/// Y APLICARLO A LA DETECCIÓN DE BORDES DE UNA IMAGEN. PARA ELLO HAY QUE :
/// IMPLEMENTAR LA FUNCIÓN DE LA MÁSCARA 3X3
/// IMPLEMENTAR LA FUNCIÓN QUE CALCULA EL SUAVIZADO DE UNA IMAGEN Y SUS BORDES
/// IMPLEMENTAR EN EL main() LA EJECUCIÓN DEL CÁLCULO DE BORDES USANDO
///    (1) 1 ITERACIÓN DE SUAVIZADO Y PERCENTIL 0.9
///    (2) 10 ITERACIONES DE SUAVIZADO Y PERCENTIL 0.9
///    (3) 1 ITERACIÓN DE SUAVIZADO Y PERCENTIL 0.95
/// EN ESTE ÚLTIMO CASO HAY QUE COMPARAR LOS RESULTADOS CON LOS ALMACENADOS EN
/// LA IMAGEN eiiBW_bordes_1_0.95_precalculado.png
/// HAY QUE SALVAR LAS IMÁGENES DE SUAVIZADO Y BORDES CALCULADAS PARA INCLUIRLAS
/// EN LA MEMORIA DE LA PRÁCTICA CON UNA DISCUSIÓN SOBRE LOS RESULTADOS OBTENIDOS


main()
{
  /// LEEMOS LA IMAGEN DE REFERENCIA
  Array2D< real > I("eiiBW.png");

  /// CALCULO DE LOS BORDES SUAVIZANDO CON 1 ITERACIÓN Y UN PERCENTIL DEL 0.9
  Array2D< real > Ig; /// IMAGEN SUAVIZADA
  Array2D< real > Bordes=mn_calculo_bordes(I,1,0.9,Ig);
  Ig.write_image2D("eiiBW_suavizada_1_0.9.png");
  Bordes.write_image2D("eiiBW_bordes_1_0.9.png");

  /// CALCULO DE LOS BORDES SUAVIZANDO CON 10 ITERACIONES Y UN PERCENTIL DEL 0.9
  Bordes=mn_calculo_bordes(I,10,0.9,Ig);
  Ig.write_image2D("eiiBW_suavizada_10_0.9.png");
  Bordes.write_image2D("eiiBW_bordes_10_0.9.png");

  /// CALCULO DE LOS BORDES SUAVIZANDO CON 1 ITERACIÓN Y UN PERCENTIL DEL 0.95
  Bordes=mn_calculo_bordes(I,1,0.95,Ig);
  Ig.write_image2D("eiiBW_suavizada_1_0.95.png");
  Bordes.write_image2D("eiiBW_bordes_1_0.95.png");

  /// PARA VALIDAR LOS RESULTADOS COMPROBAMOS QUE LOS BORDES QUE NOS HAN SALIDO
  /// SON LOS MISMOS QUE LOS DE UNA IMAGEN PRECALCULADA
  /// LEEMOS LA IMAGEN DE BORDES PRECALCULADA
  Array2D< real > Bordes2("eiiBW_bordes_1_0.95_precalculado.png");

  /// PRIMERO VERIFICAMOS SI LAS DIMENSIONES DE LAS 2 IMÁGENES COINCIDEN
  if(Bordes.dim1()!=Bordes2.dim1() || Bordes.dim2()!=Bordes2.dim2() ){
    printf("Problemas con las dimnesiones de la imagen de bordes\n");
    system("pause");
    exit(-1);
  }

  /// COMPROBAMOS SI LOS BORDES EN LAS 2 IMÁGENES SON LOS MISMOS
  /// PARA ELLO CALCULAMOS EL NÚMERO DE FALLOS

  int Nfallos=0;
  for(int i=0;i<Bordes.dim1();i++){
    for(int j=0;j<Bordes.dim2();j++){
      if(Bordes[i][j]!=Bordes2[i][j]) Nfallos++;
    }
  }

  cout << "Nfallos = " << Nfallos << "\n\n";

  cout << "El alumno debe poner imagenes ilustrativas en la memoria\n";


}



