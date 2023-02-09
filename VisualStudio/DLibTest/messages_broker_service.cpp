#include "messages_broker_service.h"

/// <inheritdoc />
void messages_broker_service::start_server()
{
	for (;;)
	{
		zmq::message_t request;

		// Receive a request from client
		server_socket_.recv(request, zmq::recv_flags::none);
		auto message = static_cast<json>(json::parse(request.str()));
		if (message["recipient"] == face_classify_service_)
			server_socket_.send(zmq::buffer(""), zmq::send_flags::dontwait);

		// Send the reply to the client
		server_socket_.send(zmq::buffer(""), zmq::send_flags::none);
	}
}

/// <inheritdoc />
void messages_broker_service::send_faces(std::vector<cv::Mat> faces)
{
	json data;

	data["sender"] = face_detection_service_;
	data["recipient"] = face_classify_service_;
	data["faces"] = faces;

	// send the request message
	client_socket_.send(zmq::buffer(data.dump()), zmq::send_flags::none);

	// wait for reply from server
	zmq::message_t reply {};
	client_socket_.recv(reply, zmq::recv_flags::none);
}
