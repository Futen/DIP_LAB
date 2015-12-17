function[output] = addSinNoise(input_s, A, u0, v0)
    tic;
    inputSize = size(input_s); % get image size
    mask = zeros(inputSize);
    height = inputSize(1);
    width = inputSize(2);
    center_row = (1+height)/2; % get center of image
    center_col = (1+width)/2;  % get center of image
    for row = 1:height
        for col = 1:width
           mask(row,col) = A * sin((u0*col + v0*row)*2*pi); % calculate sin noise to mask
        end
    end
    %tmp = (fft2(mask));
    %imshow(log10(abs(tmp)));

    output = input_s + mask; % add noise to origin image
    toc;
end

