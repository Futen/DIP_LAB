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
    imshow("TEST", input);
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
  
    imageHist(input, v);
    RecordHist("hist_ori.txt", v);

    histEqualization(input, output, v);
    imwrite("outequ.tif",output);
    namedWindow("TEST");
    imshow("TEST", output);
    waitKey(0);

    return 0;
}

void RecordHist(const char* file_name, const Mat& histVector){
    FILE *file = fopen(file_name, "w");
    float *data = (float*)histVector.data;
    Size size = histVector.size();
    for(int i=0; i<size.width*size.height; i++){
        fprintf(file, "%f\n", data[i]);
    }

    fclose(file);
}
/*
void RecordHist(const char* file_name, const Mat& histVector){
    FILE *file = fopen(file_name, "w");
    unsigned char *data = (unsigned char*)histVector.data;
    Size size = histVector.size();
    for(int i=0; i<size.width*size.height; i++){
        fprintf(file, "%d\n", (int)data[i]);
    }

    fclose(file);
}
*/