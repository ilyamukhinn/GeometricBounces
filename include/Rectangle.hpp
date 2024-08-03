#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Rectangle : public Entity, sf::RectangleShape {
private:
	sf::RectangleShape	m_recatngle;
	sf::Vector2f		m_size			{ sf::Vector2f(1.0f, 1.0f) };

public:
	Rectangle()		{};
	~Rectangle()	{};

	void			setSize(const sf::Vector2f& size);
	sf::Vector2f	getSize()							const;
	
	void			setSizeData(std::ifstream& fin);
	sf::FloatRect	getLocalBounds()					override;
	sf::FloatRect	getGlobalBounds()					override;
	std::size_t		getPointCount()						const override;
	sf::Vector2f	getPoint(std::size_t index)			const override;
	sf::Shape&		getEntity()							override;
};

#endif // RECTANGLE_H