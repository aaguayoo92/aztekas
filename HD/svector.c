#include<stdio.h>
#include<math.h>
#include"../Headers/vector.h"
#include"../Headers/main.h"
    
double funct_S(int m, double *uu)
{
   double a;
   double n, p, u=0, v=0, w=0;
   n = uu[0];
   p = uu[1];
   u = uu[2];
   if(dim >= 2){v = uu[3];}
   if(dim == 3){w = uu[4];}
    
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
      a = (alfa*p)/x1;
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
