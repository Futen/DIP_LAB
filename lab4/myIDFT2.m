function[output] = myIDFT2(input)
    tic;
    image = conj(input);
    imageSize = size(input); % get input image size
    width = imageSize(2); % get image size
    height = imageSize(1);
    % create some matrix to do operation
    row_linspace = (1:height);
    col_linspace = (1:width);
    row_exp_vector = (1:height)/height*2*pi;
    col_exp_vector = (1:width)/width*2*pi;
    % init vector
    row_exp_space = zeros([height, height]);
    col_exp_space = zeros([width, width]);
    output = zeros([height, width]);
    % make some matrix to speed up program
    for row = 1:height
        row_exp_space(row,:) = exp(complex(0,-1)*(row_exp_vector*(row-1)));
    end
    for col = 1:width
        col_exp_space(col,:) = exp(complex(0,-1)*(col_exp_vector*(col-1)));
    end
    output = row_exp_space * image * col_exp_space'; % the produt of matrix will be output
    output = abs(output)/(width*height);
    toc;
end
