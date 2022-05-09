#include "test_service.h"

// http://dlib.net/webcam_face_pose_ex.cpp.html
int main(int argc, char** argv)
{
#ifdef SHOW_IMAGE
	auto live_service = new run_test_for_ip_camera("192.168.1.236:554");
	live_service->run();
#endif

	auto prepared_service = new run_test_for_prepared_images(argc, argv);
	prepared_service->run();

	return 0;
}
