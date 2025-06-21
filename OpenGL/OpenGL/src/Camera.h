#pragma once

#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct CameraTransformMatrices
{
	glm::mat4 projection;
	glm::mat4 view;
};

class Camera
{
private:
	glm::vec3 m_CameraPosition;
	glm::vec3 m_CameraFirstPosition;
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

	int m_Width;
	int m_Height;
public:
	Camera(glm::vec3 pos, int width, int height);
	~Camera();

	void CameraInput(GLFWwindow* window, float deltaTime);
	void CameraReset();
	void UpdateCameraVectors();
	CameraTransformMatrices GetTransformMatrices(float near = 0.1f, float far = 100.0f);

	inline glm::mat4 GetLookAt() const { return glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraFront, m_CameraUp); }
	inline glm::vec3 GetPosition() const { return m_CameraPosition; }
	inline glm::vec3 GetFront() const { return m_CameraFront; }
};