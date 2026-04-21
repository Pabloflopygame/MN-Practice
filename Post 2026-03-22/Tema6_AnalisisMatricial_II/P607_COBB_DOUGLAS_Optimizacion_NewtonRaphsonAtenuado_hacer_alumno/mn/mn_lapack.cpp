#include <stdio.h>
#include "mn_lapack.h"


/// FUNCION PARA RESOLVER SISTEMAS POR UNA VARIANTE DEL METODO DE GAUSS
Array1D< real > mn_gauss(
  const Array2D< real > &A  /** MATRIZ DEL SISTEMA */,
  const Array1D< real > &b) /** VECTOR DE TERMINOS INDEPENDIENTES */
{

  real max,paso,mul;
  int i,j,i_max,k;

  int N=A.dim1();
  Array2D< real > PASO(N,N+1);
  Array1D< real > u=b.copy();

  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      PASO[i][j]=A[i][j];
    }
    PASO[i][N]=b[i];
  }

  for(i=N-1;i>=0;i--){
    max=mn_abs(PASO[i][i]);
    i_max=i;
    for(j=0;j<i;j++){
       if(mn_abs(PASO[j][i])>max){
         i_max=j; max=mn_abs(PASO[j][i]);
       }
    }
    if(max<10e-120){
      return(Array1D< real >());
    }
    if(i_max!=i){
      for(k=0;k<=N;k++){
        paso=PASO[i][k];
        PASO[i][k]=PASO[i_max][k];
        PASO[i_max][k]=paso;
      }
    }
    for(j=0;j<i;j++){
      mul=-PASO[j][i]/PASO[i][i];
      for(k=0;k<=N;k++) PASO[j][k]+=mul*PASO[i][k];
    }
  }

  for (i=0;i<N;i++){
      u[i]=PASO[i][N];
      for (j=0;j<i;j++){
         u[i]=u[i] - PASO[i][j]*u[j];
      }
      u[i]=u[i]/PASO[i][i];
  }

  return(u);
}


// FUNCION PARA CALCULAR EL ERROR DEL SISTEMA
real mn_error_sistema(const Array2D< real > &A, const Array1D< real > &u, const Array1D< real > &b)
{
   int i;
   if(b.dim()==0 || b.dim()!=u.dim() || b.dim()!=A.dim1() ||  b.dim()!=A.dim2()) return(0.);
   Array1D< real > e=A*u-b;

   real Sum=0.;
   for (i=0;i<b.dim();i++){
      Sum = Sum + mn_abs(e[i])/(mn_abs(b[i])+ 1.);
   }
   return (Sum/b.dim());
}


/* FUNCION PARA LEER UN VECTOR DE DISCO. RETORNA LA DIMENSION DEL VECTOR */
int mn_leer_vector(
  char *nombrefichero,
   Array1D< real > &vector)
{
  int dimension;
  float paso;
  FILE *f;

  // ABRIMOS EL FICHERO
  if(f=fopen( nombrefichero, "r"),!f){
    printf("Problema con la apertura del fichero\n");
    return -1;
  }

  // LEEMOS LA DIMENSION
  fscanf(f,"%d\n",&dimension);
  if(dimension<1) return(-2);

  // COGEMOS MEMORIA
   Array1D< real > v(dimension);

  // LEEMOS EL VECTOR
  for(int i=0;i<dimension;i++){
    fscanf(f,"%f\n",&paso);
    v[i]=paso;
  }
  fclose(f);
  vector=v.copy();
  return dimension;
}

/* FUNCION PARA ESCRIBIR UN VECTOR DE DISCO DE DIMENSION dimension Y LO ALMACENA EN vector */
int mn_escribir_vector(
  char *nombrefichero,
   Array1D< real > &vector)
{
  int i;
  FILE *f;
  int dimension=vector.dim();
  if(f=fopen( nombrefichero, "w"),!f){
    printf("Problema con la escritura del fichero\n");
    return 1;
  }
  fprintf(f,"%d\n",dimension);
  for(i=0;i<dimension;i++) fprintf(f,"%f\n",(float) vector[i]);
  fclose(f);
  return 0;
}

/* FUNCION PARA LEER UNA MATRIZ DE DISCO DE DIMENSION
dimension Y LO ALMACENA EN LA MATRIZ matriz  */
int mn_leer_matriz(
  char *nombrefichero,
  Array2D< real > &matriz)
{
  int dimension1,dimension2;
  float paso;
  FILE *f;
  if(f=fopen( nombrefichero, "r"),!f){
    printf("Problema con la apertura del fichero\n");
    return 1;
  }
  fscanf(f,"%d %d\n",&dimension1, &dimension2);
  if(dimension1<1 || dimension2<1) return(-1);

  // RESERVAMOS MEMORIA PARA LA MATRIZ
  Array2D< real > m(dimension1,dimension2);

  for(int i=0;i<dimension1;i++){
    for(int j=0;j<dimension2;j++){

       fscanf(f,"%f ",&paso);
       m[i][j]=paso;
       //printf("paso=%e\n",(double) m[i][j]);
    }
    fscanf(f,"\n");
  }
  fclose(f);
  matriz=m.copy();
  return dimension1;
}

/* FUNCION PARA ESCRIBIR UNA MATRIZ EN DISCO
dimension */
int mn_escribir_matriz(
  char *nombrefichero,
  Array2D< real > &matriz)
{
  int i,j;
  FILE *f;
  if(f=fopen( nombrefichero, "w"),!f){
    printf("Problema con la escritura del fichero\n");
    return 1;
  }
  fprintf(f,"%d %d\n",matriz.dim1(),matriz.dim2());
  for(i=0;i<matriz.dim1();i++){
    for(j=0;j<matriz.dim2();j++){
       fprintf(f,"%f ",(float) matriz[i][j]);
    }
    fprintf(f,"\n");
  }
  fclose(f);
  return 0;
}






