function[psnr] = computePSNR(input1_s, input2_s)
    inputSize = size(input1_s);
    height = inputSize(1);
    width = inputSize(2);
    Sum = (input1_s - input2_s).^2;
    psnr = 10 * log10(height*width/sum(sum(Sum)));
end
