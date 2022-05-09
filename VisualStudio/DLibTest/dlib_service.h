#ifndef DLIB_SERVICE
#define DLIB_SERVICE

#define DLIB_JPEG_SUPPORT

#include "face_recognition_metric.h"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>

using namespace dlib;
namespace fs = std::experimental::filesystem;

// Объявление класса обработки изображений с помощью библиотеки DLib.
class DLibService
{
public:
	/// <summary>
	/// Распознание лиц с получением результатов через структуру.
	/// </summary>
	/// <param name="detector"><see cref="frontal_face_detector"/>.</param>
	/// <param name="path">Путь до обрабатываемого файла.</param>
	/// <returns><see cref="FaceRecognitionMetric"/>.</returns>
	FaceRecognitionMetric recognize_faces(frontal_face_detector& detector, const fs::path& path);

	/// <summary>
	/// Распознание лиц с выводом результатов на экран.
	/// </summary>
	/// <param name="detector"><see cref="frontal_face_detector"/>.</param>
	/// <param name="win"><see cref="image_window"/>.</param>
	/// <param name="path">Путь до обрабатываемого файла.</param>
	void recognize_faces(frontal_face_detector& detector, image_window& win, const fs::path& path);

	/// <summary>
	/// Распознание лиц с выводом результатов на экран.
	/// </summary>
	/// <param name="detector"><see cref="frontal_face_detector"/>.</param>
	/// <param name="win"><see cref="image_window"/>.</param>
	/// <param name="image">Изображение.</param>
	void recognize_faces(frontal_face_detector& detector, image_window& win, array2d<unsigned char> image);
};

#endif
