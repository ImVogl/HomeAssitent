#include "recognize_service.h"

#include "dlib_service.h"
#include "file_service.h"
#include "face_recognition_metric.h"

#include <iostream>

using namespace dlib;
// Реализация для случая подготовленных изображений.
void recognize_service_for_prepared_images::run()
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
	auto dlib_service = DLibService(true);
	auto file_service = FileService();

	const auto result_path = fs::path(_argv[1]);
	const auto images_extension = _argv[2];
	auto images = file_service.get_all_images(result_path, images_extension);
	for (std::vector<fs::path>::const_iterator iterator = images.begin(); iterator != images.end(); ++iterator)
#ifdef SHOW_IMAGE
		dlib_service.recognize_faces(detector, win, *iterator);
#else
		results.push_back(dlib_service.recognize_faces(detector, *iterator));
#endif

	file_service.save_results_csv(results, result_path);
}
