#ifndef FILE_SERVICE
#define FILE_SERVICE

#include <boost/filesystem.hpp>
#include "face_recognition_metric.h"

class FileService
{
public:
	boost::filesystem::path get_default_dataset_path(std::string path_to_exe);
	std::string get_images_extension();
	std::vector<boost::filesystem::path> get_all_images(boost::filesystem::path source_path, std::string extension);
	void save_results_csv(std::vector<FaceRecognitionMetric> results, const boost::filesystem::path& output_dir_path);
};

#endif
