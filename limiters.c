/*
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//Do not erase any of these libraries//
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include"./Headers/main.h"
#include"./Headers/limiters.h"

int RECONST1D(double *u, char r, lim_ *l, int *I)
{
	int n, i;
	double dup2, dup1, dum1, dum2;

	i = I[0];

	for(n = 0; n < eq; n++)
	{
      l->ux[n] = u[c1(n,i)];

		if(r == 'W')
		{
	      l->ux1m[0*eq + n] = WENO5(u[n*(Nx1+1)+(i-3)],u[n*(Nx1+1)+(i-2)],u[n*(Nx1+1)+(i-1)],u[c1(n,i)],u[n*(Nx1+1)+(i+1)]);
         l->ux1m[1*eq + n] = WENO5(u[n*(Nx1+1)+(i+2)],u[n*(Nx1+1)+(i+1)],u[c1(n,i)],u[n*(Nx1+1)+(i-1)],u[n*(Nx1+1)+(i-2)]);

         l->ux1p[0*eq + n] = WENO5(u[n*(Nx1+1)+(i-2)],u[n*(Nx1+1)+(i-1)],u[c1(n,i)],u[n*(Nx1+1)+(i+1)],u[n*(Nx1+1)+(i+2)]);
         l->ux1p[1*eq + n] = WENO5(u[n*(Nx1+1)+(i+3)],u[n*(Nx1+1)+(i+2)],u[n*(Nx1+1)+(i+1)],u[c1(n,i)],u[n*(Nx1+1)+(i-1)]);
      }
		else if(r == 'G')
		{
	      l->ux1m[0*eq + n] = u[n*(Nx1+1)+(i-1)];
         l->ux1m[1*eq + n] = u[n*(Nx1+1)+( i )]; 
                                           
         l->ux1p[0*eq + n] = u[n*(Nx1+1)+( i )];
         l->ux1p[1*eq + n] = u[n*(Nx1+1)+(i+1)];
      }
      else
      {
			dum2 = u[n*(Nx1+1)+(i-1)] - u[n*(Nx1+1)+(i-2)];
			dum1 = u[n*(Nx1+1)+( i )] - u[n*(Nx1+1)+(i-1)];
			dup1 = u[n*(Nx1+1)+(i+1)] - u[n*(Nx1+1)+( i )];
			dup2 = u[n*(Nx1+1)+(i+2)] - u[n*(Nx1+1)+(i+1)];
	
			l->sx1[0*eq + n] = LIMITER(dum1,dum2,r);
			l->sx1[1*eq + n] = LIMITER(dup1,dum1,r);
			l->sx1[2*eq + n] = LIMITER(dup2,dup1,r);
	
			l->ux1m[0*eq + n] = u[n*(Nx1+1)+(i-1)] + 0.5*l->sx1[0*eq + n];
			l->ux1m[1*eq + n] = u[n*(Nx1+1)+( i )] - 0.5*l->sx1[1*eq + n];
	
			l->ux1p[0*eq + n] = u[n*(Nx1+1)+( i )] + 0.5*l->sx1[1*eq + n];
			l->ux1p[1*eq + n] = u[n*(Nx1+1)+(i+1)] - 0.5*l->sx1[2*eq + n];
      }
	}

	return 0;
}

int RECONST2D(double *u, char r, lim_ *l, int *I)
{
	int n, i, j;
	double dup2, dup1, dum1, dum2;

	i = I[0];
	j = I[1];

	for(n = 0; n < eq; n++)
	{
		l->ux[n] = u[c2(n,i,j)];
	
		if(r == 'W')
		{
	      l->ux1m[0*eq + n] = WENO5(u[c2(n,i-3,j)],u[c2(n,i-2,j)],u[c2(n,i-1,j)],u[c2(n,i,j)],u[c2(n,i+1,j)]);
         l->ux1m[1*eq + n] = WENO5(u[c2(n,i+2,j)],u[c2(n,i+1,j)],u[c2(n,i,j)],u[c2(n,i-1,j)],u[c2(n,i-2,j)]);

         l->ux1p[0*eq + n] = WENO5(u[c2(n,i-2,j)],u[c2(n,i-1,j)],u[c2(n,i,j)],u[c2(n,i+1,j)],u[c2(n,i+2,j)]);
         l->ux1p[1*eq + n] = WENO5(u[c2(n,i+3,j)],u[c2(n,i+2,j)],u[c2(n,i+1,j)],u[c2(n,i,j)],u[c2(n,i-1,j)]);

	      l->ux2m[0*eq + n] = WENO5(u[c2(n,i,j-3)],u[c2(n,i,j-2)],u[c2(n,i,j-1)],u[c2(n,i,j)],u[c2(n,i,j+1)]);
         l->ux2m[1*eq + n] = WENO5(u[c2(n,i,j+2)],u[c2(n,i,j+1)],u[c2(n,i,j)],u[c2(n,i,j-1)],u[c2(n,i,j-2)]);

         l->ux2p[0*eq + n] = WENO5(u[c2(n,i,j-2)],u[c2(n,i,j-1)],u[c2(n,i,j)],u[c2(n,i,j+1)],u[c2(n,i,j+2)]);
         l->ux2p[1*eq + n] = WENO5(u[c2(n,i,j+3)],u[c2(n,i,j+2)],u[c2(n,i,j+1)],u[c2(n,i,j)],u[c2(n,i,j-1)]);
      }
		else if(r == 'G')
		{
	      l->ux1m[0*eq + n] = u[c2(n,i-1,j)];
         l->ux1m[1*eq + n] = u[c2(n,i  ,j)]; 
                                           
         l->ux1p[0*eq + n] = u[c2(n,i  ,j)];
         l->ux1p[1*eq + n] = u[c2(n,i+1,j)];

	      l->ux2m[0*eq + n] = u[c2(n,i,j-1)];
         l->ux2m[1*eq + n] = u[c2(n,i,j  )];
                                          
         l->ux2p[0*eq + n] = u[c2(n,i,j  )];
         l->ux2p[1*eq + n] = u[c2(n,i,j+1)];
      }
		else
		{
			dum2 = u[c2(n,i-1,j)] - u[c2(n,i-2,j)];
			dum1 = u[c2(n,i,j  )] - u[c2(n,i-1,j)];
			dup1 = u[c2(n,i+1,j)] - u[c2(n,i,j  )];
			dup2 = u[c2(n,i+2,j)] - u[c2(n,i+1,j)];
	
			l->sx1[0*eq + n] = LIMITER(dum1,dum2,r);
			l->sx1[1*eq + n] = LIMITER(dup1,dum1,r);
			l->sx1[2*eq + n] = LIMITER(dup2,dup1,r);
	
			l->ux1m[0*eq + n] = u[c2(n,i-1,j)] + 0.5*l->sx1[0*eq + n];
			l->ux1m[1*eq + n] = u[c2(n,i,j  )] - 0.5*l->sx1[1*eq + n];
	
			l->ux1p[0*eq + n] = u[c2(n,i,j  )] + 0.5*l->sx1[1*eq + n];
			l->ux1p[1*eq + n] = u[c2(n,i+1,j)] - 0.5*l->sx1[2*eq + n];
	
			dum2 = u[c2(n,i,j-1)] - u[c2(n,i,j-2)];
			dum1 = u[c2(n,i,j  )] - u[c2(n,i,j-1)];
			dup1 = u[c2(n,i,j+1)] - u[c2(n,i,j  )];
			dup2 = u[c2(n,i,j+2)] - u[c2(n,i,j+1)];

			l->sx2[0*eq + n] = LIMITER(dum1,dum2,r);
			l->sx2[1*eq + n] = LIMITER(dup1,dum1,r);
			l->sx2[2*eq + n] = LIMITER(dup2,dup1,r);
	
			l->ux2m[0*eq + n] = u[c2(n,i,j-1)] + 0.5*l->sx2[0*eq + n];
			l->ux2m[1*eq + n] = u[c2(n,i,j  )] - 0.5*l->sx2[1*eq + n];
	
			l->ux2p[0*eq + n] = u[c2(n,i,j  )] + 0.5*l->sx2[1*eq + n];
			l->ux2p[1*eq + n] = u[c2(n,i,j+1)] - 0.5*l->sx2[2*eq + n];
		}

	}
	return 0;
}

int RECONST3D(double *u, char r, lim_ *l, int *I)
{
	int n, i, j, k;
	double dup2, dup1, dum1, dum2;

	i = I[0];
	j = I[1];
	k = I[2];

	for(n = 0; n < eq; n++)
	{
		l->ux[n] = u[c3(n,i,j,k)];

		if(r == 'W')
		{
	      l->ux1m[0*eq + n] = WENO5(u[c3(n,i-3,j,k)],u[c3(n,i-2,j,k)],u[c3(n,i-1,j,k)],u[c3(n,i  ,j,k)],u[c3(n,i+1,j,k)]);
         l->ux1m[1*eq + n] = WENO5(u[c3(n,i+2,j,k)],u[c3(n,i+1,j,k)],u[c3(n,i  ,j,k)],u[c3(n,i-1,j,k)],u[c3(n,i-2,j,k)]);

         l->ux1p[0*eq + n] = WENO5(u[c3(n,i-2,j,k)],u[c3(n,i-1,j,k)],u[c3(n,i  ,j,k)],u[c3(n,i+1,j,k)],u[c3(n,i+2,j,k)]);
         l->ux1p[1*eq + n] = WENO5(u[c3(n,i+3,j,k)],u[c3(n,i+2,j,k)],u[c3(n,i+1,j,k)],u[c3(n,i  ,j,k)],u[c3(n,i-1,j,k)]);

	      l->ux2m[0*eq + n] = WENO5(u[c3(n,i,j-3,k)],u[c3(n,i,j-2,k)],u[c3(n,i,j-1,k)],u[c3(n,i,j  ,k)],u[c3(n,i,j+1,k)]);
         l->ux2m[1*eq + n] = WENO5(u[c3(n,i,j+2,k)],u[c3(n,i,j+1,k)],u[c3(n,i,j  ,k)],u[c3(n,i,j-1,k)],u[c3(n,i,j-2,k)]);

         l->ux2p[0*eq + n] = WENO5(u[c3(n,i,j-2,k)],u[c3(n,i,j-1,k)],u[c3(n,i,j  ,k)],u[c3(n,i,j+1,k)],u[c3(n,i,j+2,k)]);
         l->ux2p[1*eq + n] = WENO5(u[c3(n,i,j+3,k)],u[c3(n,i,j+2,k)],u[c3(n,i,j+1,k)],u[c3(n,i,j  ,k)],u[c3(n,i,j-1,k)]);

	      l->ux3m[0*eq + n] = WENO5(u[c3(n,i,j,k-3)],u[c3(n,i,j,k-2)],u[c3(n,i,j,k-1)],u[c3(n,i,j,k  )],u[c3(n,i,j,k+1)]);
         l->ux3m[1*eq + n] = WENO5(u[c3(n,i,j,k+2)],u[c3(n,i,j,k+1)],u[c3(n,i,j,k  )],u[c3(n,i,j,k-1)],u[c3(n,i,j,k-2)]);

         l->ux3p[0*eq + n] = WENO5(u[c3(n,i,j,k-2)],u[c3(n,i,j,k-1)],u[c3(n,i,j,k  )],u[c3(n,i,j,k+1)],u[c3(n,i,j,k+2)]);
         l->ux3p[1*eq + n] = WENO5(u[c3(n,i,j,k+3)],u[c3(n,i,j,k+2)],u[c3(n,i,j,k+1)],u[c3(n,i,j,k  )],u[c3(n,i,j,k-1)]);
      }
		else if(r == 'G')
		{
	      l->ux1m[0*eq + n] = u[c3(n,i-1,j,k)];
         l->ux1m[1*eq + n] = u[c3(n,i  ,j,k)]; 
                                           
         l->ux1p[0*eq + n] = u[c3(n,i  ,j,k)];
         l->ux1p[1*eq + n] = u[c3(n,i+1,j,k)];

	      l->ux2m[0*eq + n] = u[c3(n,i,j-1,k)];
         l->ux2m[1*eq + n] = u[c3(n,i,j  ,k)];
                                         
         l->ux2p[0*eq + n] = u[c3(n,i,j  ,k)];
         l->ux2p[1*eq + n] = u[c3(n,i,j+1,k)];

	      l->ux3m[0*eq + n] = u[c3(n,i,j,k-1)];
         l->ux3m[1*eq + n] = u[c3(n,i,j,k  )];
                                        
         l->ux3p[0*eq + n] = u[c3(n,i,j,k  )];
         l->ux3p[1*eq + n] = u[c3(n,i,j,k+1)];
      }
		else
		{
			dum2 = u[c3(n,i-1,j,k)] - u[c3(n,i-2,j,k)];
			dum1 = u[c3(n,i  ,j,k)] - u[c3(n,i-1,j,k)];
			dup1 = u[c3(n,i+1,j,k)] - u[c3(n,i  ,j,k)];
			dup2 = u[c3(n,i+2,j,k)] - u[c3(n,i+1,j,k)];
	
			l->sx1[0*eq + n] = LIMITER(dum1,dum2,r);
			l->sx1[1*eq + n] = LIMITER(dup1,dum1,r);
			l->sx1[2*eq + n] = LIMITER(dup2,dup1,r);
	
			l->ux1m[0*eq + n] = u[c3(n,i-1,j,k)] + 0.5*l->sx1[0*eq + n];
			l->ux1m[1*eq + n] = u[c3(n,i  ,j,k)] - 0.5*l->sx1[1*eq + n];
	
			l->ux1p[0*eq + n] = u[c3(n,i  ,j,k)] + 0.5*l->sx1[1*eq + n];
			l->ux1p[1*eq + n] = u[c3(n,i+1,j,k)] - 0.5*l->sx1[2*eq + n];
	
			dum2 = u[c3(n,i,j-1,k)] - u[c3(n,i,j-2,k)];
			dum1 = u[c3(n,i,j  ,k)] - u[c3(n,i,j-1,k)];
			dup1 = u[c3(n,i,j+1,k)] - u[c3(n,i,j  ,k)];
			dup2 = u[c3(n,i,j+2,k)] - u[c3(n,i,j+1,k)];

			l->sx2[0*eq + n] = LIMITER(dum1,dum2,r);
			l->sx2[1*eq + n] = LIMITER(dup1,dum1,r);
			l->sx2[2*eq + n] = LIMITER(dup2,dup1,r);
	
			l->ux2m[0*eq + n] = u[c3(n,i,j-1,k)] + 0.5*l->sx2[0*eq + n];
			l->ux2m[1*eq + n] = u[c3(n,i,j  ,k)] - 0.5*l->sx2[1*eq + n];
	
			l->ux2p[0*eq + n] = u[c3(n,i,j  ,k)] + 0.5*l->sx2[1*eq + n];
			l->ux2p[1*eq + n] = u[c3(n,i,j+1,k)] - 0.5*l->sx2[2*eq + n];

			dum2 = u[c3(n,i,j,k-1)] - u[c3(n,i,j,k-2)];
			dum1 = u[c3(n,i,j,k  )] - u[c3(n,i,j,k-1)];
			dup1 = u[c3(n,i,j,k+1)] - u[c3(n,i,j,k  )];
			dup2 = u[c3(n,i,j,k+2)] - u[c3(n,i,j,k+1)];

			l->sx3[0*eq + n] = LIMITER(dum1,dum2,r);
			l->sx3[1*eq + n] = LIMITER(dup1,dum1,r);
			l->sx3[2*eq + n] = LIMITER(dup2,dup1,r);
	
			l->ux3m[0*eq + n] = u[c3(n,i,j,k-1)] + 0.5*l->sx3[0*eq + n];
			l->ux3m[1*eq + n] = u[c3(n,i,j,k  )] - 0.5*l->sx3[1*eq + n];
	
			l->ux3p[0*eq + n] = u[c3(n,i,j,k  )] + 0.5*l->sx3[1*eq + n];
			l->ux3p[1*eq + n] = u[c3(n,i,j,k+1)] - 0.5*l->sx3[2*eq + n];
		}

	}
	return 0;
}

double LIMITER(double A, double B, char r)
{
	double sig;

	switch(r)
	{
		case 'G':
			sig = GODUNOV(A,B);
		break;

		case 'M':
			sig = MINMOD(A,B);
		break;

		case 'C':
			sig = MC(A,B);
		break;

		case 'S':
			sig = SUPERBEE(A,B);
		break;
	}

	return sig;
}

double MAXMOD(double A, double B)
{  
   double sig;
   
   if(A*B <= 0)
   {  
      sig = 0;
   }
   
   if(A*B > 0)
   {  
      if(fabs(A) > fabs(B))
      {
         sig = A;
      }
      
      if(fabs(A) < fabs(B))
      {
         sig = B;
      }
   }
   
   return sig;
}

double MINMOD(double A, double B)
{
   double sig;
   
   if(A*B <= 0)
   {  
      sig = 0;
   }
   
   if(A*B > 0)
   {  
      if(fabs(A) < fabs(B))
      {  
         sig = A;
      }
      
      if(fabs(A) > fabs(B))
      {  
         sig = B;
      }
   }
   
   return sig;
}

double MC(double A, double B)
{
   double sig;
   double C;

   C = (A + B)/2;

   if(A*B <= 0)
   {
      sig = 0;
   }

   if(A*B > 0)
   {
      if(fabs(A) < fabs(B) && 2*fabs(A) < fabs(C))
      {
         sig = 2*A;
      }

      if(fabs(A) > fabs(B) && 2*fabs(B) < fabs(C))
      {
         sig = 2*B;
      }

      if(fabs(C) < 2*fabs(A) && fabs(C) < 2*fabs(B))
      {
         sig= C;
      }
   }

   return sig;
}

double SUPERBEE(double A, double B)
{
   double sig1;
   double sig2;
   double sig;

   sig1 = MINMOD(2*A,B);
   sig2 = MINMOD(A,2*B);

   sig = MAXMOD(sig1,sig2);

   return sig;
}

double GODUNOV(double A, double B)
{
   double sig;

   sig = 0;

   return sig;
}

double WENO5(double v1, double v2, double v3, double v4, double v5)
{
	double c13d12 = 13.0 / 12.0;
	double c1d4   = 1.0 / 4.0;

	double fs1, fs2, fs3;
	double bs1, bs2, bs3;

	double ep = 0.000001;

	double P1, P2, P3;
	double s1, s2, s3;
	double a1, a2, a3;

	double asum;

	double om1, om2, om3;
	double R;

	P1 = v1/3.0 - 7.0*v2/6.0 + 11.0*v3/6.0;
	P2 = -v2/6.0 + 5.0*v3/6.0 + v4/3.0;
	P3 = v3/3.0 + 5.0*v4/6.0 - v5/6.0;

	fs1 = (v1 - 2.0*v2 + v3);
	fs2 = (v2 - 2.0*v3 + v4);
	fs3 = (v3 - 2.0*v4 + v5);

	bs1 = (v1 - 4.0*v2 + 3.0*v3);
	bs2 = (v2 - v4); 
	bs3 = (3.0*v3 - 4.0*v4 + v5);

	s1 = c13d12*fs1*fs1 + c1d4*bs1*bs1;
	s2 = c13d12*fs2*fs2 + c1d4*bs2*bs2;
	s3 = c13d12*fs3*fs3 + c1d4*bs3*bs3;

	a1 = 0.1/((s1 + ep)*(s1 + ep));
	a2 = 0.6/((s2 + ep)*(s2 + ep));
	a3 = 0.3/((s3 + ep)*(s3 + ep));

	asum = a1 + a2 + a3;

	om1 = a1 / asum;
	om2 = a2 / asum;
	om3 = a3 / asum;

	R = om1*P1 + om2*P2 + om3*P3;

	return R;
}
