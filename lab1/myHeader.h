#ifndef DEFINE
#define DEFINE
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
/*
struct PIX{
    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int grey;
}pix;
*/
class ImageProcessing{
private:
    int channel_count;
    Size imageSize; // store img size
    Mat originalImage;
    Mat resizedImage;
protected:
    //unsigned char *GetPix(unsigned char* data, int row, int col) ;
public:
    int LoadImage(const char* file_name);
    unsigned char *GetPix(unsigned char* data, int row, int col) ;
    void ShowImage();
    void PrintData(); //for debug
    void ResizeImage(float scalingFactor);
};

#endif
