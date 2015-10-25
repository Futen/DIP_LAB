#include "lab2.h"

int main(){
    Mat input = imread("Fig0338(a)(blurry_moon).tif",CV_LOAD_IMAGE_UNCHANGED);
//    float a[3][3] = {{0.0625, 0.125, 0.0625}, {0.125, 0.25, 0.125}, {0.0625, 0.125, 0.0625}};
    //float b[3][3] = {{-1, -1, -1}, {-1, 8, -1}, {-1, -1, -1}}; 
    float b[3][3] = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    Mat output,v,mask,tmp;
    float* data;
//    mask = Mat(3,3,CV_32FC(1),a);
//   spatialFiltering(input, mask, tmp);
    mask = Mat(3,3,CV_32FC(1),b);
    /*
    mask.create(3,3,CV_32FC(1));
    data = (float*)mask.data;
    data[0]=0;
    data[1]=1;
    data[2]=0;
    data[3]=1;
    data[4]=-4;
    data[5]=1;
    data[6]=0;
    data[7]=1;
    data[8]=0;
    */
//    cout<<(float)mask.data[0]<<endl;
    //cout<<mask.size()<<endl;
//    spatialFiltering(input, mask, output);
    laplacianFiltering(input, mask, 10, output, v);
//    cout<<output<<endl;
//    logTransform(input,output);
    output.convertTo(output, CV_8UC(1), 255.0);
    namedWindow("TEST");
    imshow("TEST", output);
    waitKey(0);
//    imwrite("out.tif",output);
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
/*
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
///
*/
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
