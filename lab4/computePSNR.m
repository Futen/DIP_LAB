function[psnr] = computePSNR(input1_s, input2_s)
    inputSize = size(input1_s);
    height = inputSize(1);
    width = inputSize(2);
    Sum = (input1_s - input2_s).^2; % get all point difference of two image
    psnr = 10 * log10(height*width/sum(sum(Sum))); % get db value
end
