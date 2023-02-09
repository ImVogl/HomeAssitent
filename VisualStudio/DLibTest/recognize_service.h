#pragma once

// #define SHOW_IMAGE
#include <string>

// Класс запуска проверки службы.
class recognize_service
{
public:
	// Запуск теста
	void virtual run() {};

	// Деструктор
	virtual ~recognize_service() = default;
};

/// <summary>
/// Класс для работы с готовыми изображениями.
/// </summary>
class recognize_service_for_prepared_images : recognize_service
{
private:
	// Число аргументов
	int _argc;

	// Коллекция аргументов.
	char** _argv;
public:

	/// <summary>
	/// Конструктор.
	/// </summary>
	/// <param name="argc">Число аргументов.</param>
	/// <param name="argv">Аргументы.</param>
	explicit recognize_service_for_prepared_images(const int argc, char** argv)
	{
		_argc = argc;
		_argv = argv;
	}

	void run() override;
};

/// <summary>
/// Конструктор.
/// </summary>
class recognize_service_for_ip_camera_images : recognize_service
{
private:

	// Число кадров, после которого производится сохранение обнаруженных лиц.
	const int frames_count_ = 30;

	// Сокет камеры.
	std::string camera_socket_;

public:
	/// <summary>
	/// Конструктор.
	/// </summary>
	/// <param name="camera_socket">Сокет камеры.</param>
	explicit recognize_service_for_ip_camera_images(std::string camera_socket)
	{
		camera_socket_ = camera_socket;
	}

	void run() override;
};
