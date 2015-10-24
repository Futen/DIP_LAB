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
    /*
       for(int i=0; i<256; i++){
       hist_data[i] /= inputSize.width * inputSize.height;
       }
     */
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
    imageHist(input, histVector);
    hist_data = (float*)histVector.data;

    float accum = 0;
    int height = inputSize.height;
    int width = inputSize.width;
    for(int i=0; i<256; i++){
        T_data[i] = (unsigned char)((255.0/(height*width))* (accum + hist_data[i]) + 0.5);
        accum += hist_data[i];
    }
    for(int i=0; i<inputSize.width*inputSize.height; i++){
        output_data[i] = T_data[(int)input_data[i]];
    }
    time_count = (double)getTickCount() - time_count;
    printf("histEqualization Total consume %gms\n", time_count*1000/getTickFrequency());
    imageHist(output, histVector);
    RecordHist("hist_equ.txt", histVector);
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
    if(mask.size().width != mask.size().height || (mask.size().width-1)%2!=0){
        printf("Mask size error!!\n");
        exit(0);
    }
    if(input.type() == CV_32FC(1)){
        //printf("CV_32FC1 Dectect in spatialFiltering!!\n");
        input_tmp = input;
    }
    else if(input.type() == CV_8UC(1)){
        //printf("CV_8UC1 Dectect in spatialFiltering!!\n");
        input.convertTo(input_tmp, CV_32FC(1), 1/255.0);
    }
    else{
        printf("Error Type in spatialFiltering!!!\n");
        exit(0);
    }
    if(mask.type() == CV_32FC(1)){
        //printf("CV_32FC1 Dectect in spatialFiltering Mask!!\n");
        mask_tmp = mask;
    }
    else if(mask.type() == CV_8UC(1)){
        //printf("CV_8UC1 Dectect in spatialFiltering Mask!!\n");
        mask.convertTo(mask_tmp, CV_32FC(1));
    }
    else{
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
    /*
    namedWindow("GG");
    imshow("GG", input_tmp);
    waitKey(0);
    */
    int back = (maskSize.height-1)/2;
    int mask_index;
    for(int row=0; row<inputSize.height; row++){
        for(int col=0; col<inputSize.width; col++){
            mask_index = 0;
            sum = 0;
            for(int k_row=row-back; k_row<=row+back; k_row++){
                for(int k_col=col-back; k_col<=col+back; k_col++){
                    float buf;
                    if(k_row>=0 && k_row<inputSize.height && k_col>=0 && k_col<inputSize.width){
                        buf = mask_data[mask_index]*input_data[inputSize.width*k_row+k_col];
                    }
                    else{
                        buf = 0;
                    }
                    mask_index++;
                    sum+=buf;
                }
            } 
            output_data[inputSize.width*row+col] = sum;
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
    spatialFiltering(input, laplacianMask, scaledLaplacian);
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
    for(int p; p<inputSize.width*inputSize.height; p++){
        float buf;
        scaleLap_data[p] = scaleLap_data[p]*scale;
        buf = input_data[p] + scaleLap_data[p];
        
        if(buf>1)
            buf = 1;
        else if(buf<0)
            buf = 0;
        
        output_data[p] = buf;
    }
    t = (double)getTickCount()-t;
    printf("Laplacian total consume %gms\n", t*1000/getTickFrequency());
    return;
}
