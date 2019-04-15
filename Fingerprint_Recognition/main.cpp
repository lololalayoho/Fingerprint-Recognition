#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "gabor.hpp"
#include "orientation.hpp"
#include "segmentation.hpp"
#include "thinning.hpp"

using namespace std;
using namespace cv;

Scalar white = CV_RGB(255, 255, 255);
Scalar green = CV_RGB(0, 255, 0);

int main() {
	int block_size = 9;
	Mat src = imread("image/etc/2.bmp");

//	Mat segmented;
//	cvtColor(src, src, COLOR_BGR2GRAY);
//	adaptiveThreshold(src, segmented, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 15, 2);
//	threshold(src, segmented, 180, 255, THRESH_BINARY);
//	cvtColor(segmented, segmented, COLOR_GRAY2BGR);

	Mat segmented = segmentation(src);

	pair<Mat, vector<pair<float, float>>> returned = orientation(segmented, block_size);
	Mat show = returned.first;
	vector<pair<float, float>> vec = returned.second;

	Mat gabored = gabor(segmented, vec, block_size);

	Mat imgt = thinning(gabored);

	Mat harris_corners;

	pyrUp(src, src);
	imshow("src", src);

	segmented.convertTo(segmented, CV_8U);
	pyrUp(segmented, segmented);
	imshow("segmented", segmented);

	pyrUp(show, show);
	imshow("show", show);

	gabored.convertTo(gabored, CV_8U);
	pyrUp(gabored, gabored);
	imshow("gabored", gabored);

	imgt.convertTo(imgt, CV_8U);
	pyrUp(imgt, imgt);
	imshow("thinned", imgt);
	
	waitKey(0);
}