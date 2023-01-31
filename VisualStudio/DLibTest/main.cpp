#include "recognize_service.h"

// http://dlib.net/webcam_face_pose_ex.cpp.html
int main(int argc, char** argv)
{
#ifdef SHOW_IMAGE
	auto live_service = new recognize_service_for_ip_camera_images("192.168.1.236:554");
	live_service->run();
#else
	auto prepared_service = new recognize_service_for_prepared_images(argc, argv);
	prepared_service->run();
#endif


	return 0;
}
