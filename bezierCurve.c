/*
 * Date: 22nd Feb, 2021
 * Developer: Khom
 * @ikhomkodes
 * The Following example program illustrates a method for generating Bezier curves.
 * Computer Graphics Project Work
 * Sem:V
 * BE Computer
 * NCIT*/

#include <math.h>
#include <graphics.h>

void computeCoefficients (int n, int *c)
{
	int k, i;
	
	for (k=0; k<=n; k++){
		/* Compute n!/(k!(n-k)!) */
		c[k] = 1;
		for (i=n; i>=k+1; i--)
		c[k] *= i;
		for (i=n-k; i>=2; i--)
		c[k] /= i;
	}
}

void computePoint(float u, wcPt3 * pt, int nControls, wcPt3 * controls, int * c)
{
	int k, n = nControls - 1;
	float blend;
	
	pt -> x = 0.0; pt->y = 0.0; pt->z = 0.0;
	
	/* Add in influence of each control point */
	for(k=0; k<nControls; k++)
	{
		blend = c[k] * powf (u,k) * powf (1-u,n-k);
		pt->x += controls[k].x * blend;
		pt->y += controls[k].y * blend;
		pt->z += controls[k].z * blend;
	}
}

void bezier (wcPt3 * controls, int nControls, int m, wcPt3 * curve)
{
	/* Allocate space for the coefficents */
	int * c = (int *) malloc (nControls * sizeof (int));
	int i;
	
	computeCoefficients (nControls-1,  c);
	for(i=0; i<=m; i++)
	computePoint (i / (float) m, &curve[i], nControls, controls, c);
	free (c);
}
