function[output_binary, optimumT] = basicThresholding(input_uint8, delta_T)
    inputSize = size(input_uint8);
    height = inputSize(1);
    width = inputSize(2);
    histo = zeros([1,256]);
    % the following is to get histogram
    for row = 1:height
        for col = 1:width
            tmp = single(input_uint8(row,col));
            histo(tmp+1) = histo(tmp+1) + 1;
        end
    end
    histo_prob = histo/(height*width); % get histogram probility
    start_T = sum((0:255).*histo)/(height*width);
    diff = delta_T + 1;
    while diff >= delta_T
        %start_T
        c1 = histo(1:start_T+1);
        c2 = histo(start_T+2: 256);
        num_c1 = sum(c1);
        num_c2 = sum(c2);
        m1 = sum((0:start_T).*c1)/num_c1;
        m2 = sum((start_T+1:255).*c2)/num_c2;
        new_T = (m1+m2)/2;
        diff = abs(new_T - start_T);
        start_T = new_T;
    end
    optimumT = start_T;
    output_binary = input_uint8 > optimumT;
