/*
 *   This program is free software: x2ou can redistribute it and/or modify
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

void allocateArray()
{
	if(dim == 1)
	{
		X1  = (double *)malloc((Nx1+1)*sizeof(double));
		X1p = (double *)malloc((Nx1+1)*sizeof(double));
		X1m = (double *)malloc((Nx1+1)*sizeof(double));
		U   = (double *)malloc((Nx1+1)*(eq+1)*sizeof(double));
	}
	else if(dim == 2)
	{
		X1  = (double *)malloc((Nx1+1)*sizeof(double));
		X1p = (double *)malloc((Nx1+1)*sizeof(double));
		X1m = (double *)malloc((Nx1+1)*sizeof(double));
		X2  = (double *)malloc((Nx2+1)*sizeof(double));
		X2p = (double *)malloc((Nx2+1)*sizeof(double));
		X2m = (double *)malloc((Nx2+1)*sizeof(double));
		U   = (double *)malloc((Nx1+1)*(Nx2+1)*(eq+1)*sizeof(double));
	}
	else if(dim == 3)
	{
		X1  = (double *)malloc((Nx1+1)*sizeof(double));
		X1p = (double *)malloc((Nx1+1)*sizeof(double));
		X1m = (double *)malloc((Nx1+1)*sizeof(double));
		X2  = (double *)malloc((Nx2+1)*sizeof(double));
		X2p = (double *)malloc((Nx2+1)*sizeof(double));
		X2m = (double *)malloc((Nx2+1)*sizeof(double));
		X3  = (double *)malloc((Nx3+1)*sizeof(double));
		X3p = (double *)malloc((Nx3+1)*sizeof(double));
		X3m = (double *)malloc((Nx3+1)*sizeof(double));
		U   = (double *)malloc((Nx1+1)*(Nx2+1)*(Nx3+1)*(eq+1)*sizeof(double));
	}
}

void allocateEq(double **u) 
{
	if(dim == 1)
	{
		*u = (double *)malloc((Nx1+1)*(eq+1)*sizeof(double));	
	}
	else if(dim == 2)
	{
		*u = (double *)malloc((Nx1+1)*(Nx2+1)*(eq+1)*sizeof(double));
	}
	else if(dim == 3)
	{
		*u = (double *)malloc((Nx1+1)*(Nx2+1)*(Nx3+1)*(eq+1)*sizeof(double));
	}
	else
	{ 
		printf("Error at dim variable (1,2,3)");
	}
}
