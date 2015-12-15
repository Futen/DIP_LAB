function [output_f] = wienerFiltering(input_f, H, K)
    absl = (abs(H)).^2;
    tmp = (H.^(-1)) .* absl./(absl+K);
    output_f = input_f .* tmp;
end
