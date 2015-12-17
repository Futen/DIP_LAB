function[output_f, Notch] = notchFiltering(input_f, D0, u0, v0)
    tic;
    inputSize = size(input_f);  % get image size
    height = inputSize(1);
    width = inputSize(2);
    Notch = ones(inputSize);
    center_row = (1+height)/2;  % get center
    center_col = (1+width)/2;   % get center

    for row = 1:height
        for col = 1:width
            dis_pos = sqrt((row-center_row-v0)^2 + (col-center_col-u0)^2); % calculate the radius of pos
            dis_neg = sqrt((row-center_row+v0)^2 + (col-center_col+u0)^2); % calculate the radius of neg
            if dis_pos <= D0 || dis_neg <= D0   % check if point is in the radius
                Notch(row, col) = 0;
            end
        end
    end
    %Notch
    output_f = input_f .* Notch; % add Notch to image
    toc;
end
