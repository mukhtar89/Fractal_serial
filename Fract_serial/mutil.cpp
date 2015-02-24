#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#include "mutil.h"

void maccess(int *A, int *R, int a1, int a2, int b1, int b2)
{
	for (int a = a1; a <= a2; a++)
		for (int b = b1; b <= b2; b++)
			R[((a - a1)*(b2 - b1) + (b - b1))] = A[(a*(b2 - b1) + b)];
}

void maccess(int *A, int *R, int a1, int a2, int b1, int b2, int c)
{
	for (int a = a1; a <= a2; a++)
		for (int b = b1; b <= b2; b++)
			R[((a - a1)*(b2 - b1) + (b - b1))] = A[(a*(b2 - b1) + b)];
}
void msave(int *A, int *R, int a1, int a2, int b1, int b2, int c)
{
	for (int a = a1; a <= a2; a++)
		for (int b = b1; b <= b2; b++)
			R[((a - a1)*(b2 - b1) + (b - b1))] = A[(a*(b2 - b1) + b)];
}

void msave(int *A, int *R, int a1, int a2, int b1, int b2)
{
	for (int a = a1; a <= a2; a++)
		for (int b = b1; b <= b2; b++)
			R[((a - a1)*(b2 - b1) + (b - b1))] = A[(a*(b2 - b1) + b)];
}

int avg_matrix(int *R)
{
	int Rsize = sizeof(R);
	int average = 0;
	for (int x = 0; x<Rsize; x++)
		for (int y = 0; y<Rsize; y++)
			average += R[(x*Rsize) + y];
	average /= ((int)pow(Rsize, 2));
	return average;
}

