#pragma once

#include "Entity.h"

class Fox : public Entity
{
private:
	float m_TextureID;
	std::vector<std::unique_ptr<Texture>> m_Textures;
public:
	Fox();

	void OnRender(glm::mat4 view, glm::mat4 projection, float deltaTime) override;
};