#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>



int main(){
    std::string path = "/home/florian/Pictures/marker64.jpg";
    cv::Mat img = cv::imread(path);
    cv::Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

    ////////// Convert Color /////////////////
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    ////////// GaussianBlur(img,img) /////////
    cv::GaussianBlur(imgGray,imgBlur, cv::Size(3,3), 3, 0);

    ////////// Canny /////////////////////////
    cv::Canny(imgBlur, imgCanny,50, 150);

    ////////// Dilate ////////////////////////
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3));
    cv::dilate(imgCanny, imgDil, kernel);

    ////////// Erode  ////////////////////////
    cv::erode(imgDil, imgErode, kernel);

    //cv::imshow("Image", img);
    //cv::imshow("Image Gray", imgGray);
    //cv::imshow("Image Blur", imgBlur);
    //cv::imshow("Image Canny", imgCanny);
    //cv::imshow("Image Dilation", imgDil);
    cv::imshow("Image Erode", imgErode);

    cv::waitKey(0);
    return 0;
}