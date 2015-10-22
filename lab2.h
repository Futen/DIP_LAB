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

void logTransform(const Mat& input, Mat &output);
void powerlawTransform(const Mat& input, float r, Mat& output);
void imageHist(const Mat& input, Mat& histVector);
void histEqualization(const Mat& input, Mat& output, Mat& T);
#endif
