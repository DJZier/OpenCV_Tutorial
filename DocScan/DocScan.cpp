#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream> 

cv::VideoCapture cap(2);
cv::Mat img, imgThre, imgGray, imgCanny, imgDil, imgErode, imgBlur;
std::vector<cv::Point> initialPoints;

cv::Mat preProcessing(cv::Mat image){
    ////////// Convert Color /////////////////
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    ////////// GaussianBlur(img,img) /////////
    cv::GaussianBlur(imgGray,imgBlur, cv::Size(3,3), 3, 0);

    ////////// Canny /////////////////////////
    cv::Canny(imgBlur, imgCanny,25, 75);

    ////////// Dilate ////////////////////////
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(3,3));
    cv::dilate(imgCanny, imgDil, kernel);

    ////////// Erode  ////////////////////////
    //cv::erode(imgDil, imgErode, kernel);

    return imgDil;
}

std::vector<cv::Point> getContours(cv::Mat image){
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(image, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    //cv::drawContours(img, contours, -1, cv::Scalar(255,0,255),2);
    std::vector<std::vector<cv::Point>> conPoly(contours.size());
    std::vector<cv::Rect> boundRect(contours.size());

    int maxArea=0;
    std::vector<cv::Point> biggest;
    for (int i = 0; i < contours.size(); i++){
        int area = cv::contourArea(contours[i]);
        std::cout << area << std::endl;

        std::string objectType;

        if (area > 1000){
            float peri = cv::arcLength(contours[i], true);
            cv::approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);

            if (area > maxArea && conPoly[i].size()==4){
                biggest = {conPoly[i][0],conPoly[i][1],conPoly[i][2],conPoly[i][3]};
                maxArea = area;
            }

            cv::drawContours(img, conPoly, i , cv::Scalar(255,0,255),2);
            //cv::rectangle(img, boundRect[i].tl(), boundRect[i].br(), cv::Scalar(0,255,0), 5);
        }
    }
    return biggest;
}

void drawPoints(std::vector<cv::Point> points, cv::Scalar color){
    for (int i = 0; i< points.size(); i++){
        cv::circle(img, points[i], 30, color, cv::FILLED);
        cv::putText(img, std::to_string(i), points[i], cv::FONT_HERSHEY_PLAIN, 5, color, 5);
    }
}



int main(){



    while (true)
    {
        cap.read(img);

        // Preprocessing
        imgThre = preProcessing(img);
        // Get contours- Biggest
        initialPoints = getContours(imgThre);
        drawPoints(initialPoints, cv::Scalar(0,0,255));
        // Warp the image


        cv::imshow("image",img);
        cv::imshow("Image Dilation", imgDil);
        cv::waitKey(1);
    }
    return 0;
}