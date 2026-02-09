#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../mn_aritmeticas.h"
#include "../mn_raices_polinomios.h"


int main()
{
    /// DEFINIMOS LA TOLERANCIA PARA LA PRECISIÓN DEL MÉTODO
    double TOL=1e-12;

    printf("Primer polinomio de ejemplo P(x)=x^4-x^3-7x^2+x+6 (TIENE 4 RAICES SIMPLES)\n");
    Array1D< real > a(5);
    a[0]=6.; a[1]=1.; a[2]=-7.; a[3]=-1.; a[4]=1.;

    Array1D< real >  ceros = ceros_polinomio(a,TOL);
    printf("RAICES REALES : -2.000000, -1.000000, 1.000000, 3.000000\nRAICES ALUMNO : ");
    for(int k=0;k<ceros.dim();k++) printf("%lf, ",ceros[k]);

    printf("\n\nSegundo polinomio de ejemplo P(x)=x^6-3x^4+3x^2-1 (TIENE 2 RAICES MULTIPLES)\n");
    a=Array1D< real >(7,0.);
    a[0]=-1.; a[2]=3.; a[4]=-3.; a[6]=1.;

    ceros = ceros_polinomio(a,TOL);
    printf("RAICES REALES : -1.000000, -1.000000, -1.000000, 1.000000, 1.000000, 1.000000,\nRAICES ALUMNO : ");
    for(int k=0;k<ceros.dim();k++) printf("%lf, ",ceros[k]);



    printf("\n\nTercer polinomio de ejemplo P(x)=x^4+1 (NO TIENE RAICES)\n");
    a=Array1D< real >(5,0.);
    a[0]=1.; a[4]=1.;

    ceros = ceros_polinomio(a,TOL);
    printf("N. RAICES REALES : %d\n",0);
    printf("N. RAICES ALUMNO : %d\n",ceros.dim());

    printf("\nCuarto polinomio de ejemplo P(x)=x^18-10^18 (TIENE 2 RAICES SIMPLES)\n");
    a=Array1D< real >(19,0.);
    a[18]=1.; a[0]=-1e18;

    ceros = ceros_polinomio(a,TOL);
    printf("RAICES REALES : -10.000000, 10.000000,\nRAICES ALUMNO : ");
    for(int k=0;k<ceros.dim();k++) printf("%lf, ",ceros[k]);
    printf("\n");

    printf("\nQuinto polinomio de ejemplo (calculo interes plan de pensiones)\n");
    printf("Durante 10 agnos hago una aportacion de 1 euros anual y al final\n");
    printf("del decimo agno me dan 15 euros. Para calcular el interes aplicado \n");
    printf("usamos el polinomio: P(x)=x^10+x^9+....+x-15 \n");
    a=Array1D< real >(10,1.);
    a[0]=-15; ;
    ceros = ceros_polinomio(a,TOL);
    printf("\nRAIZ REAL :  1.100817,\nRAICES ALUMNO : ");
    for(int k=0;k<ceros.dim();k++) printf("%lf, ",ceros[k]);
    printf("\nPor tanto el interes aplicado es el 10.0817%%\n");


}

