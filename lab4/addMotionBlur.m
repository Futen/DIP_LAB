function[output_f, H] = addMotionBlur(input_f, T, a, b)
    inputSize = size(input_f);
    height = inputSize(1);
    width = inputSize(2);
    row_line = (1:height)*b;
    col_line = (1:width)*a;
    two_add_space = zeros(inputSize);
    for row = 1:height
        two_add_space(row,:) = row_line(row) + col_line;
    end
    two_add_space;
    exp_space = exp(complex(0,-1)*pi*two_add_space);
    sin_space = sin(pi * two_add_space);
    mul_space = (T/pi) * (two_add_space).^-1;
    H = mul_space .* sin_space .* exp_space;
    %imshow(abs(H));
    output_f = input_f .* abs(H);
end
