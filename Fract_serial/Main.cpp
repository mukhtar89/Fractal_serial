//#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <malloc.h>

#include "fenc.cpp"
#include "fdec.cpp"

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
	Mat img = imread("lena.BMP", CV_LOAD_IMAGE_UNCHANGED);
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

	Tr = (int*)malloc(nd*nd * 5 * sizeof(int));
	Tb = (int*)malloc(nd*nd * 5 * sizeof(int));
	Tg = (int*)malloc(nd*nd * 5 * sizeof(int));

	fenc(r, Tr, rsize, nd, nr, sv, sh);
	fenc(b, Tb, rsize, nd, nr, sv, sh);
	fenc(g, Tg, rsize, nd, nr, sv, sh);

	ofstream fout;
	fout.open("lena.frct");
	k = nd*nd * 5;
	for (int i = 0; i < k; i++)
		fout << Tr[i] << ","; //writing ith character of array in the file
	fout << "|";
	for (int i = 0; i < k; i++)
		fout << Tb[i] << ","; //writing ith character of array in the file
	fout << "|";
	for (int i = 0; i < k; i++)
		fout << Tg[i] << ","; //writing ith character of array in the file
	fout << "|";

	fout.close();
	free(r);
	free(b);
	free(g);
	free(Tr);
	free(Tb);
	free(Tg);


	int *r1, *g1, *b1, *Tr1, *Tb1, *Tg1;

	Tr1 = (int*)malloc(nd*nd * 5 * sizeof(int));
	Tb1 = (int*)malloc(nd*nd * 5 * sizeof(int));
	Tg1 = (int*)malloc(nd*nd * 5 * sizeof(int));
	r1 = (int*)malloc(img.total()*sizeof(int));
	b1 = (int*)malloc(img.total()*sizeof(int));
	g1 = (int*)malloc(img.total()*sizeof(int));

	ifstream fin;
	fin.open("lena.frct");
	int pos_temp;
	char temp[3] = {};
	char t = '0';
	count = 0;
	int i = 0;
	int j = 0;
	k = 0;

	while (!fin.eof())
	{
		t = fin.get();
		if (t == '|')
		{
			count++;
			cout << "Counts = " << count << "\n";
			if (count != 3)
				t = fin.get();
			i = 0;
			j = 0;
			k = 0;
		}
		if (count == 3)
			continue;
		pos_temp = 0;
		for (int i = 0; i < 3; i++)
			temp[i] = 0;
		while (t != ',')
		{
			temp[pos_temp] = t;
			pos_temp++;
			t = fin.get();
		}
		switch (count)
		{
			case 0: Tr1[(i + nd*(j + k * 5))] = atoi(temp);
					break;
			case 1: Tb1[(i + nd*(j + k * 5))] = atoi(temp);
					break;
			case 2: Tg1[(i + nd*(j + k * 5))] = atoi(temp);
					break;
			default: break;
		}
		k++;
		if (k == 5)
		{
			k = 0;
			j++;
		}
		if (j == nd)
		{
			j = 0;
			i++;
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

	return 0;
}


