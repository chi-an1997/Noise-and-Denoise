#include <cstdlib>
#include <iostream>
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

Mat addSaltNoise(const Mat srcImage, int n);


int main()
{
	Mat srcImage = imread("lena.jpg");
	if (!srcImage.data)
	{
		cout << "error image¡I" << endl;
		system("pause");
		return -1;
	}
	imshow("original image", srcImage);
	Mat dstImage = addSaltNoise(srcImage, 3000);
	imshow("salt and pepper noise", dstImage);
	//save image
	imwrite("salt_pepper_Image.jpg", dstImage);
	waitKey();

	//denoise
	Mat dstMedian;
	medianBlur(dstImage, dstMedian, 3);
	imshow("Median Blur", dstMedian);
	//save image
	imwrite("Median_Blur.jpg", dstMedian);
	waitKey();
	return 0;
}

Mat addSaltNoise(const Mat srcImage, int n)
{
	Mat dstImage = srcImage.clone();
	for (int k = 0; k < n; k++)
	{
		//random row and col
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//channel
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 255;		//salt noise
		}
		else
		{
			dstImage.at<Vec3b>(i, j)[0] = 255;
			dstImage.at<Vec3b>(i, j)[1] = 255;
			dstImage.at<Vec3b>(i, j)[2] = 255;
		}
	}
	for (int k = 0; k < n; k++)
	{
		//random row and col
		int i = rand() % dstImage.rows;
		int j = rand() % dstImage.cols;
		//channel
		if (dstImage.channels() == 1)
		{
			dstImage.at<uchar>(i, j) = 0;		//pepper noise
		}
		else
		{
			dstImage.at<Vec3b>(i, j)[0] = 0;
			dstImage.at<Vec3b>(i, j)[1] = 0;
			dstImage.at<Vec3b>(i, j)[2] = 0;
		}
	}
	return dstImage;
}