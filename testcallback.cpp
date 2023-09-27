#include <cstdlib>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/core/types_c.h>
#include <opencv2/core/core_c.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/types_c.h>
#include <opencv2/imgproc.hpp>

#include "camera.h" //camera header file with class definition
//include all necessary libraries


struct CameraCallback:Camera::SceneCallback{
    void nextScene(const cv::Mat&mat){ //takes frame, does function
        //bool x = false; //only if using if condition
        std::vector<cv::Rect> xs; //declare a rectangular vector to store all found hits
    	cv::Mat gray; //declare matrix for grayscale image of frame
    	cv::Mat sized; //declare matrix for resized image of frame
    	cv::CascadeClassifier cascade; //declare cascade as a cascade classifier in preparation
    	cascade.load("cascade.xml");//input cascade file
    	resize(mat, sized,cv::Size(600,300),0,0,cv::INTER_LINEAR);//resize if needed
    		cv::cvtColor(sized,gray,CV_BGR2GRAY); //change to grayscale
    		xs.clear();
    		cascade.detectMultiScale(gray, xs, 1.1, 0, 0, cv::Size(50, 50), cv::Size(100,100));//use detectMultiScale and get rectangles
    
    		//if (xs.empty()){//maybe add if to only do following if rectangles exist
    	
    		for( std::vector<cv::Rect>::const_iterator r = xs.begin(); r != xs.end(); r++){
            		if((r->x + ((r->width)/2)) > 300){
            			std::cout << "The x is to the right. At " << (r->x + ((r->width)/2)) << "," << (r->y + ((r->height)/2)) << ". \n";
            			}
            		else if((r->x + ((r->width)/2)) < 300){
            			std::cout << "The x is to the left. At " << (r->x + ((r->width)/2)) << "," << (r->y + ((r->height)/2)) << ". \n";
            			}
            		//maybe have value indicating if left or right, then after the for loop, decide on direction to move
        	}//add rectangles to original image and notifies direction
        	
    }
};



int main(int argc, char** argv){
    int deviceID=0;
    int apiID=0;
    if (argc>1){
        deviceID = atoi(argv[1]);
    }
    if (argc>2){
        apiID = atoi(argv[2]);
    }
    printf("deviceID =%i API = %i\n", deviceID, apiID);
    Camera camera;
    CameraCallback cameraCallback;
    camera.registerSceneCallback(&cameraCallback);
    camera.start(deviceID, apiID);
    //camera.start("/dev/video0"); 
    do {
    }while(getchar());
    camera.stop();
}
