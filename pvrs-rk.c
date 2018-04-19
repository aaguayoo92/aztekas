/**
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

int RK1D(double *u, double *u1, double *u2, int order)
{
	char r;
	int n, i;
	int I[3];
	double Dx1 = dx1;
	double Dt  = dt;
	double L[eq+1], F[eq+1];
	vec_ v;
	lim_ l;

	#pragma omp parallel shared(u,u1,u2,Dt,Dx1,order,r) private(n,L,F,v,l,i) num_threads(1)
	{
		switch(order)
		{
			case 1:
				#pragma omp for 
				for(i = 4; i <= Nx1-4; i++)
				{
					//#pragma omp atomic read
					I[0] = i;
					r = 'M';
	
					RECONST1D(u,r,&l,I);
					FLUX1D(&v,&l,I);
	
					for(n = 0; n < eq; n++)
					{
						F[n] = (pow(X1p[i],alfa)*v.Fp[n] - pow(X1m[i],alfa)*v.Fm[n])/(pow(X1[i],alfa)*Dx1) - v.S[n];
					}
	
					MxV(v.A,F,L);
			
					for(n = 0; n < eq; n++)
					{
						u1[n*(Nx1+1)+(i)] = u[n*(Nx1+1)+(i)] - (Dt)*(L[n]);
					}
				}
			break;
	
			case 2:
				#pragma omp for 
				for(i = 4; i <= Nx1-4; i++)
				{
					//#pragma omp atomic read
					I[0] = i;
					r = 'C';
				
					RECONST1D(u1,r,&l,I);
					FLUX1D(&v,&l,I);
		
					for(n = 0; n < eq; n++)
					{
						F[n] = (pow(X1p[i],alfa)*v.Fp[n] - pow(X1m[i],alfa)*v.Fm[n])/(pow(X1[i],alfa)*Dx1) - v.S[n];
					}
				
					MxV(v.A,F,L);
				
					for(n = 0; n < eq; n++)
					{
						u2[n*(Nx1+1)+(i)] = 0.5*(u1[n*(Nx1+1)+(i)] + u[n*(Nx1+1)+(i)] - (Dt)*L[n]);
					}
				}
			break;
		}	
	}

	u = u2;
	return 0;	
}

int RK2D(double *u, double *u1, double *u2, int order)
{
	char r;
	int n, i, j;
	int I[3];
	double Dx1 = dx1;
	double Dx2 = dx2;
	double Dt  = dt;
	double L[eq+1], F[eq+1];
	vec_ v;
	lim_ l;

	#pragma omp parallel shared(u,u1,u2,Dt,Dx1,order,r) private(n,L,F,v,i,j) num_threads(1)
	{
		switch(order)
		{
			case 1:
				#pragma omp for 
				for(i = 4; i <= Nx1-4; i++)
				{
					for(j = 4; j <= Nx2-4; j++)
					{
						//#pragma omp atomic read
						I[0] = i;
						I[1] = j;
						r = 'C';
		
						RECONST2D(u,r,&l,I);
						FLUX2D(&v,&l,I);
		
						for(n = 0; n < eq; n++)
						{
							F[n] = (pow(X1p[i],alfa)*v.Fp[n] - pow(X1m[i],alfa)*v.Fm[n])/(pow(X1[i],alfa)*Dx1) + (v.Gp[n] - v.Gm[n])/(Dx2) - v.S[n];
						}
		
						MxV(v.A,F,L);
				
						for(n = 0; n < eq; n++)
						{
							u1[c2(n,i,j)] = u[c2(n,i,j)] - (Dt)*(L[n]);
						}
					}
				}
			break;
		
			case 2:
				#pragma omp for 
				for(i = 4; i <= Nx1-4; i++)
				{
					for(j = 4; j <= Nx2-4; j++)
					{
						//#pragma omp atomic read
						I[0] = i;
						I[1] = j;
						r = 'C';
				
						RECONST2D(u1,r,&l,I);
						FLUX2D(&v,&l,I);
		
						for(n = 0; n < eq; n++)
						{
							F[n] = (pow(X1p[i],alfa)*v.Fp[n] - pow(X1m[i],alfa)*v.Fm[n])/(pow(X1[i],alfa)*Dx1) + (v.Gp[n] - v.Gm[n])/(Dx2) - v.S[n];
						}
					
						MxV(v.A,F,L);
					
						for(n = 0; n < eq; n++)
						{
							u2[c2(n,i,j)] = 0.5*(u1[c2(n,i,j)] + u[c2(n,i,j)] - (Dt)*L[n]);
						}
					}
				}
			break;
		}	
	}


	return 0;	
}

int RK3D(double *u, double *u1, double *u2, int order)
{
	char r;
	int n, i, j, k;
	int I[3];
	double Dx1 = dx1;
	double Dx2 = dx2;
	double Dx3 = dx3;
	double Dt  = dt;
	double L[eq+1], F[eq+1];
	vec_ v;
	lim_ l;

	#pragma omp parallel shared(u,u1,u2,Dt,Dx1,order,r) private(n,L,F,v,l,i,j,k) num_threads(4)
	{
		switch(order)
		{
			case 1:
				#pragma omp for 
				for(i = 3; i <= Nx1-3; i++)
				{
					for(j = 3; j <= Nx2-3; j++)
					{
						for(k = 3; k <= Nx3-3; k++)
						{
							//#pragma omp atomic read
							I[0] = i;
							I[1] = j;
							I[2] = k;
							r = 'M';
			
							RECONST3D(u,r,&l,I);
							FLUX3D(&v,&l,I);
			
							for(n = 0; n < eq; n++)
							{
								F[n] = (v.Fp[n] - v.Fm[n])/(Dx1) + (v.Gp[n] - v.Gm[n])/(Dx2) + (v.Hp[n] - v.Hm[n])/(Dx3) - v.S[n];
							}
			
							MxV(v.A,F,L);
					
							for(n = 0; n < eq; n++)
							{
								u1[c3(n,i,j,k)] = u[c3(n,i,j,k)] - (dt)*L[n];
							}
						}
					}
				}
			break;
		
			case 2:
				#pragma omp for 
				for(i = 3; i <= Nx1-3; i++)
				{
					for(j = 3; j <= Nx2-3; j++)
					{
						for(k = 3; k <= Nx3-3; k++)
						{
							//#pragma omp atomic read
							I[0] = i;
							I[1] = j;
							I[2] = k;
							r = 'C';
					
							RECONST3D(u1,r,&l,I);
							FLUX3D(&v,&l,I);
			
							for(n = 0; n < eq; n++)
							{
								F[n] = (v.Fp[n] - v.Fm[n])/(Dx1) + (v.Gp[n] - v.Gm[n])/(Dx2) + (v.Hp[n] - v.Hm[n])/(Dx3) - v.S[n];
							}
						
							MxV(v.A,F,L);
						
							for(n = 0; n < eq; n++)
							{
								u2[c3(n,i,j,k)] = 0.5*(u1[c3(n,i,j,k)] + u[c3(n,i,j,k)] - (dt)*L[n]);
							}
						}
					}
				}
			break;
		}	
	}

	u = u2;
	return 0;	
}

		
int MxV(double *M, double *V, double *L)
{
   int n, m;
   double res=0.0;

   for(m = 0; m < eq; m++)
   {
      for(n = 0; n < eq; n++)
      {
         res += M[m*eq + n]*V[n];
      }

      L[m] = res;
      res = 0.0;
   }

   return 0;
}
