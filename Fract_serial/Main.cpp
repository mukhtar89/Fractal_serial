//#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <conio.h>

#include "fenc.cpp"
#include "fdec.cpp"

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
	Mat img = imread("lena.BMP", CV_LOAD_IMAGE_UNCHANGED);

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
			// a ( skipped )
			/*pixels[k] = p[2] << 16; // r
			pixels[k] |= p[1] << 8;  // g
			pixels[k] |= p[0];       // b*/

			r[k] = int(p[2]);
			g[k] = int(p[1]);
			b[k] = int(p[0]);
			//cout << r[k] << "\t" << b[k] << "\t" << g[k] << "\n";
			//_getch();
			k++;
		}
	}

	if (img.data == NULL)
	{
		cout << "Image cannot be loaded..!!" << endl;
		system("pause");
		return -1;
	}

	fenc(r, Tr);
	fenc(b, Tb);
	fenc(g, Tg);






	Mat A(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 0));

	k = 0;
	for (int i = 0; i<A.rows; i++){
		for (int j = 0; j<A.cols; j++){
			A.data[A.channels()*(A.cols*i + j) + 0] = b[k];
			A.data[A.channels()*(A.cols*i + j) + 1] = g[k];
			A.data[A.channels()*(A.cols*i + j) + 2] = r[k];
			k++;
		}
	}

	namedWindow("MyImage", CV_WINDOW_AUTOSIZE);

	imshow("MyImage", A);

	waitKey(0);
	free(r);
	free(b);
	free(g);

	return 0;
}


