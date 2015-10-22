#include "myHeader.h"

int main(){
    ImageProcessing test;
    test.LoadImage("Fig0220(a)(chronometer 3692x2812  2pt25 inch 1250 dpi).tif");
//    test.ShowImage();
    test.ResizeImage(2);
//    test.PrintData();
    return 0;
}
