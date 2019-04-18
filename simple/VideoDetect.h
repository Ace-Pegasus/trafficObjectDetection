#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;
enum VIDEOTYPE
{
    CAMERAVIDEO/*摄像头*/,FILEVIDEO/*视频*/
};

class MOG2Detector
{
public:
    MOG2Detector();
    ~MOG2Detector();
    /*
    VIDEOTYPE 指定摄像头或者文件
    path 文件路径
    WindowName opencv可视化窗口名称
    */
    MOG2Detector(VIDEOTYPE type,char * path = "E:/image/s.avi",char * WindowName = "Video");
    //开始
    void startDecect();

private:
    char * WinName;
    VIDEOTYPE VideoType;
    cv::VideoCapture capture;
    cv::Ptr<cv::BackgroundSubtractorMOG2> fgbg;
};
