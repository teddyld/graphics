#pragma once

#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera
{
private:
	glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_CameraFront;
	glm::vec3 m_CameraRight;

	float m_Yaw = 0.0f;
	float m_Pitch = 0.0f;

	float m_CameraSpeed = 2.5f;
	float m_MouseSensitivity = 100.0f;
	float m_Zoom = 45.0f;
	bool m_FirstMouse = true;
	float m_MouseEnabled = false;

	float m_Width;
	float m_Height;
public:
	Camera(glm::vec3 pos, float width, float height);
	~Camera();

	void CameraInput(GLFWwindow* window, float deltaTime);

	void UpdateCameraVectors()
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		direction.y = sin(glm::radians(m_Pitch));
		direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

		m_CameraFront = glm::normalize(direction);
		m_CameraRight = glm::normalize(glm::cross(m_CameraFront, m_WorldUp));
		m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));
	}

	inline glm::mat4 GetLookAt() const { return glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp); }
	inline float GetZoom() const { return m_Zoom; }
};