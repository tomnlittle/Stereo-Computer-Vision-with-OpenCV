
#include "camera.h"

Camera::Camera(int num, int noise){
    cameraNumber = num;
    camera = cv::VideoCapture(cameraNumber);
    camera >> frame;
    threadActive = true;
    updateCount = 0;
    noise_reduction_level = noise;
   // if(!camera.isOpened()) return 1;
   updateThread = std::thread(&Camera::update, this);
}

Camera::~Camera(){
    stop();
}

void Camera::update(){
    cv::Mat3b temp_frame;
    while(threadActive){
        camera >> temp_frame;
        //fastNlMeansDenoising(temp_frame, temp_frame, noise_reduction_level, 11, 5);
        //usleep(UPDATE_FREQUENCY/1000.00);
        frame = temp_frame;
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