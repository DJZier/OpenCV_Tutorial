#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream> 

/// for image

/*int main(){
    std::string path = "../Resources/test.png";
    cv::Mat img = cv::imread(path);

    cv::CascadeClassifier faceCascade;
    faceCascade.load("../Resources/haarcascade_frontalface_default.xml");

    if (faceCascade.empty()){std::cout << "XML File not loaded" << std::endl;}

    std::vector<cv::Rect> faces;
    faceCascade.detectMultiScale(img,faces,1.1,10);

    for (int i = 0; i<faces.size(); i++){
        cv::rectangle(img,faces[i].tl(), faces[i].br(), cv::Scalar(255,0,255), 3);
    }

    cv::imshow("Image Mask", img);        
    cv::waitKey(0);
    return 0;
}*/

/// for live camera

int main(){

    cv::VideoCapture cap(2);
    cv::Mat img;
    cv::CascadeClassifier faceCascade;
    faceCascade.load("../Resources/haarcascade_frontalface_default.xml");
    if (faceCascade.empty()){std::cout << "XML File not loaded" << std::endl;}
    std::vector<cv::Rect> faces;

    while (true)
    {

        cap.read(img);
        faceCascade.detectMultiScale(img,faces,1.1,10);

        for (int i = 0; i<faces.size(); i++){
            cv::rectangle(img,faces[i].tl(), faces[i].br(), cv::Scalar(255,0,255), 3);
            cv::putText(img, "Gros beau gosse", faces[i].tl(), cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar(255,0,255), 2);
        }
        cv::imshow("image",img);
        cv::waitKey(1);
    } 
    return 0;
}