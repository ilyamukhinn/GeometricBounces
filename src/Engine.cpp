#include "Engine.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

void Engine::init(std::string configPath) {
	this->readConfig(configPath);

	this->m_currentEntity = this->m_entities[0];

	ImGui::SFML::Init(this->m_window);
	ImGui::GetStyle().ScaleAllSizes(1.0f);
}

bool Engine::playGame() {
	while (this->m_window.isOpen()) {
		sf::Event event;
		while (this->m_window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(this->m_window, event);

			if (event.type == sf::Event::Closed) {
				this->m_window.close();
			}
		}

		this->updateEntities();
		this->clearWindow();
		this->drawEntities();
		this->displayWindow();
	}

	return false;
}

void Engine::updateEntities() {
	// Settings

	ImGui::SFML::Update(this->m_window, this->m_deltaClock.restart());
	ImGui::Begin("Window title");
	if (ImGui::BeginCombo("Entities",
		this->m_currentEntity->getName().c_str())) {
		for (int i = 0; i < this->m_entities.size(); ++i) {
			const bool isSelected = (this->m_currentEntity->getId() == i);
			if (ImGui::Selectable(m_entities[i]->getName().c_str(), isSelected)) {
				this->m_currentEntity = this->m_entities[i];
			}

			if (isSelected) {
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	bool drawEntity = this->m_currentEntity->getDrawEntity();
	ImGui::Checkbox("Draw entity", &drawEntity);

	float radius;
	sf::Vector2f size;

	switch (this->m_currentEntity->getEntityType()) {
	case EntityType::CIRCLE:
		radius = std::static_pointer_cast<Circle>(this->m_currentEntity)->getRadius();
		ImGui::SliderFloat("Radius", &radius, 0.0f, 300.0f);
		break;
	case EntityType::RECTANGLE:
		size = std::static_pointer_cast<Rectangle>(this->m_currentEntity)->getSize();
		ImGui::SliderFloat("Side A", &size.x, 0.0f, 300.0f);
		ImGui::SliderFloat("Side B", &size.y, 0.0f, 300.0f);
		break;
	default:
		break;
	}

	sf::Vector2i velocity = this->m_currentEntity->getVelocity();
	ImGui::SliderInt("Velocity X", &velocity.x, -5, 5);
	ImGui::SliderInt("Velocity Y", &velocity.y, -5, 5);

	float color[3];
	memcpy_s(color, 3 * sizeof(float), 
		this->m_currentEntity->getColor(), 3 * sizeof(float));
	ImGui::ColorEdit3("Color", color);

	ImGui::InputText("Text", this->m_currentEntity->getDisplayText(), 255);
	if (ImGui::Button("Set Text")) {
		this->m_currentEntity->setTextString(
			this->m_currentEntity->getDisplayText());
	}

	ImGui::End();

	// Update Entities' parameters

	this->m_currentEntity->setDrawEntity(drawEntity);
	switch (this->m_currentEntity->getEntityType()) {
	case EntityType::CIRCLE:
		std::static_pointer_cast<Circle>(this->m_currentEntity)->setRadius(radius);
		break;
	case EntityType::RECTANGLE:
		std::static_pointer_cast<Rectangle>(this->m_currentEntity)->setSize(size);
		break;
	default:
		break;
	}
	this->m_currentEntity->setVelocity(velocity);
	this->m_currentEntity->setColor(color);

	for (auto& e : this->m_entities) {
		const auto globalBounds = e->getGlobalBounds();
		const auto localBounds = e->getLocalBounds();

		if (globalBounds.left <= 0 ||
			globalBounds.left + globalBounds.width >= this->m_window.getSize().x) {
			e->setVelocity({ -e->getVelocity().x, e->getVelocity().y });
		}

		if (globalBounds.top <= 0 ||
			globalBounds.top + globalBounds.height >= this->m_window.getSize().y) {
			e->setVelocity({ e->getVelocity().x, -e->getVelocity().y });
		}

		e->setPosition({ e->getPosition().x + e->getVelocity().x,
			e->getPosition().y + e->getVelocity().y });

		e->setTextPosition({ e->getPosition().x + localBounds.width / 2,
			e->getPosition().y + localBounds.height / 2 });
	}
}

void Engine::clearWindow() {
	this->m_window.clear();
}

void Engine::drawEntities() {
	for (const auto& e : this->m_entities) {
		if (e->getDrawEntity()) {
			this->m_window.draw(e->getEntity());
			this->m_window.draw(e->getText());
		}
	}

	ImGui::SFML::Render(this->m_window);
}

void Engine::displayWindow() {
	this->m_window.display();
}

sf::RenderWindow& Engine::getWindow() {
	return this->m_window;
}

void Engine::readConfig(std::string configPath) {
	std::ifstream fin(configPath);

	if (fin.is_open()) {
		std::string str;
		while (!fin.eof()) {
			fin >> str;
			if (str == "Window") {
				this->readWindowConfig(fin);
			} else if (str == "Font") {
				this->readTextConfig(fin);
			} else if (str == "Circle" || 
				str == "Rectangle") {
				this->readEntityConfig(fin, str);
			} else {
				std::cerr << "Unknown config option\n";
			}
		}
	}
}

void Engine::readWindowConfig(std::ifstream& fin) {
	int width, height;
	std::string title;
	fin >> width >> height >> title;
	
	this->m_window.create(sf::VideoMode(width, height), title);
	this->m_window.setVerticalSyncEnabled(this->m_enableWindowVerticalSync);
}

void Engine::readTextConfig(std::ifstream& fin) {
	std::string font_path;
	int size, RColor, GColor, BColor;
	fin >> font_path;

	if (!this->m_font.loadFromFile(font_path)) {
		std::cerr << "Could not load font\n";
	}

	fin >> size >> RColor >> GColor >> BColor;

	this->m_text.setFont(this->m_font);
	this->m_text.setCharacterSize(size);
	this->m_text.setFillColor(sf::Color(RColor, GColor, BColor));
}

void Engine::readEntityConfig(std::ifstream& fin, const std::string& entityType) {
	std::string name{ "" };
	int speedX{ 0 }, speedY{ 0 };
	float startPositionX{ 0.0f }, startPositionY{ 0.0f }, 
		RColor{ 0.0f }, GColor{ 0.0f }, BColor{ 0.0f };

	std::shared_ptr<Entity> entity;

	switch (entityTypeMap.at(entityType)) {
	case EntityType::CIRCLE:
		entity = std::make_shared<Circle>();
		break;
	case EntityType::RECTANGLE:
		entity = std::make_shared<Rectangle>();
		break;
	default:
		break;
	}

	fin >> name >> startPositionX >> startPositionY >> 
		speedX >> speedY >> RColor >> GColor >> BColor;

	entity->setName(name);
	entity->setId(this->m_entities.size());
	entity->setEntityType(entityTypeMap.at(entityType));
	entity->setPosition({ startPositionX, startPositionY });
	entity->setVelocity({ speedX, speedY });
	float color[3] = { RColor, GColor, BColor };
	entity->setColor(color);

	entity->setText(this->m_text);
	entity->setTextString(name);
	entity->setTextPosition({ startPositionX, startPositionY });
	entity->setDisplayText(name.c_str());

	entity->setSizeData(fin);

	this->m_entities.push_back(entity);
}