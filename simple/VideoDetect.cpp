#include "stdafx.h"
#include "MOG2Detector.h"


MOG2Detector::MOG2Detector()
{
}
MOG2Detector::~MOG2Detector()
{

}

MOG2Detector::MOG2Detector(VIDEOTYPE type, char * path, char * WindowName)
{
    if (type == CAMERAVIDEO) 
    {
        capture.open(0);
    }
    else if (type == FILEVIDEO)
    {
        capture.open("E:/image/s.avi");
    }
    else 
    {
        cout << "Type is error, you can input CAMERAVIDEO or FILEVIDEO" << endl;
        return;
    }

    if (!capture.isOpened())
    {
        std::cout << "video camera capture open fail! \n" << std::endl;
        exit(1);
    }

    fgbg = cv::createBackgroundSubtractorMOG2();
    WinName = WindowName;
}

void MOG2Detector::startDecect()
{
    cv::Mat frame, fgmask;
    //cnts存储边缘信息
    std::vector<std::vector<cv::Point> > cnts;
    cv::namedWindow("video", 1);

    while (1)
    {
        capture.read(frame);
        fgbg->apply(frame, fgmask);
        //检测每一帧边缘
        findContours(fgmask, cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        float Area;
        Rect rect;
        vector<Point> m;
        for (int i = cnts.size() - 1; i >= 0; i--)
        {
            vector<Point> c = cnts[i];
            //获取面积
            Area = contourArea(c);
            if (Area < 50)//50这个值根据需求设定，这里指的是目标的大小
            {
                continue;
            }
            else
            {
                m = c;
            }
            rect = boundingRect(m);
            rectangle(frame, rect, Scalar(0, 255, 0), 2);
        }
        resize(frame, frame, Size(480, 320));
        imshow("video", frame);
        char c = waitKey(33);
        if (c == 27)
            break;
    }
    //释放资源
    capture.release();
    cv::destroyWindow("video");
}
