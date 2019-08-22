// GazeCPlus.cpp : This file contains the 'main' function. Program execution begins and ends there.

//https://github.com/opencv/opencv/blob/3.4/data/haarcascades get cascades here

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include "opencv2/objdetect.hpp"



using namespace cv;
using namespace std;


void detectAndDisplay(Mat frame);

void calculateGaze(vector<Rect> eyes);
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;



int main()
{	//load haarcascades
	String face_cascade_name = "./haarcascade_frontalface_default.xml";
	String eyes_cascade_name = "./haarcascade_eye.xml";

	int input_stdin;
	cout << "IMAGE TO BE READ" << endl;
	cin >> input_stdin;

	if (!face_cascade.load(face_cascade_name))
	{
		cout << "--(!)Error loading face cascade\n";
		return -1;
	};
	if (!eyes_cascade.load(eyes_cascade_name))
	{
		cout << "--(!)Error loading eyes cascade\n";
		return -1;
	};

	vector<String> fn;
	glob("./data", fn, false);

	Mat eyes = imread(fn[input_stdin]);
	detectAndDisplay(eyes);
	waitKey(0);

	return 0;
}

void detectAndDisplay(Mat frame)
{
	Mat frame_gray;
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	//-- Detect faces
	std::vector<Rect> faces;
	face_cascade.detectMultiScale(frame_gray, faces);
	for (size_t i = 0; i < faces.size(); i++)
	{
		Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
		ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 0), 4);
		Mat faceROI = frame_gray(faces[i]);
		//-- In each face, detect eyes
		std::vector<Rect> eyes;
		eyes_cascade.detectMultiScale(faceROI, eyes);
		for (size_t j = 0; j < eyes.size(); j++)
		{
			Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
			int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
			circle(frame, eye_center, radius, Scalar(0, 255, 0), 4);
		}
	}
	imshow("Capture - Eyes detection", frame);
	waitKey(0);

	//calculateGaze(eyes);
}

void calculateGaze(vector<Rect> eyes)
{
	vector<Rect> temp = eyes;

}

