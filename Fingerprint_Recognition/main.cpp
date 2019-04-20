#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "gabor.hpp"
#include "orientation.hpp"
#include "segmentation.hpp"
#include "thinning.hpp"
#include "Minutiae.hpp"
#include "distance.hpp"

using namespace std;
using namespace cv;

int main() {
	// orientation block size
	int block_size = 7;

	Mat src = imread("image/Team1/2019_1_1_L_R_1.bmp");
	Size size = { 154,203 };
	cvtColor(src, src, COLOR_RGB2GRAY);

	// rows, cols must be devided by block size
	resize(src, src, size);

	Mat pyup_src;
	pyrUp(src, pyup_src);
//	pyrUp(pyup_src, pyup_src);
	imshow("pyup_src", pyup_src);

	Mat segmented;
	Mat segmented2 = segmentation(src, segmented);

	imshow("segmented", segmented);
	imshow("segmented2", segmented2);

	
	pair<Mat, vector<pair<float, float>>> returned = orientation(src, block_size);
	Mat show = returned.first;
	vector<pair<float, float>> vec = returned.second;

	Mat gabored = gabor(src, vec, block_size) + segmented2;
	threshold(gabored, gabored, 1, 255, THRESH_BINARY_INV);


	Mat imgt = thinning(gabored);

	Mat result = printMinutiae(imgt, segmented2, vec, block_size, size);
//	calculate(imgt, src);

	pyrUp(src, src);
	imshow("src", src);

//	segmented.convertTo(segmented, CV_8U);
//	pyrUp(segmented, segmented);
//	imshow("segmented", segmented);

	pyrUp(show, show);
	imshow("show", show);

	gabored.convertTo(gabored, CV_8U);
	pyrUp(gabored, gabored);
	imshow("gabored", gabored);

	imgt.convertTo(imgt, CV_8U);
	pyrUp(imgt, imgt);
	imshow("thinned", imgt);

	pyrUp(result, result);
	imshow("check", result);
	
	waitKey(0);
	return 0;
}