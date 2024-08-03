#include "Rectangle.hpp"

#include <fstream>

void Rectangle::setSizeData(std::ifstream& fin) {
	float side_a{ 0.0f }, side_b{ 0.0f };
	fin >> side_a >> side_b;
	this->m_size = sf::Vector2f(side_a, side_b);
	this->m_recatngle.setSize(sf::Vector2f(side_a, side_b));
}

void Rectangle::setSize(const sf::Vector2f& size) {
	this->m_size = size;
	this->m_recatngle.setSize(size);
}

sf::Vector2f Rectangle::getSize() const {
	return this->m_size;
}

std::size_t Rectangle::getPointCount() const {
	return this->m_recatngle.getPointCount();
}

sf::Vector2f Rectangle::getPoint(std::size_t index) const {
	return this->m_recatngle.getPoint(index);
}

sf::Shape& Rectangle::getEntity() {
	return this->m_recatngle;
}

sf::FloatRect Rectangle::getLocalBounds() {
	return this->m_recatngle.getLocalBounds();
}

sf::FloatRect Rectangle::getGlobalBounds() {
	return this->m_recatngle.getGlobalBounds();
}