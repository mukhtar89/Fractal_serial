#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <math.h>


void maccess(int *A, int *R, int a1, int a2, int b1, int b2);     //access A, save into R

void maccess(int *A, int *R, int a1, int a2, int b1, int b2, int c, int depth);    //access A, save into R

void msave(int *A, int *R, int a1, int a2, int b1, int b2, int c, int depth);    //access A, save into R

void msave(int *A, int *R, int a1, int a2, int b1, int b2);    //access A, save into R

int mavg(int *R);

void rotmat(int *D, int *rot);   //rotate matrix D, save it into rot

void fliph(int *D, int *rot);   //rotate matrix D, save it into rot

void flipv(int *D, int *rot);   //rotate matrix D, save it into rot

void transpose(int *D, int *rot);   //rotate matrix D, save it into rot

void scale(int *D, float k); //scale matrix with k

void increment(int *D, float k); //increment each matrix element with k

void diff(int *A, int *B, int *C); //each element of A-B = C

void msquare(int *A, int *B); //B = A.^2

int msum(int *A); //Sum of all elements of A

int ones(int *A, int k); //initialize Array A with scalar 'k'

void matsum(int *A, int *B, int *C);  // add array A + B = C
