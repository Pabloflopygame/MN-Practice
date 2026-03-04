#include "mn_aritmeticas.h"
#include "mn_raices_polinomios.h"

/// *************************************************************************************
///         EVALUACIÓN DE UN POLINOMIO a EN UN PUNTO x
/// *************************************************************************************
real evaluar_polinomio(
Array1D< real > &a /** coeficientes polinomio */,
real x /** valor donde se evalua el polinomio */){
  real Px=0;
  real xk=1;
  for(int k=0;k<a.dim();k++){
    Px+=a[k]*xk;
    xk*=x;
  }
  return Px;
}



/// *************************************************************************************
/// CALCULO DE UNA RAIZ DE UN POLINOMIO EN UN INTERVALO USANDO EL MÉTODO DE LA BISECCIÓN
/// ANTES DE LLAMAR A LA FUNCIÓN SE HA VERIFICADO QUE HAY CAMBIO DE SIGNO
/// SE UTILIZA UN MÉTODO NO-ESTANDAR DISTINTO A LOS EXPLICADOS EN CLASE.
/// *************************************************************************************
real calculo_cero_en_intervalo(
Array1D< real > &a /** coeficientes polinomio */,
real A,real B /** intervalo donde buscar la raíz */,
real TOL /** Tolerancia para el criterio de parada */){
  real step=(B-A)/10;
  while(step>TOL && A<B){
    for(int k=0;k<10 && A<=B;k++){
      real Anew=A+step;
      if(evaluar_polinomio(a,A)*evaluar_polinomio(a,Anew)<=0){
          B=Anew;
          step/=10;
          break;
      }
      A=Anew;
    }
  }
  return (A+B)/2.;
}

/// ****************************************************
///  CALCULO POLINOMIO DERIVADA
///  DEVUELVE UN VECTOR CON EL POLINOMIO DERIVADA
/// ****************************************************
Array1D< real > calcular_derivada_polinomio(
Array1D< real > &a /** coeficientes del polinomio */){

  // Si el polinomio es de grado 0 (solo término independiente),
  // su derivada es 0 -> aquí devuelve un Array vacío (convención del profe).
  if(a.dim()==1) return Array1D< real >();

  // La derivada de un polinomio de tamaño N tiene tamaño N-1.
  Array1D< real > b(a.dim()-1);

  // Si a[k] representa el coeficiente de x^k:
  // p(x) = a0 + a1 x + a2 x^2 + ... + a_{n} x^{n}
  // entonces p'(x) = a1 + 2 a2 x + 3 a3 x^2 + ... + n a_n x^{n-1}
  for(int k=0;k<b.dim();k++){
    b[k]=(k+1.)*a[k+1];   // coeficiente nuevo de x^k es (k+1)*a[k+1]
  }

  return b;
}

/// *************************************************************************************
///  CALCULO CEROS DE UN POLINOMIO A PARTIR DE LOS CEROS DE SU DERIVADA
///  DEVUELVE UN VECTOR CON LOS CEROS DEL POLINOMIO.
///  UTILIZA LA FUNCIÓN calculo_ceros_en_intervalo() PARA CALCULAR EL CERO EN CADA INTERVALO
///  PARA CONSTRUIR LOS INTERVALOS HAY QUE AÑADIR A LA IZQUIERDA Y LA DERECHA DE LOS CEROS
///  DE LA DERIVADA LOS LÍMITES DONDE ESTÁN TODAS LAS RAÍCES DEL POLINOMIO
/// *************************************************************************************
Array1D< real > ceros_polinomio_desde_ceros_derivada(
Array1D< real > &a /** coeficientes polinomio */,
Array1D< real > &d /** ceros polinomio derivada */,
real TOL){

  // Si el coeficiente líder (último) es 0, el polinomio "real" tiene menor grado.
  // El profe aquí hace un atajo: devuelve directamente los ceros de la derivada.
  // (Ojo: esto es una decisión práctica/rápida, no es una resolución general del caso.)
  if(a[a.dim()-1]==0.) return d;

  // --- Paso 1: calcular una cota A tal que TODAS las raíces reales están en [-A, A]
  // Usa una forma de la cota de Cauchy:
  // A = 1 + max{|a_k|}/|a_n|, con k=0..n-1
  real max_c=mn_abs(a[0]);
  for(int k=1;k<a.dim()-1;k++){
    if(mn_abs(a[k])>max_c) max_c=mn_abs(a[k]);
  }
  real A=1+max_c/mn_abs(a[a.dim()-1]);

  // Aquí guardará las raíces reales encontradas del polinomio "a"
  Array1D< real > ceros;

  // --- Paso 2: construir la lista de puntos que definen intervalos:
  // I = [-A, d0, d1, ..., dm-1, A]
  // donde d son ceros de la derivada (puntos críticos).
  Array1D< real > I(1,-A);     // vector I con un solo elemento: -A

  for(int k=0;k<d.dim();k++) I.push_back(d[k]);  // añade los ceros de la derivada

  I.push_back(A);              // añade el extremo derecho A

  // --- Paso 3: recorrer intervalos consecutivos [I[k], I[k+1]]
  // Si el polinomio cambia de signo en el intervalo, hay al menos una raíz real dentro
  // (por el Teorema de Bolzano).
  for(int k=0;k<I.dim()-1;k++){
    if(evaluar_polinomio(a,I[k])*evaluar_polinomio(a,I[k+1])<=0.){

      // Si hay cambio de signo (o uno de los extremos es raíz exacta),
      // calcula la raíz en ese intervalo con el método "no estándar" del profe.
      ceros.push_back(calculo_cero_en_intervalo(a,I[k],I[k+1],TOL));
    }
  }

  return ceros;
}

/// ****************************************************
///  CALCULO RAÍCES REALES DE UN POLINOMIO
///  DEVUELVE UN VECTOR CON LAS RAÍCES ENCONTRADAS
/// ****************************************************
Array1D< real > ceros_polinomio(
Array1D< real > &a /** coeficientes polinomio */,
real TOL){

  // Aquí "ceros" se reutiliza en cada iteración:
  // al principio está vacío, y representa ceros del polinomio derivado
  // del nivel más alto (constante), y luego va bajando hasta el original.
  Array1D< real > ceros;

  // Recorre k desde (n-1) hasta 0, siendo n = a.dim()-1 el grado del polinomio.
  // k indica CUÁNTAS derivadas vamos a tomar desde el polinomio original:
  //
  // - k = n-1 -> derivamos n-1 veces -> queda un polinomio lineal
  // - k = n-2 -> derivamos n-2 veces -> queda un polinomio cuadrático
  // ...
  // - k = 0   -> derivamos 0 veces -> el polinomio original
  for(int k=a.dim()-2;k>=0;k--){

    // d empieza siendo copia del polinomio original
    Array1D< real > d=a.copy();

    // derivamos k veces para obtener el polinomio "d"
    for(int n=0;n<k;n++) d=calcular_derivada_polinomio(d);

    // IMPORTANTE:
    // 'ceros' en este momento contiene los ceros del polinomio derivada de 'd'
    // (porque venimos de la iteración anterior).
    //
    // Entonces usamos esos ceros para construir intervalos y encontrar los ceros de 'd'.
    ceros=ceros_polinomio_desde_ceros_derivada(d,ceros,TOL);
  }

  // Al terminar el bucle, 'ceros' son los ceros del polinomio original 'a'
  return ceros;
}
