#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../mn_aritmeticas.h"
#include "../mn_PolinomiosHorner.h"


int main()
{
    /// TESTS PARA COMPROBAR QUE LA FUNCIÓN DE HORNER ESTÁ BIEN IMPLEMENTADA
    /// COMPARANDO CON LA EVALUCIÓN ESTANDAR DEL POLINOMIO Y SU DERIVADA
    printf("Polinomio de ejemplo P(x)=x^4+x^3-7x^2+x+6\n");

    /// HACER ALUMNO
    Array1D< real > a(5);
    a[0]=6.; a[1]=1.; a[2]=-7.; a[3]=1.; a[4]=1.;

    printf("EVALUACION HORNER EN x=2\n");
    real Px,PPx;
    mn_evaluar_polinomio_horner(a,2.,Px,PPx);
    printf("Px=%lf, PPx=%lf\n\n",Px,PPx);

    printf("EVALUACION ESTANDAR\n");
    Px=mn_evaluar_polinomio(a,2.);
    Array1D< real > d=mn_calcular_derivada_polinomio(a);
    PPx=mn_evaluar_polinomio(d,2.);
    printf("Px=%lf, PPx=%lf\n\n",Px,PPx);

}
