// #define SHOW_IMAGE
#include "file_service.h"
#include "dlib_service.h"
#include "face_recognition_metric.h"

#include <boost/filesystem.hpp>
#include <iostream>
#include <filesystem>

using namespace dlib;
using namespace std;

// http://dlib.net/webcam_face_pose_ex.cpp.html
int main(int argc, char** argv)
{
	auto dlib_service = new DLibService();
	auto file_service = new FileService();

	boost::filesystem::path result_path;
	std::string images_extension;

	if (argc < 3)
		images_extension = file_service->get_images_extension();
	else
		images_extension = argv[2];

	if (argc < 2)
		result_path = file_service->get_default_dataset_path(argv[0]);
	else
		result_path = boost::filesystem::path(argv[1]);

	frontal_face_detector detector = get_frontal_face_detector();
	std::vector<FaceRecognitionMetric> results = {};
	auto images = file_service->get_all_images(result_path, images_extension);
	for (std::vector<boost::filesystem::path>::const_iterator iterator = images.begin(); iterator != images.end(); ++iterator)
		results.push_back(dlib_service->recognize_faces(detector, *iterator));


	file_service->save_results_csv(results, result_path);
}
