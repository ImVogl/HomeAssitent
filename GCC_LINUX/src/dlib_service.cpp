#include "dlib_service.h"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <chrono>

using namespace dlib;
using namespace std;

/// <inheritdoc />
FaceRecognitionMetric DLibService::recognize_faces(frontal_face_detector& detector, const boost::filesystem::path& path)
{
	FaceRecognitionMetric result;
	std::cout << "Processing image " << path << endl;

	try
	{
		auto begin = std::chrono::steady_clock::now();
		result.file_name = path.string();
		array2d<unsigned char> image;
		load_image(image, path.string());
		result.image_size = cv::Size(image.nc(), image.nr());
		result.pixels = image.nc() * image.nr();
		auto dets = detector(image);
		result.number_of_faces_recognized = dets.size();
		auto end = std::chrono::steady_clock::now();
		result.processing_time = std::chrono::duration_cast<std::chrono::seconds> (end - begin).count();
		return result;
	}
	catch (exception& e)
	{
		cout << "\n" << "exception thrown!" << endl;
		cout << e.what() << endl;
		return {};
	}
}

