#include "test_service.h"
#include "dlib/opencv.h"

#include "dlib_service.h"
#include "file_service.h"
#include "face_recognition_metric.h"

#include <opencv2/opencv.hpp>

#include <climits>
#include <iostream>

using namespace dlib;

// Реализация для случая подготовленных изображений.
void run_test_for_prepared_images::run()
{
	using namespace std;

	if (_argc < 3)
	{
		std::cout << "Give the path to directory with images." << std::endl;
		return;
	}

	auto detector = get_frontal_face_detector();
#ifdef SHOW_IMAGE
	image_window win;
#endif

	std::vector<FaceRecognitionMetric> results = {};
	auto dlib_service = new DLibService();
	auto file_service = new FileService();

	const auto result_path = fs::path(_argv[1]);
	const auto images_extension = _argv[2];
	auto images = file_service->get_all_images(result_path, images_extension);
	for (std::vector<fs::path>::const_iterator iterator = images.begin(); iterator != images.end(); ++iterator)
#ifdef SHOW_IMAGE
		dlib_service->recognize_faces(detector, win, *iterator);
#else
		results.push_back(dlib_service->recognize_faces(detector, *iterator));
#endif

	file_service->save_results_csv(results, result_path);
}

// Реализация для случая работающей камеры.
void run_test_for_ip_camera::run()
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
	auto dlib_service = new DLibService();
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
		dlib_service->recognize_faces(detector, win, std::move(dlib_frame));
	}
}
