#include "file_service.h"

#include <fstream>

using namespace std;
namespace fs = std::experimental::filesystem;

/// <inheritdoc />
std::vector<fs::path> FileService::get_all_images(fs::path source_path, std::string extension)
{
	if (!fs::exists(source_path))
		throw new fs::filesystem_error("Path \"" + source_path.string() + "\" does not exist!");

	std::vector<fs::path> images = {};
	for (const auto & entry : fs::directory_iterator(source_path))
		if (entry.path().extension() == extension)
			images.push_back(entry.path());

	return images;
}


/// <inheritdoc />
void FileService::save_results_csv(std::vector<FaceRecognitionMetric> results, const fs::path& output_dir_path)
{
	const char separator[] = ";";
	const std::string result_file = "Result.csv";
	const auto result_path = output_dir_path / fs::path(result_file);
	if (exists(result_path))
		fs::remove(result_path);

	std::ofstream output_file;
	output_file.open(result_path, ios::out);
	output_file << "File name;Image size WxH;Pixels;Number of recognized faces;Processing time, seconds\n";
	for(std::vector<FaceRecognitionMetric>::const_iterator iterator = results.begin(); iterator != results.end(); ++iterator)
	{
		auto result_row = (*iterator).file_name + separator;
		result_row += std::to_string((*iterator).image_size.width) + "x" + std::to_string((*iterator).image_size.height) + separator;
		result_row += std::to_string((*iterator).pixels) + separator;
		result_row += std::to_string((*iterator).number_of_faces_recognized) + separator;
		result_row += std::to_string((*iterator).processing_time) + "\n";
		output_file << result_row;
	}

	output_file.close();
}
