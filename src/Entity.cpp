#include "Entity.hpp"

void Entity::setName(const std::string& name) {
	this->m_name = name;
}

void Entity::setId(std::uint8_t id) {
	this->m_id = id;
}

void Entity::setEntityType(const EntityType& entityType) {
	this->m_entityType = entityType;
}

void Entity::setVelocity(const sf::Vector2i& velocity) {
	this->m_velocity = velocity;
}

void Entity::setDrawEntity(bool drawEntity) {
	this->m_drawEntity = drawEntity;
}

void Entity::setPosition(const sf::Vector2f& position) {
	this->getEntity().setPosition(position);
	this->m_position = position;
}

void Entity::setColor(const float* color) {
	this->getEntity().setFillColor(sf::Color(color[0], color[1], color[2]));
	memcpy_s(this->m_color, 3 * sizeof(float), color, 3 * sizeof(float));
}

void Entity::setText(const sf::Text& text) {
	this->m_text = text;
}

void Entity::setTextString(const std::string& str) {
	this->m_text.setString(str);
}

void Entity::setTextCharacterSize(unsigned int size) {
	this->m_text.setCharacterSize(size);
}

void Entity::setTextPosition(const sf::Vector2f& position) {
	this->m_text.setPosition(position);
}

void Entity::setDisplayText(const char* displayText) {
	strcpy_s(this->m_displayText, displayText);
}

EntityType Entity::getEntityType() const {
	return this->m_entityType;
}

std::string Entity::getName() const {
	return this->m_name;
}

std::uint8_t Entity::getId() const {
	return this->m_id;
}

sf::Vector2i Entity::getVelocity() const {
	return this->m_velocity;
}

bool Entity::getDrawEntity() const {
	return this->m_drawEntity;
}

sf::Vector2f Entity::getPosition() const {
	return this->m_position;
}

const float* Entity::getColor() const {
	return this->m_color;
}

sf::Text Entity::getText() const {
	return this->m_text;
}

char* Entity::getDisplayText() {
	return this->m_displayText;
}