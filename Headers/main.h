#include"const.h"
#include"initial.h"
#include"param.h"

double *U, *U1, *U2, *U3;
double *X1;
double *X1p, *X1m;
double *X2;
double *X2p, *X2m;
double *X3;
double *X3p, *X3m;

double x1, x2, x3;
double dx1, dx2, dx3;
double dt, time;

double start, delta;

typedef struct
{
	double ux1p[20];
	double ux1m[20];
	double sx1[20];
	double ux2p[20];
	double ux2m[20];
	double sx2[20];
	double ux3p[20];
	double ux3m[20];
	double sx3[20];
	double ux[20];
}lim_;

typedef struct
{
	double qp[10];
	double qm[10];
	double fp[10];
	double fm[10];
	double lp;
	double lm;
}flx_;

typedef struct
{
	double A[30];
	double S[10];
	double Fp[10];
	double Fm[10];
	double Gp[10];
	double Gm[10];
	double Hp[10];
	double Hm[10];
}vec_;

double LIMITER(double A, double B, char r);

double GODUNOV(double A, double B);

double MAXMOD(double A, double B);

double MINMOD(double A, double B);

double MC(double A, double B);

double SUPERBEE(double A, double B);

double WENO5(double v1, double v2, double v3, double v4, double v5);

void allocateArray();

void allocateEq(double **u);

int MESH(); 

void INITIAL(double *dtprint);

double TIMESTEP();

int BOUNDARIES(double *U);

int PrintValues(double *tprint, double *dtprint, int *itprint);

int Output1(int *itprint);

int Output2(int *itprint);

int Output3(int *itprint);

int INTEGRATION();

int RK1D(double *u, double *u1, double *u2, int order);

int RK2D(double *u, double *u1, double *u2, int order);

int RK3D(double *u, double *u1, double *u2, int order);

int FLUX1D(vec_ *v, lim_ *l, int *I);
                                   
int FLUX2D(vec_ *v, lim_ *l, int *I);
                                   
int FLUX3D(vec_ *v, lim_ *l, int *I);

int HLL(double *F, flx_ *f);

int AMATRIX1D(double *u, vec_ *v, int *I);
                                                            
int AMATRIX2D(double *u, vec_ *v, int *I);
                                              
int AMATRIX3D(double *u, vec_ *v, int *I);

int VECTOR(int pm, char flux, lim_ *l, flx_ *f, int *I);

int c1(int n, int i);

int c2(int n, int i, int j);

int c3(int n, int i, int j, int k);

int RECONST1D(double *u, char r, lim_ *l, int *I);

int RECONST2D(double *u, char r, lim_ *l, int *I);

int RECONST3D(double *u, char r, lim_ *l, int *I);

int MxV(double *M, double *V, double *L);
