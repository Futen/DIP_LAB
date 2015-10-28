#include "lab2.h"

int main(){
    Mat input = imread("Fig0308(a)(fractured_spine).tif",CV_LOAD_IMAGE_UNCHANGED);
    float a[5][5] = {{1,4,7,4,1},{4,16,26,16,4},{7,26,41,26,7},{4,16,26,16,4},{1,4,7,4,1}};
    float b[3][3] = {{0.11, 0.11, 0.11}, {0.11, 0.11, 0.11}, {0.11, 0.11, 0.11}};
    Mat output,v,mask,tmp;
    float *data,*data2;
//    imageHist(input, v);
//    RecordHist("hist.txt", v);
    mask = Mat(3,3,CV_32FC(1),b);
//    mask.convertTo(mask, CV_32FC(1), 1/273.0);
//    spatialFiltering(input, mask, output);
//    laplacianFiltering(input, mask, 7, output, v);
//    logTransform(input, output);
    powerlawTransform(input, 0.4, output);
    //unsharpFiltering(input, mask, 4.5, output, v, tmp);
    output.convertTo(output, CV_8UC(1), 255.0);
    namedWindow("TEST");
    imshow("TEST", output);
    waitKey(0);
    imwrite("out.tif",output);

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
