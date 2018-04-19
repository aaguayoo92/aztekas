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
#include"./Headers/matrix.h"
#include"./Headers/vector.h"
#include"./Headers/param.h"

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

int AMATRIX1D(double *u, vec_ *v, int *I)
{
	int m, n;
	int i;

	x1  = X1[I[0]];
	x2  = 0;
	x3  = 0;

	funct_A(v->A,u);
	for(m = 0; m < eq; m++)
	{
		v->S[m] = funct_S(m,u);
	}	

	return 0;
}

int AMATRIX2D(double *u, vec_ *v, int *I)
{
	int m, n;

	x1  = X1[I[0]];
	x2  = X2[I[1]];
	x3  = 0;

	funct_A(v->A,u);
	for(m = 0; m < eq; m++)
	{
		v->S[m] = funct_S(m,u);
	}	

	return 0;
}

int AMATRIX3D(double *u, vec_ *v, int *I)
{
	int m, n;

	x1  = X1[I[0]];
	x2  = X2[I[1]];
	x3  = X3[I[2]];

	funct_A(v->A,u);
	for(m = 0; m < eq; m++)
	{
		v->S[m] = funct_S(m,u);
	}	

	return 0;
}

///////////////////////////////////////////////////////////////////////////

int VECTOR(int pm, char flux, lim_ *l, flx_ *f, int *I)
{
	int n;
	double *u, lr, ll;
	double up[eq+1];
	double um[eq+1];
   double Np, Pp, vx1p=0, vx2p=0, vx3p=0;
   double Nm, Pm, vx1m=0, vx2m=0, vx3m=0;
	double x1p=0, x2p=0, x3p=0;
	double x1m=0, x2m=0, x3m=0;
	double dp[3];
	double dm[3];

   if(pm == 1)
   {
		switch(flux)
		{
			case 'f':
				u = l->ux1p;
			break;
			
			case 'g':
				u = l->ux2p;
			break;
			
			case 'h':
				u = l->ux3p;
			break;
			
		}
   }
   else
   {
		switch(flux)
		{
			case 'f':
				u = l->ux1m;
			break;
			
			case 'g':
				u = l->ux2m;
			break;

			case 'h':
				u = l->ux3m;
			break;
		}
   }

	x1p  = X1p[I[0]];
	x1m  = X1m[I[0]];

	if(dim == 2)
	{
		x2p  = X2p[I[1]];
		x2m  = X2m[I[1]];
	}
	else if(dim == 3)
	{
		x2p  = X2p[I[1]];
		x3p  = X3p[I[2]];
		x2m  = X2m[I[1]];
		x3m  = X3m[I[2]];
	}

   for(n = 0; n < eq; n++)
   {
      up[n] = u[1*eq + n];
      um[n] = u[0*eq + n];
   }

	for(n = 0; n < eq; n++)
	{
		x1 = x1p;
		x2 = x2p;
		x3 = x3p;
		f->qp[n] = funct_Q(n,up);
		x1 = x1m;
		x2 = x2m;
		x3 = x3m;
		f->qm[n] = funct_Q(n,um);

		switch(flux)
		{
			case 'f':
				x1 = x1p;
				x2 = x2p;
				x3 = x3p;
				f->fp[n] = funct_F(n,up);
				x1 = x1m;
				x2 = x2m;
				x3 = x3m;
				f->fm[n] = funct_F(n,um);
			break;

			case 'g':
				x1 = x1p;
				x2 = x2p;
				x3 = x3p;
				f->fp[n] = funct_G(n,up);
				x1 = x1m;
				x2 = x2m;
				x3 = x3m;
				f->fm[n] = funct_G(n,um);
			break;

			case 'h':
				x1 = x1p;
				x2 = x2p;
				x3 = x3p;
				f->fp[n] = funct_H(n,up);
				x1 = x1m;
				x2 = x2m;
				x3 = x3m;
				f->fm[n] = funct_H(n,um);
			break;
		}
	}	

	for(n = 0; n < 3; n++)
	{
		switch(flux)
		{
			case 'f':	
				x1 = x1p;
				x2 = x2p;
				x3 = x3p;
				dp[n] = funct_Dm(n,up);
				x1 = x1m;
				x2 = x2m;
				x3 = x3m;
				dm[n] = funct_Dm(n,um);
			break;

			case 'g':
				x1 = x1p;
				x2 = x2p;
				x3 = x3p;
				dp[n] = funct_Dn(n,up);
				x1 = x1m;
				x2 = x2m;
				x3 = x3m;
				dm[n] = funct_Dn(n,um);
			break;	

			case 'h':
				x1 = x1p;
				x2 = x2p;
				x3 = x3p;
				dp[n] = funct_Do(n,up);
				x1 = x1m;
				x2 = x2m;
				x3 = x3m;
				dm[n] = funct_Do(n,um);
			break;	
		}
	}			

	lr = max(dp[0],dp[1]);
	lr = max(lr,dp[2]);
	ll = max(dm[0],dm[1]);
	ll = max(ll,dm[2]);

	f->lp = max(lr,ll);

	lr = min(dp[0],dp[1]);
	lr = min(lr,dp[2]);
	ll = min(dm[0],dm[1]);
	ll = min(ll,dm[2]);

	f->lm = min(lr,ll);


	return 0;
}

///////////////////////////////////////////////////////////////////////////
