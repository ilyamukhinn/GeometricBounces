#include "Circle.hpp"

#include <fstream>

void Circle::setSizeData(std::ifstream& fin) {
	float radius{ 0.0f };
	fin >> radius;
	this->m_radius = radius;
	this->m_circle.setRadius(radius);
}

void Circle::setRadius(float radius) {
	this->m_radius = radius;
	this->m_circle.setRadius(radius);
}

float Circle::getRadius() const {
	return this->m_radius;
}

std::size_t Circle::getPointCount() const {
	return this->m_circle.getPointCount();
}

sf::Vector2f Circle::getPoint(std::size_t index) const {
	return this->m_circle.getPoint(index);
}

sf::Shape& Circle::getEntity() {
	return this->m_circle;
}

sf::FloatRect Circle::getLocalBounds() {
	return this->m_circle.getLocalBounds();
}

sf::FloatRect Circle::getGlobalBounds() {
	return this->m_circle.getGlobalBounds();
}