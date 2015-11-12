#ifndef lab3
#define lab3
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
using namespace std;
using namespace cv;

//4-1
void myDFT2(Mat& input, Mat& output);
void myIDFT2(Mat& input, Mat& output);
void myFFT2(Mat& input, Mat& output);
void myIFFT2(Mat& input, Mat& output);
//4-3
void myGLPF(float D0, int M, int N, Mat& output);
//4-4
void myGHPF(float D0, int M, int N, Mat& output);
#endif
