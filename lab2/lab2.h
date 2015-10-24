#ifndef DEFINE
#define DEFINE
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
using namespace std;
using namespace cv;

//2-1
void RecordHist(const char* file_name, const Mat& histVector);
void logTransform(const Mat& input, Mat &output);
void powerlawTransform(const Mat& input, float r, Mat& output);
//2-2
void imageHist(const Mat& input, Mat& histVector);
void histEqualization(const Mat& input, Mat& output, Mat& T);
//2-3
void spatialFiltering(const Mat& input, const Mat& mask, Mat& output);
void laplacianFiltering(const Mat& input, const Mat& laplacianMask, float scale, Mat& output, Mat& scaledLaplacian);
void unsharpFiltering(const Mat& input, const Mat& boxMask, float scale, Mat& output, Mat& scaledUnsharp, Mat& blurredInput);
#endif
