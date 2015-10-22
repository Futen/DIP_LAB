#include "header.h"
void ResizedImage(const Mat& input, Mat& output, const double scalingFactor);
unsigned char *GetPix(unsigned char* data, int width,int row, int col);

void ResizedImage(const Mat& input, Mat& output, const double scalingFactor){
	Size size_of_input = input.size();
	int resize_row = (int)size_of_input.height * scalingFactor;
	int resize_col = (int)size_of_input.width * scalingFactor;
	output.create(resize_row, resize_col, CV_8U);

	cout<<output.size()<<endl;
	cout<<size_of_input<<endl;

	unsigned char* ori_data = input.data;
	unsigned char* resized_data = output.data;
	double t = (double)getTickCount();
	for(int row=0; row<resize_row; row++){
		for(int col=0; col<resize_col; col++){
			float map_row = (float)(size_of_input.height-1)/(float)(resize_row-1) * row;
			float map_col = (float)(size_of_input.width-1)/(float)(resize_col-1) * col;
			int start_row = (int)map_row;
			int start_col = (int)map_col;
			float dis_row = fabs(map_row-start_row);
			float dis_col = fabs(map_col-start_col);
			if(start_row+1 < size_of_input.height && start_col+1 < size_of_input.width){
				unsigned int p_x_y = (unsigned int)GetPix(ori_data, size_of_input.width,start_row, start_col)[0];
				unsigned int p_x1_y = (unsigned int)GetPix(ori_data, size_of_input.width,start_row+1, start_col)[0];
				unsigned int p_x_y1 = (unsigned int)GetPix(ori_data, size_of_input.width,start_row, start_col+1)[0];
				unsigned int p_x1_y1 = (unsigned int)GetPix(ori_data, size_of_input.width,start_row+1, start_col+1)[0];
				resized_data[row*resize_col + col] = (1-dis_row)*((1-dis_col)*p_x_y+ dis_col*p_x_y1)+ 
					dis_row*((1-dis_col)*p_x1_y + dis_col*p_x1_y1);
			}
		}
	}
	t = (double)getTickCount() - t;
	printf("Total consume %gms\n", t*1000/getTickFrequency());
	/*
	namedWindow("TEST");
	imshow("TEST", output);
	waitKey(0);
	*/
	return;

}
unsigned char *GetPix(unsigned char* data, int width,int row, int col){
	return &data[row*width + col];
}
