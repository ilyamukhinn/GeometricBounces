#ifndef ENGINE_H
#define ENGINE_H

#include "Entity.hpp"

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Engine {
	sf::RenderWindow	m_window;
	sf::Font			m_font;
	sf::Text			m_text;
	sf::Clock			m_deltaClock;

	std::vector<std::shared_ptr<Entity>>	m_entities;
	std::shared_ptr<Entity>					m_currentEntity;

	void	readConfig(std::string configPath);
	void	readWindowConfig(std::ifstream& fin);
	void	readTextConfig(std::ifstream& fin);
	void	readEntityConfig(std::ifstream& fin, const std::string& entityType);

	static const bool m_enableWindowVerticalSync = true;
public:
	Engine()	{};
	~Engine()	{};

	void	init(std::string config_path);
	bool	playGame();
	void	updateEntities();
	void	clearWindow();
	void	drawEntities();
	void	displayWindow();

	sf::RenderWindow& getWindow();
};

#endif // ENGINE_H