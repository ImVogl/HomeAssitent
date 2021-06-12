// #define SHOW_IMAGE
#include "file_service.h"
#include "dlib_service.h"
#include "face_recognition_metric.h"

#include <iostream>
#include <filesystem>

using namespace dlib;
using namespace std;
namespace fs = std::experimental::filesystem;

// http://dlib.net/webcam_face_pose_ex.cpp.html
int main(int argc, char** argv)
{
	if (argc < 3)
	{
		cout << "Give the path to directory with images." << endl;
		return 0;
	}

	frontal_face_detector detector = get_frontal_face_detector();
#ifdef SHOW_IMAGE
	image_window win;
#else
	const auto result_path = fs::path(argv[1]);
	const auto images_extension = argv[2];
#endif

	std::vector<FaceRecognitionMetric> results = {};
	auto dlib_service = new DLibService();
	auto file_service = new FileService();
	auto images = file_service->get_all_images(result_path, images_extension);
	for (std::vector<fs::path>::const_iterator iterator = images.begin(); iterator != images.end(); ++iterator)
	#ifdef SHOW_IMAGE
		dlib_service->recognize_faces(detector, win, *iterator);
	#else
		results.push_back(dlib_service->recognize_faces(detector, *iterator));
	#endif

	file_service->save_results_csv(results, result_path);
}
