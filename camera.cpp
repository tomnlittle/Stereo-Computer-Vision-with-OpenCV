/*
 * Created on Thu Jan 26 2017 
 *
 * Copyright (c) 2017 Thomas Northall-Little
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
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

int Camera::getCount(){
    return updateCount;
}