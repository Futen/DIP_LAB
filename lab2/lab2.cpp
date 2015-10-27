#include "lab2.h"
//////////////////////////////////////////////////////////////////////////////////
//  ID: 102061149 Wang Fu-En                                                    //
//  For successfully compile this code you should include the following header  //
//    <cstdlib>                                                                 //
//    <stdlib.h>                                                                //
//    <stdio.h>                                                                 //
//    <iostream>                                                                //
//    <math.h>                                                                  //
//    <opencv2/highgui/highgui.hpp>                                             //
//    <opencv2/core/core.hpp>                                                   //
//  All the function in the file will compute the processing time               //
//  automatically to get the efficiency of the code, and functions will check   //
//  whether the input data is valid or not; normally, input should be grayscale //
//  image.                                                                      //
//////////////////////////////////////////////////////////////////////////////////
void logTransform(const Mat& input, Mat &output){
    double C;
    double t;
    unsigned char max_val;
    Mat tmp_input;
    Mat tmp_output;
    //The folowing is to check Mat type
    if(input.type() == CV_32FC1){ // if it is float type
        input.convertTo(tmp_input, CV_8UC1, 255.0);
        //printf("CV_32FC1 Mat Detect in logTransform\n");
    }
    else if(input.type() == CV_8UC1){ // if it is uchar type
        //printf("CV_8UC1 Mat Detect in logTransform!!\n");
        tmp_input = input;
    }
    else{ // if the type is unknown
        //printf("Type Error in logTransform!!!\n");
        exit(0);
    }
    Size size_of_input = tmp_input.size(); //get input size
    unsigned char* data = tmp_input.data;
    t = (double)getTickCount();
    max_val = 0;
    // find the max value to determin C
    for(int index=0; index < size_of_input.height * size_of_input.width; index++)
        if(data[index] > max_val)
            max_val = data[index];

    C = 255.0/log(1+max_val); // calculate the C value
    tmp_output.create(size_of_input.height, size_of_input.width, CV_8UC(1));
    unsigned char* out_data = tmp_output.data;
    // Do log operation to every point
    for(int index=0; index < size_of_input.height * size_of_input.width; index++){
        out_data[index] = (unsigned char)(C * log(1 + data[index])+0.5);
    }
    t = (double)getTickCount() - t;
    printf("logTransform Total consume %gms\n", t*1000/getTickFrequency());
    tmp_output.convertTo(output, CV_32FC1, 1/255.0); // write output data

    return;
}
void powerlawTransform(const Mat& input, float r, Mat& output){
    double C;
    double t;
    Mat tmp_input;
    Mat tmp_output;
    unsigned char max_val;
    unsigned char* input_data;
    unsigned char* output_data;
    // Check the Mat data type 
    if(input.type() == CV_32FC1){ // if it is float
        //printf("CV_32FC1 Mat Dectect in powerlawTransform!!\n");
        input.convertTo(tmp_input, CV_8UC1, 255.0);
    }
    else if(input.type() == CV_8UC1){ // if it is uchar
        //printf("CV_8UC1 Mat Dectect in powerlawTransform!!\n");
        tmp_input = input;
    }
    else{ // if it is unknown type
        printf("Type Error in powerlawTransform!!!!\n");
        exit(0);
    }
    Size inputSize = tmp_input.size(); // get input size
    tmp_output.create(inputSize, CV_8UC(1));
    input_data = tmp_input.data;
    output_data = tmp_output.data;

    t = (double)getTickCount();
    max_val = 0;
    // fine the max value
    for(int index=0; index<inputSize.height*inputSize.width; index++)
        if(input_data[index] > max_val)
            max_val = input_data[index];
    C = 255.0/pow((double)max_val, (double)r); // calculate the constant C
    // do power operation
    for(int index=0; index<inputSize.height*inputSize.width; index++){
        output_data[index] = (unsigned char)(C * pow((double)input_data[index], (double)r)+0.5);
    }
    t = (double)getTickCount() - t;
    printf("powerlawTransform Total consume %gms\n", t*1000/getTickFrequency());
    tmp_output.convertTo(output, CV_32FC1, 1/255.0); //write output data
    return;
}
void imageHist(const Mat& input, Mat& histVector){
    Mat input_tmp;
    unsigned char *input_data;
    float *hist_data;
    Size inputSize;
    // To check data is float or uchar
    if(input.type() == CV_32FC(1)){
        //printf("CV_32FC1 Dectect in imageHist!!\n");
        input.convertTo(input_tmp, CV_8UC(1), 255.0);
    }
    else if(input.type() == CV_8UC(1)){
        //printf("CV_8UC1 Dectect in imageHist!!\n");
        input_tmp = input;
    }
    else{
        printf("Error Type in imageHist!!!\n");
        exit(0);
    }
    input_data = input_tmp.data; // get input data
    inputSize = input_tmp.size(); // get input size
    histVector = Mat::zeros(1, 256, CV_32FC(1)); // get a zero mat
    //printf("%d\n", histVector.type()==CV_32FC(1));
    hist_data = (float*)histVector.data;
    // calculat histtgram
    for(int i=0; i<inputSize.width * inputSize.height; i++){
        int tmp = (int)input_data[i];
        hist_data[tmp]++;
    }
    return;
}
void histEqualization(const Mat& input, Mat& output, Mat& T){
    Mat input_tmp;
    Mat histVector;
    unsigned char* input_data;
    unsigned char* output_data;
    unsigned char* T_data;
    float* hist_data;
    Size inputSize;
    double time_count;
    // To check input data is float or uchar
    if(input.type() == CV_32FC(1)){
        //printf("CV_32FC1 Dectect in histEqualization!!\n");
        input.convertTo(input_tmp, CV_8UC(1), 255.0);
    }
    else if(input.type() == CV_8UC(1)){
        //printf("CV_8UC1 Dectect in histEqualization!!\n");
        input_tmp = input;
    }
    else{
        printf("Error Type in histEqualization!!!\n");
        exit(0);
    }
    time_count = (double)getTickCount();
    T.create(1,256,CV_8UC(1));
    T_data = (unsigned char*)T.data;
    output.create(input.size(), CV_8UC(1));
    input_data = (unsigned char*)input_tmp.data;
    inputSize = input_tmp.size();
    output_data = (unsigned char*)output.data;
    imageHist(input, histVector); // get the image hist
    hist_data = (float*)histVector.data;

    float accum = 0; //  get the accumadata amount
    int height = inputSize.height;
    int width = inputSize.width;
    // To get the transform function
    for(int i=0; i<256; i++){
        T_data[i] = (unsigned char)((255.0/(height*width))* (accum + hist_data[i]) + 0.5);
        accum += hist_data[i];
    }
    // To write the output by T
    for(int i=0; i<inputSize.width*inputSize.height; i++){
        output_data[i] = T_data[(int)input_data[i]];
    }
    time_count = (double)getTickCount() - time_count;
    printf("histEqualization Total consume %gms\n", time_count*1000/getTickFrequency());
    return;
}
void spatialFiltering(const Mat& input, const Mat& mask, Mat& output){
    float sum;
    Mat input_tmp;
    Mat mask_tmp;
    Size inputSize;
    Size maskSize;
    float* input_data;
    float* output_data;
    float* mask_data;
    // To check mask format ---- width must equal height and be odd
    if(mask.size().width != mask.size().height || (mask.size().width-1)%2!=0){
        printf("Mask size error!!\n");
        exit(0);
    }
    // To check input type
    if(input.type() == CV_32FC(1)){// float
        //printf("CV_32FC1 Dectect in spatialFiltering!!\n");
        input_tmp = input;
    }
    else if(input.type() == CV_8UC(1)){// uisigned char
        //printf("CV_8UC1 Dectect in spatialFiltering!!\n");
        input.convertTo(input_tmp, CV_32FC(1), 1/255.0);
    }
    else{ //other type will shut down program
        printf("Error Type in spatialFiltering!!!\n");
        exit(0);
    }
    // To check mask data tye
    if(mask.type() == CV_32FC(1)){ //float
        //printf("CV_32FC1 Dectect in spatialFiltering Mask!!\n");
        mask_tmp = mask;
    }
    else if(mask.type() == CV_8UC(1)){ // unsigned char
        //printf("CV_8UC1 Dectect in spatialFiltering Mask!!\n");
        mask.convertTo(mask_tmp, CV_32FC(1));
    }
    else{ // other type will shutdown program
        printf("Error Type in spatialFiltering!!! Mask\n");
        exit(0);
    }
    maskSize = mask.size();
    mask_data = (float*)mask_tmp.data;
    inputSize = input.size();
    //cout<<inputSize.height<<endl;
    input_data = (float*)input_tmp.data;
    output.create(inputSize, CV_32FC(1));
    output_data = (float*)output.data;

    int back = (maskSize.height-1)/2;
    int mask_index;
    //start doing mask operation from (0,0)
    for(int row=0; row<inputSize.height; row++){
        for(int col=0; col<inputSize.width; col++){
            mask_index = 0;
            sum = 0;
            for(int k_row=row-back; k_row<=row+back; k_row++){
                for(int k_col=col-back; k_col<=col+back; k_col++){
                    float buf;
                    // if outside the bound then see it as 0
                    if(k_row>=0 && k_row<inputSize.height && k_col>=0 && k_col<inputSize.width){
                        buf = mask_data[mask_index]*input_data[inputSize.width*k_row+k_col];
                    }
                    else{
                        buf = 0;
                    }
                    mask_index++;
                    sum+=buf; // get the value of the pix should be
                }
            } 
            output_data[inputSize.width*row+col] = sum; //write output data
        }
    }
    return;
}
void laplacianFiltering(const Mat& input, const Mat& laplacianMask, float scale, Mat& output, Mat& scaledLaplacian){
    Mat input_tmp,tmp;
    float* input_data;
    float* output_data;
    float* scaleLap_data;
    double t = (double)getTickCount();
    Size inputSize;
    spatialFiltering(input, laplacianMask, scaledLaplacian); //get scaledLaplacian(haven't multiple scale)
    // To check input data is float or uchar
    if(input.type() == CV_8UC(1)){
        input.convertTo(input_tmp, CV_32FC(1), 1/255.0);
    }
    else if(input.type() == CV_32FC(1)){
        input_tmp = input;
    }
    else{
        printf("Error Type in laplacianFiltering!!!\n");
        exit(0);
    }
    inputSize = input.size();
    output.create(inputSize, CV_32FC(1));
    scaleLap_data = (float*)scaledLaplacian.data;
    input_data = (float*)input_tmp.data;
    output_data = (float*)output.data;
    // start doing laplace transform
    for(int p=0; p<inputSize.width*inputSize.height; p++){
        float buf;
        scaleLap_data[p] = scaleLap_data[p]*scale;//multiple scale
        buf = input_data[p] + scaleLap_data[p]; // add to origin input
        if(buf>1) // if value > 1
            buf = 1;
        else if(buf<0)// if value <0
            buf = 0;
        output_data[p] = buf;
    }
    t = (double)getTickCount()-t;
    printf("Laplacian total consume %gms\n", t*1000/getTickFrequency());
    return;
}
void unsharpFiltering(const Mat& input, const Mat& boxMask, float scale, Mat& output, Mat& scaledUnsharp, Mat& blurredInput){
    Mat input_tmp;
    float* input_data;
    float* blur_data;
    float* scaled_data;
    float* output_data;
    Size inputSize;
    double t = (double)getTickCount();
    if(input.type() == CV_8UC(1)){
        input.convertTo(input_tmp, CV_32FC(1), 1/255.0);
    }
    else if(input.type() == CV_32FC(1)){
        input_tmp = input;
    }
    else{
        printf("Error Type in unsharpFiltering!!!\n");
        exit(0);
    }
    spatialFiltering(input_tmp, boxMask, blurredInput);
    inputSize = input.size();
    output.create(inputSize, CV_32FC(1));
    scaledUnsharp.create(inputSize, CV_32FC(1));
    input_data = (float*)input_tmp.data;
    blur_data = (float*)blurredInput.data;
    output_data = (float*)output.data;
    scaled_data = (float*)scaledUnsharp.data;

    for(int i=0; i<inputSize.width*inputSize.height; i++){
        float buf;
        scaled_data[i] = scale * (input_data[i] - blur_data[i]);
        buf = input_data[i] + scaled_data[i];
        if(buf > 255)
            buf = 255;
        else if(buf < 0)
            buf = 0;
        output_data[i] = buf;
    }
    t = ((double)getTickCount() - t)*1000/getTickFrequency();
    printf("Total consume %gms\n", t);
    return;
}
