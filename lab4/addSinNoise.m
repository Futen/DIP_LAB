function[output] = addSinNoise(input_s, A, u0, v0)
    tic;
    inputSize = size(input_s);
    mask = zeros(inputSize);
    height = inputSize(1);
    width = inputSize(2);
    for row = 1:height
        for col = 1:width
           mask(row,col) = A * sin((u0*col + v0*row));
        end
    end
    output = input_s + mask;
    toc;
end

