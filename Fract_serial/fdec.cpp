#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#include "mutil.h"

using namespace std;

/*% Set timers
begrun = clock
cpu = cputime
M = imread('lena_gray_256.tif');
[sv sh] = size(M);*/


void fdec(int *R, int *T)
{
	int *M, *M1, *temp, *D, *bigM, *temp2;

	int sv, sh;
	sv = 0;
	sh = 0;

	M = (int*)malloc(sv * sh * sizeof(int));
	ones(M, 100);

	//Begin batch runs
	int min0 = 100;
	int rsize = 4;
	int nd, nr;
	nd = (sv / rsize) / 2;
	nr = sv / rsize;


	//Scale the Domain Blocks
	M1 = (int*)malloc((int)pow(rsize*nd, 2) * sizeof(int));
	temp = (int*)malloc(4 * sizeof(int));
	for (int i = 0; i < rsize*nd; i++)
	{
		for (int j = 0; j < rsize*nd; j++)
		{
			maccess(M, temp, i*2, i*2+1, j*2, j*2+1);
			M1[((i*rsize*nd) + j)] = avg_matrix(temp);
		}
	}
	free(temp);

	/*% Transform Domain Block Using T matrix
    for k=1:nr
        k1=(k-1)*rsize+1;
        k2=k*rsize;
        for l=1:nr
            l1=(l-1)*rsize+1;
            l2=l*rsize;
            i0 = T(k,l,1);
            j0 = T(k,l,2);
            m0 = T(k,l,3);
            s0 = T(k,l,4);
            g0 = T(k,l,5);
            i1 = (i0-1)*rsize+1;
            i2 = i0*rsize;
            j1 = (j0-1)*rsize+1;
            j2 = j0*rsize;
            D = M1(i1:i2,j1:j2);
            if m0==2
                D=rotmat(D);
            elseif m0==3
                D=rotmat(rotmat(D));
            elseif m0==4
                D=rotmat(rotmat(rotmat(D)));
            elseif m0==5
                D=fliph(D);
            elseif m0==6
                D=flipv(D);
            elseif m0==7
                D=D';
            elseif m0==8
                D=rotmat(rotmat(D'));
            end
            R=s0*D+g0*ones(size(D));
            MM(k1:k2,l1:l2)=R;
        end
    end
    M=MM;*/


	// Compare the range blocks and scaled domain blocks.
	// k, l - used to cycle through blocks Rkl.
	int i, j, i1, i2, j1, j2, k1, k2, l1, l2, off, dmin, i0, j0, m0, s0, g0, del_g, sum_dist, dist;
	R = (int*)malloc(rsize * rsize * sizeof(int));
	D = (int*)malloc(rsize * rsize * sizeof(int));
	T = (int*)malloc(rsize * rsize * 5 * sizeof(int));
	temp = (int*)malloc(rsize * rsize * sizeof(int));
	temp2 = (int*)malloc(rsize * rsize * sizeof(int));
	for (int k = 0; k < nd; k++)
	{
		k1 = k*rsize;
		k2 = (k + 1)*rsize - 1;
		for (int l = 0; l < nd; l++)
		{
			l1 = l*rsize;
			l2 = (l + 1)*rsize - 1;
			i0 = T[(k + nd*(l + 5 * 0))];
			j0 = T[(k + nd*(l + 5 * 1))];
			m0 = T[(k + nd*(l + 5 * 2))];
			s0 = T[(k + nd*(l + 5 * 3))];
			g0 = T[(k + nd*(l + 5 * 4))];
			i1 = i0*rsize;
			i2 = (i0 + 1)*rsize - 1;
			j1 = j0*rsize;
			j2 = (j0 + 1)*rsize - 1;
			maccess(M1, D, i1, i2, j1, j2);

			memcpy(temp, D, rsize*rsize);
			if (m0 == 1)
				rotmat(temp, D);
			else if (m0 == 2)
			{
				rotmat(temp, temp2);
				rotmat(temp2, D);
			}
			else if (m0 == 3)
			{
				rotmat(temp, temp2);
				rotmat(temp2, temp);
				rotmat(temp, D);
			}
			else if (m0 == 4)
				fliph(temp, D);
			else if (m0 == 5)
				flipv(temp, D);
			else if (m0 == 6)
				transpose(temp, D);
			else if (m0 == 7)
			{
				transpose(temp, D);
				rotmat(D, temp);
				rotmat(temp, D);
			}
			scale(D, s0);
			ones(temp, g0);
			matsum(D, temp, R);
			msave(R, M, k1, k2, l1, l2);
		}
	}
}