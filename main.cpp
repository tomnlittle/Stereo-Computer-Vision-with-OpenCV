#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

void displayImageFromFile(int argc, char **argv);
void openCamera();

int main(int argc, char** argv )
{
   
     //initialize and allocate memory to load the video stream from camera 
    cv::VideoCapture camera0(0);
    cv::VideoCapture camera1(1);

    if( !camera0.isOpened() ) return 1;
    if( !camera1.isOpened() ) return 1;

    while(true) {
        //grab and retrieve each frames of the video sequentially 
        cv::Mat3b frame0;
        camera0 >> frame0;
        cv::Mat3b frame1;
        camera1 >> frame1;
       
        cv::imshow("Video0", frame0);
        cv::imshow("Video1", frame1);

        //wait for 40 milliseconds
        int c = cvWaitKey(10);

        //exit the loop if user press "Esc" key  (ASCII value of "Esc" is 27) 
        if(27 == char(c)) break;
    }
    waitKey(0);

    

    return 0;
}

void openCamera(){
    VideoCapture cap;
    Size size(1024,576);//the dst image size,e.g.100x100
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(0))
        return;
    for(;;)
    {
          Mat frame;
          cap >> frame;
          if( frame.empty() ) break; // end of video stream
          resize(frame, frame,size);//resize image

          imshow("Webcam", frame);
          if( waitKey(1) == 27 ) break; // stop capturing by pressing ESC 
    }
    // the camera will be closed automatically upon exit
    //cap.close();
}


//takes input from console to open a file
void displayImageFromFile(int argc, char **argv){

    if ( argc != 2 ) {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return;
    }

    Size size(100,100);//the dst image size,e.g.100x100
    Mat image;
    image = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE);

    if ( !image.data )
    {
        printf("No image data \n");
        return;
    }
    resize(image, image,size);//resize image
    namedWindow("Display Image", WINDOW_NORMAL );
    imshow("Display Image", image);
}