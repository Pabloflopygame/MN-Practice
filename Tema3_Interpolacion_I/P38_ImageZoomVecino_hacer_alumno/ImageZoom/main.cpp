#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../mn_aritmeticas.h"
#include "../mn_interpolacion.h"


/// OBJETIVO 1 : IMPLEMENTAR EL MÉTODO DE INTERPOLACIÓN 2D POR EL VECINO MÁS VERCANO
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

  /// TEST ALGORITMO INTERPOLACION POR EL VECINO MAS CERCANO
  /// HACEMOS UN ZOOM BILINEAL DE FACTOR 3
  Array2D< real > Zv=zoom_vecino(I,3.);

  /// EL RESULTADO HA SIDO ALMACENADO PREVIAMENTE EN DISCO.
  /// LO LEEMOS PARA COMPROBAR EL RESULTADO DEL ALGORITMO
  Array2D< real > Av("eiiBW_zoom_test_vecino.png");

  /// COMPROBAMOS LAS DIMENSIONES
  if( Av.dim1()!=Zv.dim1() || Av.dim2()!=Zv.dim2() ){
    printf("las dimensiones de la imagen zoom is incorrecta\n");
    printf("Dimensiones reales : %d x %d\n",Av.dim1(),Av.dim2());
    printf("Dimensiones alumno : %d x %d\n",Zv.dim1(),Zv.dim2());
    system("pause");
    exit(1);
  }
  /// CALCULAMOS EL MÁXIMO ERROR
  real errorv=0.;
  for(int i=0;i<Zv.dim1();i++){
    for(int j=0;j<Zv.dim2();j++){
      real temp=fabs(Av[i][j]- Zv[i][j]);
      if(temp>errorv) errorv=temp;
    }
  }

  cout << "error maximo vecino = " << errorv << " \n" ;


 /// CREACION DE IMÁGENES PARA ILUSTRAR EL RESULTADO
 /// PRIMERO HACEMOS UN ZOOM
 /// PARA HACER LA IMAGEN MÁS PEQUEÑA CON UN ZOOM DE 1/16
 /// Y DESPUÉS HACEMOS OTRO PARA VOLVER A SUS DIMENSIONES ORIGINALES


 /// CASO VECINO MÁS CERCANO
 Array2D < real > Ivecino=zoom_vecino(I,1/16.);
 Ivecino=zoom_vecino(Ivecino,16.);
 Ivecino.write_png("eiiBW_vecino.png");

 printf("\nEL ALUMNO DEBE INCLUIR EN LA MEMORIA IMAGENES ILUSTRATIVAS\n");

}
