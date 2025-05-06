#pragma once

#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

class Camera
{
private:
	glm::vec3 m_CameraPosition;
	glm::vec3 m_CameraUp;
	glm::vec3 m_CameraFront;
	glm::vec3 m_CameraRight;
	glm::vec3 m_WorldUp;

	float m_Yaw;
	float m_Pitch;

	float m_CameraSpeed;
	float m_MouseSensitivity;
	float m_Zoom;
	bool m_FirstMouse;
	float m_LastX;
	float m_LastY;
public:
	Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
	~Camera();

	void CameraKeyboardInput(GLFWwindow* window, float deltaTime);
	void CameraMouseInput(float xpos, float ypos);
	void CameraMouseScroll(float yoffset);

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