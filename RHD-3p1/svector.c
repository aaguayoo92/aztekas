#include<stdio.h>
#include<math.h>
#include"../Headers/vector.h"
#include"../Headers/main.h"
    
double funct_S(int m, double *uu)
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
    
   if(m == 0)
   {
      a = 0;
   }
   else if(m == 1)
   {
      a = 0;
   }
   else if(m == 2)
   {
      a = (O*pow(W,2.0)*pow(x1,2.0)*pow(w,2.0)+p)/x1;
   }
   else if(m == 3)
   {
      a = 0;
   }
   else if(m == 4)
   {
      a = 0;
   }
   return a;
}
