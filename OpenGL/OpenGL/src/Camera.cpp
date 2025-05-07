#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 up)
	: m_CameraPosition(pos), m_CameraUp(up), m_WorldUp(up), m_Yaw(0.0f), m_Pitch(0.0f), m_CameraSpeed(2.5f), m_MouseSensitivity(0.1f), m_Zoom(45.0f), m_FirstMouse(true), m_LastX(480.0f), m_LastY(270.0f)
{
	UpdateCameraVectors();
}

Camera::~Camera()
{
}

void Camera::CameraKeyboardInput(GLFWwindow* window, float deltaTime)
{
	float multiplier = 1.0f;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
		multiplier = 3.0f;
	float velocity = m_CameraSpeed * deltaTime * multiplier;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_CameraPosition += velocity * m_CameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_CameraPosition -= velocity * m_CameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_CameraPosition -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * velocity;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_CameraPosition += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * velocity;
}

void Camera::CameraMouseInput(float xpos, float ypos)
{
	if (m_FirstMouse)
	{
		m_LastX = xpos;
		m_LastY = ypos;
		m_FirstMouse = false;
	}

	float xoffset = (xpos - m_LastX) * m_MouseSensitivity;
	float yoffset = (m_LastY - ypos) * m_MouseSensitivity; // reversed since y-coordinates go from bottom to top

	m_LastX = xpos;
	m_LastY = ypos;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	// Constraints
	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;

	UpdateCameraVectors();
}

void Camera::CameraMouseScroll(float yoffset)
{
	m_Zoom -= (float)yoffset;
	if (m_Zoom < 1.0f)
		m_Zoom = 1.0f;
	if (m_Zoom > 45.0f)
		m_Zoom = 45.0f;
}