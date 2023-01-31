#include "recognize_service.h"
#include "dlib/opencv.h"

#include "dlib_service.h"
#include "face_recognition_metric.h"

#include <opencv2/opencv.hpp>

#include <climits>
#include <iostream>

using namespace dlib;

// Реализация для случая работающей камеры.
void recognize_service_for_ip_camera_images::run()
{
	const auto rtsp_url = "rtsp://" + _camera_socket + "/user=admin_password=tlJwpbo6_channel=0_stream=0.sdp?real_stream";
	cv::VideoCapture capture(rtsp_url);
	if (!capture.isOpened())
	{
		std::cout << "Can't open video capturing." << std::endl;
		return;
	}

	image_window win;
	cv::Mat frame;
	cv::Mat normalize_image;
	auto dlib_service = DLibService(false);
	auto detector = get_frontal_face_detector();
	while (!win.is_closed())
	{
		if (!capture.read(frame))
		{
			std::cout << "Can't read image frame." << std::endl;
			return;
		}

		cv::normalize(frame, normalize_image, 0, UCHAR_MAX, cv::NORM_MINMAX);
		auto converted_image = dlib::cv_image<bgr_pixel>(normalize_image);
		array2d<unsigned char> dlib_frame;
		assign_image(dlib_frame, converted_image);
		dlib_service.recognize_faces(detector, win, std::move(dlib_frame));
	}
}
