#ifndef DLIB_SERVICE
#define DLIB_SERVICE

#define DLIB_JPEG_SUPPORT

#include "face_recognition_metric.h"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include "dlib/opencv.h"

using namespace dlib;
namespace fs = std::experimental::filesystem;

// Объявление класса обработки изображений с помощью библиотеки DLib.
class DLibService
{
private:

	/// <summary>
	/// Значение, показывающее, что нужно хранить полученные изображения.
	/// </summary>
	bool collect_faces_;

	/// <summary>
	/// Коллекция накопленных изображений.
	/// </summary>
	std::vector<cv::Mat> collected_faces_;

	/// <summary>
	/// Сохранение изображения по заданной границе.
	/// </summary>
	/// <param name="path">Путь до обрабатываемого изображения.</param>
	/// <param name="sub_image_borders">Область, которую предстоит вырезать.</param>
	/// <returns>Вырезанная область.</returns>
	void store_sub_image(const fs::path& path, rectangle sub_image_borders);

public:

	/// <summary>
	/// Конструктор.
	/// </summary>
	/// <param name="collect_faces">Значение, показывающее, что нужно хранить полученные изображения.</param>
	explicit DLibService(const bool collect_faces)
	{
		collect_faces_ = collect_faces;
		collected_faces_ = std::vector<cv::Mat>();
	};

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
