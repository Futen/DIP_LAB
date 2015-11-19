#include "lab3.h"

typedef class ComplexNum{
public:
    float real;
    float img;
    void Set(float in_real=0, float in_img=0){
        real = in_real;
        img = in_img;
    };
    float GetMag(){
        float out = sqrt(pow(real,2) + pow(img,2));
        return out;
    }
    ComplexNum operator+(ComplexNum input){
        ComplexNum output;
        output.Set(real+input.real, img+input.img);
        return output;
    }
    ComplexNum operator-(ComplexNum input){
        ComplexNum output;
        output.Set(real-input.real, img-input.img);
        return output;
    }
    ComplexNum operator*(ComplexNum input){
        ComplexNum output;
        output.Set(real*input.real-img*input.img, (real*input.img)+(img*input.real));
        return output;
    }
    ComplexNum operator*(float num){
        ComplexNum output;
        output.Set(real*num, img*num);
        return output;
    }
    void operator=(ComplexNum input){
        real = input.real;
        img = input.img;
    }
}ComplexNumber;

void myDFT2(Mat& input, Mat& output){
    Mat input_tmp;
    Mat FT_col_real;
    Mat FT_col_img;
    Size inputSize;
    float* input_data;
    float* output_data;
    float* FT_col_real_data;
    float* FT_col_img_data;

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
    int height = inputSize.height;
    int width = inputSize.width;
    input_data = (float*)input_tmp.data;
    output.create(inputSize, CV_32FC(1));
    FT_col_real.create(inputSize, CV_32FC(1));
    FT_col_img.create(inputSize, CV_32FC(1));
    output_data = (float*)output.data;
    FT_col_real_data = (float*)FT_col_real.data;
    FT_col_img_data = (float*)FT_col_img.data;

    for(int col=0; col<width; col++){
        for(int row=0; row<height; row++){
            float real=0;
            float img=0;
            int position = row*width+col;
            for(int in_row=0; in_row<height; in_row++){
                float pixValue = input_data[in_row*width + col];
                float num = 2*M_PI*row*in_row/(float)height;
                real += pixValue * cos(num);
                img += pixValue * -1 *sin(num);
            }
            FT_col_real_data[position] = real;
            FT_col_img_data[position] = img;
            //cout<<row<<" "<<col<<endl;
        }
    }
    for(int col=0; col<width; col++){
        for(int row=0; row<height; row++){
            float real=0;
            float img=0;
            for(int in_col=0; in_col<width; in_col++){
                int position = row*width + in_col;
                float num = 2*M_PI*in_col*col/(float)width;
                float col_real = FT_col_real_data[position];
                float col_img = FT_col_img_data[position];
                real += cos(num)*col_real + sin(num)*col_img;
                img += cos(num)*col_img - sin(num)*col_real;
            }
            output_data[row*width+col] = sqrt(real*real + img*img);
            //cout<<row<<" "<<col<<endl;
        }
    }
    
    return;
}
void myIDFT2(Mat& input, Mat& output);
void myFFT2(Mat& input, Mat& output);
void myIFFT2(Mat& input, Mat& output);
