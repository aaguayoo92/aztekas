#include<stdio.h>
#include<math.h>
#include"../Headers/vector.h"
#include"../Headers/main.h"
    
double funct_Q(int i, double *uu)
{
   double a;
   double n, p, u=0, v=0, w=0;
   n = uu[0];
   p = uu[1];
   u = uu[2];
   if(dim >= 2){v = uu[3];}
   if(dim == 3){w = uu[4];}
    
   if(i == 0)
   {
      a = n;
   }
   else if(i == 1)
   {
      a = ((K-1)*n*pow(w,2.0)+(K-1)*n*pow(v,2.0)+(K-1)*n*pow(u,2.0)+2*p)/(2*K-2);
   }
   else if(i == 2)
   {
      a = n*u;
   }
   else if(i == 3)
   {
      a = n*v;
   }
   else if(i == 4)
   {
      a = n*w;
   }
   return a;
}
