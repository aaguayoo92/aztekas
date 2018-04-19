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

int BOUNDARIES(double *B)
{
	int n, i, j, k;

	if(dim == 1)
	{	
		for(n = 0; n < eq; n++)
		{
  		   B[c1(n,3)] = B[c1(n,4)];
  		   B[c1(n,2)] = B[c1(n,4)];
  		   B[c1(n,1)] = B[c1(n,4)];
			B[c1(n,0)] = B[c1(n,4)];

			B[c1(n,Nx1-3)] = B[c1(n,Nx1-4)];
			B[c1(n,Nx1-2)] = B[c1(n,Nx1-4)];
			B[c1(n,Nx1-1)] = B[c1(n,Nx1-4)];
			B[c1(n,Nx1  )] = B[c1(n,Nx1-4)];
		}
	}
	else if(dim == 2)
	{
		for(n = 0; n < eq; n++)
		{
			for(i = 0; i <= Nx1-0; i++)
			{
				B[c2(n,i,3)] =  B[c2(n,i,4)];
				B[c2(n,i,2)] =  B[c2(n,i,4)];
				B[c2(n,i,1)] =  B[c2(n,i,4)];
 				B[c2(n,i,0)] =  B[c2(n,i,4)];
	
				B[c2(n,i,Nx2-3)] = B[c2(n,i,Nx2-4)];
				B[c2(n,i,Nx2-2)] = B[c2(n,i,Nx2-4)];
				B[c2(n,i,Nx2-1)] = B[c2(n,i,Nx2-4)];
				B[c2(n,i,Nx2)]   = B[c2(n,i,Nx2-4)];
			}
		
			for(j = 0; j <= Nx2; j++)
			{
				B[c2(n,3,j)] = B[c2(n,4,j)];
				B[c2(n,2,j)] = B[c2(n,5,j)];
				B[c2(n,1,j)] = B[c2(n,6,j)];
 				B[c2(n,0,j)] = B[c2(n,7,j)];
	
				B[c2(n,Nx1-3,j)] = B[c2(n,Nx1-4,j)];
				B[c2(n,Nx1-2,j)] = B[c2(n,Nx1-4,j)];
				B[c2(n,Nx1-1,j)] = B[c2(n,Nx1-4,j)];
				B[c2(n,Nx1  ,j)] = B[c2(n,Nx1-4,j)];
			}
		}

		////////////////////////////////////////////////
		///*---------JET-BOUNDARY-------------------*///
		////////////////////////////////////////////////
		for(j = 0; j <= Nx2; j++)
		{
			B[c2(2,3,j)] = -B[c2(2,4,j)];
			B[c2(2,2,j)] = -B[c2(2,5,j)];
			B[c2(2,1,j)] = -B[c2(2,6,j)];
 			B[c2(2,0,j)] = -B[c2(2,7,j)];
		}
		
		for(i = 0; i <= Nx1; i++)
		{
			for(j = 0; j <= Nx2; j++)
			{
				if(fabs(X1[i]) <= 1.0)
				{
					if(fabs(X2[j]) <= 1.0)
					{
						B[c2(0,i,j)] = n_jet;
						B[c2(1,i,j)] = p_jet;
						B[c2(2,i,j)] = vx1_jet;
						B[c2(3,i,j)] = vx2_jet;
					}
				}	
			}
		}
		
		////////////////////////////////////////////////
		////////////////////////////////////////////////
	}	

	else if(dim == 3)
	{
		for(n = 0; n < eq; n++)
		{
			for(i = 0; i <= Nx1-0; i++)
			{
				for(k = 0; k <= Nx3-0; k++)
				{
					B[c3(n,i,2,k)] =  B[c3(n,i,3,k)];
					B[c3(n,i,1,k)] =  B[c3(n,i,4,k)];
 					B[c3(n,i,0,k)] =  B[c3(n,i,5,k)];
	
					B[c3(n,i,Nx2-2,k)] = B[c3(n,i,Nx2-3,k)];
					B[c3(n,i,Nx2-1,k)] = B[c3(n,i,Nx2-4,k)];
					B[c3(n,i,Nx2  ,k)] = B[c3(n,i,Nx2-5,k)];
				}
			}
		
			for(j = 0; j <= Nx2-0; j++)
			{
				for(k = 0; k <= Nx3-0; k++)
				{
					B[c3(n,2,j,k)] = B[c3(n,3,j,k)];
					B[c3(n,1,j,k)] = B[c3(n,4,j,k)];
 					B[c3(n,0,j,k)] = B[c3(n,5,j,k)];
		
					B[c3(n,Nx1-2,j,k)] = B[c3(n,Nx1-3,j,k)];
					B[c3(n,Nx1-1,j,k)] = B[c3(n,Nx1-4,j,k)];
					B[c3(n,Nx1  ,j,k)] = B[c3(n,Nx1-5,j,k)];
				}
			}

			for(i = 0; i <= Nx1-0; i++)
			{
				for(j = 0; j <= Nx2-0; j++)
				{
					B[c3(n,i,j,2)] = B[c3(n,i,j,3)];
					B[c3(n,i,j,1)] = B[c3(n,i,j,4)];
 					B[c3(n,i,j,0)] = B[c3(n,i,j,5)];

					B[c3(n,i,j,Nx3-2)] = B[c3(n,i,j,Nx3-3)];
					B[c3(n,i,j,Nx3-1)] = B[c3(n,i,j,Nx3-4)];
 					B[c3(n,i,j,Nx3  )] = B[c3(n,i,j,Nx3-5)];
				}
			}
		}
	}
	return 0;
}

