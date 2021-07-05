#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream> 
//#include <vector>


cv::Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

void getContours(cv::Mat imgDil, cv::Mat img){


    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
   
    for (int i = 0; i< contours.size(); i++){
        int area = cv::contourArea(contours[i]);
        std::cout << area << std::endl;

        std::vector<std::vector<cv::Point>> conPoly(contours.size());
        std::vector<cv::Rect> boundRect(contours.size());
        std::string objectType;

        if (area>1000){
            float peri = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);
            
            std::cout << conPoly[i].size() << std::endl;
            boundRect[i] = cv::boundingRect(conPoly[i]);

            int objCor = (int)conPoly[i].size();

            if (objCor==3){objectType = "Tri";}
            if (objCor==4){

                float aspRatio= (float)boundRect[i].width/(float)boundRect[i].height;
                std::cout << aspRatio << std::endl;
                if (aspRatio> 0.95 && aspRatio<1.05){
                    objectType = "Square";
                }else {objectType = "Rect";}

                
            }
            if (objCor>4){objectType = "Circle";}

            cv::drawContours(img, conPoly, i, cv::Scalar(255,0,255), 2);
            cv::rectangle(img,boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0,255,0), 5);
            cv::putText(img, objectType, {boundRect[i].x, boundRect[i].y-5}, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0,69,255), 1);

        }
    }
}



int main(){

    std::string path = "../Resources/shapes.png";
    cv::Mat img = cv::imread(path);

    ////////// Preprocessing /////////////////
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(imgGray,imgBlur, cv::Size(3,3), 3, 0);
    cv::Canny(imgBlur, imgCanny,25, 75);
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3));
    cv::dilate(imgCanny, imgDil, kernel);

    getContours(imgDil, img);

    cv::imshow("Image", img);  
    cv::waitKey(0);
  
    return 0;
}