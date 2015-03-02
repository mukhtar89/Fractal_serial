//#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <malloc.h>
#include <assert.h>

#include "fenc.h"
#include "fdec.h"

#define IMAGE "lena256.BMP"
#define FILE "lena256.frct"

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
	Mat img = imread(IMAGE, CV_LOAD_IMAGE_UNCHANGED);
	if (img.data == NULL)
	{
		cout << "Image cannot be loaded..!!" << endl;
		system("pause");
		return -1;
	}

	int sv, sh;
	sv = img.rows;
	sh = img.cols;
	if (sv != sh)
	{
		cout << "\nImage is not square";
		return 1;
	}

	int count = 0;
	int *r, *g, *b, *Tr, *Tb, *Tg;
	r = (int*)malloc(img.total()*sizeof(int));
	b = (int*)malloc(img.total()*sizeof(int));
	g = (int*)malloc(img.total()*sizeof(int));
	int k = 0;
	for (int i = 0; i<img.rows; i++) {
		for (int j = 0; j<img.cols; j++) {
			Vec3b p = img.at<Vec3b>(i, j);
			r[k] = int(p[2]);
			g[k] = int(p[1]);
			b[k] = int(p[0]);
			k++;
			
		}
	}

	int rsize = 4;
	int nd, nr;
	nd = (sv / rsize) / 2;
	nr = sv / rsize;

	Tr = (int*)malloc(nr*nr * 5 * sizeof(int));
	Tb = (int*)malloc(nr*nr * 5 * sizeof(int));
	Tg = (int*)malloc(nr*nr * 5 * sizeof(int));

	fenc(r, Tr, rsize, nd, nr, sv, sh);
	fenc(b, Tb, rsize, nd, nr, sv, sh);
	fenc(g, Tg, rsize, nd, nr, sv, sh);

	ofstream fout;
	fout.open(FILE);
	k = nr*nr * 5;
	for (int i = 0; i < k; i++)
		fout << Tr[i] << " "; //writing ith character of array in the file
	fout << "\n";
	for (int i = 0; i < k; i++)
		fout << Tb[i] << " "; //writing ith character of array in the file
	fout << "\n";
	for (int i = 0; i < k; i++)
		fout << Tg[i] << " "; //writing ith character of array in the file
	fout << "\n";

	fout.close();
	
	int *r1, *g1, *b1, *Tr1, *Tb1, *Tg1;

	Tr1 = (int*)malloc(nr*nr * 5 * sizeof(int));
	Tb1 = (int*)malloc(nr*nr * 5 * sizeof(int));
	Tg1 = (int*)malloc(nr*nr * 5 * sizeof(int));
	r1 = (int*)malloc(img.total()*sizeof(int));
	b1 = (int*)malloc(img.total()*sizeof(int));
	g1 = (int*)malloc(img.total()*sizeof(int));

	ifstream fin;
	fin.open(FILE);
	string line;
	int value;

	k = 0;
	if (getline(fin, line))
	{
		std::istringstream iss(line);
		while (iss >> value)
		{
			Tr1[k] = value;
			k++;
		}
	}
	k = 0;
	if (getline(fin, line))
	{
		std::istringstream iss(line);
		while (iss >> value)
		{
			Tb1[k] = value;
			k++;
		}
	}
	k = 0;
	if (getline(fin, line))
	{
		std::istringstream iss(line);
		while (iss >> value)
		{
			Tg1[k] = value;
			k++;
		}
	}

	fdec(r1, Tr1, rsize, nd, nr, sv, sh);
	fdec(b1, Tb1, rsize, nd, nr, sv, sh);
	fdec(g1, Tg1, rsize, nd, nr, sv, sh);

	Mat A(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 0));

	k = 0;
	for (int i = 0; i<A.rows; i++){
		for (int j = 0; j<A.cols; j++){
			A.data[A.channels()*(A.cols*i + j) + 0] = b1[k];
			A.data[A.channels()*(A.cols*i + j) + 1] = g1[k];
			A.data[A.channels()*(A.cols*i + j) + 2] = r1[k];
			k++;
		}
	}

	namedWindow("MyImage", CV_WINDOW_AUTOSIZE);

	imshow("MyImage", A);

	waitKey(0);
	free(r1);
	free(b1);
	free(g1);
	free(Tr1);
	free(Tb1);
	free(Tg1);
	free(r);
	free(b);
	free(g);
	free(Tr);
	free(Tb);
	free(Tg);

	return 0;
}