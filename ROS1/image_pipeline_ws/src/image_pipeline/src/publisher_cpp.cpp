#include <ros/ros.h>
#include <image_transport/image_transport.h>
/*OpenCV libs*/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
/* OpenCV Lib */
#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"
#include <cv_bridge/cv_bridge.h>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    cv::Mat img;
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("publisher", 100);
    
    int frequency;
    nh.getParam("/image_acquisition/frequency", frequency);
    ros::Rate loop_rate(frequency);

    cv::VideoCapture videoCapture(0);
    while (nh.ok()) {
        videoCapture >> img; 
        if (img.empty())
            break;
        sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", img).toImageMsg();

        pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
}