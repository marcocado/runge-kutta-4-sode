#include<stdio.h>
#include<stdbool.h>


typedef struct mValues{
    double m1;
    double m2;
    double m3;
    double m4;
};

typedef struct kValues{
    double k1;
    double k2;
    double k3;
    double k4;
};

typedef struct funcValues{
    double xn;
    double yn;
    double ydn;
};

double function(double x, double y, double yd){
    double f;
    f = x*yd - 6*y;
    return f;
}

void approximation(struct funcValues *currP, struct kValues *k, struct mValues *m, double h){
    k->k1 = h*currP->ydn;
    m->m1 = h*function(currP->xn, currP->yn, currP->ydn);
    k->k2 = h*(currP->ydn + m->m1/2);
    m->m2 = h*function(currP->xn + h/2, currP->yn + k->k1/2, currP->ydn + m->m1/2);
    k->k3 = h*(currP->ydn + m->m2/2);
    m->m3 = h*function(currP->xn + h/2, currP->yn + k->k2/2, currP->ydn + m->m2/2);
    k->k4 = h*(currP->ydn + m->m3);
    m->m4 = h*function(currP->xn + h, currP->yn + k->k3, currP->ydn + m->m3);

    currP->yn = currP->yn + 0.16666*(k->k1 + 2*k->k2 + 2*k->k3 + k->k4);
    currP->ydn = currP->yn + 0.16666*(m->m1 + 2*m->m2 + 2*m->m3 + m->m4);
}

void main(){
    int i;
    int n = 20;
    double h;
    struct funcValues startValues = {1, 2, 1};
    h = (6 - startValues.xn)/n;
    printf("Die Schrittweite ist: %.2f\n", h);

    struct kValues k;
    struct kValues *kPointer = &k;
    struct mValues m;
    struct mValues *mPointer = &m;
    struct funcValues f = startValues;
    struct funcValues *fPointer = &f;

    for(i=0; i<n; i++){
        approximation(fPointer, kPointer, mPointer, h);
        fPointer->xn = fPointer->xn + h;
        printf("%.2f\n", fPointer->yn);
    }
}