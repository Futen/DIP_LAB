function[output_f, Notch] = notchFiltering(input_f, D0, u0, v0)
    tic;
    inputSize = size(input_f);
    height = inputSize(1);
    width = inputSize(2);
    Notch = ones(inputSize);
    center_row = (1+height)/2;
    center_col = (1+width)/2;

    for row = 1:height
        for col = 1:width
            dis_pos = sqrt((row-center_row-v0)^2 + (col-center_col-u0)^2);
            dis_neg = sqrt((row-center_row+v0)^2 + (col-center_col+u0)^2);
            if dis_pos <= D0 || dis_neg <= D0
                Notch(row, col) = 0;
            end
        end
    end
    %Notch
    output_f = input_f .* Notch;
    toc;
end
