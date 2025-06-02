#include "Camera.h"

Camera::Camera(glm::vec3 pos, int width, int height)
	: m_CameraPosition(pos), m_CameraFirstPosition(pos), m_Width(width), m_Height(height)
{
	UpdateCameraVectors();
}

Camera::~Camera()
{
}

void Camera::CameraInput(GLFWwindow* window, float deltaTime)
{
	// Control speed of camera
	float multiplier = 1.0f;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		multiplier = 3.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		multiplier = 0.2f;
	}

	float velocity = m_CameraSpeed * deltaTime * multiplier;

	// Control camera position
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_CameraPosition += velocity * m_CameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_CameraPosition -= velocity * m_CameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_CameraPosition -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * velocity;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_CameraPosition += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * velocity;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		m_CameraPosition += velocity * m_CameraUp;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		m_CameraPosition += velocity * -m_CameraUp;

	// Control camera mouse mode
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		m_MouseEnabled = true;
	else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		// Exit camera mode
		m_MouseEnabled = false;
		m_FirstMouse = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if (m_MouseEnabled)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Centre cursor to screen
		if (m_FirstMouse)
		{
			glfwSetCursorPos(window, (m_Width / 2), (m_Height / 2));
			m_FirstMouse = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		m_Yaw += m_MouseSensitivity * (float)(mouseX - (m_Width / 2)) / m_Width;
		m_Pitch += m_MouseSensitivity * (float)((m_Height / 2) - mouseY) / m_Height; // reversed since y-coordinates go from bottom to top

		// Constrain pitch so that the camera does not flip
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		UpdateCameraVectors();

		// Set mouse cursor to the centre of the screen
		glfwSetCursorPos(window, (m_Width / 2), (m_Height / 2));
	}
}

void Camera::CameraReset()
{
	m_Yaw = 0.0f;
	m_Pitch = 0.0f;
	m_CameraPosition = m_CameraFirstPosition;
	UpdateCameraVectors();
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 direction(
		cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)),
		sin(glm::radians(m_Pitch)),
		sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch))
	);

	m_CameraFront = glm::normalize(direction);
	m_CameraRight = glm::normalize(glm::cross(m_CameraFront, m_WorldUp));
	m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraFront));
}