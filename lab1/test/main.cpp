#include "header.h"
void ResizedImage(const Mat& input, Mat& output, const double scalingFactor);

int main(){
	Mat input = imread("Fig0220(a)(chronometer 3692x2812  2pt25 inch 1250 dpi).tif",CV_LOAD_IMAGE_UNCHANGED);
	Mat output;
	Mat output2;
	ResizedImage(input, output, 1/12.5);
	ResizedImage(output, output2, 12.5);
	namedWindow("TEST");
	imshow("TEST", output2);
	waitKey(0);
	imwrite("out.tif", output2);
	return 0;

}

