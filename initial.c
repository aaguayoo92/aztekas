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
#include<string.h>
#include"./Headers/main.h"

void INITIAL(double *dtprint)
{
	int n, i, j, k;

	if(dim == 1)
	{
		for(i = 0; i <= Nx1; i++)
		{	
			if(X1[i] < (x1max - x1min)/2.0)
			{
				U[c1(0,i)] = nl;
				U[c1(1,i)] = pl;
				U[c1(2,i)] = vx1l;
			}
			else
			{
				U[c1(0,i)] = nr;
				U[c1(1,i)] = pr;
				U[c1(2,i)] = vx1r;
			}
		}
	}
	else if(dim == 2)
	{
/*
		FILE *fdata;
		char test[50];
		fdata = fopen("./Data2D/DATA_360_2D.dat","r");

		fscanf(fdata,"%s",test);
		fscanf(fdata,"%lf",&TIME);
		fscanf(fdata,"%s",test);
		for(i = 2; i <= Nx1-2; i++)
		{
			for(j = 2; j <= Nx2-2; j++)
			{	
				fscanf(fdata,"%lf %lf %lf %lf %lf %lf",&X1[i],&X2[j],&U[c2(0,i,j)],&U[c2(1,i,j)],&U[c2(2,i,j)],&U[c2(3,i,j)]);
			}
		}
		BOUNDARIES(U);

		fclose(fdata);
*/

///////////////////////////
//--------Jet------------//
///////////////////////////

		for(i = 0; i <= Nx1; i++)
		{	
			for(j = 0; j <= Nx2; j++)
			{
				if(fabs(X1[i]) <= 1.0)
				{
					if(fabs(X2[j]) <= 1.0)
					{
						U[c2(0,i,j)] = n_jet;
						U[c2(1,i,j)] = p_jet;
						U[c2(2,i,j)] = vx1_jet;
						U[c2(3,i,j)] = vx2_jet;
					}
					else
					{
						U[c2(0,i,j)] = n_atm;
						U[c2(1,i,j)] = p_atm;
						U[c2(2,i,j)] = vx1_atm;
						U[c2(3,i,j)] = vx2_atm;
					}
				}				
				else
				{
					U[c2(0,i,j)] = n_atm;
					U[c2(1,i,j)] = p_atm;
					U[c2(2,i,j)] = vx1_atm;
					U[c2(3,i,j)] = vx2_atm;
				}
			}
		}

/////////////////////////////
//
///////////////////////////
//-----Acretion----------//
///////////////////////////
/*
		for(i = 0; i <= Nx1; i++)
		{	
			for(j = 0; j <= Nx2; j++)
			{
				double RR = sqrt(X1[i]*X1[i] + X2[j]*X2[j]);
				double R  = X1[i];
				double z  = X2[j];
				double v  = 0.5;
				double cs = 0.1;
				double r  = MM/(cs*cs + v*v);
				double rr = 2*MM;
				if(RR <= rr)
				{
					U[c2(0,i,j)] = 0.0000000001;
					U[c2(1,i,j)] = cs*cs*U[c2(0,i,j)]*(K-1)/(K*(K-1) - cs*cs*K);
					U[c2(2,i,j)] = 0.0;
					U[c2(3,i,j)] = 0.0;
				}
				else 
				{
					U[c2(0,i,j)] = 0.0000000001;
					U[c2(1,i,j)] = cs*cs*U[c2(0,i,j)]*(K-1)/(K*(K-1) - cs*cs*K);
					U[c2(2,i,j)] = -v;
					U[c2(3,i,j)] = 0.0;
				}
			}
		}
*/
/////////////////////////////


///////////////////////////
//--------Sedov----------//
///////////////////////////
/*
		for(i = 0; i <= Nx1; i++)
		{	
			for(j = 0; j <= Nx2; j++)
			{
				if(pow(X1[i] - 0.5,2.0) + pow(X2[j] - 0.5,2.0) < pow(0.15,2.0))
				{
					U[c2(0,i,j)] = 1.0;
					U[c2(1,i,j)] = 1.0;
					U[c2(2,i,j)] = 0.0;
					U[c2(3,i,j)] = 0.0;
				}
				else
				{
					U[c2(0,i,j)] = 1.0;
					U[c2(1,i,j)] = 0.1;
					U[c2(2,i,j)] = 0.0;
					U[c2(3,i,j)] = 0.0;
				}
			}				
		}
*/
/////////////////////////////

///////////////////////////
//-------Riemann---------//
///////////////////////////
/*
		for(i = 0; i <= Nx1; i++)
		{	
			for(j = 0; j <= Nx2; j++)
			{
				if(X1[i] < 0.5)
				{
					U[c2(0,i,j)] = nl;
               U[c2(1,i,j)] = pl;
					U[c2(2,i,j)] = vx1l;
					U[c2(3,i,j)] = vx2l;
				}
				else
				{
					U[c2(0,i,j)] = nr;
               U[c2(1,i,j)] = pr;
					U[c2(2,i,j)] = vx1r;
					U[c2(3,i,j)] = vx2r;
				}
			}				
		}
*/
/////////////////////////////
	}
	else if(dim == 3)
	{
		for(i = 0; i <= Nx1; i++)
		{
			for(j = 0; j <= Nx2; j++)
			{
				for(k = 0; k <= Nx3; k++)
				{
					if(X1[i] < (x1max - x1min)/2.0)
					{
						U[c3(0,i,j,k)] = nl;
						U[c3(1,i,j,k)] = pl;
						U[c3(2,i,j,k)] = vx1l;
						U[c3(3,i,j,k)] = vx2l;
						U[c3(4,i,j,k)] = vx3l;
					}
					else
					{
						U[c3(0,i,j,k)] = nr;
						U[c3(1,i,j,k)] = pr;
						U[c3(2,i,j,k)] = vx1r;
						U[c3(3,i,j,k)] = vx2r;
						U[c3(4,i,j,k)] = vx3r;
					}
				}
			}
		}
	}
	else
	{
		printf("ERROR: Variable dim distinta de {1,2,3}");
	}
	
	*dtprint = timefile;
}

