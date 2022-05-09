#pragma once

#define SHOW_IMAGE
#include <string>
#include <chrono>

// Тестовый класс запуска проверки службы.
class test_service
{
public:
	// Запуск теста
	void virtual run() {};

	// Деструктор
	virtual ~test_service() = default;
};

class run_test_for_prepared_images : test_service
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
	explicit run_test_for_prepared_images(const int argc, char** argv)
	{
		_argc = argc;
		_argv = argv;
	}

	void run() override;
};

class run_test_for_ip_camera : test_service
{
private:
	// Сокет камеры.
	std::string _camera_socket;

public:
	/// <summary>
	/// Конструктор.
	/// </summary>
	/// <param name="camera_socket">Сокет камеры.</param>
	explicit run_test_for_ip_camera(std::string camera_socket)
	{
		_camera_socket = camera_socket;
	}

	void run() override;
};
