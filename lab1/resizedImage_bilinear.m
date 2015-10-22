function outputImage = resizedImage_bilinear( originalImage, scalingFactor )
   originalImage = double(originalImage)/256; % turn to double
   oriSize = size(originalImage); % get originalimage size
   outputSize = round(oriSize*scalingFactor); % get outputImage size
   outputImage = zeros(outputSize(1), outputSize(2)); 
   for row = 1:outputSize(1)
       for col=1:outputSize(2)
           map_row = (oriSize(1)-1)/(outputSize(1)-1)*(row-1) + 1; % the mapping row
           map_col = (oriSize(2)-1)/(outputSize(2)-1)*(col-1) + 1; % the mapping col
           start_row = double(int32(map_row)); % get the start row point
           start_col = double(int32(map_col)); % get the start col point
           dis_row = map_row - start_row; % get row distance
           dis_col = map_col - start_col; % get col distance
           if start_row<oriSize(1) && start_col<oriSize(2) % prevent index out error
            outputImage(row,col) = (1-dis_row)*((1-dis_col)*originalImage(start_row, start_col)+ dis_col*originalImage(start_row,start_col+1))+ dis_row*((1-dis_col)*originalImage(start_row+1, start_col) + dis_col*originalImage(start_row+1,start_col+1));
           % outputImage(row,col) = (1-dis_col)*((1-dis_row)*originalImage(start_row, start_col)+ dis_row*originalImage(start_row,start_col+1))+ dis_col*((1-dis_row)*originalImage(start_row+1, start_col) + dis_row*originalImage(start_row+1,start_col+1));
           elseif start_row<oriSize(1) && start_col>=oriSize(2) % prevent index out error
               outputImage(row,col) = (1-dis_row)*originalImage(start_row,start_col)+dis_row*originalImage(start_row+1,start_col);
           elseif start_row>=oriSize(1) && start_col<oriSize(2) % prevent index out error
               outputImage(row,col) = (1-dis_col)*originalImage(start_row,start_col)+dis_col*originalImage(start_row,start_col+1);
           end   
       end
   end
   outputImage = uint8(outputImage*256);
end

