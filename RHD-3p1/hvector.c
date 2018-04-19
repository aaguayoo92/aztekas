#include<stdio.h>
#include<math.h>
#include"../Headers/vector.h"
#include"../Headers/main.h"
    
double funct_H(int i, double *uu)
{
   double a;
   double n, p, u=0, v=0, w=0;
   double r, W, O;
   double dWu, dWv, dWw;
   double dOn, dOp;
   n = uu[0];
   p = uu[1];
   u = uu[2];
   if(dim >= 2){v = uu[3];}
   if(dim == 3){w = uu[4];}
    
   r = x1;
   W = 1/sqrt((-pow(x1,2.0)*pow(w,2.0))-pow(v,2.0)-pow(u,2.0)+1);
   O = (K*p+(K-1)*n)/(K-1);
    
   if(W >= 1)
   {
   }
   else
   {
      W = 10;
   }
    
   if(i == 0)
   {
      a = W*n*w;
   }
   else if(i == 1)
   {
      a = O*pow(W,2.0)*w;
   }
   else if(i == 2)
   {
      a = O*pow(W,2.0)*u*w;
   }
   else if(i == 3)
   {
      a = O*pow(W,2.0)*v*w;
   }
   else if(i == 4)
   {
      a = O*pow(W,2.0)*pow(x1,2.0)*pow(w,2.0)+p;
   }
   return a;
}
