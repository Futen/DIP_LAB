
image_ori = imread('Fig0457(a)(thumb_print).tif');
image_ori = single(image_ori)/255;
imageSize = size(image_ori);
width = imageSize(2); % get image size
height = imageSize(1);
tic;

image = image_ori;
%image = zeros([height*2, width*2]);
for row = 1:height  % move center point
    for col = 1:width
        image(row,col) = image_ori(row,col)*(-1)^(row+col);
    end
end
toc;
a = myDFT2(image);
a = abs(a);
%{
f = myGHPF(160,imageSize(1),imageSize(2));
a = a.*f;
g = abs(a);
a = myIDFT2(a);
a = abs(a);
a = log(1+a);
%}
%{
for row = 1:height
    for col = 1:width
        if a(row,col) < 0.03
            a(row,col) = 1;
        else
            a(row,col) = 0;
        end
    end
end
%}
%a = myIDFT2(a);
%a = im2uint8(a);
imwrite(a,'tt.png');
