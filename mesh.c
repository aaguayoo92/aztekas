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

int MESH()
{
	int i, j, k;
	
	dx1 = (x1max - x1min)/((double)Nx1-6);
	dx2 = (x2max - x2min)/((double)Nx2-6);
	dx3 = (x3max - x3min)/((double)Nx3-6);

	if(dim == 1)
	{	
		for(i = 0; i <= Nx1-0; i++)
		{
			X1[i] = x1min + (i-3)*(dx1); 
			X1p[i] = x1min + (i+0.5-3)*(dx1);
			X1m[i] = x1min + (i-0.5-3)*(dx1);
		}
	}
	else if(dim == 2)
	{
		for(i = 0; i <= Nx1-0; i++)
		{
			X1[i]  = x1min + (i-3)*(dx1); 
			X1p[i] = x1min + (i+0.5-3)*(dx1);
			X1m[i] = x1min + (i-0.5-3)*(dx1);
		}
	
		for(j = 0; j <= Nx2-0; j++)
		{
			X2[j]  = x2min + (j-3)*(dx2);
			X2p[j] = x2min + (j+0.5-3)*(dx2);
			X2m[j] = x2min + (j-0.5-3)*(dx2);
		}
	}
	else if(dim == 3)
	{
		for(i = 0; i <= Nx1-0; i++)
		{
			X1[i]  = x1min + (i-3)*(dx1); 
			X1p[i] = x1min + (i+0.5-3)*(dx1);
			X1m[i] = x1min + (i-0.5-3)*(dx1);
		}
	
		for(j = 0; j <= Nx2-0; j++)
		{
			X2[j]  = x2min + (j-3)*(dx2); 
			X2p[j] = x2min + (j+0.5-3)*(dx2);
			X2m[j] = x2min + (j-0.5-3)*(dx2);
		}
		
		for(k = 0; k <= Nx3-0; k++)
		{
			X3[k]  = x3min + (k-3)*(dx3); 
			X3p[k] = x3min + (k+0.5-3)*(dx3);
			X3m[k] = x3min + (k-0.5-3)*(dx3);
		}
	}

	return 0;
}
