#include "lab3.h"

int main(){
    Mat input = imread("FromDFT2.fig",CV_LOAD_IMAGE_UNCHANGED);
    namedWindow("TEST");
    imshow("TEST",input);
    waitKey(0);
    Mat tmp;
    float* tmp_data;
    float* input_data;
    input.convertTo(input,CV_32FC(1),1/255.0);
    tmp.create(input.size()*2, CV_32FC(1));
    Mat output;
    Size inputSize;
    Size outputSize;
    inputSize = input.size();
    outputSize = tmp.size();
    tmp_data = (float*)tmp.data;
    input_data = (float*)input.data;
    for(int row=0; row<inputSize.height; row++){
        for(int col=0; col<inputSize.width; col++){
            if(row<inputSize.height && col<inputSize.width){
                tmp_data[row*outputSize.width+col] = pow(-1,row+col)*input_data[row*inputSize.width+col];
            }
            else
                tmp_data[row*outputSize.width+col] = 0;
        }
    }
    myDFT2(tmp, output);

    //cout<<output<<endl;
    //tmp.convertTo(tmp, CV_8UC(1), 255.0);
    imwrite("tt.tif", output);
    return 0;
}
