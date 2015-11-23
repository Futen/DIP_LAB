function[output] = myGLPF(D0, M, N)
    tic;
    center = zeros([1,2]);
    center(1) = round((1+M)/2);
    center(2) = round((1+N)/2);
    output = zeros([M,N]);
    for row = 1:M
        for col = 1:N
            distance = sqrt(sum(([row,col]-center).^2));
            output(row,col) = exp(-0.5*(distance/D0)^2);
        end
    end
    toc;
end
