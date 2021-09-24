#ifndef DLIB_SERVICE
#define DLIB_SERVICE

// #define DLIB_JPEG_SUPPORT

#include "face_recognition_metric.h"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <boost/filesystem.hpp>

using namespace dlib;

///<summary>
/// Face recognition main class
///</summary>
class DLibService
{
public:
	FaceRecognitionMetric recognize_faces(frontal_face_detector& detector, const boost::filesystem::path& path);
};

#endif
