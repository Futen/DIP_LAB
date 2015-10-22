#include "lab2.h"
unsigned char *GetPix(unsigned char* data, int width,int row, int col);

unsigned char *GetPix(unsigned char* data, int width,int row, int col){
    return &data[row*width + col];
}
void logTransform(const Mat& input, Mat &output){
    double C;
    double t;
    unsigned char max_val;
    Mat tmp_input;
    Mat tmp_output;
    //The folowing is to check Mat type
    if(input.type() == CV_32FC1){ // if it is float type
        input.convertTo(tmp_input, CV_8UC1, 255.0);
        printf("CV_32FC1 Mat Detect in logTransform\n");
    }
    else if(input.type() == CV_8UC1){ // if it is uchar type
        printf("CV_8UC1 Mat Detect in logTransform!!\n");
        tmp_input = input;
    }
    else{ // if the type is unknown
        printf("Type Error in logTransform!!!\n");
        exit(0);
    }
    Size size_of_input = tmp_input.size(); //get input size
    unsigned char* data = tmp_input.data;
    t = (double)getTickCount();
    max_val = 0;
    // find the max value
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
        printf("CV_32FC1 Mat Dectect in powerlawTransform!!\n");
        input.convertTo(tmp_input, CV_8UC1, 255.0);
    }
    else if(input.type() == CV_8UC1){ // if it is uchar
        printf("CV_8UC1 Mat Dectect in powerlawTransform!!\n");
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
    if(input.type() == CV_32FC(1)){
        printf("CV_32FC1 Dectect in imageHist!!\n");
        input.convertTo(input_tmp, CV_8UC(1), 255.0);
    }
    else if(input.type() == CV_8UC(1)){
        printf("CV_8UC1 Dectect in imageHist!!\n");
        input_tmp = input;
    }
    else{
        printf("Error Type in imageHist!!!\n");
        exit(0);
    }
    input_data = input_tmp.data;
    inputSize = input_tmp.size();
    histVector = Mat::zeros(1, 256, CV_32FC(1));
    //printf("%d\n", histVector.type()==CV_32FC(1));
    hist_data = (float*)histVector.data;
    for(int i=0; i<inputSize.width * inputSize.height; i++){
        int tmp = (int)input_data[i];
        //cout<<tmp<<endl;
        hist_data[tmp]++;
    }
    for(int i=0; i<256; i++){
        hist_data[i] /= inputSize.width * inputSize.height;
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

    if(input.type() == CV_32FC(1)){
        printf("CV_32FC1 Dectect in histEqualization!!\n");
        input.convertTo(input_tmp, CV_8UC(1), 255.0);
    }
    else if(input.type() == CV_8UC(1)){
        printf("CV_8UC1 Dectect in histEqualization!!\n");
        input_tmp = input;
    }
    else{
        printf("Error Type in histEqualization!!!\n");
    }
    time_count = (double)getTickCount();
    T.create(1,256,CV_8UC(1));
    T_data = (unsigned char*)T.data;
    output.create(input.size(), CV_8UC(1));
    input_data = (unsigned char*)input_tmp.data;
    inputSize = input_tmp.size();
    output_data = (unsigned char*)output.data;
    imageHist(input, histVector);
    hist_data = (float*)histVector.data;

    float accum = 0;
    for(int i=0; i<256; i++){
       T_data[i] = (unsigned char)(255 * (accum + hist_data[i]) + 0.5);
       accum += hist_data[i];
    }
    for(int i=0; i<inputSize.width*inputSize.height; i++){
        output_data[i] = T_data[(int)input_data[i]];
    }
    time_count = (double)getTickCount() - time_count;
    printf("histEqualization Total consume %gms\n", time_count*1000/getTickFrequency());
    return;
}
