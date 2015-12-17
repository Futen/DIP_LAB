function[output_f, H] = addMotionBlur(input_f, T, a, b)
    inputSize = size(input_f);  % get input size
    height = inputSize(1);
    width = inputSize(2);
    H = zeros(inputSize);
    center_row = (1+height)/2;  % get center point
    center_col = (1+width)/2;
    for row = 1:height
        for col = 1:width
            tmp = (b*(row-center_row) + a*(col-center_col))*pi;
            tmp = (T/tmp)*sin(tmp)*exp(-1j*tmp);
            if isnan(tmp)   % if tmp is zero , it will be infinite
                H(row,col) = 1; % set it to one
            else
                H(row,col) = tmp;   % set it to tmp
            end
        end
    end
    output_f = input_f .* H;    % process the input
end
