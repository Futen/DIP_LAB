
input = imread('Fig0431(d)(blown_ic_crop).tif');
input = im2single(input);

a = myDFT2(input);
%a = abs(a);
a = myIDFT2(a);

a = im2uint8(a);
imshow(a);
