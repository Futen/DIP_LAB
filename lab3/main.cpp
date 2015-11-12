#include "lab3.h"

int main(){
    Mat a;
    a = Mat::zeros(20,20,CV_32FC(1));
    cout<<a.size()<<endl;
    cout<<a.size()*2<<endl;
    cout<<a<<endl;
    return 0;
}
