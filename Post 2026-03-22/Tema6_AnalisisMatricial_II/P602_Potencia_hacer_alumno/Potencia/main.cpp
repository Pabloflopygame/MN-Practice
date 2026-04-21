#include "../mn_aritmeticas.h"
#include "../mn_lapack.h"

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



int main()
{

  int Nmax=10000; // NUMERO MAXIMO DE ITERACIONES
  real TOL=1e-6; // TOLERANCIA PARA LA CONVERGENCIA
  real a_max; // AUTOVALOR MAXIMO
  Array1D< real >  u(16,1.);; // AUTOVECTOR MAXIMO INICIALIZADO A 1

  /// CASO MATRIZ CONTACTOS SOCIALES COVID
  Array2D< real >  A; // MATRIZ DE EJEMPLO
  int N=mn_leer_matriz("MatrizContactosSociales.txt",A);
  int Niter=mn_metodo_potencia(A,u,a_max,Nmax,TOL);
  printf("(real)  : autovalor maximo l = %lf, Niter=%d\n",13.928960,14);
  printf("(alumno): autovalor maximo l = %lf, Niter=%d\n\n",a_max,Niter);

  printf("Comprobamos si A*u = l*u \n\n",a_max);
  Array1D< real >  Au=A*u;
  Array1D< real >  lu=u*a_max;

  printf("   A*u    -    l*u \n");
  for(int k=0;k<u.dim();k++){
    printf("%lf  - %lf\n",Au[k],lu[k]);
  }

  printf("\nPara comprobar si se gestionan bien autovalores negativos\n");
  printf("cambiamos de signo a A y volvemos a hacer los calculos\n\n");
  system("pause");

  A=A*(-1.);
  u=Array1D< real >(16,1.);
  Niter=mn_metodo_potencia(A,u,a_max,Nmax,TOL);
  printf("(real)  : autovalor maximo l = %lf, Niter=%d\n",-13.928960,14);
  printf("(alumno): autovalor maximo l = %lf, Niter=%d\n\n",a_max,Niter);

  printf("Comprobamos si A*u = l*u \n\n",a_max);
  Au=A*u;
  lu=u*a_max;

  printf("    A*u    -    l*u \n");
  for(int k=0;k<u.dim();k++){
    printf("%lf  - %lf\n",Au[k],lu[k]);
  }

}




