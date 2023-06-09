#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include<cstdlib>
#include <cmath>
#include<stack>

#include<windows.h>
#include <opencv2/opencv.hpp>
using namespace std;

using namespace cv;


int main()
{
   
cv::Mat img, cpy, ground;
img = cv::imread("C:\\Users\\fahad\\OneDrive\\Desktop\\t1.bmp", cv::IMREAD_GRAYSCALE);  //image that you want to compare with constructed image 
img.convertTo(cpy, CV_32S, 1, 0);                                                       // note if number of rows and cols is different from constructed img it will throw exception
int** arr = new int* [cpy.rows];
for (int i = 0; i < cpy.rows; ++i) {
    arr[i] = cpy.ptr<int>(i);
}
int rows1 = img.rows;
int cols1 = img.cols;
cv::Mat img1, cpy1, ground1;
img1 = cv::imread("E:\\test2\\test2\\reconstructed_image.jpg", cv::IMREAD_GRAYSCALE);
img1.convertTo(cpy1, CV_32S, 1, 0);
int** arr1 = new int* [cpy1.rows];
for (int i = 0; i < cpy1.rows; ++i) {
    arr1[i] = cpy1.ptr<int>(i);
}

   
    
    float sub=0;
    float mul = 0;
    for (int i = 0; i < img.rows ; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
          
            mul = arr[i][j] - arr1[i][j];
            mul = mul * mul;
            sub = sub+mul;
        }
    }
    //cout << sub;
    sub = sub / (img.rows * img.cols);

    float Y;
    Y = 100 * (1 - (sub / (255 * 255)));
    cout << Y;
    
}
