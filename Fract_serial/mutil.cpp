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

void maccess(int *A, int *R, int a1, int a2, int b1, int b2, int c, int depth)
{
	for (int a = a1; a <= a2; a++)
		for (int b = b1; b <= b2; b++)
			R[((a - a1)*(b2 - b1) + (b - b1))] = A[((a + c*depth)*(b2 - b1) + b)];
}
void msave(int *A, int *R, int a1, int a2, int b1, int b2, int c, int depth)
{
	for (int a = a1; a <= a2; a++)
		for (int b = b1; b <= b2; b++)
			R[((a + c*depth)*(b2 - b1) + b)] = A[((a - a1)*(b2 - b1) + (b - b1))];
}

void msave(int *A, int *R, int a1, int a2, int b1, int b2)
{
	for (int a = a1; a <= a2; a++)
		for (int b = b1; b <= b2; b++)
			R[(a*(b2 - b1) + b)] = A[((a - a1)*(b2 - b1) + (b - b1))];
}

int mavg(int *R)
{
	int sum = msum(R);
	int avg = sum / (sizeof(R)/sizeof(int));
	return avg;
}

void diff(int *A, int *B, int *C) //each element of A-B = C
{
	int Msize = sizeof(A) / sizeof(int);
	Msize = sqrt(Msize);
	for (int i = 0; i < Msize; i++)
		C[i] = A[i] - B[i];
}

void msquare(int *A, int *B) //B = A.^2
{
	int Msize = sizeof(A) / sizeof(int);
	Msize = sqrt(Msize);
	for (int i = 0; i < Msize; i++)
		B[i] = A[i] * A[i];
}

int msum(int *A) //Sum of all elements of A
{
	int Msize = sizeof(A) / sizeof(int);
	Msize = sqrt(Msize);
	int sum = 0;
	for (int i = 0; i < Msize; i++)
		sum+=A[i];
	return sum;
}

void ones(int *A, int k)   //initialize Array A with scalar 'k'
{
	int Msize = sizeof(A) / sizeof(int);
	Msize = sqrt(Msize);
	for (int i = 0; i < Msize; i++)
		A[i] = k;
}

void matsum(int *A, int *B, int *C)  // add array A + B = C
{
	int Msize = sizeof(A)/sizeof(int);
	Msize = sqrt(Msize);
	for (int i = 0; i < Msize; i++)
		C[i] = A[i] + B[i];
}

void rotmat(int *D, int *rot)
{
	int size = sizeof(D) / sizeof(int);
	int n = sqrt(size);
	for (int i = 0; i <n ; i++)
		for (int j = 0; j < n; j++)
			rot[i*n + j] = D[(n - j - 1)*n + i];
}

void transpose(int *D, int *rot)
{
	int size = sizeof(D) / sizeof(int);
	int n = sqrt(size);
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			rot[i*n + j] = D[j*n + i];
}

void flipv(int *D, int *rot)
{
	int size = sizeof(D) / sizeof(int);
	int n = sqrt(size);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			rot[i*n + j] = D[i*n + n - j + 1];
}

void fliph(int *D, int *rot)
{
	int size = sizeof(D) / sizeof(int);
	int n = sqrt(size);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			rot[i*n + j] = D[(n - i + 1)*n + j];
}

void scale(int *D, float k)
{
	int Msize = sizeof(D) / sizeof(int);
	Msize = sqrt(Msize);
	for (int i = 0; i < Msize; i++)
		D[i] = D[i] * k;
}

void increment(int *D, float k)
{
	int Msize = sizeof(D) / sizeof(int);
	Msize = sqrt(Msize);
	for (int i = 0; i < Msize; i++)
		D[i] = D[i] + k;
}