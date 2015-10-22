#include "lab2.h"

int main(){
	Mat input = imread("Fig0308(a)(fractured_spine).tif",CV_LOAD_IMAGE_UNCHANGED);
	Mat output,v;
    //imageHist(input, output);
    //logTransform(input, output);
    //powerlawTransform(input, 0.3, output);
    //histEqualization(input, output,v);
    //input = Mat::zeros(1,256,CV_32FC(1));
    /*   
	namedWindow("TEST");
	imshow("TEST", output);
	waitKey(0);
    */
    //input.convertTo(input, CV_32FC(1), 1/255.0);
    logTransform(input, output);
    output.convertTo(output, CV_8UC(1), 255.0);
    imwrite("outlog.tif",output);

    powerlawTransform(input, 0.3, output);
    output.convertTo(output, CV_8UC(1), 255.0);
    imwrite("out3.tif",output);

    powerlawTransform(input, 0.4, output);
    output.convertTo(output, CV_8UC(1), 255.0);
    imwrite("out4.tif",output);
    /*
    histEqualization(input, output, v);
    imwrite("outequ.tif",output);
    */
	return 0;
}
