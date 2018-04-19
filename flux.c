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

int FLUX1D(vec_ *v, lim_ *l, int *I)
{
	int n;

	flx_ f;

	AMATRIX1D(l->ux,v,I);
	VECTOR(1,'f',l,&f,I);
	HLL(v->Fp,&f);
	VECTOR(0,'f',l,&f,I);
	HLL(v->Fm,&f);

	return 0;
}

int FLUX2D(vec_ *v, lim_ *l, int *I)
{
	int n;

	flx_ f;

	AMATRIX2D(l->ux,v,I);
	VECTOR(1,'f',l,&f,I);
	HLL(v->Fp,&f);
	VECTOR(1,'g',l,&f,I);
	HLL(v->Gp,&f);
	VECTOR(0,'f',l,&f,I);
	HLL(v->Fm,&f);
	VECTOR(0,'g',l,&f,I);
	HLL(v->Gm,&f);

	return 0;
}

int FLUX3D(vec_ *v, lim_ *l, int *I)
{
	int n;

	flx_ f;

	AMATRIX3D(l->ux,v,I);
	VECTOR(1,'f',l,&f,I);
	HLL(v->Fp,&f);
	VECTOR(1,'g',l,&f,I);
	HLL(v->Gp,&f);
	VECTOR(1,'h',l,&f,I);
	HLL(v->Hp,&f);
	VECTOR(0,'f',l,&f,I);
	HLL(v->Fm,&f);
	VECTOR(0,'g',l,&f,I);
	HLL(v->Gm,&f);
	VECTOR(0,'h',l,&f,I);
	HLL(v->Hm,&f);

	return 0;
}

int HLL(double *F, flx_ *f)
{
	int n;
   double q[eq];

	for(n = 0; n < eq; n++)
	{
		q[n] = (f->lp)*(f->lm)*(f->qp[n] - f->qm[n]);
	}

	if(f->lm < 0 && f->lp > 0)
	{
		for(n = 0; n < eq; n++)
		{
			F[n] = ((f->lp)*(f->fm[n]) - (f->lm)*(f->fp[n]) + q[n])/(f->lp - f->lm); 
		}
	}
	else if(f->lm >= 0)
	{
		for(n = 0; n < eq; n++)
		{
			F[n] = f->fm[n];
		}
	}
	else if(f->lp <= 0)
	{
		for(n = 0; n < eq; n++)
		{
			F[n] = f->fp[n];
		}
	}

   return 0;
}
