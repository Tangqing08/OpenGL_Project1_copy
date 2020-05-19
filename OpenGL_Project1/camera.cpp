#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup) {
	Position = position;
	Worldup = worldup;
	Forward = glm::normalize(target - position);
	Right = glm::normalize(glm::cross(Worldup, Forward));
	Up = glm::normalize(glm::cross(Forward, Right));

}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup) {
	Position = position;
	Worldup = worldup;
	Pitch = pitch;
	Yaw = yaw;
	Front.z = -(cos(glm::radians(Pitch)) * cos(glm::radians(Yaw)));
	Front.y = (sin(glm::radians(Pitch)));
	Front.x = -(cos(glm::radians(Pitch)) * sin(glm::radians(Yaw)));

	
	Forward = glm::normalize(Front);
	Right = glm::normalize(glm::cross(Forward,Worldup));
	Up = glm::normalize(glm::cross(Right,Forward));

};


Camera::~Camera() {

}

glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(Position, Forward + Position, Worldup);
}

void Camera::UpdateCameraVector() {
	Front.z = -(cos(glm::radians(Pitch)) * cos(glm::radians(Yaw)));
	Front.y =  (sin(glm::radians(Pitch)));
	Front.x = -(cos(glm::radians(Pitch)) * sin(glm::radians(Yaw)));


	Forward = glm::normalize(Front);
	Right   = glm::normalize(glm::cross(Forward, Worldup));
	Up      = glm::normalize(glm::cross(Right, Forward));

}

void Camera::ProcessMouseMovement(float delX, float delY) {
	Pitch += delY;
	Yaw += delX;
	UpdateCameraVector();


};

void Camera::UpdateCameraPosition() {
	Position += Forward * speedZ * 0.001f;
}