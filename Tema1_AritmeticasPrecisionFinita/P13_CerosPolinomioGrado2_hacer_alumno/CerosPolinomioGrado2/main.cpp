#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
#include "../mn_ceros_pol_grado_2.h"

int main()
{
    int Nraices; /// número de raices
    real x1,x2; /// raíces
    real a,b,c; /// coeficientes del polinomio

    a=0; b=0; c=1.;
    printf("Polinomio 1 :  %1.0lf x^2 + %1.0lf x + %1.0lf =0\n",a,b,c);
    Nraices=mn_ceros_pol_grado_2(a,b,c,x1,x2);
    printf("N. raices reales del polinomio =0\n");
    printf("N. raices del polinomio (alumno) = %d\n",Nraices);

    a=1; b=0; c=1.;
    printf("\nPolinomio 2 :  %1.0lf x^2 + %1.0lf x + %1.0lf =0\n",a,b,c);
    Nraices=mn_ceros_pol_grado_2(a,b,c,x1,x2);
    printf("N. raices reales del polinomio =0\n");
    printf("N. raices del polinomio (alumno) = %d\n",Nraices);

    a=0; b=1; c=-2.;
    printf("\nPolinomio 3 :  %1.0lf x^2 + %1.0lf x + %1.0lf =0\n",a,b,c);
    Nraices=mn_ceros_pol_grado_2(a,b,c,x1,x2);
    printf("N. raices reales del polinomio = 1\n");
    printf("Raiz real del polinomio x1 = %1.0lf\n",2.);
    printf("N. raices del polinomio (alumno) = %d\n",Nraices);
    printf("Raiz del polinomio (alumno) x1 = %1.0lf\n",x1);

    a=1; b=-2; c=1.;
    printf("\nPolinomio 4 :  %1.0lf x^2 + %1.0lf x + %1.0lf =0\n",a,b,c);
    Nraices=mn_ceros_pol_grado_2(a,b,c,x1,x2);
    printf("N. raices reales del polinomio = 2\n");
    printf("Raiz real del polinomio x1 = %1.0lf\n",1.);
    printf("Raiz real del polinomio x2 = %1.0lf\n",1.);
    printf("N. raices del polinomio (alumno) = %d\n",Nraices);
    printf("Raiz del polinomio (alumno) x1 = %1.0lf\n",x1);
    printf("Raiz del polinomio (alumno) x2 = %1.0lf\n",x2);

    a=pow(2.,-10.); b=-1; c=pow(2.,-20.);
    printf("\nPolinomio 5 :  %e x^2 + %1.0lf x + %e =0\n",a,b,c);
    Nraices=mn_ceros_pol_grado_2(a,b,c,x1,x2);
    printf("N. raices reales del polinomio = 2\n");
    printf("Raiz real del polinomio x1 = %e\n",1024.);
    printf("Raiz real del polinomio x2 = %e\n",9.536743e-7);
    printf("N. raices del polinomio (alumno) = %d\n",Nraices);
    printf("Raiz del polinomio (alumno) x1 = %e\n",x1);
    printf("Raiz del polinomio (alumno) x2 = %e\n",x2);

    a=-pow(2.,-10.); b=1; c=-pow(2.,-20.);
    printf("\nPolinomio 6 :  %e x^2 + %1.0lf x + %e =0\n",a,b,c);
    Nraices=mn_ceros_pol_grado_2(a,b,c,x1,x2);
    printf("N. raices reales del polinomio = 2\n");
    printf("Raiz real del polinomio x1 = %e\n",1024.);
    printf("Raiz real del polinomio x2 = %e\n",9.536743e-7);
    printf("N. raices del polinomio (alumno) = %d\n",Nraices);
    printf("Raiz del polinomio (alumno) x1 = %e\n",x1);
    printf("Raiz del polinomio (alumno) x2 = %e\n",x2);


    a=1; b=0; c=0;
    printf("\nPolinomio 7 :  %1.0lf x^2 + %1.0lf x + %1.0lf =0\n",a,b,c);
    Nraices=mn_ceros_pol_grado_2(a,b,c,x1,x2);
    printf("N. raices reales del polinomio = 2\n");
    printf("Raiz real del polinomio x1 = %e\n",0.);
    printf("Raiz real del polinomio x2 = %e\n",0.);
    printf("N. raices del polinomio (alumno) = %d\n",Nraices);
    printf("Raiz del polinomio (alumno) x1 = %e\n",x1);
    printf("Raiz del polinomio (alumno) x2 = %e\n",x2);



    system ("pause");
}

