#include<stdio.h>
#include<math.h>
#include"../Headers/matrix.h"
#include"../Headers/main.h"
    
double funct_Dn(int i, double *uu)
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
      a = -(sqrt(K*n*p)-n*v)/n;
   }
   else if(i == 1)
   {
      a = (n*v+sqrt(K*n*p))/n;
   }
   else if(i == 2)
   {
      a = v;
   }
   return a;
}
