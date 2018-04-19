#include<stdio.h>
#include<math.h>
#include"../Headers/matrix.h"
#include"../Headers/main.h"
    
double funct_A(double *a, double *uu)
{
   int i, j;
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
    
   dWu = -u/(sqrt((-pow(x1,2.0)*pow(w,2.0))-pow(v,2.0)-pow(u,2.0)+1)*(pow(x1,2.0)*pow(w,2.0)+pow(v,2.0)+pow(u,2.0)-1));
   dWv = -v/(sqrt((-pow(x1,2.0)*pow(w,2.0))-pow(v,2.0)-pow(u,2.0)+1)*(pow(x1,2.0)*pow(w,2.0)+pow(v,2.0)+pow(u,2.0)-1));
   dWw = -(pow(x1,2.0)*w)/(sqrt((-pow(x1,2.0)*pow(w,2.0))-pow(v,2.0)-pow(u,2.0)+1)*(pow(x1,2.0)*pow(w,2.0)+pow(v,2.0)+pow(u,2.0)-1));
   dOn = 1;
   dOp = K/(K-1);
    
   if(W >= 1)
   {
   }
   else
   {
      W = 10;
   }
    
   for(i = 0; i < eq; i++)
   {
      for(j = 0; j < eq; j++)
      {
         if(i == 0 && j == 0)
         {
            a[i*eq + j] = -(2*O*dWw*w+2*O*dWv*v+2*O*dWu*u-O*dOp*pow(W,3.0)+O*W)/((dOn*W*dWw*n-2*O*W*dWw)*w+(dOn*W*dWv*n-2*O*W*dWv)*v+(dOn*W*dWu*n-2*O*W*dWu)*u+O*dOp*pow(W,4.0)-O*pow(W,2.0));
         }
         else if(i == 0 && j == 1)
         {
            a[i*eq + j] = (dOp*dWw*n*w+dOp*dWv*n*v+dOp*dWu*n*u)/((dOn*dWw*n-2*O*dWw)*w+(dOn*dWv*n-2*O*dWv)*v+(dOn*dWu*n-2*O*dWu)*u+O*dOp*pow(W,3.0)-O*W);
         }
         else if(i == 0 && j == 2)
         {
            a[i*eq + j] = -((dOp*pow(W,2.0)-1)*dWu*n)/((dOn*pow(W,2.0)*dWw*n-2*O*pow(W,2.0)*dWw)*w+(dOn*pow(W,2.0)*dWv*n-2*O*pow(W,2.0)*dWv)*v+(dOn*pow(W,2.0)*dWu*n-2*O*pow(W,2.0)*dWu)*u+O*dOp*pow(W,5.0)-O*pow(W,3.0));
         }
         else if(i == 0 && j == 3)
         {
            a[i*eq + j] = -((dOp*pow(W,2.0)-1)*dWv*n)/((dOn*pow(W,2.0)*dWw*n-2*O*pow(W,2.0)*dWw)*w+(dOn*pow(W,2.0)*dWv*n-2*O*pow(W,2.0)*dWv)*v+(dOn*pow(W,2.0)*dWu*n-2*O*pow(W,2.0)*dWu)*u+O*dOp*pow(W,5.0)-O*pow(W,3.0));
         }
         else if(i == 0 && j == 4)
         {
            a[i*eq + j] = -((dOp*pow(W,2.0)-1)*dWw*n)/((dOn*pow(W,2.0)*dWw*n-2*O*pow(W,2.0)*dWw)*pow(x1,2.0)*w+(dOn*pow(W,2.0)*dWv*n-2*O*pow(W,2.0)*dWv)*pow(x1,2.0)*v+(dOn*pow(W,2.0)*dWu*n-2*O*pow(W,2.0)*dWu)*pow(x1,2.0)*u+(O*dOp*pow(W,5.0)-O*pow(W,3.0))*pow(x1,2.0));
         }
         else if(i == 1 && j == 0)
         {
            a[i*eq + j] = -(O*dOn*pow(W,2.0))/((dOn*dWw*n-2*O*dWw)*w+(dOn*dWv*n-2*O*dWv)*v+(dOn*dWu*n-2*O*dWu)*u+O*dOp*pow(W,3.0)-O*W);
         }
         else if(i == 1 && j == 1)
         {
            a[i*eq + j] = -((dOn*dWw*n-2*O*dWw)*w+(dOn*dWv*n-2*O*dWv)*v+(dOn*dWu*n-2*O*dWu)*u-O*W)/((dOn*dWw*n-2*O*dWw)*w+(dOn*dWv*n-2*O*dWv)*v+(dOn*dWu*n-2*O*dWu)*u+O*dOp*pow(W,3.0)-O*W);
         }
         else if(i == 1 && j == 2)
         {
            a[i*eq + j] = (dOn*dWu*n-2*O*dWu)/((dOn*dWw*n-2*O*dWw)*w+(dOn*dWv*n-2*O*dWv)*v+(dOn*dWu*n-2*O*dWu)*u+O*dOp*pow(W,3.0)-O*W);
         }
         else if(i == 1 && j == 3)
         {
            a[i*eq + j] = (dOn*dWv*n-2*O*dWv)/((dOn*dWw*n-2*O*dWw)*w+(dOn*dWv*n-2*O*dWv)*v+(dOn*dWu*n-2*O*dWu)*u+O*dOp*pow(W,3.0)-O*W);
         }
         else if(i == 1 && j == 4)
         {
            a[i*eq + j] = (dOn*dWw*n-2*O*dWw)/((dOn*dWw*n-2*O*dWw)*pow(x1,2.0)*w+(dOn*dWv*n-2*O*dWv)*pow(x1,2.0)*v+(dOn*dWu*n-2*O*dWu)*pow(x1,2.0)*u+(O*dOp*pow(W,3.0)-O*W)*pow(x1,2.0));
         }
         else if(i == 2 && j == 0)
         {
            a[i*eq + j] = (dOn*u)/((dOn*dWw*n-2*O*dWw)*w+(dOn*dWv*n-2*O*dWv)*v+(dOn*dWu*n-2*O*dWu)*u+O*dOp*pow(W,3.0)-O*W);
         }
         else if(i == 2 && j == 1)
         {
            a[i*eq + j] = -(dOp*W*u)/((dOn*dWw*n-2*O*dWw)*w+(dOn*dWv*n-2*O*dWv)*v+(dOn*dWu*n-2*O*dWu)*u+O*dOp*pow(W,3.0)-O*W);
         }
         else if(i == 2 && j == 2)
         {
            a[i*eq + j] = ((dOn*dWw*n-2*O*dWw)*w+(dOn*dWv*n-2*O*dWv)*v+O*dOp*pow(W,3.0)-O*W)/((O*dOn*pow(W,2.0)*dWw*n-2*pow(O,2.0)*pow(W,2.0)*dWw)*w+(O*dOn*pow(W,2.0)*dWv*n-2*pow(O,2.0)*pow(W,2.0)*dWv)*v+(O*dOn*pow(W,2.0)*dWu*n-2*pow(O,2.0)*pow(W,2.0)*dWu)*u+pow(O,2.0)*dOp*pow(W,5.0)-pow(O,2.0)*pow(W,3.0));
         }
         else if(i == 2 && j == 3)
         {
            a[i*eq + j] = -((dOn*dWv*n-2*O*dWv)*u)/((O*dOn*pow(W,2.0)*dWw*n-2*pow(O,2.0)*pow(W,2.0)*dWw)*w+(O*dOn*pow(W,2.0)*dWv*n-2*pow(O,2.0)*pow(W,2.0)*dWv)*v+(O*dOn*pow(W,2.0)*dWu*n-2*pow(O,2.0)*pow(W,2.0)*dWu)*u+pow(O,2.0)*dOp*pow(W,5.0)-pow(O,2.0)*pow(W,3.0));
         }
         else if(i == 2 && j == 4)
         {
            a[i*eq + j] = -((dOn*dWw*n-2*O*dWw)*u)/((O*dOn*pow(W,2.0)*dWw*n-2*pow(O,2.0)*pow(W,2.0)*dWw)*pow(x1,2.0)*w+(O*dOn*pow(W,2.0)*dWv*n-2*pow(O,2.0)*pow(W,2.0)*dWv)*pow(x1,2.0)*v+(O*dOn*pow(W,2.0)*dWu*n-2*pow(O,2.0)*pow(W,2.0)*dWu)*pow(x1,2.0)*u+(pow(O,2.0)*dOp*pow(W,5.0)-pow(O,2.0)*pow(W,3.0))*pow(x1,2.0));
         }
         else if(i == 3 && j == 0)
         {
            a[i*eq + j] = (dOn*v)/((dOn*dWw*n-2*O*dWw)*w+(dOn*dWv*n-2*O*dWv)*v+(dOn*dWu*n-2*O*dWu)*u+O*dOp*pow(W,3.0)-O*W);
         }
         else if(i == 3 && j == 1)
         {
            a[i*eq + j] = -(dOp*W*v)/((dOn*dWw*n-2*O*dWw)*w+(dOn*dWv*n-2*O*dWv)*v+(dOn*dWu*n-2*O*dWu)*u+O*dOp*pow(W,3.0)-O*W);
         }
         else if(i == 3 && j == 2)
         {
            a[i*eq + j] = -((dOn*dWu*n-2*O*dWu)*v)/((O*dOn*pow(W,2.0)*dWw*n-2*pow(O,2.0)*pow(W,2.0)*dWw)*w+(O*dOn*pow(W,2.0)*dWv*n-2*pow(O,2.0)*pow(W,2.0)*dWv)*v+(O*dOn*pow(W,2.0)*dWu*n-2*pow(O,2.0)*pow(W,2.0)*dWu)*u+pow(O,2.0)*dOp*pow(W,5.0)-pow(O,2.0)*pow(W,3.0));
         }
         else if(i == 3 && j == 3)
         {
            a[i*eq + j] = ((dOn*dWw*n-2*O*dWw)*w+(dOn*dWu*n-2*O*dWu)*u+O*dOp*pow(W,3.0)-O*W)/((O*dOn*pow(W,2.0)*dWw*n-2*pow(O,2.0)*pow(W,2.0)*dWw)*w+(O*dOn*pow(W,2.0)*dWv*n-2*pow(O,2.0)*pow(W,2.0)*dWv)*v+(O*dOn*pow(W,2.0)*dWu*n-2*pow(O,2.0)*pow(W,2.0)*dWu)*u+pow(O,2.0)*dOp*pow(W,5.0)-pow(O,2.0)*pow(W,3.0));
         }
         else if(i == 3 && j == 4)
         {
            a[i*eq + j] = -((dOn*dWw*n-2*O*dWw)*v)/((O*dOn*pow(W,2.0)*dWw*n-2*pow(O,2.0)*pow(W,2.0)*dWw)*pow(x1,2.0)*w+(O*dOn*pow(W,2.0)*dWv*n-2*pow(O,2.0)*pow(W,2.0)*dWv)*pow(x1,2.0)*v+(O*dOn*pow(W,2.0)*dWu*n-2*pow(O,2.0)*pow(W,2.0)*dWu)*pow(x1,2.0)*u+(pow(O,2.0)*dOp*pow(W,5.0)-pow(O,2.0)*pow(W,3.0))*pow(x1,2.0));
         }
         else if(i == 4 && j == 0)
         {
            a[i*eq + j] = (dOn*w)/((dOn*dWw*n-2*O*dWw)*w+(dOn*dWv*n-2*O*dWv)*v+(dOn*dWu*n-2*O*dWu)*u+O*dOp*pow(W,3.0)-O*W);
         }
         else if(i == 4 && j == 1)
         {
            a[i*eq + j] = -(dOp*W*w)/((dOn*dWw*n-2*O*dWw)*w+(dOn*dWv*n-2*O*dWv)*v+(dOn*dWu*n-2*O*dWu)*u+O*dOp*pow(W,3.0)-O*W);
         }
         else if(i == 4 && j == 2)
         {
            a[i*eq + j] = -((dOn*dWu*n-2*O*dWu)*w)/((O*dOn*pow(W,2.0)*dWw*n-2*pow(O,2.0)*pow(W,2.0)*dWw)*w+(O*dOn*pow(W,2.0)*dWv*n-2*pow(O,2.0)*pow(W,2.0)*dWv)*v+(O*dOn*pow(W,2.0)*dWu*n-2*pow(O,2.0)*pow(W,2.0)*dWu)*u+pow(O,2.0)*dOp*pow(W,5.0)-pow(O,2.0)*pow(W,3.0));
         }
         else if(i == 4 && j == 3)
         {
            a[i*eq + j] = -((dOn*dWv*n-2*O*dWv)*w)/((O*dOn*pow(W,2.0)*dWw*n-2*pow(O,2.0)*pow(W,2.0)*dWw)*w+(O*dOn*pow(W,2.0)*dWv*n-2*pow(O,2.0)*pow(W,2.0)*dWv)*v+(O*dOn*pow(W,2.0)*dWu*n-2*pow(O,2.0)*pow(W,2.0)*dWu)*u+pow(O,2.0)*dOp*pow(W,5.0)-pow(O,2.0)*pow(W,3.0));
         }
         else if(i == 4 && j == 4)
         {
            a[i*eq + j] = ((dOn*dWv*n-2*O*dWv)*v+(dOn*dWu*n-2*O*dWu)*u+O*dOp*pow(W,3.0)-O*W)/((O*dOn*pow(W,2.0)*dWw*n-2*pow(O,2.0)*pow(W,2.0)*dWw)*pow(x1,2.0)*w+(O*dOn*pow(W,2.0)*dWv*n-2*pow(O,2.0)*pow(W,2.0)*dWv)*pow(x1,2.0)*v+(O*dOn*pow(W,2.0)*dWu*n-2*pow(O,2.0)*pow(W,2.0)*dWu)*pow(x1,2.0)*u+(pow(O,2.0)*dOp*pow(W,5.0)-pow(O,2.0)*pow(W,3.0))*pow(x1,2.0));
         }
     
      }
     
   }
   return 0;
}
