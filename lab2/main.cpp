#include "lab2.h"

int main(){
    Mat input = imread("Fig0308(a)(fractured_spine).tif",CV_LOAD_IMAGE_UNCHANGED);
    float a[5][5] = {{1,4,7,4,1},{4,16,26,16,4},{7,26,41,26,7},{4,16,26,16,4},{1,4,7,4,1}};
    float b[3][3] = {{0.11, 0.11, 0.11}, {0.11, 0.11, 0.11}, {0.11, 0.11, 0.11}};
    Mat mask, output,T;
    float *data,*data2;
//    imageHist(input, v);
//    RecordHist("hist.txt", v);
    mask = Mat(3,3,CV_32FC(1),b);
    
    histEqualization(input, output, T);
    RecordHist_CH("T_hist.txt", T);
    namedWindow("TEST");
    imshow("TEST", output);
    waitKey(0);
    imwrite("equ_out.tif",output);

/*
    logTransform(input, output);
    output.convertTo(output, CV_8UC(1), 255.0);
    namedWindow("TEST");
    imshow("TEST", output);
    waitKey(0);
    imwrite("log_out.tif",output);
*/
/*
    powerlawTransform(input, 0.8, output);
    output.convertTo(output, CV_8UC(1), 255.0);
    namedWindow("TEST");
    imshow("TEST", output);
    waitKey(0);
    imwrite("power_out08.tif",output);

    powerlawTransform(input, 0.6, output);
    output.convertTo(output, CV_8UC(1), 255.0);
    namedWindow("TEST");
    imshow("TEST", output);
    waitKey(0);
    imwrite("power_out06.tif",output);

    powerlawTransform(input, 0.4, output);
    output.convertTo(output, CV_8UC(1), 255.0);
    namedWindow("TEST");
    imshow("TEST", output);
    waitKey(0);
    imwrite("power_out_04.tif",output);

    powerlawTransform(input, 0.2, output);
    output.convertTo(output, CV_8UC(1), 255.0);
    namedWindow("TEST");
    imshow("TEST", output);
    waitKey(0);
    imwrite("power_out02.tif",output);

    powerlawTransform(input, 0.1, output);
    output.convertTo(output, CV_8UC(1), 255.0);
    namedWindow("TEST");
    imshow("TEST", output);
    waitKey(0);
    imwrite("power_out01.tif",output);
*/
    return 0;
}

void RecordHist_F(const char* file_name, const Mat& histVector){
    FILE *file = fopen(file_name, "w");
    float *data = (float*)histVector.data;
    Size size = histVector.size();
    for(int i=0; i<size.width*size.height; i++){
        fprintf(file, "%f\n", data[i]);
    }

    fclose(file);
}
void RecordHist_CH(const char* file_name, const Mat& histVector){
    FILE *file = fopen(file_name, "w");
    Mat hist_tmp;
    if(histVector.type()==CV_32FC(1))
        histVector.convertTo(hist_tmp, CV_8UC(1), 255.0);
    else
        hist_tmp = histVector;
    unsigned char *data = (unsigned char*)hist_tmp.data;
    Size size = histVector.size();
    for(int i=0; i<size.width*size.height; i++){
        fprintf(file, "%d\n", (int)data[i]);
    }

    fclose(file);
}

