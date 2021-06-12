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
namespace fs = std::experimental::filesystem;

/// <inheritdoc />
FaceRecognitionMetric DLibService::recognize_faces(frontal_face_detector& detector, const fs::path& path)
{
	FaceRecognitionMetric result;
	std::cout << "Processing image " << path << endl;

	try
	{
		auto begin = std::chrono::steady_clock::now();
		result.file_name = path.filename().string();
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
		cout << "\nexception thrown!" << endl;
		cout << e.what() << endl;
		return {};
	}
}

/// <inheritdoc />
void DLibService::recognize_faces(frontal_face_detector& detector, image_window& win, const fs::path& path)
{
	try
	{
		auto begin = std::chrono::steady_clock::now();
		cout << "processing image " << path << endl;
		array2d<unsigned char> img;
		load_image(img, path.string());
		// Make the image bigger by a factor of two.  This is useful since
		// the face detector looks for faces that are about 80 by 80 pixels
		// or larger.  Therefore, if you want to find faces that are smaller
		// than that then you need to upsample the image as we do here by
		// calling pyramid_up().  So this will allow it to detect faces that
		// are at least 40 by 40 pixels in size.  We could call pyramid_up()
		// again to find even smaller faces, but note that every time we
		// upsample the image we make the detector run slower since it must
		// process a larger image.
		// pyramid_up(img);

		// Now tell the face detector to give us a list of bounding boxes
		// around all the faces it can find in the image.
		auto dets = detector(img);

		cout << "Number of faces detected: " << dets.size() << endl;
		// Now we show the image on the screen and the face detections as
		// red overlay boxes.
		win.clear_overlay();
		win.set_image(img);
		win.add_overlay(dets, rgb_pixel(255, 0, 0));

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::seconds> (end - begin).count() << " seconds" << endl;
	}
	catch (exception& e)
	{
		cout << "\nexception thrown!" << endl;
		cout << e.what() << endl;
	}
}
