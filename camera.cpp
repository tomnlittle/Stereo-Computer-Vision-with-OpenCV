
#include "camera.h"

Camera::Camera(int num){
    cameraNumber = num;
    camera = cv::VideoCapture(cameraNumber);
    camera >> frame;
    threadActive = true;
    updateCount = 0;
   // if(!camera.isOpened()) return 1;
   updateThread = std::thread(&Camera::update, this);
}

Camera::~Camera(){
    stop();
}

void Camera::update(){
    while(threadActive){
        camera >> frame;
        usleep(UPDATE_FREQUENCY/100.00);
        updateCount++;
    }
}

void Camera::stop(){
    threadActive = false;
    updateThread.join();
    cout << "Camera " << cameraNumber << ": Number of Updates " << updateCount << "\n";
    cout << "Destructor Called \n";
}

cv::Mat3b Camera::getFrame(){
    return frame;
}