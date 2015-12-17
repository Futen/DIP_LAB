function[output_binary, optimumT] = OtsuThresholding(input_uint8)
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
    P1 = zeros([1,256]);
    P1(1) = histo_prob(1);
    for i = 2:256
        P1(i) = P1(i-1) + histo_prob(i);
    end
    P2 = 1-P1;
    m1 = zeros([1,256]);
    m2 = zeros([1,256]);
    for i = 1:256
        if(P1(i)==0)    % if p1==0 set m1 to zero
            m1(i) = 0;
        else
            num = sum((0:i-1).*histo_prob(1:i));
            m1(i) = (P1(i)^-1) * num;
        if(P2(i)==0)    % if p2==0 set m2 to zero
            m2(i) = 0;
        else
            num = sum((i:255).*histo_prob(i+1:256));
            m2(i) = (P2(i)^-1) * num;
        end
        end
    end
    delta_b = P1.*P2.*(m1-m2).^2;      % calculate all covariance
    mean_g = sum((0:255).*histo_prob); % get the global mean
    sep = (delta_b.^2)/(mean_g)^2;     % get seqerability
    max_val = max(delta_b);            % get max covariance
    tmp = find(delta_b==max_val);
    optimumT = round(mean(tmp) - 1);   % get best threshold
    output_binary = input_uint8 > uint8(optimumT);% get binary image
end
