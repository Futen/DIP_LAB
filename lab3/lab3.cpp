#include "lab3.h"

void myDFT2(Mat& input, Mat& output){
    Mat input_tmp;
    Size inputSize;
    float* input_data;

    if(input.empty()){  // if input is empty
        printf("input is empty in myDFT2");
        exit(0);
    }
    // Check input type
    if(input.type() == CV_32FC(1)){
        input_tmp = input;
    }
    else if(input.type() == CV_8UC(1)){
        input.convertTo(input_tmp, CV_32FC(1), 1/255.0);
    }
    else{
        printf("Error input type in myDFT2\n");
        exit(0);
    }
    inputSize = input.size();
    input_data = (float*)input_tmp.data;
    return;
}
void myIDFT2(Mat& input, Mat& output);
void myFFT2(Mat& input, Mat& output);
void myIFFT2(Mat& input, Mat& output);
