#pragma once

class Scene
{
private:
protected:
	size_t windowBorderSize = 50;
	std::vector<std::shared_ptr<Object>> objects;

public:
	Scene() = default;
	virtual ~Scene() = default;
	
	virtual void render(sf::RenderWindow &window) = NULL;
	virtual void scroll(int value) = NULL;
};