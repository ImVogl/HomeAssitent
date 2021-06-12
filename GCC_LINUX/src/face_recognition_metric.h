#ifndef FACE_RECOGNITION_METRIC
#define FACE_RECOGNITION_METRIC

#include <string>
#include <opencv2/core/types.hpp>

struct FaceRecognitionMetric
{
	cv::Size image_size;

	long pixels;

	int processing_time;

	std::string file_name;

	unsigned short int number_of_faces_recognized;
};

#endif
