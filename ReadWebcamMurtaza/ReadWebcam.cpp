#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


int main(){
    cv::VideoCapture cap(2);
    cv::Mat img;

    while (1)
    {
        cap.read(img);
        imshow("Image", img);
        cv::waitKey(1);
    }
    return 0;
}