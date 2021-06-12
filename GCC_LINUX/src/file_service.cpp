#include "file_service.h"
#include <fstream>
#include <boost/filesystem/path.hpp>

using namespace std;

/// <inheritdoc />
boost::filesystem::path FileService::get_default_dataset_path(std::string path_to_exe)
{
	return boost::filesystem::path(path_to_exe) /  boost::filesystem::path("../DataSet");
}

/// <inheritdoc />
std::string FileService::get_images_extension()
{
#ifdef DLIB_JPEG_SUPPORT
	return ".jpg";
#endif

	return ".bmp";
}

/// <inheritdoc />
std::vector<boost::filesystem::path> FileService::get_all_images(boost::filesystem::path source_path, std::string extension)
{
	if (!boost::filesystem::exists(source_path))
		throw;

	std::vector<boost::filesystem::path> images = {};
	for (const auto & entry : boost::filesystem::directory_iterator(source_path))
		if (entry.path().extension().string() == extension)
			images.push_back(entry.path());

	return images;
}


/// <inheritdoc />
void FileService::save_results_csv(std::vector<FaceRecognitionMetric> results, const boost::filesystem::path& output_dir_path)
{
	const std::string result_file = "Result.csv";
	const auto result_path = output_dir_path / boost::filesystem::path(result_file);
	if (exists(result_path))
		boost::filesystem::remove(result_path);

	std::ofstream output_file;
	output_file.open(result_path.string(), ios::out);
	output_file << "File name,Image size WxH,Pixels,Number of recognized faces,Processing time seconds";
	for(std::vector<FaceRecognitionMetric>::const_iterator iterator = results.begin(); iterator != results.end(); ++iterator)
	{
		output_file << (*iterator).file_name << ",";
		output_file << (*iterator).image_size.width <<  "x" << (*iterator).image_size.height << ",";
		output_file << (*iterator).pixels << ",";
		output_file << (*iterator).number_of_faces_recognized << ",";
		output_file << (*iterator).processing_time << std::endl;
	}

	output_file.close();
}
