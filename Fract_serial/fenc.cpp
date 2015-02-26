#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <malloc.h>

#include "mutil.h"

using namespace std;

/*% Set timers
begrun = clock
cpu = cputime
M = imread('lena_gray_256.tif');
[sv sh] = size(M);*/


void fenc(int *M, int *T, int rsize, int nd, int nr, int sv, int sh)
{
	int *M1, *temp, *D, *bigM, *temp2, *R;

	//Begin batch runs
	int min0 = 100;

	//Scale the Domain Blocks
	M1 = (int*)malloc((int)pow(rsize*nd,2) * sizeof(int));
	temp = (int*)malloc(4 * sizeof(int));
	for (int i = 0; i < rsize*nd; i++)
	{
		for (int j = 0; j < rsize*nd; j++)
		{
			maccess(M, temp, i*2, i*2+1, j*2, j*2+1);
			M1[((i*rsize*nd) + j)] = mavg(temp);
		}
	}
	free(temp);

	//Matrix of 4 possible scalings to transform grayscale
	float s[4] = { 0.45, 0.60, 0.80, 1.00 };

	// Create monster matrix containing all possible 2D transformations
	// of the domain blocks.Store in multidimensional matrix bigM.
	int i1, i2, j1, j2;
	temp = (int*)malloc(rsize * rsize * sizeof(int));
	temp2 = (int*)malloc(rsize * rsize * sizeof(int));
	D = (int*)malloc(rsize * rsize * sizeof(int));
	bigM = (int*)malloc((int)pow(nd*rsize,2)*8 * sizeof(int));
	for (int i = 0; i < nd; i++)
	{
		i1 = i*rsize;
		i2 = (i + 1)*rsize - 1;
		for (int j = 0; j < nd; j++)
		{
			j1 = j*rsize;
			j2 = (j + 1)*rsize - 1;
			maccess(M1, D, i1, i2, j1, j2);
			msave(D, bigM, i1, i2, j1, j2, 0, 8);
			rotmat(D, temp);
			msave(temp, bigM, i1, i2, j1, j2, 1, 8);
			rotmat(temp, temp2);
			msave(temp2, bigM, i1, i2, j1, j2, 2, 8);
			rotmat(temp2, temp);
			msave(temp, bigM, i1, i2, j1, j2, 3, 8);
			fliph(D, temp);
			msave(temp, bigM, i1, i2, j1, j2, 4, 8);
			flipv(D, temp);
			msave(temp, bigM, i1, i2, j1, j2, 5, 8);
			transpose(D, temp);
			msave(temp, bigM, i1, i2, j1, j2, 6, 8);
			rotmat(temp, temp2);
			rotmat(temp2, temp);
			msave(temp, bigM, i1, i2, j1, j2, 7, 8);
		}
	}
	//free(D);
	cout << "BigM created\n";
	/*for (int i = 0; i < nd*rsize; i++)
		for (int j = 0; j < nd*rsize; j++)
			for (int k = 0; k < 8; k++)
				cout << "BigM " << i << j << k << " = " << bigM[(i + nd*rsize*(j + 8 * k))] << "\t";*/


	// Compare the range blocks and scaled domain blocks.
	// k, l - used to cycle through blocks Rkl.
	int k1, k2, l1, l2, off, dmin, i0, j0, m0, s0, g0, del_g, sum_dist, dist;
	R = (int*)malloc(rsize * rsize * sizeof(int));
	D = (int*)malloc(rsize * rsize * sizeof(int));
	for (int k = 0; k < nd; k++)
	{
		k1 = k*rsize;
		k2 = (k + 1)*rsize - 1;
		for (int l = 0; l < nd; l++)
		{
			l1 = l*rsize;
			l2 = (l + 1)*rsize - 1;
			maccess(M1, R, k1, k2, l1, l2);
			off = mavg(R);
			// Initialize error to large value
			dmin = (int)pow(10, 6);
			i0 = 0;
			j0 = 0;
			m0 = 0;
			// Now cycle through each Domain Dij
			for (int i = 0; i < nd; i++)
			{
				i1 = i*rsize;
				i2 = (i + 1)*rsize - 1;
				for (int j = 0; j < nd; j++)
				{
					j1 = j*rsize;
					j2 = (j + 1)*rsize - 1;
					// Test each transformation
					for (int n = 0; n < 4; n++)
					{
						for (int m = 0; m < 8; m++)
						{
							maccess(bigM, D, i1, i2, j1, j2, m, 8);
							scale(D, s[n]);
							del_g = off - mavg(D);
							increment(D, del_g);
							diff(R, D, temp);
							msquare(temp, temp2);
							sum_dist = msum(temp2);
							dist = sqrt(sum_dist);
							if (dist < dmin)
							{
								dmin = dist;
								i0 = i;
								j0 = j;
								m0 = m;
								s0 = s[n];
								g0 = del_g;
							}
						}
					}
				}
			}
			T[(k + nd*(l + 5 * 0))] = i0;
			T[(k + nd*(l + 5 * 1))] = j0;
			T[(k + nd*(l + 5 * 2))] = m0;
			T[(k + nd*(l + 5 * 3))] = s0;
			T[(k + nd*(l + 5 * 4))] = g0;
		}
	}
	cout << "T created\n";
}