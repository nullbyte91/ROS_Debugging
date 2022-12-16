#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.hpp"
#include "rclcpp/rclcpp.hpp"

/*OpenCV libs*/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/* OpenCV Lib */
#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options;
    rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("image_publisher", options);
    image_transport::ImageTransport it(node);
    image_transport::Publisher pub = it.advertise("publisher", 100);

    cv::VideoCapture videoCapture(0);

    rclcpp::WallRate loop_rate(10);
    cv::Mat img;
    while (rclcpp::ok()) {
        videoCapture >> img; 
        std_msgs::msg::Header hdr;
        sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(hdr, "bgr8", img).toImageMsg();
        pub.publish(msg);
        rclcpp::spin_some(node);
        loop_rate.sleep();
    }
}