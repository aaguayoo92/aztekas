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
#include<omp.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include"./Headers/main.h"

int main(void)
{
	int itprint;
	double dtprint, tprint;

	allocateArray();

	//We set the mesh func_planarMESH.c
	MESH();

	//We set the initial parameters func_planarINITIAL.c
	INITIAL(&dtprint);
	tprint  = 0.0; //Initialize printing parameter
	itprint = 0;   //Initialize file numeration
	time    = 0.0; //Initialize time
	dt      = 0.1; //Initialize dt

	start = omp_get_wtime();	
	while(time <= tmax)
	{	
		//In this part we compute the time step
		dt = TIMESTEP();

		//We print the values: file (DATOS*) and to terminal func_planarOUTPUT.c
		PrintValues(&tprint,&dtprint,&itprint);
	
		//In here we set the integration method (Finite volume method)
		INTEGRATION();
	}

	delta = omp_get_wtime() - start;
	printf("Delta %.4g seconds with %d threads\n",delta,4);

	//fclose(mass);	
	free(U);
	free(X1);
	free(X2);
	free(X3);

	return 0;
}
