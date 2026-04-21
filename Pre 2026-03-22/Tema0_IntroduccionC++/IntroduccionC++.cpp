/// INCLUSIÓN DE LIBRERÍAS STANDARD
#include <stdlib.h>
#include <stdio.h>

/// INCLUSIÓN DE LIBRERÍA LOCAL TNT PARA EL MANEJO DE VECTORES Y MATRICES
#include "tnt_array/tnt.h"

/// MACRO PARA DEFINIR EL TIPO AUXILIAR real PARA MANEJAR LA CALIDAD DE LA ARITMÉTICA
#define real double

/// INSTRUCCIÓN PARA QUE SE RECONOZCA LA CLASE TNT (Y NO TENER QUE ESCRIBIR TNT:: ANTES DE SUS MÉTODOS)
using namespace TNT; /// clase para manejar vectores y matrices
/// INSTRUCCIÓN PARA QUE SE RECONOZCA LA CLASE std (Y NO TENER QUE ESCRIBIR std:: ANTES DE SUS MÉTODOS)
using namespace std; /// librería standard de C++ con múltiples clases y funciones

int main()
{
/// MANEJO VARIABLES NUMÉRICAS

  /// TIPO int (ENTERO)
  int i=500.8; /// el resultado es 500 porque la conversión a entero trunca el valor

  /// EL TIPO real PUEDE SER float, double o long double EN FUNCIÓN DE
  /// LA DEFINICIÓN DE LA MACRO "#define real ....."
  real a=1.; /// al añadir el punto al 1 el compilador interpreta el número como real y no
  /// como entero. Esto algunas veces puede tener mucha trascendencia. Por ejemplo:
  real b=1./2.; /// el resultado es 0.5
  real c=1/2; /// el resultado es 0 porque primero hace la operación en enteros y luego la asignación.

  /// CAST (CONVERSIÓN DE TIPOS).PONEMOS EL TIPO ENTRE PARÉNTESIS ANTES DE LA VARIABLE
  real d=(real) 1/2; /// el resultado es 0.5 porque se cambia el tipo antes de la operación

  /// CONSTANTE CON EL VALOR DEL NÚMERO PI
  real p=M_PI;

  /// OBTENCIÓN NÚMERO ENTERO ALEATORIO ENTRE 0 Y SU VALOR MÁXIMO DADO POR LA CONSTANTE RAND_MAX
  real e=(real) rand()/RAND_MAX; /// número aleatorio de tipo real entre 0 y 1.

  /// OPERACIONES BÁSICAS VARIABLES
  i++; /// actualiza i sumándole 1
  i--; /// actualiza i restándole 1
  i+=5; /// actualiza i sumándole 5
  i-=5; /// actualiza i restándole 5
  a*=5; /// actualiza a multiplicando por 5
  a/=5; /// actualiza a dividienco por 5
  int j=i%4;  /// calcula resto división enteros

  /// IMPRESIÓN POR CONSOLA DE VARIABLES NUMÉRICAS
  /// IMPRESIÓN USANDO printf
  printf("e=%lf\n",e); /// %lf indica un tipo real de la variable que se imprime
  printf("e=%e\n",e); /// %e indica un tipo real que se imprime en notación científica
  printf("pi=%1.16lf\n",p); /// se imprime el número con 16 cifras decimales
  printf("i=%d\n",i); /// %d indica un tipo entero de la variable que se imprime

  /// NOTA: %lf NO FUNCIONA CON LAS VARIABLES long double. HAY QUE USAR %Lf O HACER UN CAST
  long double f=M_PI;
  printf("f=%1.16Lf\n",f);
  printf("f=%1.16lf\n",(double) f);

  /// IMPRESIÓN USANDO cout (método de la clase std)
  cout << "e= " << e << ", i= " << i << "\n"; /// cout es un método a la clase std

///-----------------------------------------------------------------------------------
/// ESTRUCTURAS IF-ELSE, BUCLES, OPERADORES LÓGICOS Y DE COMPARACIÖN

  /// ESTRUCTURA IF-ELSE
  if(a==b || (c!=d && a<=c) ){
    /// ejecucíon si a y b son iguales o si c y d son distintos y a es menor o igual que c
    b=c;
  }
  else{
    d=b;
  }
  /// ESTRUCTURA IF-ELSE COMPACTADA
  c = a>b?a:b; /// si a>b hacemos c=a, en caso contrario hacemos c=b (es decir c=max(a,b))
  c = a>0?a:-a; /// calcula el valor absoluto de a

  /// BUCLE FOR
  for(int k=0;k<100;k++){
    if(k==i) continue; /// saltamos a la siguiente iteración
    if(k==i+3) break; /// salimos del bucle
  }
  /// NOTA: EN ESTE FOR EL ÁMBITO DE LA VARIABLE k ES SOLO EL INTERIOR DEL FOR. SI LA
  /// VARIABLE k EXISTE FUERA DEL BUCLE SE CREARÍA UNA NUEVA DENTRO (AL PONER "int k=0")

  /// BUCLE WHILE
  while(++i<100){ /// incrementa i antes de comparar (con i++ primero compara y luego incrementa)
    a*=0.5;
  }

  while(true){ /// el bucle continua hasta ejecutar un break en su interior
    if(i++ == 5) break; /// el bucle para cuando i vale 5 antes de entrar en el if
    if(++i == 5) break; /// el bucle para cuando i vale 4 antes de entrar en el if
  }

///-----------------------------------------------------------------------------------
/// FUNCIONES BÁSICAS
  int m=abs(i); /// valor absoluto para enteros
  real g=fabs(a); /// valor absoluto para reales
  m=round(a); /// se redondea a a su entero más cercano
  g=cos(a); /// coseno en precisión double
  g=cosf(a); /// en general al añadir la f detrás del nombre la función se hace en precisión float
  g=sin(a); /// seno en precisión doble
  g=tan(a); /// tangente en precisión doble
  /// para las inversas de las funciones trigonométricas se añade "a" delante del nombre.
  g=acos(a); /// arco coseno de a en en radianes en [0,pi]
  g=atan2(a,b); /// ángulo en radianes en [-pi,pi] que cumple que tan(g)=a/b
  g=exp(a); /// exponencial (e^a) en precisión doble
  g=log(a); /// logaritmo neperiano de a en precisión doble
  g=pow(a,b); /// a elevado a b en precisión doble
  g=sqrt(a); /// raíz cuadrada
  g=max(a,b); /// máximo entre a y b (max es un método de la clase std)
  g=min(a,b); /// mínimo entre a y b (min es un método de la clase std)


///-----------------------------------------------------------------------------------
/// MANEJO DE VECTORES (SE USA CLASE TNT Y SUS MÉTODOS)

  /// DEFINICIÓN DE UN VECTOR Y ASIGNACIÓN TAMAÑO Y VALORES
  Array1D< real > u(4); /// vector tipo real con tamaño 4
  for(int k=0;k<u.dim();k++) u[k]=k; /// el método dim() suministra el tamaño del vector

  /// DEFINICIÓN DE UN VECTOR Y ASIGNACIÓN TAMAÑO Y VALOR CONSTANTE
  Array1D< real > v(4,1.); /// vector tipo real con tamaño 4 y valor constante 1.

  /// OPERACIONES BÁSICAS CON VECTORES
  Array1D< real > w=u+v; ///suma
  Array1D< real > z=u*5.; /// multiplicación por un número (nota: 5.*u no funciona)

  /// IMPRESIÓN POR CONSOLA DE UN VECTOR
  w.print("w");

///-----------------------------------------------------------------------------------
/// MANEJO DE MATRICES (SE USA CLASE TNT Y SUS MÉTODOS)

  /// DEFINICIÓN DE UNA MATRIZ Y ASIGNACIÓN TAMAÑO Y VALORES
  Array2D< real > A(3,4); /// matriz de tamaño 3x4
  for(int i=0;i<A.dim1();i++){ /// el método dim1() suministra el nº de filas
    for(int j=0;j<A.dim2();j++){ /// el método dim2() suministra el nº de columnas
      A[i][j]=i+j;
    }
  }

  /// DEFINICIÓN DE UNA MATRIZ Y ASIGNACIÓN TAMAÑO Y VALOR CONSTANTE
  Array2D< real > B(3,4,1.); /// matriz de tamaño 3x4 y valor constante 1.

  /// OPERACIONES BÁSICAS CON MATRICES
  /// NOTA: EL TAMAÑO DE LAS MATRICES DEBE SER COMPATIBLE CON LA OPERACIÓN
  Array2D< real > C=A.transpose(); /// matriz traspuesta.
  Array2D< real > D=A+B; /// suma
  Array2D< real > E=A*C; /// producto
  Array2D< real > F=A*5.; /// multiplicación por un número (nota: 5.*A no funciona)
  Array1D< real > y=A*u; /// multiplicación matriz por vector (nota u*A no funciona)

  /// IMPRESIÓN POR CONSOLA DE UNA MATRIZ
  E.print("E");


}


