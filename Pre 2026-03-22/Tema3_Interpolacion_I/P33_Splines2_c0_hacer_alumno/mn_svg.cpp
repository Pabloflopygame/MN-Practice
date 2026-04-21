#include "mn_svg.h"
#include "math.h"

/// FUNCIÓN PARA ESCRIBIR UNA CURVA 2D EN FORMATO SVG AÑADIENDO
/// EL VECTOR DE LA DERIVADA EN EL PUNTO INICIAL Y FINAL
void write_svg(
Array1D< real > &x /** COORDENADA HORIZONTAL DE LA CURVA */,
Array1D< real > &y /** COORDINADA VERTICAL DE LA CURVA */,
char name[300] /** NOMBRE DEL FICHERO SVG */,
real dx,real dy /** DERIVADA DE LA CURVA EN EL PUNTO INICIAL */,
real dxn,real dyn /** DERIVADA DE LA CURVA EN EL PUNTOS FINAL */,
int linewidth /** GROSOR DE LOS SEGMENTOS QUE UNEN LA CURVA */,
int circlewidth /** GROSOR DEL CÍRCULO PARA DIBUJAR LOS PUNTOS DE LA CURVA*/)
{

    FILE *f;
    f=fopen (name , "w");
    if(f==NULL){
    printf("Problems reading %s\n",name);
    system("pause");
    }

    fprintf(f,"<?xml version=\"1.0\" standalone=\"no\"?>\n");
    fprintf(f,"<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
    fprintf(f,"\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\"> \n");
    fprintf(f,"<svg width=\"12cm\" height=\"12cm\" viewBox=\"0 0 1024 1024\"\n");
    fprintf(f,"xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\"> \n");

    if(dx!=0 || dy!=0){
        real norm=sqrt(dx*dx+dy*dy);
        dx/=norm;
        dy/=norm;
        fprintf(f,"<defs>\n");
        fprintf(f,"<marker id=\"arrowhead\" markerWidth=\"10\" markerHeight=\"7\"\n");
        fprintf(f,"refX=\"0\" refY=\"3.5\" orient=\"auto\">\n");
        fprintf(f,"<polygon points=\"0 0, 10 3.5, 0 7\" stroke=\"#f00\" fill=\"red\"/>\n");
        fprintf(f,"</marker>\n");
        fprintf(f,"</defs>\n");
        fprintf(f,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"#f00\"\n",x[0],y[0],x[0]+300*dx,y[0]+300*dy);
        fprintf(f,"stroke-width=\"3\" marker-end=\"url(#arrowhead)\" />\n");
    }
    if(dxn!=0 || dyn!=0){
        real norm=sqrt(dxn*dxn+dyn*dyn);
        dxn/=norm;
        dyn/=norm;
        fprintf(f,"<defs>\n");
        fprintf(f,"<marker id=\"arrowhead\" markerWidth=\"10\" markerHeight=\"7\"\n");
        fprintf(f,"refX=\"0\" refY=\"3.5\" orient=\"auto\">\n");
        fprintf(f,"<polygon points=\"0 0, 10 3.5, 0 7\" stroke=\"#f00\" fill=\"red\"/>\n");
        fprintf(f,"</marker>\n");
        fprintf(f,"</defs>\n");
        fprintf(f,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"#f00\"\n",x[x.dim()-1],y[x.dim()-1],x[x.dim()-1]+300*dxn,y[x.dim()-1]+300*dyn);
        fprintf(f,"stroke-width=\"3\" marker-end=\"url(#arrowhead)\" />\n");
    }
    for(int k=0;k<x.dim()-1;k++){
       fprintf(f,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" style=\"stroke:rgb(0,0,0);stroke-width:%d\" />  \n",x[k],y[k],x[k+1],y[k+1],linewidth);
    }

    for(int k=0;k<x.dim();k++){
    //printf("%lf %lf\n",x[k],y[k]);
       fprintf(f,"<circle cx=\"%lf\" cy=\"%lf\" r=\"%d\" stroke=\"none\" fill=\"black\" />  \n",x[k],y[k],circlewidth);
    }
    fprintf(f,"</svg>\n");
}
