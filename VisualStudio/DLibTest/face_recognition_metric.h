#ifndef FACE_RECOGNITION_METRIC
#define FACE_RECOGNITION_METRIC

#include <string>
#include <opencv2/core/types.hpp>

/// <summary>
/// Структура с результатами обработки изображения.
/// </summary>
struct FaceRecognitionMetric
{
	// Размер изображения.
	cv::Size image_size;

	// Общее число пикселей в изображении.
	long pixels;

	// Время в секундах, которое было затрачено на обработку изображения.
	int processing_time;

	// Имя обработанного файла
	std::string file_name;

	// Число обнаруженных лиц.
	unsigned short int number_of_faces_recognized;
};

#endif
