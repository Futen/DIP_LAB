#include "myHeader.h"

int ImageProcessing::LoadImage(const char* file_name){
    originalImage = imread(file_name,CV_LOAD_IMAGE_UNCHANGED);
    if(originalImage.data){
        channel_count = originalImage.channels();
        imageSize = originalImage.size();
        printf("Load %s succeed!!!\n",file_name);
        printf("Channel %d\n", channel_count);
        return 1;
    }
    else{
        printf("Load %s fail!!\n",file_name);
        return 0;
    }
}
void ImageProcessing::ShowImage(){
    printf("%d x %d\n", imageSize.height, imageSize.width);
    namedWindow("TEST");
    imshow("TEST", originalImage);
    waitKey(0);
    //cout<<(int)GetPix(originalImage.data, 200, 200)[0]<<endl;
    return;
}
void ImageProcessing::ResizeImage(float scalingFactor){
    int resize_row = (int)imageSize.height * scalingFactor;
    int resize_col = (int)imageSize.width * scalingFactor;
    resizedImage.create(resize_row, resize_col, CV_8U);
    
    cout<<resizedImage.size()<<endl;
    cout<<imageSize<<endl;
    
    unsigned char* ori_data = originalImage.data;
    unsigned char* resized_data = resizedImage.data;
    double t = (double)getTickCount();
    for(int row=0; row<resize_row; row++){
        for(int col=0; col<resize_col; col++){
            float map_row = (float)(imageSize.height-1)/(float)(resize_row-1) * row;
            float map_col = (float)(imageSize.width-1)/(float)(resize_col-1) * col;
            int start_row = (int)map_row;
            int start_col = (int)map_col;
            float dis_row = fabs(map_row-start_row);
            float dis_col = fabs(map_col-start_col);
            if(start_row+1 < imageSize.height && start_col+1 < imageSize.width){
                unsigned int p_x_y = (unsigned int)GetPix(ori_data, start_row, start_col)[0];
                unsigned int p_x1_y = (unsigned int)GetPix(ori_data, start_row+1, start_col)[0];
                unsigned int p_x_y1 = (unsigned int)GetPix(ori_data, start_row, start_col+1)[0];
                unsigned int p_x1_y1 = (unsigned int)GetPix(ori_data, start_row+1, start_col+1)[0];
                resized_data[row*resize_col + col] = (1-dis_row)*((1-dis_col)*p_x_y+ dis_col*p_x_y1)+ 
                                                    dis_row*((1-dis_col)*p_x1_y + dis_col*p_x1_y1);
            }
        }
    }
    t = (double)getTickCount() - t;
    printf("Total consume %gms\n", t*1000/getTickFrequency());
    namedWindow("TEST");
    imshow("TEST", resizedImage);
    waitKey(0);

    return;
}
unsigned char *ImageProcessing::GetPix(unsigned char* data, int row, int col){
    return &data[row*imageSize.width*channel_count + col*channel_count];
}
void ImageProcessing::PrintData(){
    unsigned char *value = (unsigned char*)originalImage.data;
    for(int row=0; row<imageSize.height; row++){
        for(int col=0; col<imageSize.width; col++){
            printf("%d ", (unsigned int)value[row*imageSize.width*channel_count + col*channel_count]);
        }
        cout<<endl;
    }
}
