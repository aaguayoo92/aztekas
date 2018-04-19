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

int INTEGRATION()
{
	allocateEq(&U1);
	allocateEq(&U2);
	allocateEq(&U3);

	//Runge-Kutta 2th-Order and Piecewie Polynomial Reconstruction
	if(dim == 1)
	{
		RK1D(U,U1,U2,1);
		BOUNDARIES(U1);
		RK1D(U,U1,U2,2);
		BOUNDARIES(U2);
		U = U2;
	}
	else if(dim == 2)
	{
		RK2D(U,U1,U2,1);
		BOUNDARIES(U1);
		RK2D(U,U1,U2,2);
		BOUNDARIES(U2);
		U = U2;
	}
	else if(dim == 3)
	{
		RK3D(U,U1,U2,1);
		BOUNDARIES(U1);
		RK3D(U,U1,U2,2);
		BOUNDARIES(U2);
		U = U2;
	}


	return 0;
}
