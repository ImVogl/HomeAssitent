#ifndef FILE_SERVICE
#define FILE_SERVICE

#include <filesystem>
#include "face_recognition_metric.h"

namespace fs = std::experimental::filesystem;

// Обработчик файлов.
class FileService
{
public:

	/// <summary>
	/// Получает коллекцию всех изображений.
	/// </summary>
	/// <param name="source_path">Папка с обрабатываемыми файлами.</param>
	/// <param name="extension">Расширение целевых файлов.</param>
	/// <returns><see cref="DataStorageViewModel"/> с инициализированными полями.</returns>
	std::vector<fs::path> get_all_images(fs::path source_path, std::string extension);

	/// <summary>
	/// Сохраняет результаты в .CSV файл.
	/// </summary>
	/// <param name="results">Коллекция <see cref="FaceRecognitionMetric"/>.</param>
	/// <param name="output_dir_path">Путь до выходной директории.</param>
	void save_results_csv(std::vector<FaceRecognitionMetric> results, const fs::path& output_dir_path);
};

#endif
