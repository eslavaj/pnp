//============================================================================
// Name        : project_base.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include <boost/circular_buffer.hpp>

#include "calibration_matrix.hpp"
#include "KeypointProcessorGpu.hpp"


using namespace cv;
using namespace std;

int main(int argc, char** argv)
{


	int num_args = argc;
	if(num_args!=4)
	{
		cout<<"Incorrect argument number"<<endl<<endl;
		cout<<"Usage: "<<endl;
		cout<<"      ./pnp <Match selector type> <match_point_refine_strategy>"<<endl;
		cout<<"Detector types: FAST , ORB"<<endl;
		cout<<"Selector types: SEL_NN , SEL_KNN"<<endl;
		cout<<"Match point refining strategy: FUND , HOMOGR, AUTO, NONE"<<endl;
		return -1;
	}

	string detectorType = argv[1];
	string selectorType = argv[2];
	string mpointStrat = argv[3];


    VideoCapture cap;
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(1))
        return 0;
    /*
    for(;;)
    {
          Mat frame;
          cap >> frame;
          if( frame.empty() ) break; // end of video stream
          imshow("this is you, smile! :)", frame);
          if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC
    }
    */

    int dataBufferSize = 2;       // no. of images which are held in memory (ring buffer) at the same time

    boost::circular_buffer<DataFrame> dataBuffer(dataBufferSize);
    KeypointProcessorGpu pointProcGPU(dataBuffer, detectorType, selectorType, true);

    cv::Mat frame, frame_vis;
    while(cap.read(frame) && cv::waitKey(30) != 27)    // capture frame until ESC is pressed
    {
    	if( frame.empty() ) break; // end of video stream

    	namedWindow( "Video input", WINDOW_NORMAL | WINDOW_KEEPRATIO ); // Create a window for display.
    	imshow("Video input", frame);

        frame_vis = frame.clone();                     // refresh visualisation frame
        // MAIN ALGORITHM

    	pointProcGPU.extractKpointDescriptors(frame_vis);
    	pointProcGPU.matchKpoints(mpointStrat);




    }

    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}
