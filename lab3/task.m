
input = imread('Fig0431(d)(blown_ic_crop).tif');
input = im2single(input);
inputSize = size(input);
a = myDFT2(input);
%f = myGLPF(5,inputSize(1),inputSize(2));
%a = a.*f;
%a = abs(a);
a = myIDFT2(a);
a = im2uint8(a);
imshow(a);
