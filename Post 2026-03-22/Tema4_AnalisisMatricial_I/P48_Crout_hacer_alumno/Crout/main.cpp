#include <stdio.h>
#include "../crout.h"
#include "../lapack.h"
#include <stdlib.h>

int main()
{
  int N;
  {
    printf("EJEMPLO 1 METODO DE CROUT: \n\n");
    Array1D< real > a,b,c,t,l(3,0.),m(2,0.),u(2,0.);
    N=leer_vector("../datos/a1.txt",a); // vector a de la matriz tridiagonal
    N=leer_vector("../datos/b1.txt",b); // vector b de la matriz tridiagonal
    N=leer_vector("../datos/c1.txt",c); // vector c de la matriz tridiagonal
    N=leer_vector("../datos/t1.txt",t); // vector t de términos independientes del sistema



    printf("Comprobamos la funcion crout_metodo_completo()\n");
    Array1D< real > v=crout_metodo_completo(a,b,c,t);
    if(v.dim()==3){
      printf("solucion v[] calculada por el alumno : (%lf,%lf,%lf) \n",v[0],v[1],v[2]);
    }
    else { printf("error dimension vector\n"); }
    printf("solucion v[] correcta                : (%lf,%lf,%lf) \n\n\n",1.,1.,1.);
    printf("EJEMPLO 2: METODO DE CROUT\n\n");
  }

  {

    Array1D< real > a,b,c,t,l(3,0.),m(2,0.),u(2,0.);
    N=leer_vector("../datos/a2.txt",a); // vector a de la matriz tridiagonal
    N=leer_vector("../datos/b2.txt",b); // vector b de la matriz tridiagonal
    N=leer_vector("../datos/c2.txt",c); // vector c de la matriz tridiagonal
    N=leer_vector("../datos/t2.txt",t); // vector t de términos independientes del sistema

    printf("Comprobamos la funcion crout_metodo_completo()\n");
    Array1D< real > v=crout_metodo_completo(a,b,c,t);
    if(v.dim()==3){
      printf("solucion v[] calculada por el alumno : (%lf,%lf,%lf) \n",v[0],v[1],v[2]);
    }
    else { printf("error dimension vector\n"); }
    printf("solucion v[] correcta                : (%lf,%lf,%lf) \n\n\n",3.,2.,1.);
    printf("EJEMPLO 3 METODO DE CROUT: \n\n");
  }

  {
    Array1D< real > a,b,c,t,l(5,0.),m(4,0.),u(4,0.);
    N=leer_vector("../datos/a3.txt",a); // vector a de la matriz tridiagonal
    N=leer_vector("../datos/b3.txt",b); // vector b de la matriz tridiagonal
    N=leer_vector("../datos/c3.txt",c); // vector c de la matriz tridiagonal
    N=leer_vector("../datos/t3.txt",t); // vector t de términos independientes del sistema

    printf("Comprobamos la funcion crout_metodo_completo()\n");
    Array1D< real > v=crout_metodo_completo(a,b,c,t);
    if(v.dim()==5){
      printf("solucion v[] calculada por el alumno : (%lf,%lf,%lf,%lf,%lf) \n",v[0],v[1],v[2],v[3],v[4]);
    }
    else { printf("error dimension vector\n"); }
    printf("solucion v[] correcta                : (%lf,%lf,%lf,%lf,%lf) \n\n\n",1.000000,1.071429,1.285714,2.071429,5.000000);
    system("pause");
  }

  return 0;
}
