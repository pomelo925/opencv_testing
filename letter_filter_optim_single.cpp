#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void letter_filter_track(Mat img);

//// 對單一圖片過濾 ////
int main(){
    
/// 需要調整的變數 ///
    string path = "TEL/00_Problem/2.jpg";
///               ///

    Mat src = imread(path);
    letter_filter_track(src);
    return 0;
}

void letter_filter_track(Mat img){
    Mat img_hsv, mask, mask1, mask2, result; 
    cvtColor(img, img_hsv, COLOR_BGR2HSV);

// "track_bar (dark)"
    namedWindow("track_bar (dark)");
    resizeWindow("track_bar (dark)", 500, 500);

    createTrackbar("Hue Min", "track_bar (dark)", 0, 179);
    createTrackbar("Hue Max", "track_bar (dark)", 0, 179);
    createTrackbar("Sat Min", "track_bar (dark)", 0, 255);
    createTrackbar("Sat Max", "track_bar (dark)", 0, 255);
    createTrackbar("Val Min", "track_bar (dark)", 0, 255);
    createTrackbar("Val Max", "track_bar (dark)", 0, 255);

    setTrackbarPos("Hue Min", "track_bar (dark)", 90);
    setTrackbarPos("Hue Max", "track_bar (dark)", 110);
    setTrackbarPos("Sat Min", "track_bar (dark)", 143);
    setTrackbarPos("Sat Max", "track_bar (dark)", 255);
    setTrackbarPos("Val Min", "track_bar (dark)", 140);
    setTrackbarPos("Val Max", "track_bar (dark)", 255);

// "track_bar (light)"
    namedWindow("track_bar (light)");
    resizeWindow("track_bar (light)", 500, 500);

    createTrackbar("Hue Min", "track_bar (light)", 0, 179);
    createTrackbar("Hue Max", "track_bar (light)", 0, 179);
    createTrackbar("Sat Min", "track_bar (light)", 0, 255);
    createTrackbar("Sat Max", "track_bar (light)", 0, 255);
    createTrackbar("Val Min", "track_bar (light)", 0, 255);
    createTrackbar("Val Max", "track_bar (light)", 0, 255);

    setTrackbarPos("Hue Min", "track_bar (light)", 87);
    setTrackbarPos("Hue Max", "track_bar (light)", 102);
    setTrackbarPos("Sat Min", "track_bar (light)", 75);
    setTrackbarPos("Sat Max", "track_bar (light)", 160);
    setTrackbarPos("Val Min", "track_bar (light)", 227);
    setTrackbarPos("Val Max", "track_bar (light)", 255);

    while(waitKey(1) != 'q'){
    // track_bar (dark)
        int hue_m1 = getTrackbarPos("Hue Min", "track_bar (dark)");
        int hue_M1 = getTrackbarPos("Hue Max", "track_bar (dark)");
        int sat_m1 = getTrackbarPos("Sat Min", "track_bar (dark)");
        int sat_M1 = getTrackbarPos("Sat Max", "track_bar (dark)");
        int val_m1 = getTrackbarPos("Val Min", "track_bar (dark)");
        int val_M1 = getTrackbarPos("Val Max", "track_bar (dark)");

        Scalar lower1(hue_m1, sat_m1, val_m1);
        Scalar upper1(hue_M1, sat_M1, val_M1);
        inRange(img_hsv, lower1, upper1, mask1);
        // imshow("mask1 (dark)", mask1);

    // track_bar (light)
        int hue_m2 = getTrackbarPos("Hue Min", "track_bar (light)");
        int hue_M2 = getTrackbarPos("Hue Max", "track_bar (light)");
        int sat_m2 = getTrackbarPos("Sat Min", "track_bar (light)");
        int sat_M2 = getTrackbarPos("Sat Max", "track_bar (light)");
        int val_m2 = getTrackbarPos("Val Min", "track_bar (light)");
        int val_M2 = getTrackbarPos("Val Max", "track_bar (light)");
        
        Scalar lower2(hue_m2, sat_m2, val_m2);
        Scalar upper2(hue_M2, sat_M2, val_M2);
        inRange(img_hsv, lower2, upper2, mask2);
        imshow("mask2 (light)", mask2);


    // bitwise
        imshow("Img", img);

        result = Mat::zeros(img.size(), CV_8UC3);
        bitwise_or(mask1, mask2, mask);
        bitwise_and(img, img, result, mask);
        imshow("Result", result);
    }
}
