#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/background_segm.hpp>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace cv;
using namespace std;
void numeroVotos(int numero)
{
       int rows = 600;
       int cols = 800;
       int rec = 150;
       int n = numero;
       stringstream s;
       s << n; 
       s << "-votos";
       Mat img(rows, cols, CV_8UC3, Scalar::all(0));
       circle(img, Point(cols / 2, rows / 2), 250, Scalar(255,0,0), 3);
       rectangle(img, Point(rec, rec), Point(cols - rec, rows - rec), CV_RGB(0,255,255));
       putText(img, s.str() , Point(180,320), FONT_HERSHEY_SCRIPT_COMPLEX, 3, CV_RGB(125,12,145), 2);
       imshow("Drawing", img);
       waitKey(0);
}

int main()
{
    CascadeClassifier detector;
    VideoCapture cap; 
    if(!detector.load("/usr/local/Cellar/opencv/2.4.9/share/OpenCV/haarcascades/Hand.Cascade.1.xml"))
		cout << "No se puede abrir clasificador." << endl;
    if(!cap.open("denis.avi"))
		cout << "No se puede acceder a la webcam." << endl;
	while(true)
	{	
		Mat dest, gray, imagen;
        cap >> imagen;
		cvtColor(imagen, gray, CV_BGR2GRAY);
		equalizeHist(gray, dest);
        vector<Rect> manos;
		detector.detectMultiScale(gray, manos, 1.2, 3, 0, Size(0,10));
        for(int i = 0; i < manos.size(); i++) 
        {
            Rect rc = manos[i];
			rectangle(imagen, Point(rc.x, rc.y), Point(rc.x + rc.width, rc.y + rc.height), CV_RGB(367,0,0), 2);
		}
        GaussianBlur(imagen,imagen, Size(9,9), 1.5,1.5);
		imshow("Deteccion de manos", imagen);	
		
		if(waitKey(1) >= 0) 
			{
				numeroVotos(manos.size());
			}
	}
}
