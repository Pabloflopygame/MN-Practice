/*======================================================================================
       PRACTICA 3 METODOS NUMERICOS. APLICACION INTERPOLACION AL TRATAMIENTO DE IMÁGENES
  =====================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../mn_aritmeticas.h"
#include "../mn_interpolacion.h"

/// OBJETIVO 1 : IMPLEMENTAR EL MÉTODO DE INTERPOLACIÓN 2D BILINEAL
/// OBJETIVO 2 : HACER UN ZOOM DE FACTOR 3 A LA IMAGEN DE REFERENCIA
///              Y COMPROBAR QUE LOS RESULTADOS SON LOS ESPERADOS USANDO LAS IMÁGENES
///              PRECALCULADAS CON LOS RESULTADOS QUE TIENEN QUE SALIR. PARA ELLO SE CALCULA EL ERROR
///              MÁXIMO EN VALOR ABSOLUTO DE LA DIFERENCIA Y SE IMPRIME POR PANTALLA
/// OBJETIVO 3 : HACER UN ZOOM DE FACTOR 1/16 A LA IMAGEN DE REFERENCIA
///              Y AL RESULTADO UN ZOOM DE FACTOR 16 PARA VOLVER AL TAMAÑO DE LA IMAGEN ORIGINAL
///              GUARDAR EN DISCO LAS IMÁGENES RESULTADO PARA PONERLAS EN LA ENTREGA DE LA PRÁCTICA

main()
{
  /// LECTURA DE LA IMAGEN DE REFERENCIA
  Array2D< real > I("eiiBW.png");

  /// TEST ALGORITMO INTERPOLACION BILINEAL
  /// HACEMOS UN ZOOM BILINEAL DE FACTOR 3
  Array2D < real > Zb=zoom_bilineal(I,3.);

  /// EL RESULTADO HA SIDO ALMACENADO PREVIAMENTE EN DISCO.
  /// LO LEEMOS PARA COMPROBAR EL RESULTADO DEL ALGORITMO
  Array2D< real > Ab("eiiBW_zoom_test_bilineal.png");

  /// COMPROBAMOS LAS DIMENSIONES
  if( Ab.dim1()!=Zb.dim1() || Ab.dim2()!=Zb.dim2() ){
    printf("las dimensiones de la imagen zoom is incorrecta\n");
    printf("Dimensiones reales : %d x %d\n",Ab.dim1(),Ab.dim2());
    printf("Dimensiones alumno : %d x %d\n",Zb.dim1(),Zb.dim2());
    system("pause");
    exit(1);
  }

  /// CALCULAMOS EL MÁXIMO ERROR
  real errorb=0.;
  for(int i=0;i<Zb.dim1();i++){
    for(int j=0;j<Zb.dim2();j++){
      real temp=fabs(Ab[i][j]- Zb[i][j]);
      if(temp>errorb) errorb=temp;
    }
  }

  cout << "error maximo bilineal = " << errorb << " \n" ;

 /// CREACION DE IMÁGENES PARA ILUSTRAR LOS RESULTADOS
 /// PRIMERO HACEMOS UN ZOOM
 /// PARA HACER LA IMAGEN MÁS PEQUEÑA CON UN ZOOM DE 1/16
 /// Y DESPUÉS HACEMOS OTRO PARA VOLVER A SUS DIMENSIONES ORIGINALES

 /// CASO BILINEAL
 Array2D < real > Ibilineal=zoom_bilineal(I,1/16.);
 Ibilineal=zoom_bilineal(Ibilineal,16.);
 Ibilineal.write_png("eiiBW_bilineal.png");

 printf("\nEL ALUMNO DEBE INCLUIR EN LA MEMORIA IMAGENES ILUSTRATIVAS\n");
}



