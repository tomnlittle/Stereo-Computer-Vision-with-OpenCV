#include <stdio.h>
#include <opencv2/opencv.hpp>
//#include "opencv2/gpu/gpu.hpp"
#include <thread>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

using namespace cv;
using namespace std;

#define UPDATE_FREQUENCY                                        30.00 //update 30 times a second

class Camera {
    public:
        Camera(int cameraNumber, int noise);
        ~Camera();
        void update();
        void stop();
        cv::Mat3b getFrame();
    private:
        cv::Mat3b frame;
        int cameraNumber;
        bool threadActive;
        std::thread updateThread;  
        cv::VideoCapture camera;  
        int updateCount;
        int noise_reduction_level;
};