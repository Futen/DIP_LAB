function [output] = spatialFiltering(input_s, mask)
    inputSize = size(input_s);
    tmp = zeros([inputSize(1)+2, inputSize(2)+2]);
    %size(tmp(2:(inputSize(1)+1), 2:(inputSize(2)+1)))
    %size(input_s)
    tmp(2:(inputSize(1)+1), 2:(inputSize(2)+1)) = input_s;
    output = zeros(inputSize);
    for row = 2:inputSize(1)+1
        for col = 2:inputSize(2)+1
            %size(mask)
            %size(tmp(row-1:row+1,col-1:col+1))
            output(row-1, col-1) = sum(sum(tmp(row-1:row+1,col-1:col+1) .* mask));
        end
    end
end
